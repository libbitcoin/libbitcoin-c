#!/bin/bash

gcc test.c -o test $(pkg-config --cflags --libs libbitcoin-c)
./test

gcc satoshi_words.c -o satoshi_words $(pkg-config --cflags --libs libbitcoin-c)

