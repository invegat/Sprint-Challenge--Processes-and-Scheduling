#include <stdlib.h>
int *alloc_1d(int cols)
{
    return malloc(cols * sizeof(int));
}