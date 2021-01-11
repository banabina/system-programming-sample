#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
	int shmid;
	void* shmaddr;
	int ret;

	//get shared memory id
	shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if (shmid == -1) {
		perror("shared memory access is failed\n");
		return -1;
	}

	//attach the shared memory
	shmaddr = shmat(shmid, (void *)0, 0);
	if (shmaddr == (char *)-1) {
		perror("attach failed\n");
		return -1;
	}

	//detach the shared memory
	ret = shmdt(shmaddr);
	if (ret == -1) {
		perror("detach failed\n");
		return -1;
	}

	//remove the shared memory
	ret = shmctl(shmid, IPC_RMID, 0);
	if (ret == -1) {
		perror("remove failed\n");
		return -1;
	}

	return 0;
}
