#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd = open("pipe", O_RDONLY);
	char buff;

	while(true){
		while(read(fd, &buf, 1)){\
			write(STDOUT_FILENO, &buf, 1);
		}
	}
	return 0;
}
