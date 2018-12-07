#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

typedef struct _st_array{
    int array_len;
    unsigned char *body;
}ARRAY;

void print_array(ARRAY *array)
{
    int i;

    for(i=0; i<array->array_len; i++)
    {
        printf("%02x ", array->body[i]);
    }
    printf("\n");    
}

void make_rnd_array(ARRAY *array)
{
    time_t *tloc;
    int i;

    srand(time(NULL));
    
    for(i=0; i<array->array_len; i++)
    {
        array->body[i] = (rand() % 0xff) + 1;
    }

}

bool bubble_sort(ARRAY *array)
{
    int i;
    int j;
    unsigned char temp;
    
    for(j=0; j<array->array_len; j++)
    {
        for(i=array->array_len-1; i>0; i--)
        {    
            if(array->body[i-1] > array->body[i])
            {
                temp = array->body[i];
                array->body[i] = array->body[i-1];
                array->body[i-1] = temp;
            }
        }
    }
    
    return TRUE;
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        printf("Usage : bubble [array_len]");
    }
    /* code */
    int array_len;
    ARRAY array;
    
    array.array_len = atoi(argv[1]);
    array.body = (unsigned char *)calloc(array.array_len, sizeof(unsigned char));

    make_rnd_array(&array);
    print_array(&array);
    bubble_sort(&array);
    print_array(&array);
    
    return 0;
}
