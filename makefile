CFLAGS=-std=c++11
CFLAGS+=-stdlib=libc++
CC=clang++
#flags for test.c
cc=clang
DEBUG=-g
#warnings
WARNINGS=-Weverything
#always have -Weverything on for SO lol
OPT= -O0 -O1 -O2 -O3 -O4

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(DEBUG)
