#!/bin/bash

comm test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_normal
python3 comm.py test_files/misEngHai test_files/misEnglish > py_output_normal

diff -u comm_output_normal py_output_normal

python comm.py test_files/misEngHai test_files/misEnglish > py_output_normal
diff -u comm_output_normal py_output_normal

comm -1 test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_1
python3 comm.py -1 test_files/misEngHai test_files/misEnglish > py_output_1

diff -u comm_output_1 py_output_1

python comm.py -1 test_files/misEngHai test_files/misEnglish > py_output_1
diff -u comm_output_1 py_output_1

comm -2 test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_2
python3 comm.py -2 test_files/misEngHai test_files/misEnglish > py_output_2

diff -u comm_output_2 py_output_2

python comm.py -2 test_files/misEngHai test_files/misEnglish > py_output_2
diff -u comm_output_2 py_output_2

comm -3 test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_3
python3 comm.py -3 test_files/misEngHai test_files/misEnglish > py_output_3

diff -u comm_output_3 py_output_3

python comm.py -3 test_files/misEngHai test_files/misEnglish > py_output_3
diff -u comm_output_3 py_output_3

comm -12 test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_12
python3 comm.py -12 test_files/misEngHai test_files/misEnglish > py_output_12

diff -u comm_output_12 py_output_12

python comm.py -12 test_files/misEngHai test_files/misEnglish > py_output_12
diff -u comm_output_12 py_output_12

comm -13 test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_13
python3 comm.py -13 test_files/misEngHai test_files/misEnglish > py_output_13

diff -u comm_output_13 py_output_13

python comm.py -13 test_files/misEngHai test_files/misEnglish > py_output_13
diff -u comm_output_13 py_output_13

comm -23 test_files/misEngHai test_files/misEnglish --output-delimiter='        ' > comm_output_23
python3 comm.py -23 test_files/misEngHai test_files/misEnglish > py_output_23

diff -u comm_output_23 py_output_23

python comm.py -23 test_files/misEngHai test_files/misEnglish > py_output_23
diff -u comm_output_23 py_output_23

python3 comm.py -u test_files/file1 test_files/file2 > us_output00
python comm.py -u test_files/file1 test_files/file2 > us_output01

diff -u us_output00 test_files/sample_unsorted
diff -u us_output01 test_files/sample_unsorted

python3 comm.py -u test_files/file1 - < test_files/file2 > us_output10
python comm.py -u test_files/file1 - < test_files/file2 > us_output11

diff -u us_output10 test_files/sample_unsorted
diff -u us_output11 test_files/sample_unsorted

python3 comm.py -u - < test_files/file1 test_files/file2 > us_output20
python comm.py -u - < test_files/file1 test_files/file2 > us_output21

diff -u us_output20 test_files/sample_unsorted
diff -u us_output21 test_files/sample_unsorted

python3 comm.py test_files/file7 test_files/file8 > nonl_output_py3
comm test_files/file7 test_files/file8 --output-delimiter='        ' > nonl_output_normal

diff -u nonl_output_py3 nonl_output_normal

python comm.py test_files/file7 test_files/file8 > nonl_output_py
diff -u nonl_output_py nonl_output_normal

rm *output*