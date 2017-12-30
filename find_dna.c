#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CODON "ATG"
#define END_CODON "TAA"
#define CODON_LEN 3

#define BEG_OF_NEW_SEQ "seq"
#define MIN_NUM_OF_SEQ 2
#define MAX_NUM_OF_SEQ 10
#define MAX_SEQ_NAME 30

int find_sub_str(FILE *fp, char *sub_str);	//finds sub string in file
void remove_enter(char *str);			//removes enter char ('\n')

int main(int argc, char **argv)
{
		int i = 0;
        int num_of_seq = 0;
        FILE *fp;
		int seq_num = 1;
		
		int seq_loc;
        int gene_beg_loc;
        int gene_end_loc;
		
		char seq_name[MAX_SEQ_NAME+1];	
		char end_of_seq_name;
		
        num_of_seq = atoi(argv[2]);

        if ((fp = fopen(argv[1],"r")) == NULL || num_of_seq < MIN_NUM_OF_SEQ || num_of_seq > MAX_NUM_OF_SEQ )
        {
                printf("ERROR: Invalid input\n");
                exit(1);
        }
		
	
		fgets(seq_name,MAX_SEQ_NAME,fp);	//first seq name
		remove_enter(seq_name);			
		seq_loc = ftell(fp);				//location of beginning of current sequence
		
		
		printf("Sequence\tGene_size\tStart\t\tStart_codon\tEnd\t\tEnd_codon\n");
		while(seq_num <= num_of_seq)
		{
			gene_beg_loc = find_sub_str(fp,START_CODON);
			
			if (gene_beg_loc == -1)
			{
				fgets(seq_name,MAX_SEQ_NAME,fp);
				remove_enter(seq_name);
				seq_loc = ftell(fp);
				seq_num++;
			}
			else
			{
				gene_beg_loc -= CODON_LEN;
				gene_end_loc = find_sub_str(fp,END_CODON)-CODON_LEN+1;
				
				printf("%s\t\t",seq_name);
				printf("%d\t\t",gene_end_loc-gene_beg_loc+CODON_LEN);
				printf("%d\t\t",gene_beg_loc-seq_loc);
				printf("%s\t\t",START_CODON);
				printf("%d\t\t",gene_end_loc-seq_loc);
				printf("%s\n",END_CODON);
			}
			
		}
		
		
		
        return 0;
}

int find_sub_str(FILE *fp, char *sub_str)
{
	char cur_codon[CODON_LEN+1];
		
	if (fgets(cur_codon,CODON_LEN+1,fp) == NULL)
	{
		return -1;
	}
	
	while (strcmp(cur_codon, sub_str) != 0)	//check if i am the beggining of seq
	{

		fseek(fp,-2,SEEK_CUR);			//get next	
		if (fgets(cur_codon,CODON_LEN+1,fp) == NULL)
		{
			exit(0);
		}
		
		if (strlen(cur_codon) < CODON_LEN)
		{
			return -1;
		}
	}
	
	return (int)ftell(fp);
}

void remove_enter(char *str)
{
	int i;
	
	if (!str)
		return;
	
	for (i=0; str[i]!='\n'; i++);
	
	str[i] = '\0';
}
	
	
