#ifndef DEALER_H_
#define DEALER_18_H_
#include "Factory.h"
#include "Strategy.h"

class Dealer: public Strategy{
	public:
		Dealer(){
			name = "Dealer";
		}

		void turn(int c , int First) override {
			score += c;
			if(score >= 17){
				pass = true;
			}
		}
};

namespace {
	bool d = Factory<Strategy, Strategy*(*)(), std::string>::
		get_instance()->register_strat("Dealer", Creator<Dealer, Strategy>::create);
}

#endif
