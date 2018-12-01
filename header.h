//
// Created by crbaniak on 12/1/18.
//

#ifndef ASS6_HEADER_H
#define ASS6_HEADER_H

#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>

//#include <signal.h>
//#include <sys/types.h>
//#include <unistd.h>
//#include <time.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>
//#include <sys/wait.h>
//#include <sys/time.h>
//#include <sys/stat.h>
//#include <string.h>

#define PAGE_TABLE_SHMKEY 123123

// ##### STRUCTURES #####

typedef struct {

} pageTable_t;

// ##### GLOBALS #####

int pageTableShmid; // hold the shared mem segment id
pageTable_t *pageTablePtr;  // points to the data structure

// ##### FUNCTIONS #####

void sharedMemoryConfig(){

    //shared memory for page table
    pageTableShmid = shmget(PAGE_TABLE_SHMKEY, sizeof(pageTable_t), IPC_CREAT|0777);
    if(pageTableShmid < 0)
    {
        perror("sysClock shmget error in master \n");
        exit(errno);
    }
    pageTablePtr = shmat(pageTableShmid, NULL, 0);
    if(pageTablePtr < 0){
        perror("sysClock shmat error in oss\n");
        exit(errno);
}

#endif //ASS6_HEADER_H
