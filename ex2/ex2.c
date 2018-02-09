#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
int **alloc_2d(int rows, int cols)
{
    int ** rowsp = malloc(rows * sizeof(int *));
    for (int i = 0;i<rows;i++)
        rowsp[i] = malloc(cols * sizeof(int));
    return rowsp;
}
int main(int argc, char ** argv)
{
	int **my_array = alloc_2d(5, 10);

	// First array index is row, second is column:
	my_array[2][3] = 3490;

	// The same array access could be made with pointer arithmetic:
	*(*(my_array+2)+3) = 3490;

	// By the C spec, the array notation and pointer arithmetic notation
	// are 100% equivalent.
	
    const int LOOPS = argc > 1 ? atoi(argv[1]) : 100000;
    uint64_t ticks = rdtsc(), printfTicks, writeTicks;
    for (int i = 0;i < LOOPS;i++) 
	    printf("my_array[2][3] = %d\x0d", my_array[2][3]);
    printf("\nelapsed ticks printf %12ld\n", (printfTicks = rdtsc() - ticks));
    char buf[512];
    sprintf(buf, "my_array[2][3] = %d\x0d", my_array[2][3]);
    const size_t L = strlen(buf);
    ticks = rdtsc();    
    for (int i = 0;i < LOOPS;i++) 
	    write(1, buf, L); 
    printf("\033[2Kelapsed ticks write  %12ld\n", (writeTicks = rdtsc() - ticks)); // erase the write chars 
    printf("ratio %f\n", (double)writeTicks / printfTicks);
    exit(0);
}