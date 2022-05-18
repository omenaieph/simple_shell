#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    char *str;

    str = getenv("PATH");
    printf("%s\n",str);
}