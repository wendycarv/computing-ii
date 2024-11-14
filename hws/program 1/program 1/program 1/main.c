#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "bit_flags.h"


int main(int argc, char* argv[])
{
    
    BIT_FLAGS flags;

    flags = bit_flags_init_number_of_bits(46);

    if (flags == NULL)
    {
        printf("Failed to allocate space for flags.\n");
        exit(1);

    }
    printf("size: %d\n", bit_flags_get_size(flags));
    printf("capacity: %d\n", bit_flags_get_capacity(flags));

    for (int i = 0; i < 40; i++)
    {
        bit_flags_set_flag(flags, i * 2);
        bit_flags_unset_flag(flags, i * 3);
    }

    
    printf("size: %d\n", bit_flags_get_size(flags));
    printf("capacity: %d\n", bit_flags_get_capacity(flags));

    bit_flags_destroy(&flags);

    return 0;
    
}
