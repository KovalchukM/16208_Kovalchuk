#ifndef GAME_H_
#define GAME_H_

#include "Deck.h"

class Game{
	public:
		virtual Game(Options options){
			switch (options.cardType){
				case 0:{
					deck = new RandDeck;
					break;
				}
				case 1:{
					deck = new OneDeck;
					break;
				}
				default:{
					deck = new CustomDeck(options.cardType);
				}
			}
			players = options.strategy;
		}

		virtual Game(const Game& b){}

		virtual ~Game(){
			delete deck;
			for(int i = 0 ; i < players.size() ; i++)
				delete players[i];
		}

		virtual void play(){}
	private:
		Deck *deck;
		std::vector<Strategy> players;
		int passes = 0;
}

class FastGame: public Game{
	public:
		void play() override{
			for(int i = 0 ; i < players.size() ; i++){
				players[i] -> pickFirst(deck.pick());
				players[i] -> turn(deck.pick());
			}
			int passes = 0;
			while(passes != players.size()){
				passes = 0;
				for(int i = 0 ; i < players.size() ; i++){
					if(!(players[i]->isPass)){
						players[i] -> turn(deck.pick());
					}
					else{
						passes++;
					}
				}
			}
			checkResults();
			showResult();
		}

		void checkResults(){
			int max;
			std::vector<int> index;
			for(int i = 0 ; i < players.size() ; i++){
				if((players[i] -> getScore()) < 22){ 
					if((players[i] -> getScore()) > max){
						index.clear();
						max = (players[i] -> getScore());
						index.push_back(i);
					}
					if((players[i] -> getScore()) == max){
						index.push_back(i);
					}
				}
			}
			for(int i = 0 ; i < index.size() ; i++){
				players[index[i]] -> setWin();
			}
		}

		void showResult(){
			for(int i = 0 ; i < players.size() ; i++){
				std::cout << players[i] -> getName << std::endl;
				std::cout << "		score: " << players[i] -> getScore() << " ";
				if(players[i] -> isWinner())
					std::cout << "winner";
				std::endl;
			}
		}
}

class DetailedGame: public Game{

}

class TournamentGame: public Game{

}

#endif
