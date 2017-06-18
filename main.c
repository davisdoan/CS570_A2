/**
 * Group: Davis Doan(cssc1090) & Jon Verne(cssc1145)
 * CS 570 Operating Systems Summer 2017
 * Assignment 2: Page Replacement Algorithms
 * Filename: main.c
 */

#include "header.h"

char sequenceArray[1000];
int numberFrames;
int num_characters = -1;

void read_pages()
{
    // sequenceArray[] is the global array

    // open the file
    // read in the file
    // store the sequence string, numbers with no spaces into an array [0] = first
    int arraysize = 1000;
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
   return;
}

void get_number_frames()
{
   printf("Assignment #2\n Enter number of frames in Main Memory: ");
   scanf("%d", &numberFrames);
   //printf("Number of frames is: %d \n", numberFrames); 
}
	

void second_chance(char pages[], int numFrames) {
  	int maxFrame = numFrames - 1;	//zero based so, frame[0]->frame[numFrames]
	int frames[100];
	int referenceBits[100];
	int pageFaults = 0;
 	int loaded = 0;			//set to one when page successfully loaded into frames.
	int currentPageInFrames = 0;	//set to one if page to be loaded is currently in frames array.		
	int pagesPntr = 0;
	int framesPntr = 0;
 
	//set the values for the frames and their reference bits
	int z = 0;
	for(z = 0; z <= maxFrame; z++){
		frames[z] = -1;					//-1 means they are empty
		referenceBits[z] = 0;			//reference bits start at 0	
	} 
  
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) { //traverse pages array, starting at the second page.
            		loaded = 0;
			currentPageInFrames = 0;
	
			printf("num_char: %d\n",num_characters);
			char value = pages[pagesPntr];	
			printf("checking if page %c is in current frame\n", value);
		for(framesPntr = 0 ; framesPntr <= maxFrame ; framesPntr++) { //traverse frames array checking for the current page alreadey loaded in frames array.

			
                	if(pages[pagesPntr] == frames[framesPntr]){
				printf("%c is in frames\n", value);
				currentPageInFrames = 1;
				referenceBits[framesPntr] = 1;
				loaded = 1;
				break;
			}
		}

		// if Page Number is in a frame, move on to the next number
		if(currentPageInFrames == 1){
			//pagesPntr++;
			continue;
		}
		
	
		/*
		*If the current page is not in the frames array and has not been loaded 
		*starting from the last position in frame check if its ref bit is zero
		*if true increment the position of all values in frames and ref bits
		*else if the last position in frames has a ref bit of 1
		*increment all positions in frames and ref bit, 
		*load the last postion into position one in frames
		*/
		while(currentPageInFrames == 0 && loaded == 0){
			int j;
			if (referenceBits[maxFrame] == 0){		
				for(j = maxFrame; j > 0; j--){		
					frames[j] = frames[j - 1];
					referenceBits[j] = referenceBits[j - 1];
				}
				frames[0] = pages[pagesPntr];
				referenceBits[0] = 0;
				loaded = 1;
				printf("inc page fault for value at index: %d\n", pagesPntr);
				pageFaults++;
			}
			//if the last frame bit != 0, then move the page numbers in the frames to their next frames
			//The last page value will then be moved to the first frame and it's ref bit set to 0.
			// increment page index
			else{
				int temp = frames[maxFrame];
				for(j = maxFrame; j > 0; j--){
					frames[j] = frames[j - 1];
					referenceBits[j] = referenceBits[j - 1];
				}			
				frames[0] = temp;
				referenceBits[0] = 0;
			}
		}
		//pagesPntr++;
        }            
	printf("Second Chance faults: %d\n", pageFaults);
}

void clock(char pages[], int numFrames){
	int maxFrame = numFrames - 1;   //zero based so, frame[0]->frame[numFrames]
        int frames[100];
        int referenceBits[100];
        int pageFaults = 0;
        int loaded = 0;                 //set to one when page successfully loaded into frames.
        int currentPageInFrames = 0;    //set to one if page to be loaded is currently in frames array.         
        int pagesPntr = 0;
        int framesPntr = 0;
	int clockHand = 0;	

	//set the values for the frames and their reference bits
        int z = 0;
        for(z = 0; z <= maxFrame; z++){
                frames[z] = -1;                                 //-1 means they are empty
                referenceBits[z] = 0;                   //reference bits start at 0     
        }
	
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) { //traverse pages array, starting at the second page.
		loaded = 0;
                currentPageInFrames = 0;
		int value = pages[pagesPntr];
		for(framesPntr = 0 ; framesPntr <= maxFrame ; framesPntr++) { //traverse frames array checking for the current page alreadey loaded in frames array.
			
			if(pages[pagesPntr] == frames[framesPntr]){
                                printf("%c is in frames\n", value);
                                currentPageInFrames = 1;
                                referenceBits[framesPntr] = 1;
                                loaded = 1;
                                break;
                        }
		}
	
		// if Page Number is in a frame, move on to the next number
                if(currentPageInFrames == 1){
                        //pagesPntr++;
                        continue;
                }
		
		while(currentPageInFrames == 0 && loaded == 0){
			while (referenceBits[clockHand] == 1){
				referenceBits[clockHand] = 0;
				clockHand++;
				if(clockHand > maxFrame){clockHand = 0;}

			}
			frames[clockHand] = pages[pagesPntr];
			referenceBits[clockHand] = 1;
			loaded = 1;
			clockHand++;
			if(clockHand > maxFrame){clockHand = 0;}
		}
	}
	printf();
}

int main(){
   get_number_frames();
   read_pages();
   second_chance(sequenceArray, numberFrames); 
   clock(sequenceArray, numberFrames);
   //call Seconc Chance Algorithm
   //Call Clock Algorithm

   return 0;
}
