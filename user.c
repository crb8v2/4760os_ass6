//
// Created by crbaniak on 12/1/18.
//

#include "header.h"

int main() {

    sharedMemoryConfig();

    messageQueueConfig();

//  ***** writes to message queue
//    sprintf(message.mesg_text, "%d", getpid());
////  strcpy(message.mesg_text, "A message from the msgQ");
//    message.mesg_type = 1;
//    // msgsnd to send message queue
//    msgsnd(msgid, &message, sizeof(message), 0);



    // clean shared mem
    shmdt(sharedPtr);

    return 0;
}

