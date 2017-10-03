#include <iostream>
#include <string>
#include <fstream>
typedef struct Value {
  unsigned age;
  unsigned weight;
} Value;

class hash_table {
public:
	hash_table(){
		hash_table next == NULL;
		Value.age = 0;
		Value.weight = 0;
	}
	~hash_table(){

	}

	hash_table(const hash_table& b){
		parameters = b.parameters;
		name = b.name;
		next = b.next;
	}

	void swap(hash_table& b){
		std :: swap (tmp, b.tmp);
	}

	void clear(){
		
	}

	bool erase(const Key& k){

	}

	bool insert(const Key& k, const Value& v){

	}

	bool contains(const Key& k) const{

	}


	hash_table& operator=(const hash_table& b);

	void set_parameters(int a , int w){
		parameters.age = a;
		parameters.weight = w;
	}

	void set_name(std :: string new_name){
		name = new_name;
	}

	Value get_parameters(){
		return(parameters);		
	}

	std :: string get_name(){
		return(name);
	}

	hash_table *next;

private:
	std :: string name;
	Value parameters;
}

int get_hash_key(std :: string name){

}

void create_student(hash_table students , std :: string name , int age , int weight){
	hash_table *tpm = students;
	hash_table *tpm_prev == NULL;
	if((tmp.get_parameters()).age != 0){
		tpm_prev = tmp;
		while(tpm_prev.next != NULL){
			tpm = tpm.next;
			tpm_prev = tmp;
		}
		tmp = new hash_table;
		tpm_prev.next = tmp;
	}
	tmp.set_parameters(age , weight);
}

hash_table *read(char *str){
	std :: ifstream input(str);
	hash_table *students = new hash_table[256];
	while(!input.eof()){
		std :: string name;
		int age = 0;
		int weight = 0;
		input >> name;
		input >> age;
		input >> weight;
		if(name.empty() || age == 0 || weight == 0){
			break;
		}
		int key = get_hash_key(name);
		create_student(students[key] , name , age , weight);
	}
	return (students);
}

int main(int argc , char *argv)
{
	hash_table *students = read(argv[1]);
	delete(students);
	return 0;
}