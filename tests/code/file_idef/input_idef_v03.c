#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//The purpose of this code is to identify the input format of the file and the flags that are given as input while running the code  

int COUNT_FLAG = 0;
int VERBOSE_FLAG = 0;
int INPUT_FLAG = 0;

int main( int argc, char *argv[] )
{
int i, j, k, m, flag_count = 0;
char input_file_name[20];
/*
char temp[20];
for(i = 1; i < argc; i++)
    {
    //strcpy(temp, argv[i]);
	if ( strcmp(argv[i], "-") == 1 )
        {
        flag_count++;
        }
    }

//printf("%d\n", argc);
//printf("%s\n", argv[1]);
printf("%d\n", flag_count);
*/

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
    else if(strcmp(argv[i],"-i") == 0 && VERBOSE_FLAG == 0)
        {
        INPUT_FLAG =1;
        if(i < argc-1)
            {
            strcpy(input_file_name, argv[i+1]);
            i++;
            }
        }
/*
    else
        {
        continue;
       } 
*/
    }

if(COUNT_FLAG == 1 )
    {
    printf("We count %d flags as input\n", flag_count);
    }
    if(INPUT_FLAG == 1 )
    {
    printf("%s\n", input_file_name);
    }
}



