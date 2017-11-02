#include <iostream>
#include <string>

class strategy_1{
private:
	int score;

public:
	strategy_1(){
		score = rand(11);
		score += rand(11);
	}

	void turn(){

	}
}

class game{ // ход в зависимости от режима
	private:
		int gameMod;
		int card;
		std :: string *strategy;

		int dealers_score;
	public:
		table(){
			gameMod = 1;
			card = 1;
		}
		~table(){}
}

class factory{ //создание игроков-стратегий
public:

}

int main(int argc , char *argv[]){
	if ( argc >= 1)
		char *mode = argv[1];
	char cards = "a";
	if ( argc >= 2 )
		cards = argv[2];
}

// argv: detailed|fast|tournament   a|b|c   (имена стратегий)