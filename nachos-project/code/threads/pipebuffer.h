#ifndef PIPEBUFFER_H
#define PIPEBUFFER_H

#define PIPE_SIZE 1024

class Semaphore;

class PipeBuffer {
public:
    char data[PIPE_SIZE];
    int count;
    int readPos;
    int writePos;
    Semaphore* mutex;
    Semaphore* full;
    Semaphore* empty;

    PipeBuffer();
    ~PipeBuffer();
    int Write(char* buf, int size);
    int Read(char* buf, int size);
};

#endif