#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void read_fasta(const char *input_file, char *input_seq)
	{
	char temp_input[256];
	int sequence_flag = 0;
	int i = 0;

	//Open file and assign pointer

	FILE *fp = fopen(input_file, "r");
	if(fp == NULL)
		{
		printf("Input file is empty.\n");
		exit(0);
		}

	//Get sequence from file, while avoiding 1st line in fasta file

	while(fgets(temp_input, sizeof(temp_input), fp))
		{
		if(temp_input[0] == '>')
			{
			sequence_flag = 1;
			continue;
			}
		
	//Copy input to input_seq in main function from the address passed in second arguement of read_fasta function

		if(sequence_flag)
			{
			memcpy(input_seq, temp_input, sizeof(temp_input));
			}
		}

	fclose(fp);
	}

int orf_start_detector(int frame, char* input_seq, int seq_length, int* orf_start)
{
int i;
int orf_count = 0;

for(i = frame; i < seq_length; i += 3)
	{
	if(input_seq[i] == 'A' && input_seq[i+1] == 'T' && input_seq[i+2] == 'G')
		{
		orf_start[orf_count] = i;
		orf_count++;
		}
	}
return(orf_count);
}

int orf_end_detector(int orf_start, char* input_seq, int seq_length)
{
int i;
int orf_finish;	

for(i=orf_start+3; i<seq_length; i+=3)
	{
	//Find stop codon and return its position
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

void remove_nested_orf()
{}

void print_results(char *input_seq, int *orf_start, int *orf_finish, int *orf_count, int frame)
{
int i;

for(i = 0; i < orf_count[0]; i++)
	{
	printf("\nORF detected, start codon from:%d stop codon from: %d, in frame +%d\n\n", orf_start[i]+1, orf_finish[i]+1, frame+1);
	}
	
}


int main( int argc, char *argv[] )
{
const char *input_file = argv[1];
int i, j;
int orf_count[3];
int orf_frame;
int seq_length;
int orf_start[3][100];								//In orf_start[0][x] contains the aa for reading frame +1, orf_start[1][x] for reading frame +2 and 
int orf_finish[3][100];								//orf_start[1][x] for reading frame +3. 
char input_seq[1000];

	//Exit program if there is no input file

if( argc != 2 )
		{
        printf("Wrong input\n\n");
	    exit(1);
		}

	//Get sequence and the number of neucleic acids from the file

read_fasta(input_file, &input_seq[0]);

seq_length = strlen(input_seq);

int start = 0;
orf_count[0] = 0;
orf_count[1] = 0;
orf_count[2] = 0;

//Find all the start codons and the frame they are in

for(i = 0; i < 3; i++)
	{
	orf_count[i] = orf_start_detector(i, &input_seq[0], seq_length, &orf_start[i][0]);
	}

for(j = 0; j < 3; j++)
	{	
	for(i = 0; i < orf_count[j]; i++)
		{
		orf_finish[j][i] = orf_end_detector(orf_start[j][i], &input_seq[0], seq_length);
		}
	}

//Print results of there are any
for(i = 0; i < 3; i++)
	{
	if(orf_finish[i][0] != 0)
		{
		print_results(&input_seq[0], &orf_start[i][0], &orf_finish[i][0], &orf_count[i], i);
		}
	}
}