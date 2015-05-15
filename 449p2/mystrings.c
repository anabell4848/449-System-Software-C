/*
Hanyu Xiong
CS449
Project 2 part 1
*/

#include <stdio.h>
#include <string.h>

// Function to get and print the strings from the file
int getstring(char *filename) {
	FILE *file;
	int charcount=0; // count 4 characters before print
	char thechar=0; //  current character from file
	char minchars=0; // previous characters for output

	// print filename
	printf("\nFilename: %s\n\n",filename);

	// open the file to read
	file = fopen(filename,"rb");

    //check if file is not empty
    if (file == NULL) {
		return(1);
	}
	// loop while not the end of file
	while(!feof(file)) {
		thechar = fgetc(file); // get the character from the file

        if ((thechar >= 32) && (thechar <= 126)) { // check if is character
            charcount++;
            if (charcount == 4) {  //character is at 4
                fseek(file,-5,SEEK_CUR); // Go 5 chars back to print string so far
                int i;
                for (i = 0; i < 4; i++) {
                    minchars = fgetc(file);
                    printf("%c", minchars);
                }
            }
            else if (charcount > 4) { //characters is at position greater than 4
                printf("%c", thechar);
            }
        }
		else {
			if (charcount >= 4){
                printf("\n"); // End of current string
			}
            charcount = 0;
		}
	}
	// close file
	fclose(file);

	return 0;
}

int main (int argc, char *argv[]) {
	int results;

	// Initially set results equal to 0.
	results = 0;

	if (argc == 1) { //no arguments
		printf("Enter a filename\n");
	}
	else if (argc == 2) { //entered filename
		results = getstring(argv[1]);
	}
    else { // invalid number of arguments
		printf("Entered an invalid number of arguments!\n");
	}

	// If a bad filename was provided by the user.
	if (results == 1) {
		printf("This is a bad file.\n");
	}

	return results;
}
