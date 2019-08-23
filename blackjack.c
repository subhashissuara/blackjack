/*
	Made by Subhashis Suara
*/

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
	To prevent repeating of cards:

	type ->
	1 - Spades
	2 - Hearts
	3 - Diamonds
	4 - Clubs

	number ->
	1 to 13
*/
struct card
{
	int type;
	int number;
};

// Array to keep track and avoid of repeating cards
struct card noRepeat[30];
int noRepeat_counter = 0;

int givePoint();
int cardRound(int players[], int size);
int randfor2();
bool checkDisqualify(int points);
bool checkWin(int points);
bool checkRepeat(struct card card_);
int printType(struct card card_);

int main(){
	int players[2] = {0}, size = 2;
	bool flag = true;
	int points = 0;
	srand (time(NULL));
	cardRound(players, size);
	cardRound(players, size);
	char choice;
	while(flag){
	for(int i = 0; i < size; i++){
		if(checkDisqualify(players[i])){
			if(i == (size - 1)){
				if(checkDisqualify(players[i - 1])){
					printf("\nNo one won the game!\n");
					flag = false;
					break;
				}
				else
				{
					printf("Player %d exceeded 21 points and got disqualified!\n", i + 1);
					printf("Player %d won with %d points!\n", i, players[i - 1]);
					flag = false;
					break;
				}
				
			}
			else{
				if(checkDisqualify(players[i + 1])){
					printf("No one won the game!\n");
					flag = false;
					break;
				}
				else
				{	
					printf("Player %d exceeded 21 points and got disqualified!\n", i + 1);
					printf("Player %d won with %d points!\n", i + 2, players[i + 1]);
					flag = false;
					break;
				}
			}
		}
		
		if(checkWin(players[i])){
			printf("blackjack! Player %d won with %d points!\n", i + 1, players[i]);
			flag = false;
			break;
		}
		printf("\nPlayer %d -> %d points!\n", i + 1, players[i]);
		printf("Do you want to hit, player %d? y or n\n", i + 1);
	    scanf(" %c", &choice);
		if(choice == 'y' || choice == 'Y'){
			points = givePoint();
			players[i] += points;
		}
		else if(choice == 'n' || choice == 'N')
			continue;
		else{
			printf("Invalid input!\n");
			flag = false;
			break;
		}

	}
	}
	return 0;
}
/*
Gives random between 2 given number
1 - returns 1 points
2 - returns 11 points
*/
int randfor2(){
	int chosen = ((rand()) % (2 - 1 + 1) + 1);
	if(chosen == 1)
		return 1;
	else if(chosen == 2)
		return 11;
}

// Checks so that cards are not repeated
bool checkRepeat(struct card card_){
	for(int i = 0; i < 30; i = i + 2){
		if(card_.type == noRepeat[i].type && card_.type == noRepeat[i].type)
			return true;
	noRepeat[noRepeat_counter].type = card_.type;
	noRepeat[noRepeat_counter + 1].number = card_.number;
	noRepeat_counter = noRepeat_counter + 2;
	return false;
	}
}

// Gets the card and returns the point
int givePoint(){
	int random_number = rand();
	int lwr = 1, upr = 4;
	struct card card_;
	card_.type = ((random_number) % (upr - lwr + 1)) + lwr;
	lwr = 1, upr = 13;
	card_.number = ((random_number) % (upr - lwr + 1)) + lwr;
	if(checkRepeat(card_)){
		givePoint();
	}
	else
	{	
		if(card_.number < 11){
			if(card_.number == 1){
				int chosen = randfor2();
				return chosen;
			}		
			return card_.number;
		}
		else
			return 10;
	}
	
}

// Checks if a player has more than 21 points
bool checkDisqualify(int points){
	if(points > 21)
		return true;
	else
		return false;
}

// Checks if a player has 21 points and won
bool checkWin(int points){
	if(points == 21)
		return true;
	else
		return false;
}

// To assign cards and points to players every round
int cardRound(int players[], int size){
	int points = 0;
	for(int i = 0; i < size; i++){
		points = givePoint();
		players[i] += points;
	}
}
/*
// To print card if required
int printCard(struct card card_){
	char Picture[1];
	bool pic;
	if(card_.number < 11 && card_.number > 1){
		pic = false;
	}
	else if(card_.number == 11){
		pic = true;
		Picture[1] = "Jack";
	}
	else if(card_.number == 12){
		pic = true;
		Picture[1] = "Queen";
	}
	else if(card_.number == 13){
		pic = true;
		Picture[1] = "King";
	}
	else
	{
		pic = true;
		Picture[1] = "Ace";
	}
	
	switch(card_.type){
		case 1:
			if(pic){
				printf("%s of Spades", Picture[1]);
			}
			else{
				printf("%d of Spades", card_.number);
			}
			break;
		case 2:
			if(pic){
				printf("%s of Hearts", Picture[1]);
			}
			else{
				printf("%d of Hearts", card_.number);
			}
			break;
		case 3:
			if(pic){
				printf("%s of Diamonds", Picture[1]);
			}
			else{
				printf("%d of Diamonds", card_.number);
			}
			break;
		case 4:
			if(pic){
				printf("%s of Clubs", Picture[1]);
			}
			else{
				printf("%d of Clubs", card_.number);
			}
			break;
		default:
			break;
	}
}
*/