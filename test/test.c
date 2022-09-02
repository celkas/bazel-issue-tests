#include <stdio.h>
#include "func.h"

int main(void)
{
    int tmp = -1;

    tmp = func(1);
    if (5 != tmp)
    {
        printf("ERROR! expected 5 but received %d\n!!!", tmp);
    }
    return 0;
}
