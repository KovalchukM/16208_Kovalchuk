#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "Factory.h"

class Strategy{
	public:
		virtual void turn(int n){}

		void pickFirst(int n){
			firstCard = n;
			score = n;
		}

		void setWin(){
			win = true;
		}

		bool isPass(){
			return pass;
		}

		bool isWinner(){
			return win;
		}

		int getScore(){
			return score;
		}

		int getFirst(){
			return firstCard;
		}

		std::string getName(){
			return name;
		}

		void reset(){
			firstCard = 0;
			score = 0;
			pass = false;
			win = false;
		}

		void operator =(const Strategy* b){
			name = b->name;
			firstCard = b->firstCard;
			score = b->score;
			pass = b->pass;
			win = b->win;
		}

	protected:
		std::string name;
		int firstCard = 0;
		int score = 0;
		bool pass = false;
		bool win = false;
};

#endif
