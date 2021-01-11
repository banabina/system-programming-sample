#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG_SIZE		80
#define PIPENAME		"./named_pipe_file"

int main(void)
{
	char msg[MSG_SIZE];
	int fd;
	int ret, i;

	//open the named pipe
	fd = open(PIPENAME, O_WRONLY);
	if (fd < 0) {
		printf("Open failed\n");
		return 0;
	}

	for (i = 0; i < 3; ++i) {
		sleep(1);
		snprintf(msg, MSG_SIZE, "Message[%d]", i);
		ret = write(fd, msg, MSG_SIZE);
		if (ret < 0) {
			perror("Write failed\n");
			return 0;
		}
	}
	return 0;
}
