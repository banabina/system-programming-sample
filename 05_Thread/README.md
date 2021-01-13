## Process와 Thread의 비교
### Process
- 독자적으로 자원을 보유
  - 모든 프로세스는 자신만의 Address space를 가지고 있다
  
### Thread
- 실행을 위한 최소한의 자원만을 추가하고 서로 다른 스레드와 대다수의 자원을 공유한다.
  - 코드,데이터 영역은 스레드끼리 서로 공유하는 자원
  - program counter, 스택 공간 등은 스레드끼리 서로 독자적으로 가지고 있음
  
## 사용
pthread는 POSIX에서 표준으로 제안한 thread 라이브러리이다.
pthread.h를 include해주어야 한다.

### pthread_create
```
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
void *(*start_routine) (void *), void *arg);
```
- thread : 새로 생성된 thread의 id를 보유할 변수에 대한 포인터
- attr : pthread의 기능을 조정하는 데 사용할 수 있는 속성에 대한 포인터
- start_routine : 실행하고자 하는 함수의 함수 포인터
- arg : 실행하고자 하는 함수에게 넘길 매개변수

사용 예시
```
#include <stdio.h>
#include <pthread.h>

void *busy(void *ptr) {
  // ptr will point to "Hi"
  puts("Hello World");
  return NULL;
}
int main() {
  pthread_t id;
  pthread_create(&id, NULL, busy, "Hi");
  void *result;
  pthread_join(id, &result);
}
```
- void *(*start_routine) (void *), void *arg);에 맞게 스레드로 돌릴 함수를 정의했다.
- busy 함수에서 NULL을 반환했으므로 result의 값은 NULL이 된다
