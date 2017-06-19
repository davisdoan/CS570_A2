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
    int arraysize = 1000;
    char current_char;
    int i = 0;
    int checkSize = sizeof(sequenceArray);
    // ********************************************************************************************
    // Open the pages.txt file, read the file and store the sequence into an array
    // ********************************************************************************************
    ifstream myfile ("pages.txt");
       if (myfile.is_open())
          {
            while ( !myfile.eof())
            {
                  myfile >> sequenceArray[i];
                  i++;
                  num_characters++;
            }      
     } 
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
}

void second_chance(char pages[], int numFrames) {
  	int maxFrame = numFrames - 1;	// zero based so, frame[0]->frame[numFrames]
	int frames[100];                // this array holds the pages in the frames
	int referenceBits[100];         
	int pageFaults = 0;
 	int loaded = 0;			// set to one when page successfully loaded into frames.
	int currentPageInFrames = 0;	// set to one if page to be loaded is currently in frames array.		
	int pagesPntr = 0;
	int framesPntr = 0;
 
	//set the values for the frames and their reference bits
	int z = 0;
	for(z = 0; z <= maxFrame; z++){
		frames[z] = -1;					//-1 means they are empty
		referenceBits[z] = 0;			//reference bits start at 0	
	} 
        // traverse the pages array, starting at the second page 
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) {
            loaded = 0;
	    currentPageInFrames = 0;
	    char value = pages[pagesPntr];	
            
            // traverse the frames array to check if the current page is already loaded into the frames array
	    for(framesPntr = 0 ; framesPntr <= maxFrame ; framesPntr++) {
                if(pages[pagesPntr] == frames[framesPntr]){
		    currentPageInFrames = 1;
		    referenceBits[framesPntr] = 1;
		    loaded = 1;
		    break;
		}
	    }

	    // if Page Number is in a frame, move on to the next number
	    if(currentPageInFrames == 1){
  	        continue;
	    }

            // if the current page is not in your frames list and isn't loaded
            // working backwards in the frames list, check if the bit is zero
            // if the bit is zero then adjust the positions of the frames and their refernece bits
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
        }            
	printf("The number of page faults in the Second Chance algorithm is: %d\n", pageFaults);
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

        // traverse through the pages array	
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) {
		loaded = 0;
                currentPageInFrames = 0;
		int value = pages[pagesPntr];
                
                // traverse the frames array to check if current page is already loaded
		for(framesPntr = 0 ; framesPntr <= maxFrame ; framesPntr++) {
			if(pages[pagesPntr] == frames[framesPntr]){
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
		
		while(currentPageInFrames == 0 && loaded == 0) {
                    // check the reference bit, if its 1, set it to 0
                    // move the clockhand to the next frame
		    while (referenceBits[clockHand] == 1) {
	                referenceBits[clockHand] = 0;
			clockHand++;
			if(clockHand > maxFrame){
                            clockHand = 0;
                        }
		    }
                    // do the swap and set the bit to one of the new element
		    frames[clockHand] = pages[pagesPntr];
		    referenceBits[clockHand] = 1;
		    loaded = 1;
		    clockHand++;
		   
                    if(clockHand > maxFrame){
                        clockHand = 0; 
                    }
		    pageFaults++;
		}
	}
	printf("The number of page faults in the Clock algorithm is: %d\n",pageFaults);
}

void optimal(char pages[], int numFrames){
	int maxFrame = numFrames - 1;   //zero based so, frame[0]->frame[numFrames]
        int frames[100];
        int refFrames[100];
        int pageFaults = 0;
        int loaded = 0;                 //set to one when page successfully loaded into frames.
        int currentPageInFrames = 0;    //set to one if page to be loaded is currently in frames array.         
        int pagesPntr = 0;
        int framesPntr = 0;

	//set the values for the frames and their reference frames.
        int z = 0;
        for(z = 0; z <= maxFrame; z++){
                frames[z] = -1;                                 //-1 means they are empty
                refFrames[z] = 0;                   //reference frames start at 0     
        }
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) { //traverse pages array.
		loaded = 0;
                currentPageInFrames = 0;
		int cnt;
                int value = pages[pagesPntr];
                // **************************************************************************************************
                // Load in the Sequences in the future into the Reference Frames        
                // if we are towards the end of the sequence, and our number of frames is > sequence numbers remaning
                // **************************************************************************************************
                if(pagesPntr >= (num_characters - maxFrame)){
			for(cnt = 0;cnt < (num_characters-pagesPntr-2);cnt++){
				refFrames[cnt] = pages[pagesPntr + 1 + cnt]; 
			}
		} else {
                // we are not near the end of the sequence, so load in the sequence numbers to the reference frames
                    int p; 
                    char loadThisPage;
                    for( p = 0; p <= maxFrame; p++) {
                         // load the next future frames into the reference array
                             loadThisPage = pages[pagesPntr + 1+ p];
                             refFrames[p] = pages[pagesPntr + 1+ p];
                    }
                }
                
                // **************************************************************************************************
                // Traverse the current frames array to check to see if the current page number is already in the current frames array
                // **************************************************************************************************
                for(framesPntr = 0 ; framesPntr <= maxFrame ; framesPntr++) { 
	                // checking to see if the current page is in the current frames list
	                // if it is, set values of boolean flags so that you move onto the next page in the sequence	
			if(pages[pagesPntr] == frames[framesPntr]){
                                currentPageInFrames = 1;
                                loaded = 1;
                                break;
                        }		
		}
		// if Page Number is in a frame, move on to the page number in the overall sequence
                if(currentPageInFrames == 1){
                        continue;
                }
	
                // **************************************************************************************************
                // this page number is NOT in the current frames, so check against the future reference frames
                // to see which is the best number to swap out	
                // **************************************************************************************************
		
                // if we are on the last page of the sequence, just load it in and don't do any checks
                if(pagesPntr == (num_characters - 1)) {
                   frames[0] = pages[pagesPntr];
                   loaded = 1;
                   pageFaults++;
                   break;
                } 
                int futurePtr;
                int refMatchFlag;
                while(currentPageInFrames == 0 && loaded == 0){
			//next handle the swap case.
			//Walk through the current pages inside the frames list
			for(framesPntr = 0; framesPntr <= maxFrame; framesPntr++){
                                // walk through the pages inside the future refernece list
				for(futurePtr = 0; futurePtr <= maxFrame; futurePtr++){
                                    // compare the current page number from the current frame list 
                                    // against the current page number from the future frame list
                                    // if the current frame is equal to one of the elements inside the future list
                                    // continue onto the NEXT frame
                                   char futureVal, currentVal;
                                   futureVal = refFrames[futurePtr];
                                   currentVal = frames[framesPntr];
                                
                                  if(refFrames[futurePtr] == frames[framesPntr]) {
                                     refMatchFlag = 1;
                                     break;
                                   } else{
                                    // if it goes through the entire future list and there are NO matches 
                                    // then mark the current frames pointer to be swapped out 
                                     refMatchFlag = 0; 
                                    }
                                } 
                                // The current page is not coming up soon in the future so swap it out
                                 if( refMatchFlag == 0) {
                                     frames[framesPntr] = pages[pagesPntr]; // swap the current frame with the current page number
                                     pageFaults++;
				     loaded = 1;
                                     break;
                                  }
			}	
		}
	}
	printf("The number of page faults in the Optimal algorithm is : %d\n", pageFaults);
}

int main(){
   get_number_frames();
   read_pages();
   second_chance(sequenceArray, numberFrames); 
   clock(sequenceArray, numberFrames);
   optimal(sequenceArray,numberFrames);
   printf("That is the end of the Page Replacement program, have a nice day!\n");		
   return 0;
}
