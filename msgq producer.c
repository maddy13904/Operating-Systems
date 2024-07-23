#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 1024

// structure for message queue
struct msg_buffer {
    long msg_type;
    char msg_text[MAX];
} message;

int main() {
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    printf("Write Data : ");
    fgets(message.msg_text, MAX, stdin);

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
    printf("Data sent is : %s \n", message.msg_text);

    return 0;
}

