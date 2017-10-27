#ifndef CROUPIER_H
#define CROUPIER_H
#include <iostream>
#include <ctime> //time
#include <cstdlib> //rand, srand
#include "Card.h" //Card class
//#include <unistd.h>//usleep(usecs) works only on unix systems

using namespace std;

class Croupier{

	public:
	Croupier(){

		srand(time(0));

	}

	void nl(){

		cout<<"\n";

	}

	//GAME CHANGERS	
	void wait(int waitingTime){
		//usleep(waitingTime);
	}

	//CROUPIER'S METHODS

	void assembleDeck(){
	//SUIT OF CLUBS from 0-12 INCLUDED
		for(int i = 0; i < 13; i++){
    			deck[i].setRank(i + 2);
    			deck[i].setSuit('c');
   		}	

	//SUIT OF DIAMONDS from 13-25 INCLUDED    
    		for(int i = 13; i < 26; i++){
    			deck[i].setRank(i + 2 - 13);
    			deck[i].setSuit('d');
    		}

	//SUIT OF HEARTS from 26-38 INCLUDED
    		for(int i = 26; i < 39; i++){
    			deck[i].setRank(i + 2 - 26);
    			deck[i].setSuit('h');
    		}
   	//SUIT OF SPADES from 39-51 INCLUDED
    		for(int i = 39; i < 52; i++){
    			deck[i].setRank(i + 2 - 39);
    			deck[i].setSuit('s');
    		}
	}



	void layoutDeck(int waitingTime){

		for(int i = 0; i < 52; i++){
			deck[i].viewCard();
			//usleep(waitingTime);
			nl();
		}
	}


	void shuffleDeck(){

		Card tempCard;     //->Template for copying values

		srand(time(0));

		for(int i=0; i<52; i++){	
			r = rand()%51;
			
			tempCard.setRank(deck[i].getRank());
			tempCard.setSuit(deck[i].getSuit());
			deck[i] = deck[r];
			deck[r].setRank(tempCard.getRank());
			deck[r].setSuit(tempCard.getSuit());
		}
	}


	void drawCards(int begin, int nOfCards, int playernumber){

		int a = playernumber * 2;     
		int b = playernumber * 2 + 1; 

		if(nOfCards == 1){

			ptr    [0] = &deck [a];  
			ptrptr [0] = ptr   [0];

		}else if(nOfCards == 2){

			ptr    [0] = &deck [a]; 
			ptrptr [0] = ptr   [0];

			ptr    [1] = &deck [b];  
			ptrptr [1] = ptr   [1];

		}else{

			for(int i = begin; i < nOfCards - 2; i++){

				ptr    [i]  = &deck [i];
				ptrptr [i]  = ptr   [i];
			}
		
				ptr    [nOfCards - 1]  = &deck [nOfCards + a]; //hole card 1
				ptrptr [nOfCards - 1]  = ptr   [nOfCards - 1];

				ptr    [nOfCards - 2]  = &deck [nOfCards + b]; //hole card 2
				ptrptr [nOfCards - 2]  = ptr   [nOfCards - 2];

		}
	}	


	void viewDrawCards(int waitingTime, int begin, int nOfCards, int playernumber){

		drawCards(begin,nOfCards,playernumber);

		if(nOfCards == 1) { ptr[0]->viewCard(); nl(); }

		if(nOfCards == 2) { ptr[0]->viewCard(); nl(); ptr[1]->viewCard(); nl(); } 

		if(nOfCards > 2){

			for(int i = begin; i < nOfCards; i++){		
				ptr[nOfCards - i - 1]->viewCard();
				//usleep(waitingTime);
				nl();
			}
		}
	}

	void viewDrawCard(int begin, int nOfCards, int playernumber, int numberofthecard){

		drawCards(begin,nOfCards,playernumber); 

		ptr[nOfCards - numberofthecard - 1]->viewCard();

		nl();

	}


//1. HIGH CARD/////////////////////////////////////////////////////////////////////

