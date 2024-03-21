#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define seq_length 1000

int main()
{
int i, j, k, l, m, seq1_length, seq2_length, temp_max_val, step_num=0;
char seq1[seq_length];
char seq2[seq_length];

//Get sequences and caalculate their lengths to form scoring matrix

scanf("%s", &seq1);
scanf("%s", &seq2);

seq1_length = strlen(seq1);
seq2_length = strlen(seq2);

//Create the scoring matrix for the two sequences

int** scoring_matrix = malloc((seq1_length+1)*sizeof(int*));
for(i=0; i<=seq1_length; i++)
    {
    scoring_matrix[i] = malloc((seq2_length+1)*sizeof(int));
    }

//Add values for the first row and collumn

for(i=0; i<=seq2_length; i++)
    {
    scoring_matrix[0][i] = 0;
    }

for(i=1; i<=seq1_length; i++)
    {
    scoring_matrix[i][0] = 0;
    }

//Calculate the scores

for(i=0; i<seq1_length; i++)
    {
//y axis fill
    for(j=i; j<seq2_length; j++)
        {
        if(seq1[i+1] != seq2[j+1])
            {
            temp_max_val = 0;

            if(scoring_matrix[i+1][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i+1][j];
                }

            else if(scoring_matrix[i][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            else if(scoring_matrix[i][j+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }
            scoring_matrix[i+1][j+1] = temp_max_val;
            }
        else
            {
            temp_max_val = 0;

            if(scoring_matrix[i+1][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i+1][j];
                }

            else if(scoring_matrix[i][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            else if(scoring_matrix[i][j+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }

            for(k=j; k<seq2_length; k++)
                {
                scoring_matrix[i+1][k+1] = temp_max_val+1;
                }
            j = seq2_length;
            }
        }
//x axis fill
        for(j=i; j<seq1_length; j++)
        {
        if(seq2[i+1] != seq1[j+1])
            {
            temp_max_val = 0;

            if(scoring_matrix[j][i+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i+1][j];
                }

            else if(scoring_matrix[j][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            else if(scoring_matrix[j+1][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }
            scoring_matrix[i+1][j+1] = temp_max_val;
            }
        else
            {
            temp_max_val = 0;

            if(scoring_matrix[j][i+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i+1][j];
                }

            else if(scoring_matrix[j][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            else if(scoring_matrix[j+1][i] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }

            for(k=j; k<seq1_length; k++)
                {
                scoring_matrix[k+1][i+1] = temp_max_val+1;
                }
            j = seq1_length;
            }
        }
    }
/*
for(i=0; i<seq1_length; i++)
    {
    for(j=0; j<seq2_length; j++)
        {
        if(seq1[i] == seq2[j])
            {   
            temp_max_val = scoring_matrix[i+1][j];

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
            temp_max_val = scoring_matrix[i+1][j];

            if(scoring_matrix[i][j] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j];
                }
            
            else if(scoring_matrix[i][j+1] > temp_max_val)
                {
                temp_max_val = scoring_matrix[i][j+1];
                }
            scoring_matrix[i+1][j+1] = temp_max_val;
            }
        }
    }
*/

for(i=0; i<seq1_length; i++)
    {
    printf(" %c", seq1[i]);
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

int trackback;

i = seq1_length-1;
j = seq2_length-1;

char output_matrix[seq1_length*seq2_length][2];

while( i+j>1)  
    {
printf("i = %d\tj = %d\n\n", i, j );  
    if(scoring_matrix[i][j] >= scoring_matrix[i][j+1] && scoring_matrix[i][j] >= scoring_matrix[i+1][j])
        {
        trackback = 1;
        output_matrix[step_num+1][0] = seq1[i];
        output_matrix[step_num+1][1] = seq2[j];
        }
    
    else if(scoring_matrix[i+1][j] >= scoring_matrix[i][j] && scoring_matrix[i+1][j] >= scoring_matrix[i][j+1])
        {
        trackback = 0;
        output_matrix[step_num+1][0] = '-';
        output_matrix[step_num+1][1] = seq2[j];
        }

    else if(scoring_matrix[i][j+1] >= scoring_matrix[i][j] && scoring_matrix[i][j] >= scoring_matrix[i+1][j])
        {
        trackback = 2;
        output_matrix[step_num+1][0] = seq1[i];
        output_matrix[step_num+1][1] = '-';
        }
printf("max value = %d\n", temp_max_val);
printf("trackback = %d\n\n", trackback);
    if(trackback == 0)
        {
        j--;
        }
    else if(trackback == 1)
        {
        i--;
        j--;
        }   
    else if(trackback == 2)
        {
        i--;
        } 
    
    step_num++;
    }
/*
while( i+j>0 )   
    {
printf("i = %d\tj = %d\n\n", i, j );
temp_max_val = scoring_matrix[i][j];

    if(scoring_matrix[i][j] >= temp_max_val)
        {
        temp_max_val = scoring_matrix[i+1][j+1];
        trackback = 1;
        output_matrix[step_num+1][0] = seq1[i];
        output_matrix[step_num+1][1] = seq2[j];
        }

    if(scoring_matrix[i+1][j] > temp_max_val)
        {
        temp_max_val = scoring_matrix[i+1][j];
        trackback = 0;
        output_matrix[step_num+1][0] = '-';
        output_matrix[step_num+1][1] = seq2[j];
        }

    if(scoring_matrix[i][j+1] > temp_max_val)
        {
        temp_max_val = scoring_matrix[i][j+1];
        trackback = 2;
        output_matrix[step_num+1][0] = seq1[i];
        output_matrix[step_num+1][1] = '-';
        }
printf("max value = %d\n", temp_max_val);
printf("trackback = %d\n\n", trackback);
    if(trackback == 0)
        {
        j--;
        }
    else if(trackback == 1)
        {
        i--;
        j--;
        }   
    else if(trackback == 2)
        {
        i--;
        } 
    
    step_num++;
    }
*/
//Print output

printf("\n\n");

for(i=step_num; i>=0; i--)
    {
    printf("%c", output_matrix[i][0]);
    }

printf("\n");

for(i=step_num; i>=0; i--)
    {
    printf("%c", output_matrix[i][1]);
    }
}