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
		}

		virtual ~Game(){
			delete deck;
		}
	private:
		Deck deck;
}

class FastGame: public Game{
	public:
		FastGame(){}

		~FastGame(){}

	private:
		std::vector<Strategy> strategy;
}

class DetailedGame: public Game{

}

class TournamentGame: public Game{

}

#endif
