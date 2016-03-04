1. Unmodified version
time ./srt 1-test.ppm >1-test.ppm.tmp

real 0m52.352s
user 0m52.349s
sys  0m0.000s

2. Modified version
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m51.841s
user	0m51.826s
sys	0m0.007s

time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m26.953s
user	0m53.048s
sys	0m0.000s

time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m14.160s
user	0m55.218s
sys	0m0.001s

time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m7.533s
user	0m56.434s
sys	0m0.004s

Clearly, the real time is approximately user time / number of threads,
and this is the best out of multithreading,
thanks to the insane parallelism of pixel rendering.

Also we saw a slight increase in user time.
This is the cost of creating more threads.

The eight-thread version is way way faster than the single-thread version.
This shows the power of parallelism.

3. Issues previously ran into
Previously I didn't setup an array to format the output,
so running 'make check' always shows that the output is different.
