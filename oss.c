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
    signal(SIGINT, sigint);     // for ctrl-c termination
    signal(SIGSEGV, sigint);    // for seg faults


    // ##### MAIN LOOP #####

    for(int ii = 0; ii < 5; ii++){
//    while(1){
        // fork processes
        int ii;
        for(ii = 0; ii < 2; ii++){
            createProcess();
        }

        sleep(2);
        checkMsgQ();
    }









    //##### OUTPUTS FOR CHECKING #####

    int ii;
    for(ii = 0; ii < 18; ii++){
        printf("%d ", mainPIDHolder[ii]);
    }

//    sleep(2);



//    for(int ii = 0; ii < 2; ii++){
//        checkMsgQ();
//    }

    printf("\n ref: %d \n",sharedShmptr -> checkProcNum[0]);
    printf("\n addr: %d \n",sharedShmptr -> processAddressCalled[0]);
    printf("\n RW: %d \n",sharedShmptr -> processReadOrWrite[0]);
    printf("\n count: %d \n",sharedShmptr -> processCallCount[0]);


    printf("\n ref: %d \n",sharedShmptr -> checkProcNum[1]);
    printf("\n addr: %d \n",sharedShmptr -> processAddressCalled[1]);
    printf("\n RW: %d \n",sharedShmptr -> processReadOrWrite[1]);
    printf("\n count: %d \n",sharedShmptr -> processCallCount[1]);

    printf("\n addr: %d \n",sharedShmptr -> processAddressCalled[2]);
    printf("\n RW: %d \n",sharedShmptr -> processReadOrWrite[2]);
    printf("\n count: %d \n",sharedShmptr -> processCallCount[2]);



    cleanup();

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

        char stashbox[10];

        sprintf(stashbox, "%d", positionPID);

        // creates process in the pidHolder at
        if ((mainPIDHolder[positionPID] = fork()) == 0) {
            // argv{0] is page table number
            execl("./user", "user", stashbox, NULL);
        }
        //nothing below this is access, until end of statement
    }
}
