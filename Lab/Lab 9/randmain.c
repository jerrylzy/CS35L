/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
 instruction if available to generate random numbers, falling back
 on /dev/urandom and stdio otherwise.
 
 This program is not portable.  Compile it with gcc -mrdrnd for a
 x86-64 machine.
 
 Copyright 2015 Paul Eggert
 
 This program is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "randcpuid.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
    /* Check arguments.  */
    bool valid = false;
    long long nbytes;
    if (argc == 2)
    {
        char *endptr;
        errno = 0;
        nbytes = strtoll (argv[1], &endptr, 10);
        if (errno)
            perror (argv[1]);
        else
            valid = !*endptr && 0 <= nbytes;
    }
    if (!valid)
    {
        fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 1;
    }
    
    /* If there's no work to do, don't worry about which library to use.  */
    if (nbytes == 0)
        return 0;
    
    /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
    void* dl_handle;
    unsigned long long (* rand64) (void);
    char* error;
    if (rdrand_supported ())
    {
        dl_handle = dlopen("randlibhw.so", RTLD_LAZY);
        if (!dl_handle)
        {
            fprintf (stderr, "dlopen() error - %s\n", dlerror());
            return 1;
        }
        rand64 = dlsym(dl_handle, "rand64");
        error = dlerror();
        if (error != NULL)
        {
            fprintf (stderr, "dlsym randlibhw error - %s\n", error);
            return 1;
        }
    }
    else
    {
        dl_handle = dlopen("randlibsw.so", RTLD_LAZY);
        if (!dl_handle)
        {
            fprintf (stderr, "dlopen() error - %s\n", dlerror());
            return 1;
        }
        rand64 = dlsym(dl_handle, "rand64");
        error = dlerror();
        if (error != NULL)
        {
            fprintf (stderr, "dlsym randlibsw error - %s\n", error);
            return 1;
        }
    }

    int wordsize = sizeof rand64 ();
    int output_errno = 0;
    
    do
    {
        unsigned long long x = rand64 ();
        size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (fwrite (&x, 1, outbytes, stdout) != outbytes)
        {
            output_errno = errno;
            break;
        }
        nbytes -= outbytes;
    }
    while (0 < nbytes);
    
    if (dlclose(dl_handle))
    {
        fprintf (stderr, "dlclose() error - %s\n", dlerror());
        return 1;
    }
    
    if (fclose (stdout) != 0)
        output_errno = errno;
    
    if (output_errno)
    {
        errno = output_errno;
        perror ("output");
        return 1;
    }

    return 0;
}
