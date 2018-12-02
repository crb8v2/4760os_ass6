//
// Created by crbaniak on 12/1/18.
//

#include "header.h"

int main() {

    sharedMemoryConfig();


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
