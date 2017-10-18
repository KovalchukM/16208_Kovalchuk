#include <iostream>
#include <string>
#include <fstream>

#define DEFAULT_SIZE 32

typedef std::string key;

typedef struct Value {
	key name;
	unsigned age;
	unsigned weight;
} Value;

bool operator ==(const Value& a , const Value& b){
	if(a.name != b.name || a.age != b.age || a.weight != b.weight)
		return 0;
	return 1;
}

bool operator !=(const Value& a , const Value& b){
	if( a == b )
		return 0;
	return 1;
}

class hash_table {
public:
	hash_table(){
		parameters = new Value[DEFAULT_SIZE];
		for(int i = 0 ; i < DEFAULT_SIZE ; i++){
			parameters[i].name = "NULL";
			parameters[i].age = 0;
			parameters[i].weight = 0;
		}
		size = DEFAULT_SIZE;
	}

	hash_table(int n , char *str){
		parameters = new Value[n];
		for(int i = 0 ; i < n ; i++){
			parameters[i].name = "NULL";
			parameters[i].age = 0;
			parameters[i].weight = 0;
		}
		std :: ifstream input(str);
		while(!input.eof()){
			Value tmp;
			input >> tmp.name;
			input >> tmp.age;
			input >> tmp.weight;
			if(tmp.name.empty() || tmp.age < 1 || tmp.weight < 1){
				break;
			}
			insert( tmp );
		}
		size = n;
	}
	~hash_table(){
		delete (parameters);
	}

	hash_table(const hash_table& b){
		parameters = b.parameters;
		size = b.size;
	}

	int get_hash_key(const key& k){
		int index = 0;
		for(int i = 0 ; i < k.size() ; i++){
			index += k[i];
		}
		index = index % size;
		return(index);
	}

	void swap(hash_table& b){
		Value *p = b.parameters;
		b.parameters = parameters;
		parameters = p;
		int k = size;
		size = b.size;
		b.size = k;
	}

	hash_table& operator = (const hash_table& b){
		delete(parameters);
		parameters = b.parameters;
		size = b.size;
	}

	void clear(){
		delete(parameters);
		size = 0;
	}

	bool erase(const key& k){
		int index = get_hash_key(k);
		parameters[index].name = "NULL";
		parameters[index].age = 0;
		parameters[index].weight = 0;
		if(parameters[index].name == "NULL" && parameters[index].age == 0 && parameters[index].weight == 0)
			return 0;
		return 1;
	}

	bool insert(Value& v){
		int index = get_hash_key(v.name);
		parameters[index] = v;
		if(parameters[index] == v)
			return 0;
		return 1;
	}

	bool contains(const key& k){
		if (parameters == NULL)
			return 0;
		int index = get_hash_key(k);
		if (parameters[index].name != "NULL")
			return 0;
		return 1;
	}

	// Value& operator[](const key& k){
			
	// }

	Value& at(const key& k){
		if( parameters == NULL)
			throw 1;
		int index = get_hash_key(k);
		return(parameters[index]);
	}
	// size_t size() const;{

	// }

	bool empty() const{
		for(int i = 0 ; i < size ; i++){
			if(parameters[i].name != "NULL"){
				return 0;
			}
		}
		return 1;
	}

	friend bool operator == (const hash_table & a, const hash_table & b){
		if(a.size != b.size)
			return 0;
		for(int i = 0 ; i < a.size ; i++){
			if (a.parameters[i] != b.parameters[i]){
				return 0;
			}
		}
		return 1;
	};
 	friend bool operator != (const hash_table & a, const hash_table & b){
 		if(a == b)
 			return 0;
 		return 1;
 	};

private:
	Value *parameters;
	unsigned int size;
};

int main(int argc , char *argv[])
{
	hash_table students(256 , argv[1]);
	int n = 1;
	return 0;  
}