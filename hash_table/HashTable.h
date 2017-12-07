#ifndef _HASHTEBLE_
#define _HASHTEBLE_

#include <numeric>

const int defailt_capacity = 32;

struct value {
	int age = 0;
	int weight = 0;
	value(){}
	value(int a , int w){
		age = a;
		weight = w;
	}
};

typedef std::string key;

template<class key , class value>
struct basic_NODE{
	key name;
	value parameters;
	basic_NODE *next = nullptr;
	bool flag = false;

	basic_NODE(){}

	void operator =(const basic_NODE& b){
		name = b.name;
		parameters = b.parameters;
		flag = 1;
		next = b.next;
	}
};

typedef basic_NODE<key,value> NODE;

bool operator ==(const value& a , const value& b){
	if(a.age != b.age || a.weight != b.weight)
		return 0;
	return 1;
}

bool operator !=(const value& a , const value& b){
	if( a == b )
		return 0;
	return 1;
}

template<class N>
class basic_hash_table {
public:
	basic_hash_table(): capacity(defailt_capacity){
		array = new N[defailt_capacity];
		capacity = defailt_capacity;
		size = 0;
	}

	basic_hash_table(int n ): size(n){
		array = new N[n];
		capacity = n;
		size = 0;
	}

	basic_hash_table(const basic_hash_table& b) : array(b.array) , size(b.size) , capacity(b.capacity) {}

	~basic_hash_table(){
		for(int i = 0; i < capacity ; i++){
			if(array[i].next != nullptr)
				listDelete(array[i].next);
		}
		delete [] array;
	}

	void listDelete(N *a){
		if(a->next != nullptr){
			listDelete(a->next);
		}
		delete a;
	}

	int get_hash_key(const key& k){
		int index = 0;
		index = (std :: accumulate(k.begin() , k.end(), 0)) % capacity;
		return(index);
	}

	void swap(basic_hash_table& b){
		std :: swap(array , b.array);
		std :: swap(size , b.size);
		std :: swap(capacity , b.capacity);
	}

	basic_hash_table& operator = (const basic_hash_table& b){
		clear();
		array = new N [b.capacity];
		size = b.size;
		capacity = b.capacity;
		for(int i = 0 ; i < capacity ; i++){
			if(b.array[i].flag){
				array[i].name = b.array[i].name;
				array[i].parameters = b.array[i].parameters;
				array[i].flag = true;
			}
		}
	}

	bool insert(const key& k , const value& v){
		int index = get_hash_key(k);
		if( !contains(k) ){
			array[index].name = k;
			array[index].parameters = v;
			array[index].flag = true;
			size++;
			if( size * 2 >= capacity){
				resize();
			}
			return true;
		}
		N *a = array+index;
		while( a->next != nullptr )
			a = a->next;
		a->next = new N;
		a = a->next;
		a->name = k;
		a->parameters = v;
		a->flag = true;
		return true;
	}

	void resize(){
		capacity *= 3;
		N *new_array = new N [capacity];
		for(int i = 0 ; i < capacity/3 ; i++){
			if(array[i].flag){
				int index = get_hash_key(array[i].name);
				new_array[index] = array[i];
			}
		}
		delete [] array;
		array = new_array;
	}


	void clear(){
		for(int i = 0; i < capacity ; i++){
			if(array[i].next != nullptr)
				listDelete(array[i].next);
		}
		delete [] array;
		size = 0;
		capacity = defailt_capacity;
	}

	bool erase(const key& k){
		if( contains(k)){
			int index = get_hash_key(k);
			if(array[index].next != nullptr){
				if(array[index].name == k){
					N *a = array[index].next;
					array[index].name = array[index].next ->name;
					array[index].parameters = array[index].next -> parameters;
					array[index].next = array[index].next -> next;
					array[index].flag = true;
					delete a;
				}
				else{
					N *a = array+index;
					while( a->next->name != k){
						a = a->next;
					}
					N *b = a->next;
					a->next = a->next->next;
					delete b;				}
			}
			else{
				array[index].parameters.age = 0;
				array[index].parameters.weight = 0;
				array[index].flag = false;
			}
			return 1;
		}
		return 0;
	}

	bool contains(const key& k){
		return (array[get_hash_key(k)].flag);
	}

	value& at(const key& k){
		if( !contains(k))
			throw 1;
		int index = get_hash_key(k);
		N *a = array+index;
		while(a->name != k){
			a = a->next;
			if( a == nullptr){
				throw 2;
			}
		}
		return(a->parameters);
	}

	bool empty() const{
		for(int i = 0 ; i < capacity ; i++){
			if(array[i].flag){
				return 0;
			}
		}
		return 1;
	}

	int check_size(){
		return size;
	}

	int check_capacity(){
		return capacity;
	}

	friend bool operator == (const basic_hash_table & a, const basic_hash_table & b){
		if(a.size != b.size)
			return 0;
		for(int i = 0 ; i < a.size ; i++){
			if (a.array[i].parameters != b.array[i].parameters){
				return 0;
			}
		}
		return 1;
	};

 	friend bool operator != (const basic_hash_table & a, const basic_hash_table & b){
 		if(a == b)
 			return 0;
 		return 1;
 	};

private:
	N *array;
	int size;
	int capacity;
};

#endif
