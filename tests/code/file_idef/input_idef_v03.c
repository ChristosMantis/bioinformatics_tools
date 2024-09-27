#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int COUNT_FLAG = 0;
int VERBOSE_FLAG = 0;

int main( int argc, char *argv[] )
{
int i, j, k, m, flag_count = 0;

/*
for(i = 1; i < argc; i++)
    {
	if ( strcmp( argv[i], "-") == 1 )
        {
        flag_count++;
        }
    }
*/
//printf("%d\n", argc);
//printf("%d\n", flag_count);

for(i = 1; i < argc; i++)
    {
    if(strcmp(argv[i], "--help") == 0)
        {
        printf("--help: Shows all modifiers\n-c: counts all the flags that were used as input in the program\n-v: Verboses the proceedure\n");
        exit(0);
        }
    else if(strcmp(argv[i],"-c") == 0 && COUNT_FLAG == 0)
        {
        COUNT_FLAG = 1;
        flag_count++;
        }
    else if(strcmp(argv[i],"-v") == 0 && VERBOSE_FLAG == 0)
        {
        VERBOSE_FLAG = 1;
        flag_count++;
        }
    else
        {
        continue;
        }
    }

if(COUNT_FLAG == 1 )
    {
    printf("We count %d flags as input\n", flag_count);
    }

}



