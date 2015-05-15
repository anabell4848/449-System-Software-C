/*
Hanyu Xiong
CS 449 Project 1 part 1

Mastermind. In this game, the computer chooses 4 pegs each with one of 6 colors.
The player’s job is then to guess the colors that the computer has chosen in the proper order.
After each guess by the player, the computer will then give two numbers as feedback.
The first number is how many pegs are the proper color and in the proper position.
The second number is how many pegs are the proper color, but not in the correct position.

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    //declarations
    const int size =4;
	int i, j, guesscount=1, win=0, correctplace, wrongplace, used1, used2, used3, used4;
	int Rcount=0, Bcount=0, Gcount=0, Ycount=0, Pcount=0, Ocount=0;
	char play[20];
	int table[size];
	char code[size];
	char string[100];
	char yess[] = "yes\0";

	while (strcmp(play,yess) != 0){
        printf("Welcome to Mastermind! \nWould you like to play? ");
        scanf("%s", play);
        play[4]="\0";
	}
    printf("\n");

    srand((unsigned int)time(NULL));  //random int seed

	//generate 4 random integers
	for (i=0;i<size;i++){
		int value = rand() % (size - 1 + 1) + 1;
		table[i]= value;
	}

    //use random integers to make random colors table
	for (i=0;i<size;i++){
        if (table[i]==1){
            code[i]='r';
            Rcount++;
        }
        if (table[i]==2){
            code[i]='b';
            Bcount++;
        }
        if (table[i]==3){
            code[i]='g';
            Gcount++;
        }
        if (table[i]==4){
            code[i]='y';
            Ycount++;
        }
        if (table[i]==5){
            code[i]='p';
            Pcount++;
        }
        if (table[i]==6){
            code[i]='o';
            Ocount++;
        }
        //printf("%c", code[i]);
    }

//asks user for guess, until they get it right, or after 10 guesses
	while (win==0){
		printf("Enter guess number %d: ", guesscount);
		scanf("%s", string);

        //determine how many are in correct place, wrong place, and if it's completely correct
        win=1;
        correctplace=0;
        wrongplace=0;
        used1=10;
        used2=10;
        used3=10;
        used4=10;
        for (i=0;i<size;i++){
            if (string[i]==code[i]){
                correctplace++;
            }
            else{
                win=0;
                for(j=0;j<size;j++){
                    if (string[i]==code[j]&& string[j]!=code[j] && j!=used1 && j!=used2 && j!=used3){
                        if (used1==10){
                            used1=j;
                            wrongplace++;
                        }
                        else if(used2==10){
                            used2=j;
                            wrongplace++;
                        }
                        else if (used3==10){
                            used3=j;
                            wrongplace++;
                        }else if (used4==10){
                            used4=j;
                            wrongplace++;
                        }
                        break;
                    }
                }
            }
        }
		if (win==1){
            printf("Congratulations! You after %d tries\n", guesscount);
			break;
        }
        printf("Colors in the correct place: %d\n", correctplace);
        printf("Colors correct but in wrong position: %d\n", wrongplace);
        if (guesscount==10){
            printf("\nSorry, you reached 10 tries, the maximum number. You Lose.\n");
			break;
        }

        //output correct

        //increment count
		guesscount++;
		printf("\n");
	}
    return 0;
}
