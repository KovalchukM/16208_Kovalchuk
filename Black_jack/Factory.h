#ifndef FACTORY_H_
#define FACTORY_H_

#include <unordered_map>

template<class T>
class Creator{
	static T *create(){
		return (new T);
	}
};

template<class Product,
		 class Creator,
		 class ID>
class Factory {
public:
	Factory() {};
	typedef Strategy * (*creator_f)(); //Указатель на функцию, создающую какой-то объект класса Strategy 

//В двух словах себе. Я здесь создаю один глобальный объект и пользуюсь только им. 
//Как я понял, это называется синглтон. Я не должен больше нигде обявлять обекты этого класса. 
//Доступ к методам объекта осуществляется через Factory::get_instance().метод 
	static Factory* get_instance() {
		static Factory f;
		return &f;
	} 

	bool register_strat(const ID& id, Creator creator) {
		return creators.insert({id, creator}).second;
	}

	Product* create(const ID& id) {
		if(creators.find(id) == creators.end()){
			return nullptr;
		}
		return creators[id]();
	}

	~Factory(){}
private:
	std::unordered_map<ID, Creator> creators;
};

typedef Factory<Strategy, Strategy*(*)(), std::string> factory;

#endif
