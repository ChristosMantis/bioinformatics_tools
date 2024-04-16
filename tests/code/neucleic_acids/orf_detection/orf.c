#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <pthread.h>

int main( int argc, char *argv[] )
{
char INPUT_FILE;

	//Exit program if there is no input file

if( argc == 1 )
		{
        printf("Give the name of the input file\n");
        scanf("%c", &INPUT_FILE);
		}
else if (argc == 2)
    {
    INPUT_FILE = argv[1];
    }
else
    {
    printf("Wrong input\n\n");
	exit(1);
    }

	//Open input file and assign pointer to it 
	//Get the number of lines in the file

FILE *fp;
fp = fopen(INPUT_FILE, "r");


}