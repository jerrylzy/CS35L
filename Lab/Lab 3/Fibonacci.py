#!/usr/bin/python

import sys

"""
Define a custom exception class that derives from the 
existing Exception class of the standard library
"""

class FibonacciException(Exception): #Derives from Exception
    def __init__(self, msg, errCode):
        self.message = msg
        self.errorCode = errCode



"""
This is a function that can throw an exception. 
Exception is thrown if the number of fibonacci numbers 
to be generated is <= 0
"""

def GenerateFibonacci(n):
    if n < 0:
        raise FibonacciException("Argument should not be negative", 100) 
        #Error number = 100 for future reference to have an idea of what went wrong
    elif n == 0:
        raise FibonacciException("Argument should not be zero", 101) 
        #Error number = 101 for future reference to have an idea of what went wrong
    
    
    #If arg is valid then carry on with normal execution of the 
    #function...i.e.to generate fibonacci numbers
    fib = [0]
    if n == 1:
        return fib

    fib.append(1)
    for i in range(2, n):
        fib.append(fib[i-1] + fib[i-2])

    return fib




"""
Catch any exceptions that might be thrown from the functions
"""

def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: ./scriptname.py N\n")
        sys.stderr.write("where N = number of fibonacci numbers to be generated\n")
        quit()

    try:
        n = int(sys.argv[1])
        fibList = GenerateFibonacci(n)
    except FibonacciException as e:
        #See what went wrong by examining 'e', which is an instance of type FibonacciException
        print 'Something went wrong inside GenerateFibonacci'
        print 'Message: ' + e.message
        print 'Error code is {0}'.format(e.errorCode)
        quit()
    except:
        #Catches any kind of exception
        print 'Caught an exception other than FibonacciException!'
        quit()

    print 'The first {0} Fibonacci numbers are'.format(n)
    print fibList
    print 'No exceptions occurred. Everything worked!'



if __name__=="__main__":
    main()
