#ifndef SCORE_17_H_
#define SCORE_17_H_
#include "Factory.h"
#include "Strategy.h"

class Score_17: public Strategy{
	public:
		Score_17(){
			name = "Score_17";
		}

		void turn(int c) override {
			score += c;
			if(score >= 17){
				pass = true;
			}
		}

};

// Strategy* createScore_17(){
// 	return new Score_17;
// }

namespace {
	bool b = Factory<Strategy, Strategy*(*)(), std::string>::
		get_instance()->register_strat("Score_17", Creator<Score_17, Strategy>::create);
}

#endif
