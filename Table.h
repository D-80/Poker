#ifndef TABLE_H
#define TABLE_H
#include<iostream>
#include"Player.h"

using namespace std;

	class Table{

	public:
	Table(){

		for(int i = 0; i < 23; i++){

			ptrUser[i] = &user[i];

		}
	}
 

	void nl(){

		cout<<"\n"; 

	}

	void setGame(int howManyPlayers, int howManyChips, int howBigBlinds){ 

		nOfPlayers = howManyPlayers;

		nOfActivePlayers = nOfPlayers; 

		playersPlaying = nOfActivePlayers; 
 
		smallBlind = howBigBlinds / 2; 
	
		bigBlind = howBigBlinds; 

		for(int i = 0; i < nOfActivePlayers; i++){

			char number = i + 1 + '0';

			string name = {'P','l','a','y','e','r',' ',number}; 		
	
			user[i].setAll(name, i + 1, howManyChips, 1); 

		}	
	}


	void viewPlayers(){ 

		int totalStacks = 0;

		for(int i = 0; i < nOfPlayers; i++){

			user[i].viewAll();

			totalStacks += user[i].getStack();  

		}

		cout<<"\ntotalStacks = "<<totalStacks<<"\n"; 
	}


	void viewPot(){ 

		cout<<"\nThere are "<<pot<<" chips in the main pot.\n";

	}




////////PREPARING GAME////////////

	void prepareTable(){

		leChiffre.assembleDeck();	
		leChiffre.shuffleDeck();
	}

	void showCards(){

		cout<<"\nPLAYERS HANDS:\n"; 

		for (int i = 0; i < nOfActivePlayers; i++){
			cout<<"\n"<< ptrUser[i] -> getPlayerName() <<":\n";
			leChiffre.viewDrawCard(0, 7, i, 0);  //0-7 cards, 0 player, first card //nl()
			leChiffre.viewDrawCard(0, 7, i, 1);
			nl();
		}

		nl(); 
	}
	

////////1. BETTING ROUNDS/////////



	void bettingRound ( int largestBet, int lastBet, int i ){	

		int playersCalled = 0;  

		while( playersCalled != playersPlaying ){		

			nl(); ptrUser[i] -> callName(); nl(); 
		
			if (  ptrUser[i] -> getActivity() == 1  ){
		
				ptrUser[i] -> askForDecision(largestBet, lastBet, bigBlind);

				switch ( ptrUser[i] -> getInput() ){

					case 1: //call or wait

							ptrUser[i] -> call(largestBet); 

							playersCalled++; 

							pot += ptrUser[i] -> getLastBet();  

							break; 

					case 2: //bet or raise 

							if ( (largestBet - ptrUser[i] -> getTotalBet() ) == 0 ){

								ptrUser[i] -> betRaise(largestBet, bigBlind); 

							}else{

								ptrUser[i] -> raise(largestBet, lastBet); 

							}

							lastBet = ptrUser[i] -> getLastBet();
							largestBet = ptrUser[i] -> getTotalBet(); 
							playersCalled = 1; 

							pot += ptrUser[i] -> getLastBet(); 

							break; 

					case 3: //fold

							ptrUser[i] -> fold(); 
							playersPlaying--;
							playersFolded++; 
							
							cout<<"playersFolded = "<<playersFolded<<" nOfActivePlayers = "<<nOfActivePlayers<<"\n"; 

							if( playersFolded == nOfActivePlayers - 1 ){		
	
								lastManStanding = 1; 
								
								playersCalled = playersPlaying; //terminates above while loop  	

							}

							break; 

					case 4: //allIn

							ptrUser[i] -> allIn();

							pot += ptrUser[i] -> getLastBet();

							
							if ( lastBet > ptrUser[i] -> getLastBet() ){

								playersCalled++; 

							}else{
	
								lastBet = ptrUser[i] -> getLastBet();
								largestBet = ptrUser[i] -> getTotalBet(); 
								playersCalled = 1; 

							}

							break; 

					case 5: //0 chips or wentAllIn

							playersCalled++; 

							break; 

				}	
			}

			i++;	//evaluate next player
			
			nl(); 

			if (i == nOfActivePlayers)

				i = 0;  //restart loop 
		}
	}



	void preFlop(){ //2 hole cards for each player

		if (lastManStanding != 1){

			int lastBet = bigBlind; 
			int largestBet = bigBlind; 
  		
			int i = 2; //start betting round from player 3; 

			if (nOfActivePlayers == 2) //heads up 
			i = 0;

			pot = smallBlind + bigBlind; 

			for (int j = 0; j < nOfActivePlayers; j++){

				sidePot[j] = 0; 

			}

			cout<<"\nPRE-FLOP\n";  

			ptrUser[0] -> openingBet(smallBlind); 			
			ptrUser[1] -> openingBet(bigBlind); 

			viewPot(); 
			
			nl(); 
			
			bettingRound(largestBet, lastBet, i);	

			viewPot(); //END OF THE PRE-FLOP 

		}
	}


	void flop(){	//+3 cards on the table

		cout<<"\nFLOP\n\n";	
		leChiffre.viewDrawCard(0,7,0,2);
		leChiffre.viewDrawCard(0,7,0,3);
		leChiffre.viewDrawCard(0,7,0,4);

		if (lastManStanding != 1){
	
			int lastBet = 0; 
			int largestBet = 0;    
			int i = 0; //start betting round from player 1; 

			resetBets(); 		

			viewPot(); 
			
			nl(); 
			
			bettingRound(largestBet, lastBet, i);	

			viewPot(); //END OF THE FLOP 

		}
	}



	void turn(){	//+1 card on the table

		cout<<"\nTURN\n\n";	
		leChiffre.viewDrawCard(0,7,0,5);	

		if (lastManStanding != 1){

			int lastBet = 0; 
			int largestBet = 0;    
			int i = 0; //start betting round from player 1; 

			resetBets(); 

			viewPot(); 
			
			nl(); 
			
			bettingRound(largestBet, lastBet, i);	

			viewPot(); //END OF THE TURN

		}
	}


	void river(){	//+1 card on the table, end

		cout<<"\nRIVER\n\n";	
		leChiffre.viewDrawCard(0,7,0,6);
	
		if (lastManStanding != 1){

			int lastBet = 0; 
			int largestBet = 0;    
			int i = 0; //start betting round from player 1; 

			resetBets(); 		

			viewPot(); 
			
			nl(); 
			
			bettingRound(largestBet, lastBet, i);	

			viewPot();  

		}
	}
	


	void showDownAlpha(){ 

	cout<<"\nShowdownAlpha\n";

	//Compare i player with j (all) players with leChiffre.winningHand() (possible outcomes = p1, p2, 50) 
		//if p1 - declare p1 the winner. 
		//if p2 - change i to j, declare all players loosers and p2 the winner, and change nOfDraws to 0. 
		//if 50 - change nOfDraws++, declare p1 and p2 winners and continue.
	//so we need winners[nOfActivePlayers]

	//If player went all in, he can only win the amount saved in his sidePot * the number of players who called his bet. 
	//Substract that amount from the mainPot, change players activity to 0 
	//and then do the whole showDown again. 

	//sidePot1 = mainPot at the time of going allIn + allIn bet * nOfActivePlayers who called that bet 

		int nOfWinners = 1; //there is always atleast one  

		int i; //second index number for the main (for (int j)) loop 

		for (i = 0; i < nOfActivePlayers; i++){ //finding the first active player to start the next loop from

			if (ptrUser[i] -> getActivity() == 1)
			
			break;  

		}

		for (int j = 0; j < nOfActivePlayers; j++){ //comparing hands of all players


//			cout<<"\ncomparing:\n"; 
//			ptrUser[i] -> callName(); nl(); 
//			ptrUser[j] -> callName(); nl(); 	

			if(  ( ptrUser[i] -> getActivity() == 1 ) && ( ptrUser[j] -> getActivity() == 1 ) && ( i != j )  ){

				int victor = leChiffre.winningHand(0,7,i,j); 

				if (victor == i){	

					winners[i] = 1;

					winners[j] = 0; 
					
//					cout<<"\nwinners[i] = 1\n"; 
			
				}else if (victor == j){

					for (int k = 0; k < nOfActivePlayers; k++){

						winners[k] = 0; 

					}

					winners[j] = 1; 

					i = j; 

					j = 0; 

					nOfWinners = 1;

	 
//					cout<<"\nwinners[j] = 1\n"; 

				}else if (victor == 50){

					nOfWinners++; 

					winners[i] = 1; 
					winners[j] = 1; 		

//					cout<<"\ndraw\n"; 

				} 
			}	
		}

		for(int i = 0; i < nOfActivePlayers; i++){
		
			if(  ( winners[i] == 1 )    &&    ( ptrUser[i] -> getActivity() == 1 )  ){
		
				if ( ptrUser[i] -> getAllIn() == 1 ){

					sidePot[i] = ptrUser[i] -> getTotalTotalBet(); 

					for(int j = 0; j < nOfActivePlayers; j++){

						if ( winners[j] != 1 ){

							if (  (ptrUser[i] -> getTotalTotalBet())   >   (ptrUser[j] -> getTotalTotalBet())  ){
							
								sidePot[i] += ptrUser[j] -> getTotalTotalBet(); 

								ptrUser[j] -> setTotalTotalBet(0); 

								ptrUser[i] -> callName(); nl(); 
//								cout<<i<<" sidePot[i] = "<<sidePot[i]<<" TotalTotal =  "<<ptrUser[i] -> getTotalTotalBet()<<"\n";
					
								ptrUser[j] -> callName(); nl(); 
//								cout<<j<<" sidePot[j] = "<<sidePot[j]<<" TotalTotal =  "<<ptrUser[j] -> getTotalTotalBet()<<"\n";



							}else{	//ptrUsers[i] stack was smaller than the loosers ptrUser[j]

								sidePot[i] += ptrUser[i] -> getTotalTotalBet();

								ptrUser[j] -> setTotalTotalBet( ptrUser[j] -> getTotalTotalBet() - ptrUser[i] -> getTotalTotalBet() );

								ptrUser[i] -> callName(); nl(); 
//								cout<<i<<" sidePot[i] = "<<sidePot[i]<<" TotalTotal =  "<<ptrUser[i] -> getTotalTotalBet()<<"\n";
					
								ptrUser[j] -> callName(); nl(); 
//								cout<<j<<" sidePot[j] = "<<sidePot[j]<<" TotalTotal =  "<<ptrUser[j] -> getTotalTotalBet()<<"\n";

							}	
						}						
					} 

					int chipsWon = sidePot[i]; 
			
					ptrUser[i] -> setStack ( chipsWon );

					ptrUser[i] -> setTotalTotalBet(0);  
											
					cout<<"\n"<< ptrUser[i] -> getPlayerName() <<" has won "<<chipsWon<<" chips with:\n";
				
					leChiffre.callHand (0, 7, i); 

					nl(); 

					ptrUser[i] -> setActivity(0); //for next showDown

					pot -= sidePot[i]; 
			
					viewPot(); 

					if(pot > 0){

						doShowDownAgain = 1;
//						cout<<"\ndoShowDownAgain()\n";
					}

				}else{

					int chipsWon = pot / nOfWinners;

					ptrUser[i] -> setStack (  ptrUser[i] -> getStack() + chipsWon ); 

					cout<<"\n"<<ptrUser[i] -> getPlayerName()<<" has won "<<chipsWon<<" chips with:\n";
				
					leChiffre.callHand (0, 7, i); 

					nl();
				
					doShowDownAgain = 0; 

				}
			}
		}	
	}


	void showDown(){

		for (int i = 0; i < nOfActivePlayers; i++){	//assigning 0 value for bool winners[] by default

			winners[i] = 0; 

		}

		if ( lastManStanding != 1 ){

			showDownAlpha(); 

			for (int i = 0; i < playersPlaying - 1; i++){

				if (doShowDownAgain == 1){

					showDownAlpha(); 

//					cout<<"\nDo showdown again loop\n";

					for (int i = 0; i < playersPlaying; i++){

						if ( winners[i] == 0 && ptrUser[i] -> getActivity() == 1){
						
							ptrUser[i] -> setStack( ptrUser[i] -> getTotalTotalBet() );
		
//							nl(); cout<<ptrUser[i]->getPlayerName()<<ptrUser[i]->getStack(); nl(); 
						}
					} 
				}	
			}
		}else{

			for (int i = 0; i < nOfActivePlayers; i++){

				if ( ptrUser[i] -> getActivity() == 1 ){

					ptrUser[i] -> setStack( ptrUser[i] -> getStack() + pot ); 

					cout<<"\n"<<ptrUser[i] -> getPlayerName()<<" has won "<<pot<<" chips.\n";

				}
			}
		}
	}



	void resetBets(){

		for(int i = 0; i < nOfActivePlayers; i++ ){

			ptrUser[i] -> setLastBet(0); 

			ptrUser[i] -> setTotalBet(0); 

		}
	}



	void cleanUp(){

		nOfActivePlayers = nOfPlayers; 

		for (int i = 0; i < nOfPlayers; i++ ){

			sidePot[i] = 0;

			winners[i] = 0; 

			user[i].setActivity(1); 

			user[i].setLastBet(0);  

			user[i].setTotalBet(0);

			user[i].setTotalTotalBet(0); 

			user[i].setWentAllIn(0); 

			if ( user[i].getStack() == 0 ){

				cout<<"\n"<< user[i].getPlayerName() <<" has lost all his chips.\n";

				user[i].setActivity(0);

				user[i].setPosition(0); 

				nOfActivePlayers--;

				if ( nOfActivePlayers == 1 ){

					for (int i = 0; i < nOfPlayers; i++){

						if (user[i].getActivity() == 1){

							cout<<"\n"<< user[i].getPlayerName() <<" has won!\n"; 

						}
					}

					end = 1; 

				}

			}
		}

		pot = 0;

		playersPlaying = nOfActivePlayers; 
		playersFolded = 0; 
		doShowDownAgain = 0;
		lastManStanding = 0;
		 

	}


	void rotatePositions(){

		int j = 0;

		for (int i = 0; j < nOfActivePlayers; i++){ //eliminating loosers

			if (ptrUser[i] -> getActivity() == 1){	//activity for remaining players set to 1 in cleanUp()

				ptrUser[j] = ptrUser[i]; 

				ptrUser[j] -> setPosition(j+1); 
				
//				cout<<"\nptrUser["<<j<<"] = ptrUser["<<i<<"]\n";
				j++;		

				nl(); 
//				cout<<"rotate positions nOfActivePlayers = "<<nOfActivePlayers; nl(); 

			}
		}


		for (int i = 1; i < j; i++){ //changing positions

			ptrUser[22]	=	ptrUser[i]; //ptrUser[22] is a template

			ptrUser[i]	=	ptrUser[i-1]; 

			ptrUser[i-1]	=	ptrUser[22]; 
	
		}
	}


	void deal(){

		prepareTable(); 

		nl(); 

		showCards(); 

		nl(); 

		preFlop(); 

		nl(); 

		flop(); 

		nl(); 
	
		turn(); 
	
		nl(); 

		river();

		nl(); 

		showDown();  

		cleanUp();

		rotatePositions();   

		viewPlayers(); 
	}


	void play(){


		setGame(4, 15000, 50);

/*		
		user[0].setStack(1000);
		user[1].setStack(2000);
		user[2].setStack(3000); 
		user[3].setStack(4000); 
*/
		prepareTable(); 

		viewPlayers();  

		while (end != 1){

//			cout<<"\nNOFACTIVEPLAYERS = "<<nOfActivePlayers<<"\n";

			deal(); 

		}

		cout<<"\n\nTHE END\n";
	}



	private:
	
	Croupier leChiffre; 

	//Assigned in setGame():

	Player user[23];  
		Player* ptrUser[23];  //positions

	int smallBlind; 
	int bigBlind; 

	int sidePot[23]; //critical for rotatePositions()

	int nOfPlayers; //original number of players

	int playersPlaying; //players who haven't folded

	int nOfActivePlayers; //players that are still playing 

	int playersFolded = 0;

	//Assigned elsewhere:

	int pot; //assigned in all betting rounds	

	bool lastManStanding = 0; //bettingRound() + checked as a condition at all betting rounds

	bool doShowDownAgain = 0; //showDownAlpha(), showDown()

	bool winners[23]; //showDownAlpha(), showDown()

	bool end = 0; //cleanUp()

	};

#endif//TABLE_H


