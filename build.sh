#!/bin/bash

g++ -Iinclude/ -fPIC -shared src/*/*.cpp -o libbitcoin_c.so $(pkg-config --cflags --libs libbitcoin) -std=c++11

