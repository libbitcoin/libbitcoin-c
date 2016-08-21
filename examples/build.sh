#!/bin/bash

gcc test.c -o test $(pkg-config --cflags --libs libbitcoin-c)
./test

