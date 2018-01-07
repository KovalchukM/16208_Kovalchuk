#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "Score_17.h"

class Strategy{
	public:
		virtual Strategy(){}

		virtual void turn(int n){
			score += n;
			if(score > 21){
				pass = true;
			}
		}

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

	private:
		std::string name;
		int firstCard = 0;
		int score = 0;
		bool pass = false;
		bool win = false
}

#endif
