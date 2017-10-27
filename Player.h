#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>

	using namespace std;

		class Player{

		public: 
		
		void nl(){

			cout<<"\n";

		}


		void callName(){

			cout<<playerName;

		} 


		void setAll(string a, int b, int c, bool d){

			playerName = a;
			setPosition(b); 
			setStack(c);
			setActivity(d); 

		}


		void viewAll(){

			nl(); 
			cout<<position<<".";
			nl(); 
			cout<<playerName;
			nl();
			cout<<stack<<" chips.";
			nl(); 

		}


		void setStack(int x){

			stack = x; 

		}

		
		void setActivity(bool x){

			activity = x;

		}


		int getStack(){

			int x = stack;

			return x;
		}


		void setPosition(int x){

			position = x; 

		}


		bool setWentAllIn(bool x){

			wentAllIn = x; 

		}



		int getPosition(){

			int x = position;
		
			return x;
		}


		bool getActivity(){

			bool x = activity; 

			return x;  

		}


		string getPlayerName(){

			string x = playerName; 
			
			return x; 

		}

		//BETTING ROUND//////////////

		void bet(int sizeOfBet){ 
			
			setStack (getStack() - sizeOfBet); 
			
			lastBet = sizeOfBet;

			totalBet += sizeOfBet; 

			totalTotalBet += sizeOfBet;  

		}	


		void openingBet(int sizeOfBet){ 
			
			cout<<"\n"<<playerName<<" has bet "<<sizeOfBet<<".\n";

			setStack (getStack() - sizeOfBet); 
			
			lastBet = sizeOfBet;

			totalBet += sizeOfBet;  

			totalTotalBet += sizeOfBet; 
		
			cout<<stack<<" chips left.\n"; 

			nl(); 
		}	

		
		void call(int largestBet){

			if ( (largestBet - totalBet) >= stack ){

				allIn(); 

			}else{

				cout<<"\n"<<playerName<<" has called.\n";
			
				bet ( largestBet - totalBet ); 

				cout<<stack<<" chips left.\n"; 

			}
		}


		void raise (int largestBet, int sizeOfLastBet){

			playersInput = 0; 

			cout<<"\nBy how much do you want to raise? (you've already bet "<<totalBet<<" chips and min. raise is "<<sizeOfLastBet<<" chips).\n"; 

			while (  ( playersInput < sizeOfLastBet )  ||  ( playersInput + (largestBet - totalBet) > stack )  ){

				getUsersInput();  

				if ( playersInput < sizeOfLastBet ){

					cout<<"\nThe minimum raise you can make is "<< sizeOfLastBet << " chips. Try again.\n"; 

				}else if ( playersInput + (largestBet - totalBet) > stack){

					cout<<"\nThe maximum raise you can make is "<< stack - totalBet <<" chips. Try again.\n"; 

				}
			}

			
			cout<<"\n"<<playerName<<" has raised the previous bet of "<<sizeOfLastBet<<" by "<< playersInput << " chips.\n";

			bet( playersInput + (largestBet - totalBet) );
		
			cout<<stack<<" chips left.\n"; 
		}



		void betRaise(int largestBet, int bigBlind){

			playersInput = 0; 

			cout<<"\nEnter the amount of chips that you want to bet (you've already bet "<<totalBet<<" chips this round";
			cout<<" and min. bet is "<<bigBlind<<" chips).\n"; 

			while (  ( playersInput < bigBlind )  ||  ( playersInput + (largestBet - totalBet) > stack )  ){

				getUsersInput(); 

				if ( playersInput < bigBlind ){

					cout<<"\nThe minimum bet you can make is "<< bigBlind << " chips. Try again.\n"; 

				}else if ( playersInput + (largestBet - totalBet) > stack){

					cout<<"\nThe maximum bet you can make is "<< stack - totalBet <<" chips. Try again.\n"; 

				}
			}

			
			cout<<"\n"<<playerName<<" has bet "<<playersInput<<" chips.\n";

			bet(playersInput);
		
			cout<<stack<<" chips left.\n"; 
		}


		
		void fold(){ 

			cout<<"\n"<<playerName<<" has folded.\n";

			activity = 0; 

		}

		
		void allIn(){

			bet(stack); 	

			cout<<"\n"<<playerName<<" declared all-in with "<<lastBet<<" chips.\n";

			wentAllIn = 1; 

		}



	void askForDecision(int largestBet, int sizeOfLastBet, int bigBlind){ 

		if( stack == 0 || wentAllIn == 1 ){

			playersInput = 5; 	


		}else if( (largestBet - totalBet) == 0 ){
	
			cout<<"\n1.CHECK.\n";
			cout<<"2.BET (minimum bet = "<<bigBlind<<" chips).\n"; 
			cout<<"3.FOLD.\n";
			cout<<"4.ALL IN ("<<stack<<" chips).\n";

			getUsersInput();

			 

		}else{

			cout<<"\n1.CALL ("<< (largestBet - totalBet) <<" chips to call).\n";
			cout<<"2.RAISE (minimum raise = "<<sizeOfLastBet<<" chips).\n"; 
			cout<<"3.FOLD.\n";
			cout<<"4.ALL IN ("<<stack<<" chips).\n";

			getUsersInput(); 

		}
	}

	
	int getUsersInput (){

		cin >> playersInput; 

		if (playersInput < 0){

		cout <<"Not a valid input. Please enter your number again.\n";
		cin >> playersInput; 

		}

		while ( cin.fail() ){

			cin.clear(); 
			cin.ignore(); 
			cout << "\nNot a valid input. Please enter your number again.\n";
			cin >> playersInput;  
		}
	}


	
	int getInput(){ 

		int x = playersInput; 

		return x; 

	}


	int getLastBet(){

		int x = lastBet; 

		return x; 

	}

	
	int getTotalBet(){

		int x = totalBet; 

		return x; 

	}	


	int getTotalTotalBet(){

		int x = totalTotalBet; 

		return x; 

	}	

	
	bool getAllIn(){

		bool x = wentAllIn;

		return x; 

	}


	void setLastBet( int x ){

		lastBet = x;

	}


	void setTotalBet( int x ){

		totalBet = x;

	}


	void setTotalTotalBet( int x ){

		totalTotalBet = x;

	}

	private:
	string playerName; 
	int position; //place in line for drawing cards
	int stack; //total number of chips
	bool activity; //if activity = 0 player folded

	int lastBet = 0; 

	int totalBet = 0; //sum of all bets during one betting round

	int totalTotalBet = 0; //sum of all bets during one showdown

	int playersInput; 

	bool wentAllIn = 0; 

	};	


#endif//PLAYER_H

