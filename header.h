/**
 * Group: Davis Doan(cssc1090) & Jon Verne(cssc1145)
 * CS 570 Operating Systems Summer 2017
 * Assignment 2: Page Replacement Algorithm
 * Filename: header.h
 */

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define N 7

void write_pid();
void create_threads();
void create_semaphore();
void *worker_thread(void *arg);

#endif
