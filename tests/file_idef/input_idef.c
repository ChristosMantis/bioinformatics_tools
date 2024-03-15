#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <regex.h>

int flags(int)

int main( int argc, char *argv[] )
{
int i, j, k, m, flag_count;

flag_count = flags(argc, &argv);

printf("We count %d flags as input\n", flag_count);
}



int flahs(int argc, int *argv)
{
int i, flag_count = 0;

for(i = 0; i < argc; i++)
    {
    if((temp_value = regcomp(&argv[i], "-", 1)) == 1)
        {
        flag_count++;
        }
    }

return flag_count;
}
