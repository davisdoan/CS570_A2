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
	
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) { //traverse pages array.
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
			pageFaults++;
		}
	}
	printf("Page Faults in Clock: %d\n",pageFaults);
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
        printf("About to traverse the Page Sequence inside of Optimal\n");	
	for(pagesPntr = 0; pagesPntr < num_characters; pagesPntr++) { //traverse pages array.
		loaded = 0;
                currentPageInFrames = 0;
		int cnt;
                int value = pages[pagesPntr];
                printf("=====Your Current Page from the Sequence is %c=====\n", value );  
                printf("You are current on the index %d for pages\n",pagesPntr); 

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
                             printf("loading in new pages %c into the Futures Ref because there are empty spots\n", loadThisPage);
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
                                printf("Your page is currently in the current frames list, no need to load it\n");
                                currentPageInFrames = 1;
                                loaded = 1;
                                break;
                        }		
		}
		// if Page Number is in a frame, move on to the page number in the overall sequence
                if(currentPageInFrames == 1){
                        printf("=== $$$$$ Inside your flag check right before the CONTINUE, moving on to the next page $$$$\n");
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
                   printf("We are in the LAST page of the sequence and we just loaded in!\n");
                   break;
                } 
                int futurePtr;
                int refMatchFlag;
                printf("about to enter the while loop to check future frames against current frames\n");
                while(currentPageInFrames == 0 && loaded == 0){
			//next handle the swap case.
			//Walk through the current pages inside the frames list
			for(framesPntr = 0; framesPntr <= maxFrame; framesPntr++){
				printf("@@@@@@@@@@@@@ walking through the current pages inside your frame list @@@ \n");
                                // walk through the pages inside the future refernece list
				for(futurePtr = 0; futurePtr <= maxFrame; futurePtr++){
                                    // compare the current page number from the current frame list 
                                    // against the current page number from the future frame list
                                    // if the current frame is equal to one of the elements inside the future list
                                    // continue onto the NEXT frame
                                   printf("About to check if future frame number is equal to frames list-------------------\n");
                                   char futureVal, currentVal;
                                   futureVal = refFrames[futurePtr];
                                   currentVal = frames[framesPntr];
                                   printf("~~~~~~~~~~Your future value is : %c\n", futureVal);
                                   printf("~~~~~~~~~~Your current val is : %c\n", currentVal);
                                
                                  if(refFrames[futurePtr] == frames[framesPntr]) {
                                     refMatchFlag = 1;
                                     printf("Current frame MATCHES a frame from the FUTURE ########\n");
                                     printf("THE PAGE YOU ARE ON IS %d =========\n", pagesPntr);
                                     break;
                                   } else{
                                    printf("There is NO match, setting your flag to ZERO &&&&&&&&&&&&\n"); 
                                    // if it goes through the entire future list and there are NO matches 
                                    // then mark the current frames pointer to be swapped out 
                                     refMatchFlag = 0; 
                                    }
                                } 
                                // The current page is not coming up soon in the future so swap it out
                                 if( refMatchFlag == 0) {
                                     frames[framesPntr] = pages[pagesPntr]; // swap the current frame with the current page number
                                     pageFaults++;
                                     printf("******** You have a fault in OPTIMAL ******\n");
				     loaded = 1;
                                     break;
                                  }
			}	
		}
		
	}
	printf("Optimal algorith faults: %d\n", pageFaults);
}


int main(){
   get_number_frames();
   read_pages();
   //second_chance(sequenceArray, numberFrames); 
   //clock(sequenceArray, numberFrames);
   optimal(sequenceArray,numberFrames);		
   //call Seconc Chance Algorithm
   //Call Clock Algorithm
   // comment
   return 0;
}
