#include <stdio.h>
#include <pthread.h>

void printMsg(void* arg_msg) {
        char *msg = (char *) arg_msg;
        printf("%s\n", msg);
}

int main(int argc, char** argv) {
        pthread_t thrdID;

        printf("creating a new thread\n");
        pthread_create(&thrdID, NULL, (void*)printMsg, (void *) argv[1]);
        printf("created thread %d\n", (int) thrdID);
        pthread_join(thrdID, NULL);

        return 0;
}
