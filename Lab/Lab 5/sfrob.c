/*
 *  sfrob
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SPACE       ' '
#define INIT_SIZE   19

char decrypt(const char c);
int  frobcmp(char const* a, char const* b);
int  cmpWrapper(const void* a, const void* b);
void checkMemErr(void* ptr);
void checkIOErr(FILE* p);
void reportErr(const char* msg);
void strWrite(const char* str);
void initLinebuf(char** linebuf, char* buf, size_t size);

int main(void)
{
    /* Declare Variables, a pain in C */
    int (* cmp) (const void*, const void*);
    char* input, * input2, ** linebuf, curChar;
    size_t lineNum, lineSize, bufferSize, i, fileSize;
    int isEOF, isSpace;
    
    /* Initialize variables */
    bufferSize = 0, lineNum = 0, lineSize = 0, isEOF = feof(stdin);
    fileSize = INIT_SIZE;
    
    /* Set frobcmp pointer */
    cmp = &cmpWrapper;
    
    /* Setup Initial Buffer */
    input = (char*) malloc(sizeof(char) * fileSize);
    checkMemErr(input);
    
    /*                                                      *
     *  To prevent getting a char with value EOF,           *
     *  We use feof(STDIN_FILENO) as the condition for the loop.   *
     */
    while ( ! isEOF)
    {
        curChar = getchar();
        checkIOErr(stdin);
        isSpace = curChar == SPACE;
        isEOF = feof(stdin);
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
        
        lineNum++;  /* New Line */
        lineSize = 0;
    }
    linebuf = (char**) malloc(sizeof(char*) * lineNum);
    checkMemErr(linebuf);
    
    initLinebuf(linebuf, input, bufferSize);
    
    /* Sort the input */
    qsort(linebuf, lineNum, sizeof(char*), cmp);
    
    /* Output results */
    for (i = 0; i < lineNum; i++)
        strWrite(linebuf[i]);
    
    /* Free input array */
    free(linebuf);
    free(input);
    return 0;
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
    for (;;)
    {
        putchar(*str);
        checkIOErr(stdout);
        if (*str++ == SPACE)
            return;
    }
}

void initLinebuf(char** linebuf, char* buf, size_t size)
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
}

/* Compare two frobnicated characters */
int frobcmp(char const* a, char const* b)
{
    for ( ; *a == *b; a++, b++)
        if (*a == SPACE)
            return 0;
    return ((decrypt(*a) < (decrypt(*b)) ? -1 : 1));
    
}
