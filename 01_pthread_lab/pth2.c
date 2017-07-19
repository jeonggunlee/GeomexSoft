#include <stdio.h>
#include <pthread.h>
#include <malloc.h>

void printMsg(char* msg) {
        int status = 0;
        printf("%s\n", msg);
        //pthread_exit((void *) 1);
        pthread_exit(&status);
}

int main(int argc, char** argv) {
        pthread_t thrdID;
        int* status = (int*)malloc(sizeof(int));
        int* temp;

        printf("creating a new thread\n");
        pthread_create(&thrdID, NULL, (void*)printMsg, (void *)argv[1]);
        printf("created thread %d\n", (int) thrdID);
        pthread_join(thrdID, (void **) &status);
        temp = (int *) status;
        printf("Thread %d exited with status %d\n", (int) thrdID, *temp);

        return 0;
}
