/* 
function: secondchance
Note: 1. take in int value for frameNum and the values in the pages array
      2. Set all the initial values for the frames and their reference bits
      3. Go through each page, and check if they match any values in the frames
      		a. if a frame is empty, add the page number to empty frame
      		b. if a frame value == page number, set it's bit to 1
      		c. if page number doesnt exist in the frames, check the last frame's reference bit
      				if reference bit is 0, drop last frame value and move all frames down, add current page to first frame
      				if reference bit is 1, move last frame to first frame, set its reference bit to 0, move all frames down
      4. increment fault counter as you add/replace pages in frames
      5. print the fault counter
*/
int secondchance(int frameNum, int pages[]){
	int maxFrame = frameNum - 1;	//zero based so, frame[0]->frame[frameNum]
	int frames[100];
	int referenceBits[100];
	int fault = 0;


	//set the values for the frames and their reference bits
	int k = 0;
	for(k = 0; k <= maxFrame; k++){
		frames[k] = -1;					//-1 means they are empty
		referenceBits[k] = 0;			//reference bits start at 0	
	}

	int added;
	int pageExistInFrame;
	int pIndex = 0;
	int fIndex;

	while(pages[pIndex]){				//keeps going as long as a page exists
		
		added = 0;
		pageExistInFrame = 0;
		 
		 
		//Check if the page number already exists in a frame
		//if so, set pageExistFrame, added, and it's reference bit to 1
		for(fIndex = 0; fIndex <= maxFrame; fIndex++){
			if(pages[pIndex] == frames[fIndex]){
				pageExistInFrame = 1;
				referenceBits[fIndex] = 1;
				added = 1;
				break;
			}
		}

		// if Page Number is in a frame, move on to the next number
		if(pageExistInFrame == 1){
			pIndex++;
			continue;
		}

		// if Page Number is not in the frame and it has not been added
		//check if the page in the last frame has a bit of 0.
		//if so, remove that frame value and move all the rest of the page values to the next frame
		//along with their ref bits, then add the new page value to the first frame and 
		//set it's ref bit to 0. set added value = 1 and increment the fault counter and page index
		while(pageExistInFrame == 0 && added == 0){
			int j;
			if (referenceBits[maxFrame] == 0){		
				for(j = maxFrame; j > 0; j--){		
					frames[j] = frames[j - 1];
					referenceBits[j] = referenceBits[j - 1];
				}
				frames[0] = pages[pIndex];
				referenceBits[0] = 0;
				added = 1;
				fault++;
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
		pIndex++;
	}

	printf("Second Chance faults: %d\n", fault);
	return fault;
}