	int highCard (int begin, int nOfCards){         //be careful! highCard() analises ptrptr
							//which is aligned using highLow()	
		int x = 0;

		for(int i=begin; i<nOfCards-1; i++){

			int a = ptrptr[i] -> getRank();
			int b = ptrptr[i+1] -> getRank();
			
			if(a>x || b>x){ 
				
				if(a>=b){
					x = a; 
					index[0] = i;
				}
				else{
					x = b;
					index[0] = i+1;
				}
			}			
		}
		return x;
	}	


	void highLow (int begin, int nOfCards){ //function for organising elements high->low

	
		for(int i = begin; i < nOfCards-1; i++){

			highCard(i, (nOfCards));

			ptrptr[nOfCards]     = ptrptr[i]; //ptrptr[nOfCards] = vessel = first card	

			ptrptr[i]            = ptrptr[index[0]]; //ptrptr[i] = highCard[index]
	
			ptrptr[index[0]]     = ptrptr[nOfCards]; //[index] = vessel
	
		}
	}

	
	void callHighCard (int begin, int nOfCards, int player){

		drawCards (nOfCards-2, nOfCards, player);
		highCard (nOfCards-2, nOfCards);

		nl(); nl();

		cout<<"HIGH CARD:\n";

		ptrptr[index[0]] -> viewCard();

		nl();
	}


//2. PAIR//////////////////////////////////////////////////////////////////////////
	bool pair (int begin, int nOfCards){
		
		bool x;
		highLow(begin,nOfCards);
	
		for(int i = begin; i < nOfCards - 1; i++){

			int a = ptrptr[i]->getRank();

			for(int j = i + 1; j < nOfCards; j++){

				int b = ptrptr[j]->getRank();
					
				if(a == b){

					index[0] = i;
					index[1] = j;

					return x = 1;	
				}
			}
		}
		return x = 0;
	} 


	void callPair (int begin, int nOfCards){
		if(pair(begin, nOfCards) == 1){

			cout<<"\nPAIR:\n";
	
			for(int i = 0; i < 2; i++){
				ptrptr[index[i]]->viewCard();nl();
			}
			
			nl();			
	} else{
			cout<<"\nThere is no pair.\n";
			
			nl();
		}
	}	


//3. TWO PAIRS ////////////////////////////////////////////////////////////////////

	bool twoPairs (int begin, int nOfCards){

		bool x;
		highLow(begin,nOfCards);

		if(pair(begin, nOfCards) == 1){

			for(int i = index[1] + 1; i < nOfCards-1; i++){

				int a = ptrptr[i]->getRank();
			
				for(int j = i + 1; j < nOfCards; j++){

					int b = ptrptr[j]->getRank();
					
					if(   (a == b)   &&   ( a != ptrptr[index[0]]->getRank() )   ){

						index[2] = i;
						index[3] = j;
						return x = 1;
					}
				}
			}
		}
		return x = 0;
	}


	void callTwoPairs (int begin, int nOfCards){

		if(twoPairs(begin, nOfCards) == 1){

			callPair(begin, nOfCards);

			cout<<"\nSECOND PAIR:\n";
	
			for(int i = 2; i<4; i++){

				ptrptr[index[i]]->viewCard();nl();

			}
			
			nl();			

		} else{

			cout<<"\nThere isn't a second pair.\n";
			nl();
		}
	}



//4. THREE OF A KIND///////////////////////////////////////////////////////////////


	bool threeOfAKind (int begin, int nOfCards){

		bool x; 
	
		highLow(begin,nOfCards);
	
		for(int i = begin; i < nOfCards - 2; i++){

			int a = ptrptr[i]->getRank();

			for(int j = i+1; j < nOfCards - 1; j++){

				int b = ptrptr[j]->getRank();

				for(int k = j+1; k < nOfCards; k++){
						
					int c = ptrptr[k]->getRank(); 

					if((a == b) && (b == c)){ 
							
						index[4] = i; 
						index[5] = j; 
						index[6] = k; 
						return x = 1;
					}
				}
			}
		}
		return x = 0;
	}	

	
	void callThreeOfAKind (int begin, int nOfCards){

		if(threeOfAKind(begin, nOfCards) == 1){
		
			cout<<"\nTHREE OF A KIND:\n";

			for(int i = 4; i<7; i++){

				ptrptr[index[i]]->viewCard();nl();

			}
			
			nl();			

		}else{

			cout<<"\nThere is no Three of a Kind.\n";	
			nl();
		}
	}


//5.STRAIGHT///////////////////////////////////////////////////////////////////////



