#!/bin/bash

gcc -I../include/ test.c -o test -L.. -lbitcoin_c
LD_LIBRARY_PATH=$(pwd)/../ ./test

