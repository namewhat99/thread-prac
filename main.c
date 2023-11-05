#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int num = 0;
pthread_cond_t my_condition_variable;
pthread_mutex_t mutex;
pthread_t thread_queue[6];

int front = 0 , back = 0;

void enqueue(pthread_t thread){
    thread_queue[back] = thread;
    back = (back + 1) % 6;
}

pthread_t dequeue(){
    pthread_t thread = thread_queue[front];
    front = (front + 1) % 6;
    return thread;
}

void* thread_function(void* arg){
    
    pthread_t* thread = (pthread_t*) arg;

    for(int i = 0; i < 10; i++){
        //pthread_mutex_lock(&mutex);
        //printf("Thread %lu: %d Before inc\n", (unsigned long)*thread, num);
        num++;
        printf("Thread %lu: %d After inc\n", (unsigned long)*thread, num);
        //pthread_mutex_unlock(&mutex);
    }
}
int main(void){

    pthread_t thread1 , thread2 , thread3;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&my_condition_variable, NULL);

    pthread_create(&thread1, NULL, thread_function, &thread1);
    pthread_create(&thread2, NULL, thread_function, &thread2);
    pthread_create(&thread3, NULL, thread_function, &thread3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}

// mutex 를 걸지 않을 경우,
// 스레드에서 실행이 되는 시간보다 콘솔에 출력하는 I/O 에 드는 시간이 더 오래 걸려서 1,2,3.. 순서대로 안나오나?
// 콘솔 출력은 I/O 작업이기 때문에 일반적으로 다른 계산 작업보다 더 많은 시간이 발생한다. 따라서 
// 스레드가 순환하면서 출력하는 동안 출력이 늦어질 수 있다.