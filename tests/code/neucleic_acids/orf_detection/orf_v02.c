#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int orf_detector(int orf_start, char* input_seq, int seq_length)
{
int i;
int orf_finish;	

for(i=orf_start+3; i<seq_length; i+=3)
	{
	if(i >= seq_length)
		{
		printf("No orf was found\n");
		exit(1);
		}
	else if(input_seq[i] == 'T' && input_seq[i+1] == 'G' && input_seq[i+2] == 'A')
		{
		orf_finish = i;
		break;
		}
	else if(input_seq[i] == 'T' && input_seq[i+1] == 'A' && input_seq[i+2] == 'G')
		{
		orf_finish = i;
		break;
		}
	else if(input_seq[i] == 'T' && input_seq[i+1] == 'A' && input_seq[i+2] == 'A')
		{
		orf_finish = i;
		break;
		}
	}

return(orf_finish);
}


int main( int argc, char *argv[] )
{
int i, j;
int seq_length;
int orf_start[10];
int orf_finish[10];
char input_seq[100];

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

fscanf(fp, "%s", &input_seq);

seq_length = strlen(input_seq);

int start = 0;
j = 0;

for(i=start; i<seq_length; i++)
	{
	if(input_seq[i] == 'A' && input_seq[i+1] == 'T' && input_seq[i+2] == 'G')
		{
		orf_start[j] = i;
		j++;
		}
	}

for(i = 0; i < j; i++)
	{
	orf_finish[i] = orf_detector(orf_start[i], &input_seq[0], seq_length);
	}

if(orf_finish[0] != 0)
	{
	for(i = 0; i < j; i++)
		{
		printf("\nORF detected, start codon from:%d stop codon from: %d\n\n", orf_start[i], orf_finish[i]);
		}
	}
else
	{
	printf("\nNo ORFs were detected\n\n");
	}

fclose(fp);
}