	bool straight (int begin, int nOfCards){
	//1. start counting from the highest card. 
	//2. compare highest card to each element. 
	//3. if it satisfies a = b+1 -> nOfStraight++
	//4. if not -> start counting anew. 

		bool x;
		int nOfStraight = 1;
		int i = 0;   
		int j = 0;
    
		highLow(begin, nOfCards);
		int a = ptrptr[0]->getRank(); //start counting from the highest card
		int b;	


		Card ace2[4];	   //->Aces with rank 1 just for Straight
		int nOfAces = 0;

		//BAKING ACES
		for(i = 0; i < nOfCards; i++){
			
			if(ptrptr[i]->getRank() == 14){

				ace2[nOfAces].setRank(1);
				ace2[nOfAces].setSuit(ptrptr[i]->getSuit());
				nOfAces++;
			}
		}
		//ASSIGNING ACES
		for(i = 0; i<nOfAces; i++){
		
			ptrptr[52 + i] = ptrptr[nOfCards+i];
			ptrptr[nOfCards+i] = &ace2[i];
//	TEST----->	ptrptr[nOfCards+i]->viewCard();nl();
		}


		for(i; i<nOfCards + nOfAces; i++){

			for(j = 0; j<nOfCards + nOfAces; j++){ 

				b = ptrptr[j]->getRank(); 
		
				if(a == b+1){

///*			TEST----->*/	nl();cout<<i<<". a = "<<a<<" b = "<<b<<" nOfStraight = "<<(nOfStraight+1);nl(); 
				
				a = b;	 				

					nOfStraight++;
					
					if(nOfStraight == 2){index[0] = j-1; index[1] = j;}
					if(nOfStraight == 3){index[2] = j;}
					if(nOfStraight == 4){index[3] = j;}
					if(nOfStraight == 5){index[4] = j;			
	
					//CLEANING UP ACES
					for(i = 0; i<nOfAces; i++){
			
						ptrptr[nOfCards + i] = ptrptr[52+i];
					}

											return x = 1;

					}

					j = nOfCards; //terminate second loop

				}else if(j == nOfCards-1){

					a = ptrptr[i]->getRank(); 
					
					nOfStraight = 1;
				}		
			}
		}		
		//CLEANING UP ACES
		for(i = 0; i<nOfAces; i++){
			
			ptrptr[nOfCards + i] = ptrptr[52+i];	
	//		ptrptr[nOfCards + i]->viewCard();nl();
		}
			
		return x = 0;
	}



  	
	void callStraight (int begin, int nOfCards){

		if(straight(begin, nOfCards) == 1){
		
			cout<<"\nSTRAIGHT:\n";

			for(int i = 0; i<5; i++){
		
				ptrptr[index[i]]->viewCard(); nl();
			}
			
			nl();			

		}else{

			cout<<"\nThere is no Straight.\n";	
			nl();
		}
	}



//6.FLUSH//////////////////////////////////////////////////////////////////////////
	
	bool flush (int begin, int nOfCards){

		bool x; 
		char color[nOfCards];
		
		highLow(begin,nOfCards);

		for(int i = begin; i < nOfCards; i++){
		
			color[i] = ptrptr[i]->getSuit();
		}

		for(int i = begin; i < nOfCards - 4; i++){
			
			for(int j = i+1; j < nOfCards - 3; j++){
	
				for(int k = j+1; k < nOfCards - 2; k++){
			
					for(int l = k+1; l < nOfCards - 1; l++){
	
						for(int m = l+1; m < nOfCards; m++){

		if( (color[i] == color[j]) && (color[j] == color[k]) && (color[k] == color[l]) && (color[l] == color[m]) ){

								index[0] = i; 
								index[1] = j; 
								index[2] = k; 
								index[3] = l; 
								index[4] = m; 

								return x = 1;
								
							}
						}
					}
				}
			}	
		}
		return x = 0;
	}
	


