#ifndef SCORE_17_H_
#define SCORE_17_H_

class Score_17: public Strategy{
	public:
		Score_17() override{
			name = "score_17";
		}

		void turn(int c) override {
			score += c;
			if(score >= 17){
				pass = true;
			}
		}

}

Strategy *createScore_17(){
	return new Score_17;
}

namespace {
	bool b = factory::get_instance()->register_strat("Score_17", createScore_17);
}

#endif
