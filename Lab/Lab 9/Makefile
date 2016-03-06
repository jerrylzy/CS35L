# Make x86-64 random byte generators.

# Copyright 2015 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Change the -O2 to -Og or -O0 to ease runtime debugging.
# -O2 is often better for compile-time diagnostics, though.
OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

default: randall randmain randlibhw.so randlibsw.so

randall: randall.c
	$(CC) $(CFLAGS) randall.c -o $@

# randmain.mk contains instructions for building
# randmain, randlibhw.so, and randlibsw.so.
-include randmain.mk

skeleton: dlskeleton.tgz
skeleton_files = COPYING Makefile randall.c randcpuid.h randlib.h
dlskeleton.tgz: $(skeleton_files)
	tar -czf $@ --mode=a-w $(skeleton_files)

submission: dlsubmission.tgz
submission_files = lab.txt randmain.mk \
  randcpuid.c randlibhw.c randlibsw.c randmain.c \
  $(skeleton_files)
dlsubmission.tgz: $(submission_files)
	tar -czf $@ $(submission_files)

.PHONY: default clean skeleton submission

clean:
	rm -f *.o *.so *.so.* *.tgz randall randmain
