/*
 *  sfrobu
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SPACE       ' '

static size_t numOfComp = 0;

char decrypt(const char c);
int  frobcmp(char const* a, char const* b);
int  cmpWrapper(const void* a, const void* b);
void checkMemErr(void* ptr);
void checkIOErr(ssize_t ret);
void reportErr(const char* msg);
void strWrite(const char* str);
size_t initLinebuf(char** linebuf, char* buf, size_t size);

int main(void)
{
    /* Declare Variables, a pain in C */
    int (* cmp) (const void*, const void*);
    char* input, * input2, ** linebuf, * line, curChar;
    char readbuf[2];
    size_t lineNum, lineSize, bufferSize, i, fileSize;
    int isEOF, isSpace;
    ssize_t ret;
    struct stat buf;
    
    /* Initialize variables */
    bufferSize = 0, lineNum = 0, lineSize = 0, isEOF = 0;
    
    /* Set frobcmp pointer */
    cmp = &cmpWrapper;
    
    /* File Information */
    ret = fstat(STDIN_FILENO, &buf);
    checkIOErr(ret);
    fileSize = buf.st_size + 1;
    
    /* Setup Initial Buffer */
    input = (char*) malloc(sizeof(char) * fileSize);
    checkMemErr(input);
    line = input;
    
    /*                                                           *
     * Read from Input
     */
    while ( ! isEOF)
    {
        ret = read(STDIN_FILENO, readbuf, 1);
        checkIOErr(ret);
        curChar = readbuf[0];
        isSpace = curChar == SPACE;
        isEOF = ! ret;
        if ( ! lineSize && isSpace)
            continue;
        /* Resize buffer */
        if (bufferSize == fileSize)
        {
            fileSize *= 2;
            input2 = (char*) realloc(input, sizeof(char) * fileSize);
            checkMemErr(input2);
            input = input2;
        }
        
        /* Store the current character */
        if ( ! isEOF)
        {
            input[bufferSize++] = curChar;
            lineSize++;
            if ( ! isSpace)
                continue;
        }
        else
        {
            if ( ! bufferSize)
            {
                free(input);
                return 0;         /* An Empty file or a file with only spaces */
            }
            /* Append a space if there is none */
            if (input[bufferSize-1] != SPACE)
                input[bufferSize++] = SPACE;
            if ( ! lineSize)
                break;
        }

        /* New Line */
        lineNum++;
        lineSize = 0;
    }
    linebuf = (char**) malloc(sizeof(char*) * lineNum);
    checkMemErr(linebuf);
    
    if (lineNum != initLinebuf(linebuf, input, bufferSize))
        reportErr("Wrong Line Number.");
    
    /* Sort the input */
    qsort(linebuf, lineNum, sizeof(char*), cmp);
    
    /* Output results */
    for (i = 0; i < lineNum; i++)
        strWrite(linebuf[i]);
    
    /* Free input array */
    free(linebuf);
    free(input);
    fprintf(stderr, "Comparisons: %ld\n", numOfComp);
    return 0;
}

/* Report error */
inline
void reportErr(const char* msg)
{
    fprintf(stderr, "%s Error\n", msg);
    exit(1);
}

/* Check IO Error */
inline
void checkIOErr(ssize_t ret)
{
    if (ret < 0)      reportErr("IO");
}

/* Check if malloc / realloc allocates memory successfully */
inline
void checkMemErr(void* ptr)
{
    if (ptr == NULL)    reportErr("Memory Allocation");
}

/*  Decrypt each character */
inline
char decrypt(const char c)
{
    return c ^ 42;      /* 00101010 is 0x2a, 42 */
}

/* Wrapper function */
inline
int cmpWrapper(const void* a, const void* b)
{
    return frobcmp(*((const char**) a), *((const char**) b));
}

void strWrite(const char* str)
{
    ssize_t ret;
    for (;;)
    {
        ret = write(STDOUT_FILENO, str, 1);
        checkIOErr(ret);
        if (*str++ == SPACE)
            return;
    }
}

size_t initLinebuf(char** linebuf, char* buf, size_t size)
{
    size_t i, lineNum;
    char* line = buf;
    for (i = 0, lineNum = 0; i < size; i++)
    {
        if (buf[i] == SPACE)
        {
            linebuf[lineNum++] = line;
            line = buf + i + 1;
        }
    }
    return lineNum;
}

/* Compare two frobnicated characters */
int frobcmp(char const* a, char const* b)
{
    numOfComp++;
    for ( ; *a == *b; a++, b++)
        if (*a == SPACE)
            return 0;
    return ((decrypt(*a) < (decrypt(*b)) ? -1 : 1));
    
}
