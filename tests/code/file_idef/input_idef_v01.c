#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main( int argc, char *argv[] )
{
int i, j, k, m, flag_count = 0;

for(i = 1; i < argc; i++)
    {
	if ( strcmp( argv[i], "-") == 1 )
        {
        flag_count++;
        }
    }


printf("We count %d flags as input\n", flag_count);
}



