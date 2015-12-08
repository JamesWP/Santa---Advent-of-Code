CFLAGS=-std=c++11
CFLAGS+=-stdlib=libc++
#flags for test.c
CC=clang++
DEBUG=-g
#warnings
WARNINGS=-Weverything
#always have -Weverything on for SO lol
OPT= -O0 -O1 -O2 -O3 -O4

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(DEBUG)

day4: day4.o libs/md5.o
	$(CC) day4.o libs/md5.o -o day4
