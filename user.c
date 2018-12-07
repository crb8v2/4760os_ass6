//
// Created by crbaniak on 12/1/18.
//

#include "header.h"

int main() {

    sharedMemoryConfig();

    messageQueueConfig();

    // init clock to random
    time_t t;
    srand((unsigned) time(&t));
    int memoryRequest = (rand() % 31999) + 1;

    int readOrWrite = (rand() % 9);

    if(readOrWrite <= 6){
        //read
    } else {
        //write
    }





//  ***** writes to message queue
    sprintf(message.mesg_text, "%d", getpid());
////  strcpy(message.mesg_text, "A message from the msgQ");
    message.mesg_type = 1;
//    // msgsnd to send message queue
    msgsnd(msgid, &message, sizeof(message), 0);



    // clean shared mem
    shmdt(sharedShmptr);

    printf("\n process with PID: %d \n", getpid());

    exit(0);

}