	void callFlush (int begin, int nOfCards){

		if(flush(begin, nOfCards) == 1){
		
			cout<<"\nFLUSH:\n";

			for(int i = 0; i<5; i++){

				ptrptr[index[i]]->viewCard();nl();

			}			
			nl();
		}else{

			cout<<"\nThere is no Flush.\n";	
			nl();
		}
	}


//7.FULL HOUSE/////////////////////////////////////////////////////////////////////
//if two pair(1) && three of a kind(1) = fullhouse(1)
//three of a kind + pair

	bool fullHouse (int begin, int nOfCards){

		bool x; 

		highLow(begin,nOfCards); 

		if((twoPairs(begin,nOfCards) == 1)  &&  (threeOfAKind(begin,nOfCards) == 1)){
			
			pair(begin,nOfCards); //for indexes

			if(   ( ptrptr[index[0]]->getRank() )   !=   ( ptrptr[index[4]]->getRank() )   ){
			//if first pair doesn't equal three of a kind swap indexes with second			
				index[2] = index[0];
				index[3] = index[1];
			}	
		
			return x = 1;
		}
		return x = 0;
	}


	void callFullHouse(int begin, int nOfCards){

		if(fullHouse(begin,nOfCards) == 1){

			cout<<"\nFULL HOUSE:\n";
			
			for(int i = 2; i<7; i++){
			
				ptrptr[index[i]]->viewCard();nl(); 
			}			
			nl();
		}
		else{

			cout<<"\nThere is no Full House.\n";
			nl();
		}
	}


//8.FOUR OF A KIND/////////////////////////////////////////////////////////////////


	bool fourOfAKind (int begin, int nOfCards){

		bool x; 
	
		highLow(begin,nOfCards);
	
		for(int i = begin; i < nOfCards - 3; i++){

			int a = ptrptr[i]->getRank();

			for(int j = i+1; j < nOfCards - 2; j++){

				int b = ptrptr[j]->getRank();

				for(int k = j+1; k < nOfCards -1; k++){
						
					int c = ptrptr[k]->getRank(); 

					for(int l = k+1; l < nOfCards; l++){

						int d = ptrptr[l]->getRank();

						if((a == b) && (b == c) && (c == d)){ 
							
							index[0] = i;
							index[1] = j;
							index[2] = k;
							index[3] = l;
							return x = 1;
						}
					}
				}
			}
		}
		
		for(int i = 0; i < 5; i++){ index[i] = 0; }

		return x = 0;
	}	

	
	void callFourOfAKind (int begin, int nOfCards){

		if(fourOfAKind(begin, nOfCards) == 1){
		
			cout<<"\nFOUR OF A KIND:\n";


			for(int i = 0; i<4; i++){

				ptrptr[index[i]]->viewCard();nl();

			}			
			nl();
		}else{

			cout<<"\nThere is no Four of a Kind.\n";	
			nl();
		}
	}



//9.STRAIGHT FLUSH/////////////////////////////////////////////////////////////////

	bool straightFlush(int begin, int nOfCards){

		bool x; 

		for(int i = 0; i < 5; i++){ index[i] = 0; }

		flush(begin,nOfCards); //it aligns from high->low so next step is easy

		int a,b,c,d,e;

		a = ptrptr[index[0]]->getRank(); 
		b = ptrptr[index[1]]->getRank(); 
		c = ptrptr[index[2]]->getRank(); 
		d = ptrptr[index[3]]->getRank(); 
		e = ptrptr[index[4]]->getRank(); 

		if ( (a == b+1) && (b == c+1) && (c == d+1) && (d == e+1) )  { return x = 1; } 
									else { return x = 0; }	
	}


	void callStraightFlush(int begin, int nOfCards){

		if(straightFlush(begin,nOfCards) == 1){

			cout<<"\nSTRAIGHT FLUSH:\n";

			for(int i = 0; i < 5; i++){
				
				ptrptr[index[i]]->viewCard();
				nl();

			}
			nl();
		}else{

			cout<<"\nThere is no Straight Flush.\n";
			nl();
		}
	}


//////////////POKER HANDS ANALYSIS//////////////////////////////////////////////


