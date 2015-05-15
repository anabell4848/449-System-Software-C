/*
Hanyu Xiong
CS449
Project 4

*/

#include <stdio.h>
#include <stdlib.h>

/* Reads the arguments from the command line.
 * Rejects your command if the number of arguments entered is not 3 or if the 
 * start number of bigger than the end number
 */
int main (int argc, char *argv[]) {
	int start, end, length;			//declare the start num, end num, and the length
	char* howtouse = "How to use: e_digit STARTNUM ENDNUM\n";	//prints this if user has no arguments
	FILE *eDevice;	//the pointer to the e char device
	
	if (argc <= 2 || argc > 3) {	//if argument count not correct 
		printf(howtouse, argv[0]);	//output the instruction message
		return 0;					
	}
	start = atoi(argv[1]); 		//first argument is start number
	end = atoi(argv[2]); 		//second argument is end number
	
	if (start < 0 || end < 0 || start > end) { //make sure start and end numbers make sense
		printf("Please enter valid start and end values!\n");	//if not we give error message
		return 1;												//didn't work properly
	}
	
	eDevice = fopen("/dev/e", "r"); 		// Open the e char device for reading
	if (eDevice == NULL) {					//if there's an error opening it we output error message
		printf("Failed to open /dev/e\n");	
		return 1;							//didn't work
	}
	
	length = (end - start) + 1; 		//get length from the start and end values
	char e_value[length + 1];			//allocate a char array for 
	
	fseek(eDevice, start, SEEK_SET);		// seek to the right start position
	fread(e_value, 1, length, eDevice); 	// uses the e_read() function to read the data

	e_value[length] = '\0'; 		//adds the terminating null
	printf("%s\n", e_value); 		//prints the vhar array containing the correct values 
	
	fclose(eDevice); 				//closes the file to finish up
	
	return 0;
}
