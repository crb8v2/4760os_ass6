//
// Created by crbaniak on 12/1/18.
//

#include "header.h"

void checkMsgQ();
void cleanup();

int main() {


    sharedMemoryConfig();

//    checkMsgQ();

//    while(1){
//
//    }


    cleanup();

    return 0;
}

void checkMsgQ(){
    int pidPass;

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, IPC_NOWAIT);

    // display the message
    if(message.mesg_text[0] != '0') {
        pidPass = atoi(message.mesg_text);
//        printf("Data Received is : %s \n", message.mesg_text);
    }

    strcpy(message.mesg_text, "0");
}

void cleanup(){
    // kill open forks
    int ii;
    for(ii = 0; ii < 18; ii++){
        if(pidHolder[ii] != 0){
            signal(SIGQUIT, SIG_IGN);
            kill(pidHolder[ii], SIGQUIT);
        }
    }

    // clean shared memory
    shmdt(sharedPtr);
    shmctl(sharedShmid, IPC_RMID, NULL);
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
}
