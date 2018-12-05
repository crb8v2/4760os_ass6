//
// Created by crbaniak on 12/1/18.
//

#ifndef ASS6_HEADER_H
#define ASS6_HEADER_H

#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

//#include <sys/types.h>
//#include <time.h>
//#include <sys/ipc.h>
//#include <sys/wait.h>
//#include <sys/time.h>
//#include <sys/stat.h>

#define MAX_PROCS 18
#define SHMKEY 123123

// #####
// ##### STRUCTURES #####
// #####

// struct for time
typedef struct {
    unsigned int seconds;
    unsigned int nanoseconds;
} systemClock_t;

// frame table
typedef struct {
    int pageTablePages[256];
    int PIDS[256];
    int referenceFlag[156];
    int dirtyBit[156];
} frameTable_t;

// page table
typedef struct {
    int frameTableFrames[32];
} pageTable_t;

//for shared memory
typedef struct {
    int processAddressCalled[18];
    int processReadOrWrite[18];
    int processCallCount[18];
} shared_t;

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

// #####
// ##### VARIABLES #####
// #####

unsigned int seconds;           // oss clock seconds
unsigned int nanoseconds;       // oss clock nanoseconds

int pidHolder[18] = {};         // for checking program termination

frameTable_t frameTable;        // define frame table
pageTable_t pageTable[MAX_PROCS];   // define array of page tables

int sharedShmid; // shmem - holds the shared memory segment id
shared_t *sharedPtr; // shmem - points to the data structure

int msgid;                      // for message queue
key_t key;                      // for message queue


// #####
// ##### FUNCTIONS #####
// #####

void sharedMemoryConfig() {
    //shared mem for sysClock
    sharedShmid = shmget(SHMKEY, sizeof(systemClock_t), IPC_CREAT|0777);
    if(sharedShmid < 0)
    {
        perror("sysClock shmget error in master \n");
        exit(errno);
    }
    sharedPtr = shmat(sharedShmid, NULL, 0);
    if(sharedPtr < 0){
        perror("sysClock shmat error in oss\n");
        exit(errno);
    }
}

void messageQueueConfig(){
        // ftok to generate unique key
        key = ftok("progfile", 65);
        // msgget creates a message queue
        // and returns identifier
        msgid = msgget(key, 0666 | IPC_CREAT);
}

#endif //ASS6_HEADER_H









//// adjust request timer
//if ((nanoseconds + timeIncrement) > 999999999){
//rollover = (nanoseconds + timeIncrement) - 999999999;
//seconds += 1;
//nanoseconds = rollover;
//} else {
//nanoseconds += timeIncrement;
//}
