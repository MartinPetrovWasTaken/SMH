#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "cyclicBuf.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXO );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	int res;
	res = ftruncate( memFd, sizeof(struct cyclic_buf) );
	if( res == -1 )
	{
		perror("Can't truncate file");
		return res;
	}

	struct cyclic_buf* mem = mmap( NULL, sizeof(struct cyclic_buf), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	mem->pos %= 4096;
    int current_value = mem->array[mem->pos];

    while (true) {
        mem->pos++;
        mem->pos %= 4096;

        printf("Written: %d\n", current_value);
        mem->array[mem->pos] = current_value;
        current_value++;

        if (mem->pos % 1024 == 0) {
            sleep(1);
        }
	}

	return 0;
}
