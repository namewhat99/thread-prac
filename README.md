# Thread-prac <br>

## 목표: 멀티스레드가 어떻게 동작하는건지 한번 직접 작성해보자

### 스레드를 직접 구현해보자 (연습)
- 1 도 모르지만 찾아보면서 할 예정
- 어떤 것 부터 해봐야할지 모르겠어서 일단 간단한 예제를 chat-gpt 한테 추천해달라 함

#### 1. Chat-gpt 추천 : 두개의 스레드를 이용해 간단한 덧셈 수행

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
```

- ~~위의 3개의 라이브러리를 사용했다. 답을 줬지만 바로 보기는 싫어서 직접 짜보면서 연습해볼 예정~~
- 먼저 예제를 보고 어떻게 구현된건지 한번 분석해보자

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

pthread_create(&thread1  , NULL , &thread_function , &num1);
```
- pthread_create 는 새로운 스레드 생성
- 첫번째 인자는  새로 생성된 스레드의 ID 로두번째는 스레드의 특성 , 세번째는 스레드가 실행할 함수를 가리키고 네번째는 실행 함수에 전달할 인자

```c
int pthread_join(pthread_t thread, void **status); // 원형

pthread_join(thread1, (void **)&result1);
```

- pthread_join 은 스레드가 완료될 때 까지 기다리고, 스레드의 결과를 가져온다
- 첫번째 인자는 기다리는 스레드의 ID , 두번째 인자는 스레드가 종료되면 결과를 저장할 변수를 전달한다.

```c
    pthread_create(&thread1  , NULL , &thread_function , &num1);
    pthread_create(&thread2  , NULL , &thread_function , &num2);
```

 - <span style="color:pink"> pthread_create 함수를 사용하여 스레드를 생성하면 각각의 스레드는 각자 자신의 작업을 병렬로 수행한다. 스레드 1은 스레드 2를 기다리지 않고, 스레드 2는 스레드 1을 기다리지 않는다.