#include <iostream>
#include <string>
#include "Strategy.h"
#include "Factory.h"
#include "Settings.h"
#include "Game.h"

int main(int argc , char *argv[]){
	if (argc < 4){
		std::cout << "wrong number of arguments"<< std::endl;
		return 1;
	}
	Options options = Settings(argc,argv).getOptions();

	if(options.gameType == "wrong" || Options.cardType < 0 || (options.gameType == "tournament" && argc < 4))
		return 1;

	switch (options.gameType){
		case "fast":{
			FastGame game(options);
			break;
		}
		case "detailed":{
			DetailedGame game(options);
			break;
		}
		case "tournament":{
			TournamentGame game(options);
			break;
		}
	}

	return 0;
}

// argv: detailed|fast|tournament   a|b|c   (имена стратегий)
