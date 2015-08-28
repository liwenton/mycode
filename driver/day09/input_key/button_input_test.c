#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>

int main(int argc, char *argv[])
{
	int fd;
	struct input_event button;

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("open failed.\n");
		return -1;
	}

	while (1) {
		read(fd, &button, sizeof(button));
		printf("type = %#x, code = %#x, value = %#x\n",
				button.type, button.code,button.value);
	}

	close(fd);
	return 0;
}
