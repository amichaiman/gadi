/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int is_in_array(int n, int *b, int size);       //returns 1 if n is in array b; 0 otherwise
int num_of_different(int *a, int *b, int size); //returns number of elements that are in array a but not in array b
int *array_sub(int *a, int *b, int size, int *plen);    //returns array with elements that are in a but aren't in b
void print_array(int *a, int size); //prints array
int num_of_common(int *a, int *b, int size);    //return numer of elements thar are both in a and in b
int *array_intersection(int *a,int *b, int size, int *plen);    //returns array with elements that are both in a and in b
void get_array(int *a, int size);

int main()
{
    int *a;
    int *b;
    int size;
    
    
    scanf("%d",&size);
    
    a = (int *) malloc (size*sizeof(int));  //a[size]
    b = (int *) malloc (size*sizeof(int));  //b[size]
    
    get_array(a,size);
    get_array(b,size);
        
    int *a_sub_b = NULL;
    int len_of_a_sub_b = 0;
    
    int *b_sub_a = NULL;
    int len_of_b_sub_a = 0;
    
    
    int *a_common_b = NULL;
    int len_of_a_common_b = 0;
    
    a_sub_b = array_sub(a,b,size,&len_of_a_sub_b);
    b_sub_a = array_sub(b,a,size,&len_of_b_sub_a);
    a_common_b = array_intersection(a,b,size,&len_of_a_common_b);
    
    
    printf("A-B = ");
    print_array(a_sub_b,len_of_a_sub_b);
    
    printf("B-A = ");
    print_array(b_sub_a,len_of_b_sub_a);
    
    printf("A&B = ");
    print_array(a_common_b,len_of_a_common_b);
    
    return 0;
}


int *array_sub(int *a, int *b, int size, int *plen)
{
    int *c;
    int c_size;
    int loc_in_c;
    int i;
    
    
    c_size = num_of_different(a,b,size);
    c = (int *) malloc (c_size*sizeof(int));    //c[num_of_different]
    
    for (i=0, loc_in_c=0; i<size; i++)
    {
        if (is_in_array(a[i],b,size) == 0)
        {
            c[loc_in_c] = a[i];
            loc_in_c++;
        }
    }
    
    *plen = c_size; //change len(which was defined in main) to array c's size
    return c;
}


int is_in_array(int n, int *b, int size)
{
    int i;
    
    for (i=0; i<size; i++)
    {
        if (b[i] == n)
        {
            return 1;
        }
    }
    
    return 0;
}


int num_of_different(int *a, int *b, int size)
{
    int counter = 0;
    int i;
    
    for (i=0; i<size; i++)
    {
        if (is_in_array(a[i],b,size) == 0)  // if(!bitui)  <--> if(bitui == 0)
        {
            counter++;
        }
    }
    
    return counter;
}

int num_of_common(int *a, int *b, int size)
{
    int i;
    int counter = 0;
    
    for (i=0; i<size; i++)
    {
        if (is_in_array(a[i],b,size) == 1)
        {
            counter++;
        }
    }
    
    return counter;
}
void print_array(int *a, int size)
{
    int i;
    
    for (i=0; i<size; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int *array_intersection(int *a,int *b, int size, int *plen)
{
    int i;
    int *a_common_b;
    int len_of_a_common_b;
    int spot;
    
    len_of_a_common_b = num_of_common(a,b,size);
    
    a_common_b = (int *) malloc (len_of_a_common_b*sizeof(int));
    
    for(i=0, spot=0; i<size; i++)
    {
        if(is_in_array(a[i],b,size) == 1)
        {
            a_common_b[spot]=a[i];
            spot++;
        }
    }
    
    *plen = len_of_a_common_b;
    return a_common_b;
}

void get_array(int *a, int size)
{
    int i;
    
    for (i=0; i<size; i++)
    {
        scanf("%d",a+i);
    }
}
