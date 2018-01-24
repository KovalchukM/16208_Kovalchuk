#ifndef GAME_H_
#define GAME_H_

#include "Deck.h"

class Game{
	public:

		virtual void makeDeck(Options options){
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
		}

		virtual ~Game(){
			delete deck;
			for(auto This : players)
				delete This;
		}

		virtual void play(){}

		void checkResults(){
			int max;
			std::vector<int> index;
			for(int i = 0 ; i < players.size() ; i++){
				if((players[i]->getScore()) < 22){ 
					if((players[i]->getScore()) > max){
						index.clear();
						max = (players[i]->getScore());
						index.push_back(i);
					}
					if((players[i]->getScore()) == max){
						index.push_back(i);
					}
				}
			}
			for(int i = 0 ; i < index.size() ; i++){
				players[index[i]]->setWin();
			}
		}

		void showResult(){
			std::cout<<std::endl;
			std::cout<<"game over" <<std::endl;
			std::cout<<std::endl;
			for( auto i : players ){
				std::cout << i->getName() << std::endl;
				std::cout << "		score: " << i->getScore() << " ";
				if(i->isWinner())
					std::cout << "winner";
				std::cout << std::endl;
			}
		}

	protected:
		Deck *deck;
		std::vector<Strategy*> players;
		int passes = 0;
};

class FastGame: public Game{
	public:

		FastGame(Options options){
			makeDeck(options);
			players = options.strategy;
			play();
		}

		void play() override{
			for(auto i : players){
				i->pickFirst(deck->pick());
				i->turn(deck->pick());
			}
			int passes = 0;
			while(passes != players.size()){
				passes = 0;
				for(auto i : players){
					if(!(i->isPass())){
						i->turn(deck->pick());
					}
					if(i->isPass()){
						passes++;
					}
				}
			}
			checkResults();
			showResult();
		}

};

class DetailedGame: public Game{
	public:
		DetailedGame(Options options){
				makeDeck(options);
				players = options.strategy;
				play();
			}

		void play() override{
			std::cout<< "begin" << std::endl;
			for(auto i : players){
				i->pickFirst(deck->pick());
				i->turn(deck->pick());
				std::cout<< i->getName() << " : " << std::endl;
				std::cout<< "		score:" << i->getScore() <<std::endl;
				std::cout<< "		pass:";
				if(i->isPass())
					std::cout<< "yes" <<std::endl;
				else
					std::cout<< "no" <<std::endl;
			}
			std::cout<<"============================="<<std::endl;
			int passes = 0;
			int turn = 1;
			while(passes != players.size()){
				std::cout<< "turn " << turn <<std::endl;
				passes = 0;
				for(auto i : players){
					if(!(i->isPass())){
							i->turn(deck->pick());
						}
					if(i->isPass()){
						passes++;
					}
					std::cout<< i->getName() << " : " << std::endl;
					std::cout<< "		score:" << i->getScore() <<std::endl;
					std::cout<< "		pass:";
					if(i->isPass())
						std::cout<< "yes" <<std::endl;
					else
						std::cout<< "no" <<std::endl;
				}
				turn++;
				std::cout<<"============================="<<std::endl;
			}
			checkResults();
			showResult();
		}
};

class TournamentGame: public Game{
	public:
		TournamentGame(Options options){
			makeDeck(options);
			players = options.strategy;
			wins = new int [players.size()];
			std::fill_n(wins , players.size() , 0);
			play();
		}

		~TournamentGame(){
			delete wins;
		}

		void play() override{
			for(int i = 0 ; i < (players.size() - 1) ; i++){
				for(int k = (i + 1) ; k < players.size() ; k++){
					players[i]->pickFirst(deck->pick());
					players[i]->turn(deck->pick());
					players[k]->pickFirst(deck->pick());
					players[k]->turn(deck->pick());
					int passes = 0;
					while(passes != 2){
						passes = 0;
						if(!(players[i]->isPass()))
							players[i]->turn(deck->pick());
						if(players[i]->isPass()){
							passes++;
						}
						if(!(players[k]->isPass()))
							players[k]->turn(deck->pick());
						if(players[k]->isPass()){
							passes++;
						}
					}
					checkResults(i , k);
					players[i]->reset();
					players[k]->reset();
				}
			}
			checkTournament();
			showResult();
		}

		void checkResults(int i ,int k){
			if( (players[k]->getScore() < 22 ) || (players[i]->getScore() < 22 ) ){
				if( players[k]->getScore() == players[i]->getScore()){
					wins[i]++;
					wins[k]++;
				}
				if( players[k]->getScore() < players[i]->getScore() )
					wins[i]++;
				if( players[i]->getScore() < players[k]->getScore() )
					wins[k]++;
			}
		}

		void checkTournament(){
			int max = 0;
			std::vector<int> index;
			for(int i = 0 ; i < players.size() ; i++){
				if(wins[i] == max){
					index.push_back(i);
				}
				if(wins[i] > max){ 
					index.clear();
					max = wins[i];
					index.push_back(i);
				}
			}
			for(auto i : index){
				if( wins[i] > 0)
					players[i]->setWin();
			}
		}

		void showResult() {
			std::cout << std::endl;
			std::cout << "Tournament over" << std::endl;
			for(int i = 0 ; i < players.size() ; i++){
				std::cout << players[i]->getName() << " :" << std::endl;
				std::cout << "		wins: " << wins[i] << "  ";
				if(players[i]->isWinner())
					std::cout << "champion!"<< std::endl;
				else
					std::cout << std::endl;
				std::cout << std::endl;
			}
		}

	private:
		int* wins;
};

#endif
