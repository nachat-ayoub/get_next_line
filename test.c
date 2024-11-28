#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

void fp(int fd, int readn)
{
    char *s = ft_calloc(readn + 1, sizeof(char));
    read(fd, s, readn);
    s[9] = '\0';
    printf("==> res: \"%s\"\n", s);
}

int main()
{
    static int count;
	int fd = open("test.txt", O_RDONLY);
    int readn = 5;

    fp(fd, readn);
    fp(fd, readn);
    fp(fd, readn);
    fp(fd, readn);
    fp(fd, readn);
    fp(fd, readn);
    fp(fd, readn);
    return 0;
}