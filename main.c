#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int global_var = 10;
int accessAble = 1;

void *thread_function2(void *num) {

    while(1){
        if(accessAble == 0) {
            printf("스레드2 실행 불가능\n");
            continue;
        }
        else{
            accessAble = 0;
            printf("스레드2 실행 시작\n");
            global_var += 1;
            printf("스레드2 실행 결과: %d\n", global_var);
            accessAble = 1;
            pthread_exit(NULL);
        }
    }
}

void *thread_function1(void *num) {

    while(1){
        if(accessAble == 0) {
            printf("스레드1 실행 불가능\n");
            continue;
        }
        else{
            accessAble = 0;                 // entry section
            printf("스레드1 실행 시작\n");
            global_var *= 2;
            printf("스레드1 실행 결과: %d\n", global_var);
            accessAble = 1;                // exit section  
            pthread_exit(NULL);
        }
    }
}

int main(void){
    
    pthread_t thread1 , thread2;

    pthread_create(&thread1  , NULL , thread_function1 , NULL);
    pthread_create(&thread2  , NULL , thread_function2 , NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("스레드 실행 결과: %d\n", global_var);

    return 1;
}