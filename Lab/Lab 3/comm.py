#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, locale, string, sys
from optparse import OptionParser

delimiter = "        "
EMPTY = ""

class comm:
    def __init__(self, args, only_file_1, only_file_2, both, files_unsorted):
        if args[0] == "-":
            self.lines1 = sys.stdin.readlines()
        else:
            file1 = open(args[0], 'r')
            self.lines1 = file1.readlines()
            file1.close()

        if args[1] == "-":
            self.lines2 = sys.stdin.readlines()
        else:
            file2 = open(args[1], 'r')
            self.lines2 = file2.readlines()
            file2.close()

        self.only_file_1 = only_file_1
        self.only_file_2 = only_file_2
        self.both = both
        self.unsorted = files_unsorted
        self.lines1 = self.str_process(self.lines1)
        self.lines2 = self.str_process(self.lines2)

    def str_process(self, file):
        if not len(file):
            file.append("\n")
        else:
            temp = file[-1]
            NEW_LINE = "\n"
            if NEW_LINE not in temp:
                temp += NEW_LINE
            file[-1] = temp
        return file

    def writeline(self, line, output_class):
        stream = ""
        if output_class == 1:
            if not self.only_file_1:
                return
        elif output_class == 2:
            if not self.only_file_2:
                return
            if self.only_file_1:
                stream += delimiter
        elif output_class == 3:
            if not self.both:
                return
            if self.only_file_1:
                stream += delimiter
            if self.only_file_2:
                stream += delimiter
        else:
            sys.stderr.write("incorrect argument for suppressing\n")
        sys.stdout.write(stream + line)

    def issorted(self):
        sorted_line1, sorted_line2 = sorted(self.lines1), sorted(self.lines2)
        files_sorted = True

        if sorted_line1 != self.lines1:
            files_sorted = False
            sys.stderr.write("FILE1 not sorted\n")

        if sorted_line2 != self.lines2:
            files_sorted = False
            sys.stderr.write("FILE2 not sorted\n")
        return files_sorted

    def compare_files(self):
        if self.unsorted:
            diff_line2 = self.lines2
            for line1 in self.lines1:
                if line1 not in self.lines2:
                    self.writeline(line1, int(1))
                else:
                    self.writeline(line1, int(3))
                    diff_line2.remove(line1)

            for line2 in diff_line2:
                self.writeline(line2, int(2))
            return

        if not self.issorted():
            return

        i, j = 0, 0
        len_line1, len_line2 = len(self.lines1), len(self.lines2)

        while i in range(len_line1) or j in range(len_line2):
            line1,line2 = EMPTY, EMPTY

            if i < len_line1:
                line1 = self.lines1[i]
            if j < len_line2:
                line2 = self.lines2[j]

            if line1 == EMPTY or (line2 != EMPTY and line1 > line2):
                self.writeline(line2, 2)
                j += 1
            elif line2 == EMPTY or line1 < line2:
                self.writeline(line1, 1)
                i += 1
            else:
                self.writeline(line2, 3)
                i += 1
                j += 1
        return

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Compare files FILE1 and FILE2 line by line.

When FILE1 or FILE2 (not both) is -, read standard input.
"""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", "--nofile1",
                      action="store_false", dest="only_file_1", default=True,
                      help="suppress column 1 (lines unique to FILE1)")
    parser.add_option("-2", "--nofile2",
                      action="store_false", dest="only_file_2", default=True,
                      help="suppress column 2 (lines unique to FILE2)")
    parser.add_option("-3", "--nocommon",
                      action="store_false", dest="both", default=True, help=
                      "suppress column 3 (lines that appear in both files)")
    parser.add_option("-u", "--unsorted",
                      action="store_true", dest = "files_unsorted",
                      default=False, help="work with unsorted files")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        only_file_1 = bool(options.only_file_1)
    except:
        parser.error("invalid argument for -1: {0}".
                     format(options.only_file_1))
    try:
        only_file_2 = bool(options.only_file_2)
    except:
        parser.error("invalid argument for -2: {0}".
                     format(options.only_file_2))
    try:
        both = bool(options.both)
    except:
        parser.error("invalid argument for -3: {0}".
                     format(options.both))
    try:
        files_unsorted = bool(options.files_unsorted)
    except:
        parser.error("invalid argument for -u --unsorted: {0}".
                     format(options.files_unsorted))

    if len(args) != 2:
        parser.error("missing operand")

    if args[0] == "-" and args[0] == args[1]:
        parser.error("only one file can be read from stdin")

    try:
        generator = comm(args, only_file_1, only_file_2, both, files_unsorted)
    except OSError as err:
        parser.error("OS Error: {0}".format(err))
    try:
        generator.compare_files()
    except:
        parser.error("error")

if __name__ == "__main__":
    main()
