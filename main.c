#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int global_var = 10;

//스레드끼리 공유하는 영역은 stack 을 제외한 영역

void *thread_function2(void *num) {
    printf("스레드2 진입\n");
    global_var += 1;
    printf("스레드2 실행 결과: %d\n", global_var);
    pthread_exit(NULL);
}

void *thread_function1(void *num) {
    printf("스레드1 진입\n");
    global_var *= 2;
    printf("스레드1 실행 결과: %d\n", global_var);
    pthread_exit(NULL);
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