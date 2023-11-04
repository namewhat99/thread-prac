# DAY 04

### 나만의 Sempaphore 를 직접 구현해보자 (코드를 직접 보지 않고 구현해야할 부분에 대해서 찾아보면서 구현)

#### 구현 목록
- 실행되는 스레드
- 다음에 실행될 스레드를 담는 큐 (FIFO 로 구현 예정)
  
- ##### wait()
  <span style="color:pink"> 현재 해당 자원이 사용중이면 대기, 사용중이지 않으면 실행한다.</span>
  - semaphore 변수가 1 이면 스레드 실행, 0 이면 현재 스레드를 thread_queue 에 넣는다.

- #### signal()

  <span style="color:pink"> 현재 스레드가 종료되었다는 신호를 다음 스레드에 보낸다. </span>
  
    ```c
    int pthread_kill(pthread_t thread, int sig);
    ```
    - pthread_t thread : 시그널을 받을 대상
    - int sig : 보낼 시그널의 번호, 미리 정의된 시그널 혹은 사용자 정의 시그널 모두 사용 가능
  
  - 현재 스레드가 종료되었다는 신호를 보낸다.

