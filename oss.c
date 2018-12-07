//
// Created by crbaniak on 12/1/18.
//

#include "header.h"

void sigint(int);
void checkMsgQ();
void cleanup();
void createProcess();

int main() {

    sharedMemoryConfig();

    messageQueueConfig();

    signal(SIGINT, sigint);

    for(int ii = 0; ii < 5; ii++){
//    while(1){
        // fork processes
        int ii;
        for(ii = 0; ii < 2; ii++){
            createProcess();
        }
    }

    int ii;
    for(ii = 0; ii < 18; ii++){
        printf("%d ", mainPIDHolder[ii]);
    }

    sleep(5);

    for(int ii = 0; ii < 2; ii++){
        checkMsgQ();
    }

    cleanup();

    printf("\n were back\n");

    return 0;
}

// handles control c
void sigint(int a) {

    // write to log

    // cleanup
    cleanup();

    printf("^C caught\n");
    exit(0);
}


void checkMsgQ(){
    int pidPass;

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, IPC_NOWAIT);

    // display the message
    if(message.mesg_text[0] != '0') {
//        pidPass = atoi(message.mesg_text);
        printf("\n Data Received is : %s \n", message.mesg_text);
    }

    strcpy(message.mesg_text, "0");
}

void cleanup(){
    // kill open forks
    int ii;
    for(ii = 0; ii < 18; ii++){
        if(mainPIDHolder[ii] != 0){
            signal(SIGQUIT, SIG_IGN);
            kill(mainPIDHolder[ii], SIGQUIT);
        }
    }

    // clean shared memory
    shmdt(sharedShmptr);
    shmctl(sharedShmid, IPC_RMID, NULL);
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
}

void createProcess(){

    //max forks allowed
    while(numForksMade < 2){

        int positionPID = numForksMade;
        numForksMade++;

        // creates process in the pidHolder at
        if ((mainPIDHolder[positionPID] = fork()) == 0) {
            execl("./user", "user", NULL);
        }
        //nothing below this is access, until end of statement
    }
}
