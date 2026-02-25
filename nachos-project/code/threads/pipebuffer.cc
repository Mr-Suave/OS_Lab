#include "synch.h"
#include "pipebuffer.h"

PipeBuffer::PipeBuffer() {
    count = 0;
    readPos = 0;
    writePos = 0;
    mutex = new Semaphore("pipe_mutex", 1);
    full  = new Semaphore("pipe_full", 0);
    empty = new Semaphore("pipe_empty", PIPE_SIZE);
}

PipeBuffer::~PipeBuffer() {
    delete mutex;
    delete full;
    delete empty;
}

int PipeBuffer::Write(char* buf, int size) {
    int i;
    for (i = 0; i < size; i++) {
        empty->P();
        mutex->P();
        data[writePos] = buf[i];
        writePos = (writePos + 1) % PIPE_SIZE;
        count++;
        mutex->V();
        full->V();
    }
    return size;
}

int PipeBuffer::Read(char* buf, int size) {
    int i;
    for (i = 0; i < size; i++) {
        full->P();
        mutex->P();
        buf[i] = data[readPos];
        readPos = (readPos + 1) % PIPE_SIZE;
        count--;
        mutex->V();
        empty->V();
    }
    return size;
}