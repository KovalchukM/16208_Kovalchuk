#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <vector>

struct Options{
	std::string gameType;
	int cardType;
	std::vector<Strategy> strategy;
}

class Settings{
	public:
		Settings(int argc , char *argv[]){
			options.gameType = setGame(argv[1]);
			options.cardType = setCard(argv[2]);
			options.strategy = createStrategy(argc , argv)
		}

		Settings(const Settings& b ) : options.gameType(b.options->gameType) , options.cardType(b.options->cardType) , options.strategy(b.options->strategy) {}

		virtual ~Settings(){
			delete [] strategy;
		}

		std::string setGame(char *str){
			switch(str){
				case "fast":
					return "fast";
				case "detailed":
					return "detailed";
				case "tournament":
					return "tournament";
				default:
					std::cout << "wrong gameType" << std::endl;
			}
			return "wrong";
		}

		int setCard(char *str){
			switch(str){
				case "a":
					return 0;
				case "b"
					return 1;
				case "c":{
					int N = 0;
					std::cout << "please enter card number" << std::endl;
					std::cin  >> N;
					return N; 
				}
				default:
					std::cout << "wrong cardType" << std::endl;
			}
			return (-1);
		}

		std::vector<Strategy> createStrategy(int argc , char *argv[]){
			std::vector<Strategy> strategy;
			for(int i = 3 ; i < argc ; i++){
				options.strategy->push_back(factory::get_instance()->create(argv[i]));
			}
			return strategy;
		}

		Options getOptions(){
			return options;
		}

	private:
		Options options;
}

#endif
