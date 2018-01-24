#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include "Strategy.h"
#include "Settings.h"
#include "Game.h"

int main(int argc , char *argv[]){
	srand(time(NULL));
	if (argc < 4){
		std::cout << "wrong number of arguments"<< std::endl;
		return 1;
	}
	Options options = Settings(argc,argv).getOptions();

	if(options.gameType == "wrong" || options.cardType < 0 || (options.gameType == "tournament" && argc < 4))
		return 1;

	if(options.gameType == "fast")
		FastGame game(options);
	if(options.gameType == "detailed")
		DetailedGame game(options);
	if( options.gameType == "tournament")
		TournamentGame game(options);
	return 0;
}

// argv: detailed|fast|tournament   a|b|c   (имена стратегий)
