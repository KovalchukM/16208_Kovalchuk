#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <vector>

struct Options{
	std::string gameType;
	int cardType;
	std::vector<Strategy*> strategy;
};

class Settings{
	public:
		Settings(int argc , char *argv[]){
			options.gameType = setGame(argv[1]);
			options.cardType = setCard(argv[2]);
			options.strategy = createStrategy(argc , argv);
			// std::cout<< "EBOBO 2  " << options.strategy[0]->getName() << std::endl;
			// std::cout<< "EBOBO 2  " << options.strategy[1]->getName() << std::endl;
		}

		Settings(const Settings& b ){
			options.gameType = b.options.gameType;
			options.cardType = b.options.cardType;
			options.strategy = b.options.strategy; 
		}

		std::string setGame(std::string str){
			if(str == "fast")
				return "fast";
			if( str == "detailed")
				return "detailed";
			if( str == "tournament")
				return "tournament";
			std::cout << "wrong gameType" << std::endl;
			return "wrong";
		}

		int setCard(std::string str){
			if(str == "a")
				return 0;
			if(str == "b")
				return 1;
			if(str == "c"){
				int N = 0;
				std::cout << "please enter card number" << std::endl;
				std::cin  >> N;
				return N;
			}
			std::cout << "wrong cardType" << std::endl;
			return (-1);
		}

		std::vector<Strategy*> createStrategy(int argc , char *argv[]){
			std::vector<Strategy*> strategy;
			for(int i = 3 ; i < argc ; i++){
				strategy.push_back(Factory<Strategy, Strategy*(*)(), std::string>::get_instance()->create(argv[i]));
				// std::cout<< "EBOBO  " << strategy[i-3]->getName() << std::endl;
			}
			return strategy;
		}

		Options getOptions(){
			return options;
		}

	private:
		Options options;
};

#endif
