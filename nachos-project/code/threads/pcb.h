#ifndef PCB_H
#define PCB_H
#include "pipebuffer.h"

#define MAX_FD 20
#define FD_FREE 0
#define FD_PIPE_READ 1
#define FD_PIPE_WRITE 2

struct FileDescriptor {
    int type;
    PipeBuffer* pipe;
};

class PCB {
   private:
    Semaphore *joinsem;
    Semaphore *exitsem;
    Semaphore *multex;

    int exitcode;
    int numwait;

    Thread *thread;
    char filename[128];

   public:
    int parentID;
    int processID;
    PCB();
    PCB(int id);
    ~PCB();

    int Exec(char *filename, int pid);
    int GetID();
    int GetNumWait();

    void JoinWait();
    void ExitWait();
    void JoinRelease();
    void ExitRelease();

    void IncNumWait();
    void DecNumWait();

    void SetExitCode(int ec);
    int GetExitCode();

    void SetFileName(char *fn);
    char *GetFileName();

    FileDescriptor fdTable[MAX_FD];
    void InitFdTable();
    int AllocFd(int type, PipeBuffer* pipe);
    
};

#endif
