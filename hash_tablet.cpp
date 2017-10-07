#include <iostream>
#include <string>
#include <fstream>
typedef std::string key;

typedef struct Value {
	key name;
	unsigned age;
	unsigned weight;
} Value;

class hash_table {
public:
	hash_table(int n){
		parameters = new Value[n];
		for(int i = 0 ; i < n ; i++){
			parameters[i].name = "NULL";
			parameters[i].age = 0;
			parameters[i].weight = 0;
		}
		size = n;
	}
	~hash_table(){

	}

	hash_table(const hash_table& b){
		parameters = b.parameters;
	}

	int get_hash_key(const key& name){
		int index = 0;
		for(int i = 0 ; i < name.size() ; i++){
			index += name[i];
		}
		index = index % size;
		return(index);
	}

	void swap(hash_table& b){
		std :: swap (parameters, b.parameters);
		int k = size;
		size = b.size;
		b.size = k;
	}

	hash_table& operator=(const hash_table& b){
		parameters = b.parameters;
		size = b.size;
	}

	void clear(){
		delete(parameters);
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

	bool insert(const key& k, Value& v){
		int index = get_hash_key(k);
		parameters[index] = v;
		if(parameters[index] == v)
			return 0;
		return 1;
	}

	bool contains(const key& k) const{
		int index = get_hash_key(k);
		if (parameters[index].name != "NULL")
			return 0;
		return 1;
	}

	Value& operator[](const key& k){

	}

	Value& at(const key& k){
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

	friend bool operator==(const hash_table & a, const hash_table & b);
  	friend bool operator!=(const hash_table & a, const hash_table & b);

private:
	Value *parameters;
	unsigned int size;
}

hash_table *read(char *str){
	std :: ifstream input(str);
	hash_table *students = new hash_table(256);
	while(!input.eof()){
		Value tmp;
		input >> tmp.name;
		input >> tmp.age;
		input >> tmp.weight;
		if(tmp.name.empty() || tmp.age < 1 || tmp.weight < 1){
			break;
		}
		students.insert(name , tmp );
	}
	return (students);
}

int main(int argc , char *argv)
{
	hash_table *students = read(argv[1]);
	delete(students);
	return 0;  
}