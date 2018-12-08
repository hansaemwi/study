#include <stdio.h>

#define LITTLE 1
#define BIG 0

int main(void)
{
    int i       = 0x00000001;
    int endian  = 0;
    
    endian = (char)(i) == 0x01 ? LITTLE:BIG;
    
    if(endian == LITTLE)
        printf("THIS MACHINE IS LITTLE-ENDIAN\n");
    else
        printf("THIS MACHINE IS BIG-ENDIAN\n");
    
    return 0;
}