#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define seq_length 1000
#define DEFAULT_PENALTY 1

int main()
{
int i, j, k, l, m, seq1_length, seq2_length, temp_max_val, temp_seq_length, step_num=0, trackback;;
int penalty;
char seq1[seq_length];
char seq2[seq_length];
char temp_seq[seq_length];

//Get sequences and caalculate their lengths to form scoring matrix

scanf("%s", &seq1);
scanf("%s", &seq2);

seq1_length = strlen(seq1);
seq2_length = strlen(seq2);

//Make sure that sequence 1 string has the biggest sequence

if(seq2_length > seq1_length)
    {
    strcpy(temp_seq, seq2);
    strcpy(seq2, seq1);
    strcpy(seq1, temp_seq);
    temp_seq_length = seq2_length;
    seq2_length = seq1_length;
    seq1_length = temp_seq_length;
    }

//Create the scoring matrix for the two sequences

int** scoring_matrix = malloc((seq1_length+1)*sizeof(int*));
for(i=0; i<=seq1_length; i++)
    {
    scoring_matrix[i] = malloc((seq2_length+1)*sizeof(int));
    }

//Add values for the first row and collumn

for(i=0; i<=seq2_length; i++)
    {
    scoring_matrix[0][i] = -i;
    }

for(i=1; i<=seq1_length; i++)
    {
    scoring_matrix[i][0] = -i;
    }

//Calculate the scores

penalty = DEFAULT_PENALTY; 

for(i=0; i<seq1_length; i++)
    {
//x axis scorint matrix fill
        for(j=i; j<seq1_length; j++)
        {
        if(seq2[j] == seq1[i])
            {
            temp_max_val = -100;

            if(scoring_matrix[j][i+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[j][i+1];
                }

            if(scoring_matrix[j][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[j][i];
                }
            
            if(scoring_matrix[j+1][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[j+1][i];
                }
            scoring_matrix[j+1][i+1] = temp_max_val+1;
            }
        else
            {
            temp_max_val = -100;

            if(scoring_matrix[j][i+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[j][i+1];
                }

            if(scoring_matrix[j][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[j][i];
                }
            
            if(scoring_matrix[j+1][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[j+1][i];
                }
            scoring_matrix[j+1][i+1] = temp_max_val - penalty;
            }
        }

//y axis scoring matrix fill
    for(j=i; j<seq2_length; j++)
        {
        if(seq1[i] == seq2[j])
            {
            temp_max_val = -100;

            if(scoring_matrix[i+1][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i+1][j];
                }

            if(scoring_matrix[i][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            if(scoring_matrix[i][j+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }
            scoring_matrix[i+1][j+1] = temp_max_val+1;
            }
        else
            {
            temp_max_val = -100;

            if(scoring_matrix[i+1][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i+1][j];
                }

            if(scoring_matrix[i][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            if(scoring_matrix[i][j+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }
            scoring_matrix[i+1][j+1] = temp_max_val - penalty;
            }
        }
    }

for(i=0; i<=seq2_length; i++)
    {
    for(j=0; j<=seq1_length; j++)
        {
        printf("%d ", scoring_matrix[j][i]);
        }
    printf("\n");
    }

//Trackack algorithm

i = seq1_length-1;
j = seq2_length-1;

char output_matrix[seq1_length*seq2_length][2];

while( i+j+1>=0)  
    {
printf("i = %d\tj = %d\n\n", i, j );  
    if(scoring_matrix[i][j] >= scoring_matrix[i][j+1] && scoring_matrix[i][j] >= scoring_matrix[i+1][j] && i+1 > 0 && j+1 > 0)
        {
        trackback = 1;
        }
    
    else if(scoring_matrix[i+1][j] >= scoring_matrix[i][j] && scoring_matrix[i+1][j] >= scoring_matrix[i][j+1] && j+1 > 0)
        {
        trackback = 0;
        }

    else if(scoring_matrix[i][j+1] >= scoring_matrix[i][j] && scoring_matrix[i][j+1] >= scoring_matrix[i+1][j] && i+1 > 0)
        {
        trackback = 2;
        }

printf("trackback = %d\n\n", trackback);

    if(trackback == 0)
        {
        output_matrix[step_num][0] = '-';
        output_matrix[step_num][1] = seq2[j];
        j--;
        }
    else if(trackback == 1)
        {
        output_matrix[step_num][0] = seq1[i];
        output_matrix[step_num][1] = seq2[j];
        i--;
        j--;
        }   
    else if(trackback == 2)
        {
        output_matrix[step_num][0] = seq1[i];
        output_matrix[step_num][1] = '-';
        i--;
        } 
    
    step_num++;
    }

//Print output

for(i=step_num-1; i>=0; i--)
    {
    if(output_matrix[i][0] == 0)
        {
        output_matrix[i][0] = '-';
        }
    }

for(i=step_num-1; i>=0; i--)
    {
    if(output_matrix[i][1] == 0)
        {
        output_matrix[i][1] = '-';
        }
    }

for(i=step_num-1; i>=0; i--)
    {
    printf("%c ", output_matrix[i][0]);
    }

printf("\n");

for(i=step_num-1; i>=0; i--)
    {
    printf("%c ", output_matrix[i][1]);
    }

for(i=0; i<=seq1_length; i++)
    {
    free(scoring_matrix[i]);
    }
free(scoring_matrix);

}
