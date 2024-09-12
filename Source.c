#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // in order to use the "rand" and "srand" functions
#include <time.h>	// in order to use "time" function

#define FULL_NAME 21
#define FIRST_Card 4
#define TYPE_CARD 10
#define INITIAL_Card 4
#define ALL_CARDS 14

typedef struct {
	int num;
	char color;
	char type[TYPE_CARD];
}Card;

typedef struct {
	char name[FULL_NAME];
	Card* hand;
	int logicalSize;
	int physicalSize;
}Player;

typedef struct {
	char type[TYPE_CARD];
	int amount;

}Statistic;


void getNames(Player* PlayerArry, int numOfPlayer);
void distributionCard(int numOfCard, int numOfPlayers, Player* PlayerArry);
int firstCard(Card *color);
void printFirstCard(int num, Card color);
void printPlayerCards(Player* PlayerArry, int whichPlayer);
void regularCard(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard);
void printUpperCard(Card* upperCard);
void addPhysicalCard(Player* PlayerArry, int whichPlayer);
void newCard(Player* PlayerArry, int whichPlayer, int indexCard, Statistic* pStatistic);
void addCardToPack(Player* PlayerArry, int whichPlayer, Statistic* pStatistic);
void putDownACard(Player* PlayerArry, int whichPlayer, int indCard);
bool cheackingValidtionCard(Player* PlayerArry, Card* currentCard, int newPlayer, int newCard);
char colorCard(Player* PlayerArry, Card* currentCard,Card *upperCard, int whichPlayer, int whichCard);
void colorCardForTaki(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard);
int takiCard(Player* PlayerArry, Card *upperCard, int whichPlayer, int whichCard);
void stopCard(Player* PlayerArry, Card* currentCard, Card *upperCard, int whichPlayer, int whichCard);
int plusCard(Player* PlayerArry, Card* currentCard, Card *upperCard, int whichPlayer, int whichCard);
void changDirectionCard(Player* PlayerArry, Card* currentCard, Card *upperCard, int whichPlayer, int whichCard);
bool selectCard(Player* PlayerArry, Card* currentCard, Card *upperCard, Card* comper, int howManyPlayers, int* whichPlayer, int* count, Statistic* pStatistic);
void connvert(Statistic *pStatistic);
void sort(Statistic *pStatistic);
void printArray(Statistic *pStatistic);
void freeAllMalloc(Player* player, int numOfPlayers);

void main() {
	srand(time(NULL));
	int numOfPlayers, numOfFirstCard = 0, i=0,count=0,x;
	
	Player *PlayerArry = NULL;
	Card *upperCard = NULL;
	Card *currentCard = NULL,color;
	Card *comper = NULL;
	bool winner = false;
	Statistic* pStatistic = NULL;
	
	
	
	currentCard = &color;
	upperCard = &color;
	
	pStatistic = (Statistic*)malloc(ALL_CARDS * sizeof(Statistic));
	if (!pStatistic)
	{
		exit(1);
	}

	for (x = 0; x < ALL_CARDS; x++)
	{
		pStatistic[x].amount = 0;
	}


	printf("************ Welcome to TAKI game !!! ************\n");
	printf("Please enter the number of Player:\n");
	scanf("%d",&numOfPlayers);

	PlayerArry = (Player*)malloc(numOfPlayers+1 * sizeof(Player));
	
	if (!PlayerArry)
	{
		exit(1);
	}

	getNames(PlayerArry, numOfPlayers);
	distributionCard(INITIAL_Card, numOfPlayers, PlayerArry);
	numOfFirstCard = firstCard(&color);
	printFirstCard(numOfFirstCard, color);
	 
	upperCard->color = color.color;
	upperCard->num = numOfFirstCard;
	currentCard->color = color.color;


	while (winner == false)
	{
		winner = selectCard(PlayerArry, currentCard, upperCard, comper, numOfPlayers, &i, &count,pStatistic);
		if (winner)
		{
			printf("The Winner is...%s! Congratulations!",PlayerArry[i].name);
			break;
		}
		if (count%2==0){
			i++;
			if (i==numOfPlayers){
				i = 0;
			}
		}
		else{
			i--;
			if (i<0){
				i = numOfPlayers - 1;
			}
		}
	 }
	connvert(pStatistic, pStatistic);
	sort(pStatistic);
	printArray(pStatistic);	

	free(pStatistic);
	freeAllMalloc(PlayerArry, numOfPlayers);
	free(PlayerArry);
}

