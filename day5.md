# DAY 05

### DAY 04 에 이은 진행

```c
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

```

- 세마포어를 구현하던 중 문제가 발생했다. 
- 원래 의도는 만약 semaphore 가 0 이면 자기 자신의 pid 를 큐에 넣고 자기 자신을 종료시킨다. 그리고 현재 실행중인 스레드의 실행이 끝나면 종료된 스레드를 실행시키는 방식으로 구현해보려고 했는데 thread 를 지정해서 실행시키는 pthread 라이브러리는 존재하지 않고 운영체제가 임의로 실행시키는 방식이었다.

- 그래서 일단 내일 구현해 볼 방식은 스레드를 종료시키는 방식 pthread_exit 이 아니라 실행을 멈추고 대기시키는 방식으로 진행해보려 한다.
