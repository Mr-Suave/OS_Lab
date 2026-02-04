// alarm.cc
//	Routines to use a hardware timer device to provide a
//	software alarm clock.  For now, we just provide time-slicing.
//
//	Not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "alarm.h"
#include "main.h"

//----------------------------------------------------------------------
// Alarm::Alarm
//      Initialize a software alarm clock.  Start up a timer device
//
//      "doRandom" -- if true, arrange for the hardware interrupts to
//		occur at random, instead of fixed, intervals.
//----------------------------------------------------------------------

Alarm::Alarm(bool doRandom) { 
    timer = new Timer(doRandom, this);
    sleepQueue = new SortedList<SleepingThread *>(CompareSleepingThreads); }

//----------------------------------------------------------------------
// Alarm::CallBack
//	Software interrupt handler for the timer device. The timer device is
//	set up to interrupt the CPU periodically (once every TimerTicks).
//	This routine is called each time there is a timer interrupt,
//	with interrupts disabled.
//
//	Note that instead of calling Yield() directly (which would
//	suspend the interrupt handler, not the interrupted thread
//	which is what we wanted to context switch), we set a flag
//	so that once the interrupt handler is done, it will appear as
//	if the interrupted thread called Yield at the point it is
//	was interrupted.
//
//	For now, just provide time-slicing.  Only need to time slice
//      if we're currently running something (in other words, not idle).
//----------------------------------------------------------------------



void Alarm::CallBack() {
    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    // Check if any threads in the sleepQueue need to be woken up
    if (!sleepQueue->IsEmpty()) {
        int currentTime = kernel->stats->totalTicks;
        
        // Peek at the front of the sorted list
        while (!sleepQueue->IsEmpty() && sleepQueue->Front()->wakeTime <= currentTime) {
            SleepingThread *st = sleepQueue->RemoveFront();
            
            // Put the thread back on the ready queue
            kernel->scheduler->ReadyToRun(st->thread);
            
            delete st; // Clean up the helper object
        }
    }

    if (status != IdleMode) {
        interrupt->YieldOnReturn();
    }
}

//compare sleeping threads helper function
int Alarm::CompareSleepingThreads(SleepingThread *a, SleepingThread *b) {
    if (a->wakeTime < b->wakeTime) return -1;
    if (a->wakeTime > b->wakeTime) return 1;
    return 0;
}


//alarm wait until function to handle the thread and enter the new entry into the sorted list
void Alarm::WaitUntil(int x) {

    if (x <=0) {return;}
    // Disable interrupts 
    IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);

    // 2. Calculate the absolute time when this thread should wake up
    // Stats->totalTicks  = current system time
    int wakeTime = kernel->stats->totalTicks + x;
    
    DEBUG(dbgThread, "Thread " << kernel->currentThread->getName() 
          << " sleeping until " << wakeTime);

    // 3. Create a record for this thread and put it in the sorted queue
    SleepingThread *st = new SleepingThread(kernel->currentThread, wakeTime);
    sleepQueue->Insert(st);

    // 4. Put the thread to sleep (this changes status to BLOCKED and yields CPU)
    // Thread::Sleep expects interrupts to be OFF
    kernel->currentThread->Sleep2(FALSE);

    // 5. Re-enable interrupts after waking up
    (void)kernel->interrupt->SetLevel(oldLevel);
}