void getNames(Player* PlayerArry, int numOfPlayer)
{
	int i;
	for (i = 0; i < numOfPlayer; i++)
	{
		printf("Please enter the first name of player #%d:\n", i + 1);
		scanf("%s", PlayerArry[i].name);
		printf("\n");
	}
}
void distributionCard(int numOfCard, int numOfPlayers, Player* PlayerArry)
{
	int i, j, num = 0;
	char color;

	for (i = 0; i < numOfPlayers; i++)
	{
		PlayerArry[i].hand = (Card*)malloc(numOfCard * sizeof(Card));
		if (PlayerArry[i].hand == NULL)
		{
			exit(1);
		}
		for (j = 0; j < numOfCard; j++) {
			num = rand() % 14;
			if (num != 0) {
				color = rand() % 4;
				switch (color) {
				case 0://0=G it will get the color Green//
					PlayerArry[i].hand[j].color = 'G';
					break;
				case 1://1=B it will get the color Blue//
					PlayerArry[i].hand[j].color = 'B';
					break;
				case 2://2=R it will get the color Red//
					PlayerArry[i].hand[j].color = 'R';
					break;
				case 3://3=Y it will get the color Yellow//
					PlayerArry[i].hand[j].color = 'Y';
					break;
				default:
					break;
				}
				if (num > 0 && num < 10) {
					PlayerArry[i].hand[j].num = num;
				}
				else {
					switch (num) {
					case 10:
						strcpy(PlayerArry[i].hand[j].type, "   +   ");
						break;
					case 11:
						strcpy(PlayerArry[i].hand[j].type, "  STOP ");
						break;
					case 12:
						strcpy(PlayerArry[i].hand[j].type, "  <->  ");
						break;
					case 13:
						strcpy(PlayerArry[i].hand[j].type, "  TAKI ");
						break;
					default:
						break;
					}
				}
			}
			else if (num == 0) {
				strcpy(PlayerArry[i].hand[j].type, " COLOR ");
			}
		}
		PlayerArry[i].logicalSize = numOfCard;
		PlayerArry[i].physicalSize = numOfCard;
	}
}
int firstCard(Card *color)
{
	int num = 0, numForColor = 0;
	srand(time(NULL));

	num = 1 + rand() % 9;
	numForColor = rand() % 4;
	switch (numForColor) {
	case 0://0=G it will get the color Green//
		color->color = 'G';
		break;
	case 1://1=B it will get the color Blue//
		color->color = 'B';
		break;
	case 2://2=R it will get the color Red//
		color->color = 'R';
		break;
	case 3://3=Y it will get the color Yellow//
		color->color = 'Y';
		break;
	default:
		break;
	}

	return num;
}
void printFirstCard(int num, Card color)
{

	printf("Upper card:\n");
	printf("*********\n");
	printf("*       *\n");
	printf("*   %d   *\n", num);
	printf("*   %c   *\n", color.color);
	printf("*       *\n");
	printf("*********\n");
}
void printPlayerCards(Player* PlayerArry, int whichPlayer)
{

	int j, i = 0;

	i = whichPlayer;

	/*printf("p%d's turn:\n", i + 1);*/
	for (j = 0; j < PlayerArry[i].logicalSize; j++) {
		if (PlayerArry[i].hand[j].num >= 1 && PlayerArry[i].hand[j].num <= 9) {

			printf("card #%d:\n", j + 1);
			printf("*********\n");
			printf("*       *\n");
			printf("*   %d   *\n", PlayerArry[i].hand[j].num);
			printf("*   %c   *\n", PlayerArry[i].hand[j].color);
			printf("*       *\n");
			printf("*********\n");
		}
		else if (strcmp(PlayerArry[i].hand[j].type, " COLOR ") == 0) {

			printf("card #%d:\n", j + 1);
			printf("*********\n");
			printf("*       *\n");
			printf("*%s*\n", PlayerArry[i].hand[j].type);
			printf("*       *\n");
			printf("*       *\n");
			printf("*********\n");
		}
		else {
			printf("card #%d:\n", j + 1);
			printf("*********\n");
			printf("*       *\n");
			printf("*%s*\n", PlayerArry[i].hand[j].type);
			printf("*   %c   *\n", PlayerArry[i].hand[j].color);
			printf("*       *\n");
			printf("*********\n");
		}
	}
}
void printUpperCard(Card* upperCard)
{
	if (upperCard->num>= 1 && upperCard->num <= 9) {

		printf("Upper card:\n");
		printf("*********\n");
		printf("*       *\n");
		printf("*   %d   *\n", upperCard->num);
		printf("*   %c   *\n", upperCard->color);
		printf("*       *\n");
		printf("*********\n");
	}
	else if (strcmp(upperCard->type, " COLOR ") == 0) {

		printf("Upper card:\n");
		printf("*********\n");
		printf("*       *\n");
		printf("*%s*\n", upperCard->type);
		printf("*   %c   *\n", upperCard->color);
		printf("*       *\n");
		printf("*********\n");
	}
	else {
		printf("Upper card:\n");
		printf("*********\n");
		printf("*       *\n");
		printf("*%s*\n", upperCard->type);
		printf("*   %c   *\n", upperCard->color);
		printf("*       *\n");
		printf("*********\n");
	}
}
void addPhysicalCard(Player* PlayerArry, int whichPlayer)
{
	int  i = 0;
	Card* tempCards = NULL;
	i = whichPlayer;

	PlayerArry[i].physicalSize *= 2;
	tempCards = realloc(PlayerArry[i].hand, PlayerArry[i].physicalSize * sizeof(Card));
	if (tempCards == NULL)
		exit(1);
	else
		PlayerArry[i].hand = tempCards;
}
void newCard(Player* PlayerArry, int whichPlayer, int indexCard, Statistic* pStatistic)
{
	int i, j, num = 0;
	
	char color;
	i = whichPlayer;
	j = indexCard;
	num = rand() % 14;
	pStatistic[num].amount += 1;

	if (num != 0) {
		color = rand() % 4;
		switch (color) {
		case 0://0=G it will get the color Green//
			PlayerArry[i].hand[j].color = 'G';
			break;
		case 1://1=B it will get the color Blue//
			PlayerArry[i].hand[j].color = 'B';
			break;
		case 2://2=R it will get the color Red//
			PlayerArry[i].hand[j].color = 'R';
			break;
		case 3://3=Y it will get the color Yellow//
			PlayerArry[i].hand[j].color = 'Y';
			break;
		default:
			break;
		}
		if (num > 0 && num < 10) {
			PlayerArry[i].hand[j].num = num;
		}
		else {
			switch (num) {
			case 10:
				strcpy(PlayerArry[i].hand[j].type, "   +   ");
				break;
			case 11:
				strcpy(PlayerArry[i].hand[j].type, "  STOP ");
				break;
			case 12:
				strcpy(PlayerArry[i].hand[j].type, "  <->  ");
				break;
			case 13:
				strcpy(PlayerArry[i].hand[j].type, "  TAKI ");
				break;
			default:
				break;
			}
		}
		PlayerArry[i].logicalSize++;
	}
	else if (num == 0) {
		strcpy(PlayerArry[i].hand[j].type, " COLOR ");
		PlayerArry[i].logicalSize++;
	}
	
}
void addCardToPack(Player* PlayerArry, int whichPlayer, Statistic* pStatistic)
{
	int i = 0;
	i = whichPlayer;

	if (PlayerArry[i].logicalSize == PlayerArry[i].physicalSize)
		addPhysicalCard(PlayerArry, whichPlayer);
	newCard(PlayerArry, whichPlayer, PlayerArry[i].logicalSize, pStatistic);


}
void putDownACard(Player* PlayerArry, int whichPlayer, int indCard)
{
	int i, j;
	i = whichPlayer;

	if (PlayerArry[i].logicalSize-1 == indCard) {
		PlayerArry[i].logicalSize--;

	}
	else {
		for (j = indCard; j < PlayerArry[i].logicalSize - 1; j++) {
			PlayerArry[i].hand[j] = PlayerArry[i].hand[j + 1];
		}
		PlayerArry[i].logicalSize--;
	}
}
char colorCard(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard)
{
	int choise, i, j;
	char selectColor;


	i = whichPlayer;
	j = whichCard;

	printf("Please enter your color choice:\n");
	printf("1 - Yellow\n");
	printf("2 - Red\n");
	printf("3 - Blue\n");
	printf("4 - Green\n");
	scanf("%d", &choise);

	switch (choise) {
	case 1:
		selectColor = 'Y';
		break;
	case 2:
		selectColor = 'R';
		break;
	case 3:
		selectColor = 'B';
		break;
	case 4:
		selectColor = 'G';
		break;
	default:
		break;
	}
	upperCard->color = selectColor;
	strcpy(upperCard->type, PlayerArry[i].hand[j].type);
	upperCard->num = PlayerArry[i].hand[j].num;

	printUpperCard(upperCard);
	

	currentCard->color = selectColor;

	putDownACard(PlayerArry, whichPlayer, whichCard);

	return selectColor;
}
void colorCardForTaki(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard)
{
	int choise, i, j;
	char selectColor;


	i = whichPlayer;
	j = whichCard;

	printf("Please enter your color choice:\n");
	printf("1 - Yellow\n");
	printf("2 - Red\n");
	printf("3 - Blue\n");
	printf("4 - Green\n");
	scanf("%d", &choise);

	switch (choise) {
	case 1:
		selectColor = 'Y';
		break;
	case 2:
		selectColor = 'R';
		break;
	case 3:
		selectColor = 'B';
		break;
	case 4:
		selectColor = 'G';
		break;
	default:
		break;
	}
	upperCard->color = selectColor;
	strcpy(upperCard->type, PlayerArry[i].hand[j].type);
	upperCard->num = PlayerArry[i].hand[j].num;

	printUpperCard(upperCard);


	currentCard->color = selectColor;
}
int takiCard(Player* PlayerArry, Card* upperCard, int whichPlayer, int whichCard)
{
	int i = 0, j = 0,selectNum;
	i = whichPlayer;
	j = whichCard;
	
	upperCard->color = PlayerArry[i].hand[j].color;
	strcpy(upperCard->type, PlayerArry[i].hand[j].type);
	upperCard->num = PlayerArry[i].hand[j].num;
	printUpperCard(upperCard);

	putDownACard(PlayerArry, i, j);
	printf("%s's turn:\n", PlayerArry[i].name);
	printPlayerCards(PlayerArry, i);
	printf("Please enter 0 if you want to finish your turn\n");
	printf("or 1 - %d if you want to put one of your cards in the middle:\n", PlayerArry[i].logicalSize);
	scanf("%d", &selectNum);

	return selectNum;
}
void stopCard(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard)
{
	int i = 0, j = 0;
	i = whichPlayer;
	j = whichCard;

	upperCard->color = PlayerArry[i].hand[j].color;
	strcpy(upperCard->type, PlayerArry[i].hand[j].type);
	upperCard->num = PlayerArry[i].hand[j].num;
	printUpperCard(upperCard);

	putDownACard(PlayerArry, i, j);
}
int plusCard(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard)
{
	int i = 0, j = 0;
	i = whichPlayer;
	j = whichCard;

	upperCard->color = PlayerArry[i].hand[j].color;
	strcpy(upperCard->type, PlayerArry[i].hand[j].type);
	upperCard->num = PlayerArry[i].hand[j].num;
	printUpperCard(upperCard);

	putDownACard(PlayerArry, whichPlayer, whichCard);

	return i - 1;
}
void changDirectionCard(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard)
{
	int i = 0, j = 0;
	i = whichPlayer;
	j = whichCard;

	upperCard->color = PlayerArry[i].hand[j].color;
	strcpy(upperCard->type, PlayerArry[i].hand[j].type);
	upperCard->num = PlayerArry[i].hand[j].num;
	printUpperCard(upperCard);

	putDownACard(PlayerArry, whichPlayer, whichCard);

}
void regularCard(Player* PlayerArry, Card* currentCard, Card* upperCard, int whichPlayer, int whichCard)
{
	int i = 0, j = 0;
	i = whichPlayer;
	j = whichCard;

	upperCard->color = PlayerArry[i].hand[j].color;
	upperCard->num = PlayerArry[i].hand[j].num;
	printUpperCard(upperCard);

	putDownACard(PlayerArry, whichPlayer, whichCard);
}
bool cheackingValidtionCard(Player* PlayerArry, Card *currentCard, int newPlayer, int newCard)
{
	int i,m;
	i = newPlayer;
	m = newCard;
	if (PlayerArry[i].logicalSize > m)
	{
		if (strcmp(PlayerArry[i].hand[m].type, " COLOR ") == 0) {
			strcpy(currentCard->type, " COLOR ");
			return true;
		}
		else if (currentCard->color == PlayerArry[i].hand[m].color) {
			currentCard->color = PlayerArry[i].hand[m].color;

			return true;
		}
		else
			return false;
	}
	else
		return false;
}
bool selectCard(Player* PlayerArry, Card *currentCard ,Card *upperCard, Card* comper,int howManyPlayers ,int *whichPlayer, int *count, Statistic* pStatistic)
{
	int *i=NULL, j = 0, addCard = 1, playerChoice;
	char chosenColor;
	i = whichPlayer;
	
	
	printf("%s's turn:\n", PlayerArry[*i].name);
	printPlayerCards(PlayerArry, *i);
	printf("Please enter 0 if you want to take a card from the deck\n");
	printf("or 1 - %d if you want to put one of your cards in the middle:\n", PlayerArry[*i].logicalSize);
	scanf("%d", &playerChoice);

	if (playerChoice != 0)
	{
		j = playerChoice - 1;

		while (cheackingValidtionCard(PlayerArry, currentCard, *i, j) == false) {

			printf("Inavlid card! Try again.\n");
			printf("Please enter 0 if you want to take a card from the deck\n");
			printf("or 1 - %d if you want to put one of your cards in the middle:\n", PlayerArry[*i].logicalSize);
			scanf("%d", &playerChoice);
			if (playerChoice==0)
			{
				break;
			}
		}
		j = playerChoice - 1;
		if (j != -1) {
			if (strcmp(PlayerArry[*i].hand[j].type, " COLOR ")==0) {
				chosenColor = colorCard(PlayerArry, currentCard,upperCard, *i, j);
				if (PlayerArry[*i].logicalSize == 0)
					return 1;
				else
					return 0;
				

			}
			else if (strcmp(PlayerArry[*i].hand[j].type, "  TAKI ") == 0) {
				addCard = takiCard(PlayerArry, upperCard, *i, j);
				
				while (addCard != 0) {
					addCard -= 1;
					cheackingValidtionCard(PlayerArry, currentCard, *i, addCard);
					if (strcmp(upperCard->type," COLOR ") == 0){
						colorCardForTaki(PlayerArry, currentCard, upperCard, *i, j);
						break;
					}
					addCard = takiCard(PlayerArry, upperCard, *i, addCard);
					
					if (PlayerArry[*i].logicalSize == 0)
						return 1;
					
				}
				if (addCard==0)
				{
					if (strcmp(upperCard->type, "  STOP ") == 0) {
						if (*i == howManyPlayers)
							*i = 0;
						else
							*i += 1;
					}
					if (strcmp(upperCard->type, " COLOR ") == 0) {
						colorCardForTaki(PlayerArry, currentCard, upperCard, *i, j);
					}
					else if (strcmp(upperCard->type, "  <->  ") == 0) {
						*count += 1;
					}
					else if (strcmp(upperCard->type, "   +   ") == 0) {
						*i -= 1;
						if (PlayerArry[*i].logicalSize == 0) {
							addCardToPack(PlayerArry, *i, pStatistic);
							return 0;
						}
					}
				}
				if (PlayerArry[*i].logicalSize == 0)
					return 1;
				else
					return 0;
			}
			else if (strcmp(PlayerArry[*i].hand[j].type, "  STOP ") == 0) {
				stopCard(PlayerArry, currentCard, upperCard, *i, j);
				
				if (*i == howManyPlayers)
					*i = 0;
				else
					*i += 1;

				if (PlayerArry[*i].logicalSize == 0) {
					if (howManyPlayers == 2) {
						addCardToPack(PlayerArry, *i, pStatistic);
						return 0;
					}
					return 1;
				}
				else
					return 0;

			}
			else if (strcmp(PlayerArry[*i].hand[j].type, "  <->  ") == 0) {
				changDirectionCard(PlayerArry, currentCard, upperCard, *i, j);
				*count+=1;
				if (PlayerArry[*i].logicalSize == 0)
					return 1;
				else
					return 0;
			}
			else if (strcmp(PlayerArry[*i].hand[j].type, "   +   ") == 0) {
				*i = plusCard(PlayerArry, currentCard, upperCard, *i, j);
				if (PlayerArry[*i].logicalSize == 0) {
					addCardToPack(PlayerArry, *i, pStatistic);
					return 0;
				}
			}
			else if (PlayerArry[*i].hand[j].num>=1 || PlayerArry[*i].hand[j].num <= 9) {
				regularCard(PlayerArry, currentCard, upperCard, *i, j);
				if (PlayerArry[*i].logicalSize == 0)
					return 1;
				else
					return 0;
			}
		}
		else if (j == -1) {
			printUpperCard(upperCard);
			addCardToPack(PlayerArry, *i, pStatistic);
			return 0;
		}
	}
	else {
		printUpperCard(upperCard);
		addCardToPack(PlayerArry,*i, pStatistic);
		return 0;
	}
}
void connvert(Statistic* pStatistic)
{
	
	int i;

	for  (i = 0;i < ALL_CARDS; i++)
	{
		switch (i) {

		case 0:
			strcpy(pStatistic[i].type," COLOR ");
			
			break;
		case 1:
			strcpy(pStatistic[i].type,"   1   ");
			break;
		case 2:
			strcpy(pStatistic[i].type,"   2   ");
			break;
		case 3:
			strcpy(pStatistic[i].type, "   3   ");
			break;
		case 4:
			strcpy(pStatistic[i].type, "   4   ");
			break;
		case 5:
			strcpy(pStatistic[i].type, "   5   ");
			break;
		case 6:
			strcpy(pStatistic[i].type, "   6   ");
			break;
		case 7:
			strcpy(pStatistic[i].type, "   7   ");
			break;
		case 8:
			strcpy(pStatistic[i].type, "   8   ");
			break;
		case 9:
			strcpy(pStatistic[i].type, "   9   ");
			break;
		case 10:
			strcpy(pStatistic[i].type, "   +   ");
			break;
		case 11:
			strcpy(pStatistic[i].type, "  STOP ");
			break;
		case 12:
			strcpy(pStatistic[i].type, "  <->  ");
			break;
		case 13:
			strcpy(pStatistic[i].type, "  TAKI ");
			break;
		default:
			break;
		}
	
	}


}
void sort(Statistic* pStatistic)
{

	Statistic tempS[ALL_CARDS];
	int tempI;
	// loop to access each array element
	for (int step = 0; step < ALL_CARDS - 1; ++step) {

		// loop to compare array elements
		for (int i = 0; i < ALL_CARDS - step - 1; ++i) {
			if (pStatistic[i].amount > pStatistic[i + 1].amount) {
				tempI = pStatistic[i].amount;
				strcpy(tempS[i].type, pStatistic[i].type);
				pStatistic[i].amount = pStatistic[i + 1].amount;
				strcpy(pStatistic[i].type, pStatistic[i+1].type);
				pStatistic[i + 1].amount = tempI;
				strcpy(pStatistic[i+1].type, tempS[i].type);
			}
		}
	}	
}
void printArray(Statistic* pStatistic)
{
	int i;

	printf("************ Game Statistics ************\n");
	printf("Card # | Frequency\n");
	printf("__________________\n");
	for (i = 13; i >= 0; i--) {
		printf("%s|     %d     \n", pStatistic[i].type, pStatistic[i].amount);
	}
}
void freeAllMalloc(Player* player, int numOfPlayers)
{
	for (int i = 0; i < numOfPlayers; i++)
	{
		free(player[i].hand);
	}
	free(player->hand);

}
