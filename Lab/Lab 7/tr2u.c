/*  tr2u.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int strsearch(const char* str, char letter);
int finddup(const char* str);
char findletter(const char* from, const char* to, size_t len, char letter);

int main(int argc, const char * argv[])
{
    const char* from, * to;
    size_t len;
    ssize_t ret;
    char src[2];
    
    if (argc != 3)
    {
        fprintf(stderr, "Error in number of arguments %d.\\n", argc);
        exit(1);
    }
    
    from = argv[1];
    to = argv[2];
    len = strlen(from);
    
    if ( ! len)
    {
        fprintf(stderr, "Missing operand.\\n");
        exit(1);
    }
    
    if (len != strlen(to))
    {
        fprintf(stderr, "Different lengths of arguments.\\n");
        exit(1);
    }
    
    if (finddup(from))
    {
        fprintf(stderr, "From has duplicate bytes.\\n");
        exit(1);
    }
    
    for (;;)
    {
        ret = read(STDIN_FILENO, src, 1);
        if ( ! ret)
            break;
        else if (ret < 0)
        {
            fprintf(stderr, "Read Error.\\n");
            exit(1);
        }
        src[0] = findletter(from, to, len, src[0]);
        ret = write(STDOUT_FILENO, src, 1);
        if (ret < 0)
        {
            fprintf(stderr, "Write Error.\\n");
            exit(1);
        }
    }
    return 0;
}

int finddup(const char* str)
{
    for ( ; *str != 0; str++)
        if (strsearch((str+1), *str))
            return 1;
    return 0;
}

int strsearch(const char* str, char letter)
{
    for ( ; *str != 0; str++)
        if (*str == letter)
            return 1;
    return 0;
}

char findletter(const char* from, const char* to, size_t len, char letter)
{
    size_t i;
    for (i = 0; i < len; i++)
        if (from[i] == letter)
            return to[i];
    return letter;
}
