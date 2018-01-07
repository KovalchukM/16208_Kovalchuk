#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "Score_17.h"

class Strategy{
	public:
		virtual Strategy(){
			firstCard = 1 + rand() % 10;
			score = (1 + rand() % 10) + firstCard;
		}

		virtual void turn(){
			pickCard();
			if(score > 21){
				pass = true;
				lose = true;
			}
		};

		virtual void pickCard(){
			score += (1 + rand() % 10);
		}

	private:
		int firstCard = 0;
		int score = 0;
		bool pass = false;
		bool lose = false;
}

#endif
