#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function2(void *arg) {
    int *input = (int *)arg;
    int result2 = 0;

    for (int i = 1; i <= *input; i++) {
        printf("스레드 2: %d\n", i);
        result2 += i;
    }
    printf("스레드 2의 결과******: %d\n", result2);
    return (void *)(intptr_t)result2;
}

void *thread_function1(void *arg) {
    int *input = (int *)arg;
    int result1 = 0;

    for (int i = 1; i <= *input; i++) {
        printf("스레드 1: %d\n", i);
        result1 += i;
    }
    printf("스레드 1의 결과******: %d\n", result1);
    return (void *)(intptr_t)result1;
}

int main(void){
    
    pthread_t thread1 , thread2, thread3;

    int pid1 , pid2, pid3;
    int num1 = 10;
    int num2 = 10;
    void* result1 = 0, *result2 = 0, *result3 = 0;

    pthread_create(&thread1  , NULL , &thread_function1 , &num1);
    pthread_create(&thread2  , NULL , &thread_function2 , &num2);

    pthread_join(thread1, (void **)&result1);
    pthread_join(thread2, (void **)&result2);
    
    printf("스레드 1의 결과: %d\n", (int)(intptr_t)result1);
    printf("스레드 2의 결과: %d\n", (int)(intptr_t)result2);

    return 1;
}

