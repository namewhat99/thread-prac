#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int semaphore = 1;
pthread_t thread_queue[6];
int front = 0 , back = 0;

void enqueue(pthread_t thread){
    thread_queue[back] = thread;
    back = (back + 1) % 6;
}

pthread_t dequeue(){
    void* thread = thread_queue[front];
    front = (front + 1) % 6;
    return thread;
}

void* thread_function(void* arg){

    int* thread_num = (int*)arg;
    
    pthread_t next_thread;

    // entry section
    if(semaphore == 1){ 
        semaphore = 0;
        printf("Thread %d is entering\n", *thread_num);
    }else{
        enqueue(pthread_self());
        printf("Thread %d is waiting\n", *thread_num);
        pthread_exit(NULL);
    }

    // critical section
    printf("Thread %d is working\n", *thread_num);
    printf("Thread %d is done\n", *thread_num);

    // exit section
    if(thread_queue[0] != NULL){ // 스레드 큐 가 비어있는 경우
        semaphore = 1;
        printf("Thread %d is exiting , no thread waiting\n", *thread_num);
        pthread_exit(NULL);
    }else{ // 스레드 큐에 작업이 있는 경우
        semaphore = 1;
        next_thread = dequeue();
        printf("Thread %d is exiting , thread %d is waiting\n", *thread_num, (int)next_thread);
        pthread_kill(next_thread, 0);
    }

}

int main(void){

    pthread_t thread[5];
    int i = 0;

    for(i = 0; i < 5; i++) pthread_create(&thread[i], NULL, thread_function, &i);
    for(int j = 0; j < 5; j++) pthread_join(thread[j], NULL);
    
    return 0;
}
