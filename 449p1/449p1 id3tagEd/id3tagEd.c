/*
Hanyu Xiong
CS 449 Project 1 part 2

id3 Tag Editor: a utility that can print the contents of an existing tag, if there, and add or modify a tag

when using keep "-field" the field part in lower case
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Main function.
int main (int argc, char *argv[]) {
   //struct for the id3tag
	struct id3tag {
		char identifier[3];
		char title[30];
		char artist[30];
		char album[30];
		char year[4];
		char comment[28];
		char separator;
		unsigned char track;
		unsigned char genre;
	};
	// declarations
	struct id3tag tag;
	int count;
	FILE *mp3file;
	FILE *writefile;

	if (argc == 1) { // no arguments for filename
		printf("No filename entered. \n");
	}
	else if (argc == 2) { //only a filename, print the contents of the ID3 tag to the console if present
		// print the filename
		printf("Filename: %s\n",argv[1]);
		// open the file for reading
		mp3file = fopen(argv[1],"rb");

		if (mp3file == NULL) // file null
			printf("Invalid filename\n");
		else {
			// Go to tag data at the end of the file, read into struct
			fseek(mp3file,-128,SEEK_END);
			fread(&tag,1,128,mp3file);
			fclose(mp3file);

			if (strncmp(tag.identifier,"TAG",3)==0){ // tag contains the identifier
				printf("\nIdentifier: %.3s\n",tag.identifier);
				printf("Title: %.30s\n",tag.title);
				printf("Artist: %.30s\n",tag.artist);
				printf("Album: %.30s\n",tag.album);
				printf("Year: %.4s\n",tag.year);
				printf("Comment: %.28s\n",tag.comment);
				printf("Track number: %d\n",tag.track);
				printf("Genre: %d\n\n",tag.genre);
			}
			else { // no identifier, so no tag
				printf("No ID3v1.1 tag in this file\n");
			}
		}

	}
	else {  //more than 2 arguments
        if ((argc % 2) == 1) // odd number of arguments, invalid
            printf("Invalid number of arguments!\n");
        else if ((argc % 2) == 0) { // correct number of arguments beyond the first 2
            // prints the filename
            printf("Filename: %s\n",argv[1]);

            // open the file to read
            mp3file = fopen(argv[1],"rb");

            if (mp3file == NULL) // file null
                printf("Invalid filename\n");
            else {   //file not null
                // Go to tag data at the end of the file, read into struct
                fseek(mp3file,-128,SEEK_END);
                fread(&tag,1,128,mp3file);
                fclose(mp3file);

                if (strncmp(tag.identifier,"TAG",3)==0) { // tag contains the identifier
                    // check if there are more tags to be set
                    for (count = 2;count < argc;count++) {
                        if ((strcmp(argv[count],"-title")) == 0){
                            count++;
                            strncpy(tag.title,argv[count],30);
                        }
                        else if ((strcmp(argv[count],"-artist")) == 0){
                            count++;
                            strncpy(tag.artist,argv[count],30);
                        }
                        else if ((strcmp(argv[count],"-album")) == 0){
                            count++;
                            strncpy(tag.album,argv[count],30);
                        }
                        else if ((strcmp(argv[count],"-year")) == 0){
                            count++;
                            strncpy(tag.year,argv[count],4);
                        }
                        else if ((strcmp(argv[count],"-comment")) == 0){
                            count++;
                            strncpy(tag.comment,argv[count],28);
                        }
                        else if ((strcmp(argv[count],"-track")) == 0){
                            count++;
                            tag.track = atoi(argv[count]);
                        }
                    }
                    // open the file for reading and writing and go to tag
                    writefile = fopen(argv[1],"r+b");
                    fseek(writefile,-128,SEEK_END);
                    // write the tag then closes the file.
                    fwrite(&tag,1,128,writefile);
                    fclose(writefile);

                }
                else { // no tag
                    //empty all fields, fill with 0 bytes
                    strncpy(tag.identifier,"TAG",3);
                    strncpy(tag.title,"",30);
                    strncpy(tag.artist,"",30);
                    strncpy(tag.album,"",30);
                    strncpy(tag.year,"",4);
                    strncpy(tag.comment,"",28);
                    tag.separator = '\0';
                    tag.track = atoi("");
                    tag.genre = atoi("");

                    // Loop to check to see if there are tags to be set
                    for (count = 2;count < argc;count++) {
                        if ((strcmp(argv[count],"-title")) == 0){
                            count++;
                            strncpy(tag.title,argv[count],30);
                        }
                        else if ((strcmp(argv[count],"-artist")) == 0){
                            count++;
                            strncpy(tag.artist,argv[count],30);
                        }
                        else if ((strcmp(argv[count],"-album")) == 0){
                            count++;
                            strncpy(tag.album,argv[count],30);
                        }
                        else if ((strcmp(argv[count],"-year")) == 0){
                            count++;
                            strncpy(tag.year,argv[count],4);
                        }
                        else if ((strcmp(argv[count],"-comment")) == 0){
                            count++;
                            strncpy(tag.comment,argv[count],28);
                        }
                        else if ((strcmp(argv[count],"-track")) == 0){
                            count++;
                            tag.track = atoi(argv[count]);
                        }
                    }
                    // open file for appending
                    writefile = fopen(argv[1],"ab");
                    // write the tag then closes the file.
                    fwrite(&tag,1,128,writefile);
                    fclose(writefile);
                }
                // Print new ID3v1.1 data
                printf("\nNew ID3v1.1 data:\n");
                printf("\nIdentifier: %.3s\n",tag.identifier);
                printf("Title: %.30s\n",tag.title);
                printf("Artist: %.30s\n",tag.artist);
                printf("Album: %.30s\n",tag.album);
                printf("Year: %.4s\n",tag.year);
                printf("Comment: %.28s\n",tag.comment);
                printf("Track number: %d\n",tag.track);
                printf("Genre: %d\n\n",tag.genre);
            }
        }
	}
	return 0;
}
