/*  tr2b.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int strsearch(const char* str, char letter);
int finddup(const char* str);
char findletter(const char* from, const char* to, size_t len, char letter);
void checkIOErr(FILE* p);
void reportErr(const char* msg);

int main(int argc, const char * argv[])
{
    const char* from, * to;
    size_t len;
    char src;
    
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
        src = getchar();
        checkIOErr(stdin);
        if (feof(stdin))
            break;
        putchar(findletter(from, to, len, src));
        checkIOErr(stdout);
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

/* Report error */
inline
void reportErr(const char* msg)
{
    fprintf(stderr, "%s Error: %d\n", msg, errno);
    exit(1);
}

/* Check IO Error */
inline
void checkIOErr(FILE* p)
{
    if (ferror(p))      reportErr("IO");
}