	int getHandRank (int begin, int nOfCards, int playernumber){

		drawCards(begin, nOfCards, playernumber);

		int handRank = 0;

			if (straightFlush (begin, nOfCards)    == 1) { handRank = 9; }
		else	if (fourOfAKind   (begin, nOfCards)    == 1) { handRank = 8; }
		else	if (fullHouse     (begin, nOfCards)    == 1) { handRank = 7; }
		else	if (flush         (begin, nOfCards)    == 1) { handRank = 6; }
		else	if (straight      (begin, nOfCards)    == 1) { handRank = 5; }
		else	if (threeOfAKind  (begin, nOfCards)    == 1) { handRank = 4; }
		else	if (twoPairs      (begin, nOfCards)    == 1) { handRank = 3; }
		else	if (pair          (begin, nOfCards)    == 1) { handRank = 2; }
		                                    else     { handRank = 1; } 

			return handRank;
	}

	void callHand (int begin, int nOfCards, int playernumber){

		int x = getHandRank (begin, nOfCards, playernumber);
		int a = begin; 
		int b = nOfCards;
		int p = playernumber;

			if (x == 9) { /*cout << "\nYou've got a Straight Flush\n"; */callStraightFlush (a,b);}
		else	if (x == 8) { /*cout << "\nYou've got a Four of a Kind\n"; */callFourOfAKind   (a,b);}
		else	if (x == 7) { /*cout << "\nYou've got a Full House\n";     */callFullHouse     (a,b);}
		else	if (x == 6) { /*cout << "\nYou've got a Flush\n";          */callFlush         (a,b);}
		else	if (x == 5) { /*cout << "\nYou've got a Straight.\n";      */callStraight      (a,b);}
		else	if (x == 4) { /*cout << "\nYou've got Three of a Kind.\n"; */callThreeOfAKind  (a,b);}
		else	if (x == 3) { /*cout << "\nYou've got Two Pairs.\n";       */callTwoPairs      (a,b);}
		else	if (x == 2) { /*cout << "\nYou've got a Pair.\n";          */callPair          (a,b);}
		else	if (x == 1) { /*cout << "\nYou've got High Card.\n";       */callHighCard      (a,b,p);}
		else    if (x == 0) { cout << "\nERROR\n";			                         }

		nl();
	}


	void getRanksForHoleCards (int nOfCards, int player1, int player2){
					
		drawCards(nOfCards - 2, nOfCards, player1); 
		highLow (nOfCards - 2, nOfCards);
          
		rank1 = ptrptr[nOfCards - 2] -> getRank();
		rank11 = ptrptr[nOfCards - 1] -> getRank(); 	    	    

		drawCards (nOfCards - 2, nOfCards, player2);
		highLow (nOfCards - 2, nOfCards);

		rank2 = ptrptr[nOfCards - 2] -> getRank();
		rank22 = ptrptr[nOfCards - 1] ->getRank(); 

		//TEST 
		/*
		cout<<"\nrank1 is "<<rank1<<"\n"; 
		cout<<"\nrank11 is "<<rank11<<"\n"; 

		cout<<"\nrank2 is "<<rank2<<"\n"; 
		cout<<"\nrank22 is "<<rank22<<"\n";
		*/ 
	}



