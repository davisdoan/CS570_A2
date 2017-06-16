/**
 * Group: Davis Doan(cssc1090) & Jon Verne(cssc1145)
 * CS 570 Operating Systems Summer 2017
 * Assignment 2: Page Replacement Algorithms
 * Filename: main.c
 */

#include "header.h"

char sequenceArray[10000];

void read_pages()
{
    // sequenceArray[] is the global array

    // open the file
    // read in the file
    // store the sequence string, numbers with no spaces into an array [0] = first
    int arraysize = 100000;
    char current_char;
    int num_characters = 0;
    int i = 0;

    ifstream myfile ("pages.txt");

       if (myfile.is_open())
          {
            while ( !myfile.eof())
            {
                  myfile >> sequenceArray[i];
                  i++;
                  num_characters ++;
            }      

      for (int i = 0; i <= num_characters; i++)
        {
           cout << sequenceArray[i];
        } 
       // system("pause");
     } 
   printf( "Your contents are :  %s\n " , sequenceArray);
   // check if pages.txt has more than 99 numbers in the sequence
   if(sizeof(sequenceArray) > 99) {
      printf("The limit of number of pages any process/thread may have is 99, please change your pages.txt file to follow that limit\n");
     exit(1);
   }
   //return sequenceArray; 
}

void get_number_frames()
{
   printf("Assignment #2\n Enter number of frames in Main Memory: ");
   int numberFrames;
   scanf("%d", &numberFrames);
   //printf("Number of frames is: %d \n", numberFrames); 
}

int main(){
   // check if pages.txt has more than 99 numbers in the sequence
   
   get_number_frames();
   read_pages();
   
   printf(" In Main, your contents are : %s\n " , sequenceArray);
   return 0;
}
