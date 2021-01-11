## IPC
- 프로세스 사이의 데이터 통신을 IPC(Inter-Process Communication)라고 정의
  - 리눅스 커널은 다양한 IPC 메커니즘을 시스템 호출을 통해 제공
  - 프로세스는 IPC를 통해 다른 프로세스에게 데이터를 주고 받을 수 있음

## 대표적인 IPC
### Pipe
- 단방향 통신이며 부모 자식간 프로세스 통신에 쓰임
- 한쪽 프로세스가 읽기만 하도 다른쪽 프로세스는 쓰기만 하는 구조에서 사용하면 좋음

### Named Pipe
- Pipe에 이름이 있는 것을 Named Pipe라고 함
- 부모 자식 관계가 아닌 프로세스 사이에서 pipe를 이용해 통신하기 위해 만들어짐
- 기본적으로 단방향, Write Pipe, Read Pipe를 각각 만들면 양방향 통신이 가능

### Message Queue
- 메시지를 주고 받으며 프로세스 간 통신이 이루어짐
- 커널은 메시지를 저장할 장소인 메시지 큐 자료구조를 제공
- 한 프로세스에서 메시지를 생성하여 큐에 집어넣으면 다른 프로세스에서 이를 꺼내가는 구조

### Shared Memory
- 두 개 이상의 프로세스가 특정한 메모리 영역을 공유하는 것을 말함
- 공유메모리 영역에 대한 쓰기와 읽기 작업을 통해 데이터 통신이 가능

## Shared Memory
공유 메모리란 여러 프로세스가 공동으로 사용하는 메모리

### shmget: key 값을 통해 shared memory의 id를 얻어오는 함수
- 함수원형
  - int shmget(key_t key, size_t size, int shmflg)
- 인자
  - key_t key: shared memory 객체를 식별할 수 있는 고유번호
  - size_t size: 가져올 shared memory의 크기
  - int shmflg: shared memory를 얻어올 때 사용할 flag
    - IPC_CREAT: key에 해당하는 shared memory가 없다면 새로 생성
    - IPC_EXCL: key에 해당하는 shared memory가 있다면 실패 반환
    - msgflg은 IPC 옵션에 모드 값을 or 연산하여 사용하기도 함
      - 예시: IPC_CREAT | 0666
- 반환값
  - 성공하면 shmid 반환, 실패하면 -1 반환
  
### shmat: 프로세스의 메모리 공간에 공유 메모리를 붙이는 함수
- 함수원형
  - void *shmat(int shmid, const void *shmaddr, int shmflg)
- 인자
  - int shmid: 아직 메모리 공간에 붙여지지 않은 shared memory의 id
  - const void *shmaddr: 공유 메모리 주소. NULL((void *)0) 값인 경우 반환값으로 나오는 공유 메모리 주소
를 dynamic하게 설정하겠다는 뜻
  - int shmflg: 동작 옵션
    - SHM_RDONLY: 읽기 전용
    - SHM_RND: shmaddr가 NULL이 아닌 경우에 사용되며 shmaddr를 반올림하여 메모리 페이지 경계에 맞춤
- 반환값
  - 성공하면 공유 메모리 주소, 실패하면 -1 반환

### shmdt: 프로세스의 메모리 공간에서 공유 메모리를 떼는 함수
- 함수원형
  - int shmdt(const void *shmaddr)
- 인자
  - const void *shmaddr: 공유 메모리 주소
- 반환값
  - 성공하면 0, 실패하면 -1 반환
  
### shmctl: shared memory 정보를 확인/변경/제거하는 함수
- 함수 원형
  - int shmctl(int shmid, int cmd, struct shmid_ds *buf)
- 인자
  - int shmid: 정보를 확인/변경/제거하려는 shared memory의 id
  - int cmd: 제어 명령
    - IPC_RMID: shared memory 제거
    - IPC_SET: shared memory의 정보 변경
    - IPC_STAT: shared memory의 정보를 조회하여 buf에 저장
    - SHM_LOCK: shared memory 잠금
    - SHM_UNLOCK: shared memory 잠금 해제
  - struct shmid_ds *buf: 공유 메모리 정보를 가져올 때 사용하는 구조체. 정보를 가져올 필요가 없을 때는 0
을 사용
- 반환값
  - 성공하면 0, 실패하면 -1 반환
