#!/bin/bash
g++ -o libbitcoin_c_test -I../include/ main.cpp math/*.cpp utility/*.cpp wallet/*.cpp -lboost_unit_test_framework $(pkg-config --cflags --libs libbitcoin) -L..  -lbitcoin_c -std=c++11
LD_LIBRARY_PATH=$(pwd)/../ ./libbitcoin_c_test
