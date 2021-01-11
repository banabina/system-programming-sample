#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buffer[20];
	int i;
	int fd[2];

	if (pipe(fd) == -1) {
		perror("Pipe error\n");
		return -1;
	}
	
	pid_t pid;
	pid = fork();

	if (pid == -1) {
		perror("fork error\n");
		return -1;
	} else if (pid == 0) {
		write(fd[1], "Hello, pa!\n", 20);
		sleep(1);
	} else {
		read(fd[0], buffer, 20);
		printf("The pipe message from Child Process : %s\n", buffer);
	}
	return 0;
}
