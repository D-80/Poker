#ifndef CARD_H
#define CARD_H
#include<iostream>

using namespace std;

class Card{
	public:

//METHODS FOR AESTHETICS
	void viewCard(){
		viewRank();
		viewSuit();
	}

	void nl(){
		cout<<"\n";
	}

//METHODS FOR RANKS
	void setRank(int x){
		rank = x;
	}

	int getRank(){
		return rank;
	}
	
	void viewRank(){
		if(rank > 1 && rank < 11){
			cout<<rank<<" ";
		}
		else if(rank == 11){
			cout<<"Jack ";
		}
		else if(rank == 12){
			cout<<"Queen ";
		}		
		else if(rank == 13){
			cout<<"King ";
		}
		else if(rank == 14){
			cout<<"Ace ";
		}
		else{cout<<"invalid ";}
	}

//METHODS FOR SUITS
	void setSuit(char x){
		suit = x;
	} 
	
	char getSuit(){
		return suit;
	}
	
	void viewSuit(){
		if(suit == 'c'){
			cout<<"of Clubs";
		}
		else if(suit == 'd'){
			cout<<"of Diamonds";
		}
		else if(suit == 'h'){
			cout<<"of Hearts";
		}
		else if(suit == 's'){
			cout<<"of Spades";
		}
		else{
			cout<<"invalid ";
		}
	}

//VARIABLES
	protected:
	int rank;
	char suit; 
};

#endif//CARD_H
