#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main( int argc, char *argv[] )
{

	//Exit program if there is no input file

if( argc != 2 )
		{
        printf("Wrong input\n\n");
	    exit(1);
		}

	//Open input file and assign pointer to it 
	//Get the number of lines in the file

FILE *fp;
fp = fopen(argv[1], "r");

char input;

fscanf(fp, "%s", input);
printf("%s\n", input);

fclose(fp);
}