	int winningHand (int begin, int nOfCards, int player1, int player2){

		int winner;
		
		int hand1 = getHandRank(begin, nOfCards, player1);
		int hand2 = getHandRank(begin, nOfCards, player2);

		Card *ptrSeven1[7];
		Card *ptrSeven2[7];

		drawCards(begin, nOfCards, player1);
		highLow(begin, nOfCards);	
	
		for(int i = 0; i < 7; i++){
			
			ptrSeven1[i] = ptrptr[i];

		}	
		
		drawCards(begin, nOfCards, player2);
		highLow(begin, nOfCards);	
	
		for(int i = 0; i < 7; i++){
			
			ptrSeven2[i] = ptrptr[i];

		}	

		if	 ( hand1 > hand2 ){

			winner = player1;
			return winner;

		}else if ( hand2 > hand1 ){

			winner = player2;
			return winner;		

		}else if ( hand1 == hand2){

/*HIGH CARD*/		if (hand1 == 1){

					
				getRanksForHoleCards (nOfCards, player1, player2);

				if	(rank1 > rank2){

					return winner = player1;			

				}else if(rank2 > rank1){

					return winner = player2;

				}else if(rank1 == rank2){
			
					if	(rank11 > rank22){

						return winner = player1;			

					}else if(rank22 > rank11){

						return winner = player2;
					
					}

				}

				return winner = 50; //DRAW
				
/*PAIR*/		}else if (hand1 == 2){	
		
				drawCards(begin, nOfCards, player1); 
				pair(begin, nOfCards); 
				rank1 = ptrptr[index[0]] -> getRank(); 

				drawCards(begin, nOfCards, player2); 
				pair(begin, nOfCards); 
				rank2 = ptrptr[index[0]] -> getRank(); 

				if	(rank1 > rank2){
		
					return winner = player1;	
	
				}else if(rank2 > rank1){

					return winner = player2;

				}else if(rank1 == rank2){

					for(int i = 0; i < 7; i++){

						rank1 = ptrSeven1[i] -> getRank(); //<--it's equivalent with 
//						drawCards(begin, nOfCards, player1);	what's commented out below
//						highLow(begin, nOfCards);		
//						rank1 = ptrptr[i] -> getRank();
						
						rank2 = ptrSeven2[i] -> getRank();

						if(rank1 > rank2){

							return winner = player1; 

						}else if(rank2 > rank1){

							return winner = player2;

						}
					}				
				}

				return winner = 50;
	
/*TWO PAIRS*/		}else if (hand1 == 3){	

				drawCards(begin, nOfCards, player1); 
				twoPairs(begin, nOfCards); 
				rank1 = ptrptr[index[0]] -> getRank(); //<--First Pair
				rank11 = ptrptr[index[2]] -> getRank();//<--Second Pair

				drawCards(begin, nOfCards, player2); 
				twoPairs(begin, nOfCards); 
				rank2 = ptrptr[index[0]] -> getRank(); 
				rank22 = ptrptr[index[2]] -> getRank(); 

				if	(rank1 > rank2){
		
					return winner = player1;	
	
				}else if(rank2 > rank1){

					return winner = player2;

				}else if(rank1 == rank2){
					
					if	(rank11 > rank22){
						
						return winner = player1;

					}else if(rank22 > rank11){

						return winner = player2;

					}else if(rank11 == rank22){
								
						for(int i = 0; i < 7; i++){

							rank1 = ptrSeven1[i] -> getRank();  
							rank2 = ptrSeven2[i] -> getRank();

							if(rank1 > rank2){

								return winner = player1; 

							}else if(rank2 > rank1){

								return winner = player2;

							}
						}				
					}
				}

				return winner = 50;		

/*THREE OF A KIND*/	}else if (hand1 == 4){	

				drawCards(begin, nOfCards, player1); 
				threeOfAKind(begin, nOfCards); 
				rank111 = ptrptr[index[4]] -> getRank();//<--Three

				drawCards(begin, nOfCards, player2); 
				threeOfAKind(begin, nOfCards); 
				rank222 = ptrptr[index[4]] -> getRank(); 

				if(rank111 > rank222){

					return winner = player1; 

				}else if(rank222 > rank111){

					return winner = player2; 

				}else if (rank111 == rank222){

					for(int i = 0; i < 7; i++){

						rank1 = ptrSeven1[i] -> getRank();  
						rank2 = ptrSeven2[i] -> getRank();

						if(rank1 > rank2){

							return winner = player1; 

						}else if(rank2 > rank1){

							return winner = player2;

						}
					}				
				}

				return winner = 50;		

/*STRAIGHT*/ 		}else if (hand1 == 5){
				
				for(int i = 0; i < 5; i++){

					drawCards(begin, nOfCards, player1); 
					straight(begin, nOfCards); 
					rank1 = ptrptr[index[i]] -> getRank(); //<--Highest Card

					drawCards(begin, nOfCards, player2); 
					straight(begin, nOfCards); 
					rank2 = ptrptr[index[i]] -> getRank();

					if(rank1 > rank2){
					
						return winner = player1; 

					}else if(rank2 > rank1){

						return winner = player2; 
					}
				}

				return winner = 50;

/*FLUSH*/		}else if (hand1 == 6){	

				for(int i = 0; i < 5; i++){

					drawCards(begin, nOfCards, player1); 
					flush(begin, nOfCards); 
					rank1 = ptrptr[index[i]] -> getRank(); 

					drawCards(begin, nOfCards, player2); 
					flush(begin, nOfCards); 
					rank2 = ptrptr[index[i]] -> getRank();

					if(rank1 > rank2){
					
						return winner = player1; 

					}else if(rank2 > rank1){

						return winner = player2; 
					}
				}

				return winner = 50;

/*FULL HOUSE*/		}else if (hand1 == 7){

				drawCards(begin, nOfCards, player1); 
				fullHouse(begin, nOfCards); 
				rank1 = ptrptr[index[0]] -> getRank(); //<--Pair
				rank111 = ptrptr[index[4]] -> getRank();//<--Three

				drawCards(begin, nOfCards, player2); 
				fullHouse(begin, nOfCards); 
				rank2 = ptrptr[index[0]] -> getRank(); 
				rank222 = ptrptr[index[4]] -> getRank(); 

				if(rank111 > rank222){

					return winner = player1; 

				}else if(rank222 > rank111){

					return winner = player2; 

				}else if (rank111 == rank222){

					if(rank1 > rank2){

						return winner = player1; 

					}else if(rank2 > rank1){

						return winner = player2;

					}else if(rank1 == rank2){

						for(int i = 0; i < 7; i++){

							rank1 = ptrSeven1[i] -> getRank();  
							rank2 = ptrSeven2[i] -> getRank();

							if(rank1 > rank2){

								return winner = player1; 

							}else if(rank2 > rank1){

								return winner = player2;

							}
						}
					}				
				}


				return winner = 50;

/*FOUR OF A KIND*/	}else if (hand1 == 8){

				drawCards(begin, nOfCards, player1); 
				fourOfAKind(begin, nOfCards); 
				rank1 = ptrptr[index[0]] -> getRank();


				drawCards(begin, nOfCards, player2);
				fourOfAKind(begin, nOfCards);  	
				rank2 = ptrptr[index[0]] -> getRank();

				if(rank1 > rank2){

					return winner = player1; 

				}else if(rank2 > rank1){

					return winner = player2; 

				}else if(rank1 == rank2){

					for(int i = 0; i < 7; i++){

						rank1 = ptrSeven1[i] -> getRank();  
						rank2 = ptrSeven2[i] -> getRank();

						if(rank1 > rank2){

							return winner = player1; 

						}else if(rank2 > rank1){

							return winner = player2;

						}
					}
				}

				return winner = 50;

/*STRAIGHT FLUSH*/	}else if (hand1 == 9){	
		
				for(int i = 0; i < 5; i++){

					drawCards(begin, nOfCards, player1); 
					straightFlush(begin, nOfCards); 
					rank1 = ptrptr[index[i]] -> getRank(); 

					drawCards(begin, nOfCards, player2); 
					straightFlush(begin, nOfCards); 
					rank2 = ptrptr[index[i]] -> getRank();

					if(rank1 > rank2){
					
						return winner = player1; 

					}else if(rank2 > rank1){

						return winner = player2; 
					}
				}
				return winner = 50;

			}
		} 
	}

	void callWinningHand (int begin, int nOfCards, int player1, int player2, string player1name, string player2name){

		cout<<"\nAnd the winner is... ";

		int winner = winningHand(begin, nOfCards, player1, player2); 

		if (winner == player1){

			cout<<player1name<<".\n"; 		

		}else if (winner == player2){

			cout<<player2name<<".\n"; 
		
		}else if (winner == 50){

			cout<<"It's a draw.\n";

		}

		nl();

		}




//MEMBERS
	protected:

	Card deck[54];     //->ORIGINAL DECK
	Card *ptr[54];     //->RANDOMLY SHUFFLED DECK
	Card *ptrptr[58];  //->ORGANISED DECK HIGH->LOW
				//53-57 additional aces

	int rank1,rank11,rank111;
	int rank2,rank22,rank222; 

	int r; 		    //->Random variable

	int index[10];      //->Index for analysis purposes 
};

#endif//CROUPIER
