#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){
	char* message = "VSICKO E RUBY";
	mkfifo("pipe", 0666);
	
	int fd = open("pipe", O_WRONLY);
	while(true){
		write(fd, message, strlen(message));
	}
}
