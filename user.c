//
// Created by crbaniak on 12/1/18.
//

#include "header.h"

void getUserVariables(int);
void writeMessageQ();

int main(int argc, char* argv[]) {

    //gets proc number from execl argv[1]
    char *p;
    int pageTableID = strtol(argv[1], &p, 10);

    // functions
    sharedMemoryConfig();
    messageQueueConfig();
    getUserVariables(pageTableID);
    writeMessageQ();


    // clean shared mem
    shmdt(sharedShmptr);

//    printf("\n process with PID: %d \n", getpid());

//    exit(0);
}

void getUserVariables(int pageTableID){

//    printf("\n page table/ process id is: %d \n", pageTableID);

    // init clock to random
    srand(getpid());

    // process address space called 0-32k
    sharedShmptr -> processAddressCalled[pageTableID] = (rand() % (31999-1)) + 1;

    int readOrWrite = (rand() % 9);

    if(readOrWrite <= 5){
        //read is 0
        sharedShmptr -> processReadOrWrite[pageTableID] = 0;
    } else {
        //write is 1
        sharedShmptr -> processReadOrWrite[pageTableID] = 1;
    }

    // increment call count
    sharedShmptr -> processCallCount[pageTableID]++;

    // check proc number passed correctly
    sharedShmptr -> checkProcNum[pageTableID] = pageTableID;
}

void writeMessageQ(){

    sprintf(message.mesg_text, "%d", getpid());
//  strcpy(message.mesg_text, "A message from the msgQ");
    message.mesg_type = 1;
//    // msgsnd to send message queue
    msgsnd(msgid, &message, sizeof(message), 0);

}

