#include <iostream>
#include "Card.h"
#include "Croupier.h"
#include "Player.h"
#include "Table.h"

using namespace std;

int main (int argc, char *argv[])
{

//	ADD INTERFACE, NETWORKING, AI

	//GAMEPLAY VARIABLES
	int twoSeconds = 2000000;
	int oneSecond = 1000000;
	int drawingTime = 50000;
	int nofCards = 7;

	//PREPARING TABLE
	Table green; 
	green.setGame(4,15000,50); 

	//NETWORKING
	
	green.play();


//	5-CARD HANDS TEST
/*
	//PREPARING CARDS
	Croupier filip;  
	filip.assembleDeck();	
	filip.shuffleDeck();

	string player1{'P','l','a','y','e','r','1'};
	string player2{'P','l','a','y','e','r','2'};
	int p1 = 0; 
	int p2 = 1; 

	cout<<"\nHow many cards?\n";
	cin>>nofCards;

	filip.nl();

	cout<<player1<<":\n\n";
//	filip.drawCards(0,nofCards,p1);
//	filip.viewDrawCard(0,nofCards,p1,0);
//	filip.viewDrawCard(0,nofCards,p1,1);
//	filip.viewDrawCard(0,nofCards,p1,2);
//	filip.viewDrawCard(0,nofCards,p1,3);
//	filip.viewDrawCard(0,nofCards,p1,4);
//	filip.viewDrawCard(0,nofCards,p1,5);
//	filip.viewDrawCard(0,nofCards,p1,6);
	filip.viewDrawCards(drawingTime,0,nofCards,p1); 

	filip.nl();

	cout<<player2<<":\n\n";
//	filip.drawCards(0,nofCards,p2);
//	filip.viewDrawCard(0,nofCards,p2,0);
//	filip.viewDrawCard(0,nofCards,p2,1);
//	filip.viewDrawCard(0,nofCards,p2,2);
//	filip.viewDrawCard(0,nofCards,p2,3);
//	filip.viewDrawCard(0,nofCards,p2,4);
	filip.viewDrawCards(drawingTime,0,nofCards,p2);

	filip.nl();

	cout<<player1<<":\n";
	filip.callHand(0,nofCards,p1);
	
	cout<<player2<<":\n";
	filip.callHand(0,nofCards,p2);

	filip.callWinningHand(0,nofCards,p1,p2,player1,player2);
*/


return 0;
}
