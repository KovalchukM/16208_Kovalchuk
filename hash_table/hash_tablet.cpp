#include <iostream>
#include <string>

typedef std::string key;

typedef struct Value {
	int age;
	int weight;
	Value(){
		age = 0;
		weight =0;
	}
} value;

typedef struct NODE{
	value parameters;
	bool flag;
	NODE(){
		flag = 0;
	}
}NODE;

bool operator ==(const Value& a , const Value& b){
	if(a.age != b.age || a.weight != b.weight)
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
		array = new NODE[32];
		size = 32;
	}

	hash_table(int n ){
		array = new NODE[n];
		size = n;
	}

	~hash_table(){
		delete [] array;
	}

	hash_table(const hash_table& b){
		array = b.array;
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
		NODE *p = b.array;
		b.array = array;
		array = p;
		int k = size;
		size = b.size;
		b.size = k;
	}

	hash_table& operator = (const hash_table& b){
		delete(array);
		array = b.array;
		size = b.size;
	}

	void clear(){
		delete(array);
		size = 0;
	}

	bool erase(const key& k){
		int index = get_hash_key(k);
		array[index].parameters.age = 0;
		array[index].parameters.weight = 0;
		array[index].flag = 0;
		return 1;
	}

	bool insert(const key& k , const Value& v){
		int index = get_hash_key(k);
		if( !contains(k) ){
			array[index].parameters = v;
			return 1;
		}
		return 0;
	}

	bool contains(const key& k){
		int index = get_hash_key(k);
		if( !array[index].flag)
			return 0;
		return 1;
	}

	Value& at(const key& k){
		if( !contains(k))
			throw 1;
		return(array[get_hash_key(k)].parameters);
	}
	// size_t size() const;{

	// }

	bool empty() const{
		for(int i = 0 ; i < size ; i++){
			if(array[i].flag == 1){
				return 0;
			}
		}
		return 1;
	}

	friend bool operator == (const hash_table & a, const hash_table & b){
		if(a.size != b.size)
			return 0;
		for(int i = 0 ; i < a.size ; i++){
			if (a.array[i].parameters != b.array[i].parameters){
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
	NODE *array;
	int size;
};

int main(int argc , char *argv[])
{
	hash_table students(256);
	return 0;  
}
