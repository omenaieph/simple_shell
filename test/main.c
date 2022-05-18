#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    char *buff;
    size_t  nread;
    size_t len = 32;

    buff = (char*)malloc(len * sizeof(char));
    if (buff == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    printf("Type something: ");
    nread = getline(&buff, &len, stdin);
    printf("%zu characters were read \n", nread);
    printf("You typed: '%s'\n", buff);

    return (0);
}
