/**
 * Group: Davis Doan(cssc1090) & Jon Verne(cssc1145)
 * CS 570 Operating Systems Summer 2017
 * Assignment 2: Page Replacement Algorithms
 * Filename: main.c
 */

#include "header.h"

char sequenceArray[10000];
int numberFrames;
int num_characters =0;

void read_pages()
{
    // sequenceArray[] is the global array

    // open the file
    // read in the file
    // store the sequence string, numbers with no spaces into an array [0] = first
    int arraysize = 100000;
    char current_char;
    //int num_characters = 0;
    int i = 0;

    ifstream myfile ("pages.txt");

       if (myfile.is_open())
          {
            while ( !myfile.eof())
            {
                  myfile >> sequenceArray[i];
                  i++;
                  num_characters++;
            }      

      for (int i = 0; i <= num_characters; i++)
        {
           cout << sequenceArray[i];
        } 
       // system("pause");
     } 
//   printf( "Your contents are :  %s\n " , sequenceArray);
   int checkSize = sizeof(sequenceArray);
   printf(" Your sequence array size is : %d\n", checkSize);
   // check if pages.txt has more than 99 numbers in the sequence
   if(num_characters > 99) {
      printf("The limit of number of pages any process/thread may have is 99, please change your pages.txt file to follow that limit\n");
     exit(1);
   }
   myfile.close(); 
   printf("go home");
   return;
}

void get_number_frames()
{
   printf("Assignment #2\n Enter number of frames in Main Memory: ");
   scanf("%d", &numberFrames);
   //printf("Number of frames is: %d \n", numberFrames); 
}

void second_chance(char sequence[], int frames) {
   
   printf("inside 2nd chance\n");
   int i, j;
   char framesArray[3];
   int faultCounter = 0;
   // load in the first number of the sequence into the first frame
   framesArray[0] = sequence[0];
  printf("before the for loop\n"); 
   for(i = 1; i < num_characters; i++) { //go through the page sequence
            for(j = 0 ; j < frames; j++) {
                printf("checking if current page is in current frame\n");
                if(sequence[i] == framesArray[j]) {
                    printf("your current sequence is : %d\n",sequence[i]);
                    char tmp = framesArray[j];
                    printf("your temp var is : %d\n", tmp);
                    while( j >= 0) {
                        printf("inside the first while loop");
                        framesArray[j] = framesArray[--j];
                    }
                    framesArray[0] = tmp;
                    continue;                
                 }
                 else {
                  int numberCharsCopy = num_characters -1;
                      printf("no matches, inside the else\n");
                      printf("your numbCharsCopy Var contains: %d\n", numberCharsCopy);
                      // start from the end and move the current frames downwards
                      while( numberCharsCopy > 1) {
                          printf("the start of the while loop inside the else\n");
                          framesArray[numberCharsCopy - 1] = framesArray[numberCharsCopy - 2];
                          numberCharsCopy--;
                      }   printf("you are free from the while loop\n");
                          framesArray[0] = sequence[i];
                          printf("incrementing fault counter for sequence: %d\n", *sequence[i]);
                          faultCounter++;
                          printf("the current fault counter is : %d\n", faultCounter);
                      }
                 } printf("*************** outside of the frames loop\n");
             }
   printf("The number of faults is : %d\n", faultCounter);
}

void least_recently_used(){

}

int main(){
   get_number_frames();
   read_pages();
   second_chance(sequenceArray, numberFrames); 
   //call OPT algorithm
   //call Seconc Chance Algorithm
   //Call Clock Algorithm

   return 0;
}
