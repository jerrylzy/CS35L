#  Copyright (c) 2010 Brian F. Allen.
#  Copyright 2016 Paul Eggert.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC = gcc
CFLAGS = -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter
LDLIBS = -lm -lpthread

all: srt

srt_objects = main.o raymath.o shaders.o
srt: $(srt_objects)
	$(CC) $(CFLAGS) -o $@ $(srt_objects) $(LDLIBS)

main.o raymath.o: raymath.h
main.o shaders.o: shaders.h

tests = 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm
check: baseline.ppm $(tests)
	for file in $(tests); do \
	  diff -u baseline.ppm $$file || exit; \
	done
$(tests): srt
	time ./srt $@ >$@.tmp
	mv $@.tmp $@

dist: srt.tgz
sources = COPYING Makefile main.c raymath.c raymath.h shaders.c shaders.h \
   baseline.ppm
srt.tgz: $(sources)
	tar cf - --transform='s|^|srt/|' $(sources) | gzip -9 >$@

clean:
	rm -f *.o *.tmp $(tests) srt srt.tgz
