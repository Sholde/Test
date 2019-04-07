#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char** argv) {
	if(argc != 2)
		return 0;
	
	char* path = argv[1];
	
	int fd;
	fd = open(path, O_RDONLY);
	
	int a = 0, b = 0;
	if(read(fd, &a, sizeof(int)) == -1)
		printf("error\n");
	read(fd, &b, sizeof(int));
	
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("a + b = %d\n", a+b);
	
	close(fd);
	return 0;
}
