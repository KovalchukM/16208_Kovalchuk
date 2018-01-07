#ifndef SCORE_17_H_
#define SCORE_17_H_

class Score_17: public Strategy{
	public:
		void turn() override {
			if(score < 17)
				pickCard();
			else
				pass = true;
		}

	private:
		std::string name = "score_17";
}

Strategy *createScore_17(){
	return new Score_17;
}

namespace {
	bool b = factory::get_instance()->register_strat("Score_17", createScore_17);
}

#endif
