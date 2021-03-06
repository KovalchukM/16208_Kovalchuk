#ifndef SCORE_20_H_
#define SCORE_20_H_
#include "Factory.h"
#include "Strategy.h"

class Score_20: public Strategy{
	public:
		Score_20(){
			name = "score_20";
		}

		void turn(int c , int dealerFirst) override {
			score += c;
			if(score >= 20){
				pass = true;
			}
		}
};

namespace {
	bool b = Factory<Strategy, Strategy*(*)(), std::string>::
		get_instance()->register_strat("Score_20", Creator<Score_20, Strategy>::create);
}

#endif
