#####################################################
# Group: Davis Doan(cssc1090) & Jon Verne(cssc1145)
# CS 570: Operating Systems Summer 2017
# Assignment 2: Page Replacement Algorithm
# Filename: makefile
#####################################################

EXE= a2
FILE= main.c
CC = g++
flags =

make: 
	$(CC) $(flags) -o$(EXE) $(FILE)

clean:main.c
	rm a2
