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


//#include <signal.h>
//#include <sys/types.h>
//#include <time.h>
//#include <sys/ipc.h>
//#include <sys/wait.h>
//#include <sys/time.h>
//#include <sys/stat.h>

#define PAGE_TABLE_SHMKEY 123123

// #####
// ##### STRUCTURES #####
// #####
typedef struct {

} pageTable_t;

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

// #####
// ##### GLOBALS #####
// #####
unsigned int seconds;       // oss clock seconds
unsigned int nanoseconds;   // oss clock nanoseconds
int pageTableShmid;         // hold the shared mem segment id
pageTable_t *pageTablePtr;  // points to the data structure
key_t key;                  // for message queue
int msgid;                  // for message queue

// #####
// ##### FUNCTIONS #####
// #####
void sharedMemoryConfig() {

    //shared memory for page table
    pageTableShmid = shmget(PAGE_TABLE_SHMKEY, sizeof(pageTable_t), IPC_CREAT | 0777);
    if (pageTableShmid < 0) {
        perror("sysClock shmget error in master \n");
        exit(errno);
    }
    pageTablePtr = shmat(pageTableShmid, NULL, 0);
    if (pageTablePtr < 0) {
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
