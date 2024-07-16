#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main( int argc, char *argv[] )
{
int i, j, k, m, flag_count = 0;
int count_flag = 0;
int verbose_flag = 0;


for(i = 1; i < argc; i++)
    {
    switch (argv[i])
        {
        case '-help':
            printf("-help: Shows all modifiers\n
            -c: counts all the flags that were used as input in the program\n
            -v: Verboses the proceedure\n");
            break;
        case '-c':
            count_flag = 1;
            break;
        case '-v':
            verbose_flag = 1;
            break;
        default:
            printf("There was an aerror in the input\n");
            exit(0);
        }
    }
    
if(count_flag == 1 )
    {
    for(i = 1; i < argc; i++)
        {
	    if ( strcmp( argv[i], "-") == 1 )
            {
            flag_count++;
            }
        }
    printf("We count %d flags as input\n", flag_count);
    }

}



