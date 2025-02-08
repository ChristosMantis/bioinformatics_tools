#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void read_fasta(const char*, char*);

int orf_start_detector(int, char*, int, int*);

int orf_end_detector(int, char*, int);

void remove_nested_orf(int, int*, int*, int*);

void print_results(char*, int*, int*, int*, int );


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

if( argc != 2 )										//Exit program if there is no input file	
		{
        printf("Wrong input\n");
	    exit(1);
		}

char temp[256];
int temp_length;

strcpy(temp, input_file);
temp_length = strlen(temp);
if(temp_length < 8)
	{
	printf("The file entered is not in fastsa format\n");
	exit(1);
	}

for(i = 0; i < temp_length-5; i++)
	{
	if(temp[i] == '.'&& temp[i+1] == 'f' && temp[i+2] == 'a' && temp[i+3] == 's' && temp[i+4] == 't' && temp[i+5] == 'a')
		{
		read_fasta(input_file, &input_seq[0]);												//Get sequence and the number of neucleic acids from the file
		break;
		}
	else if(i > temp_length-6)																//This line may cause problems in the future, you have been warned
		{
		printf("The file entered is not in fastsa format\n");
		exit(1);
		}
	}

seq_length = strlen(input_seq);

int start = 0;
orf_count[0] = 0;
orf_count[1] = 0;
orf_count[2] = 0;

for(i = 0; i < 3; i++)																
	{
	orf_count[i] = orf_start_detector(i, &input_seq[0], seq_length, &orf_start[i][0]);			//Find all the start codons and the frame they are in
	}

for(j = 0; j < 3; j++)
	{	
	for(i = 0; i < orf_count[j]; i++)
		{
		orf_finish[j][i] = orf_end_detector(orf_start[j][i], &input_seq[0], seq_length);
		}
	}
for(i = 0; i < 3; i++)
	{
	remove_nested_orf(i, &orf_start[i][0], &orf_finish[i][0], &orf_count[i]);
	}

for(i = 0; i < 3; i++)
	{
	if(orf_finish[i][0] != 0)
		{
		print_results(&input_seq[0], &orf_start[i][0], &orf_finish[i][0], &orf_count[i], i);	//Print results of there are any
		}
	}
}

void read_fasta(const char *input_file, char *input_seq)
	{
	char temp_input[256];
	int sequence_flag = 0;
	int i = 0;

	FILE *fp = fopen(input_file, "r");								//Open file and assign pointer
	if(fp == NULL)
		{
		printf("Input file is empty.\n");
		exit(0);
		}

	while(fgets(temp_input, sizeof(temp_input), fp))				//Get sequence from file, while avoiding 1st line in fasta file
		{
		if(temp_input[0] == '>')
			{
			sequence_flag = 1;
			continue;
			}

		if(sequence_flag)											//Copy input to input_seq in main function from the address passed in 
			{														//second arguement of read_fasta function
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
	if(input_seq[i] == 'A' && input_seq[i+1] == 'T' && input_seq[i+2] == 'G')		//Check all codons in this frame and find all ATG codons
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

for(i=orf_start+3; i<seq_length; i+=3)												//Find stop codon for given start codon and return its position
	{
	if(i >= seq_length)																//Check if codon is not at the end of the sequence
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

void remove_nested_orf(int frame, int *orf_start, int *orf_finish, int *orf_count)
{
int i, j;

for(i = 0; i < orf_count[frame]-1; i++)
	{
	if(orf_start[i+1] < orf_finish[i] && i < orf_count[frame]-1)		//Checks if x orf starts before x-1 orf finishes 
		{
		if(i = orf_count[frame]-1)										//If its the last orf, remove it and break
			{
			orf_start[i+1] = 0;
			orf_finish[i+1] = 0;
			orf_count[frame]--;
			break;
			}
		for(j = i; j < orf_count[frame]; j++)							//Move all following orfs one step behind
			{
			orf_start[j+1] = orf_start[j+2];
			orf_finish[j+1] = orf_finish[j+2];
			}
		i--;
		orf_count[frame]--;
		}
	}
}

void print_results(char *input_seq, int *orf_start, int *orf_finish, int *orf_count, int frame)
{
int i;

//Print all ORFs in the reading frame

for(i = 0; i < orf_count[0]; i++)
	{
	printf("\nORF detected, start codon from:%d stop codon from: %d, in frame +%d\n\n", orf_start[i]+1, orf_finish[i]+1, frame+1);
	}
	
}