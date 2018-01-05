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

bool operator ==(const value& a , const value& b){
	if(a.age != b.age || a.weight != b.weight)
		return false;
	return true;
}

bool operator !=(const value& a , const value& b){
	return !(a == b);
}

typedef std::string key;

template<class key , class value>
class basic_hash_table {
public:
	basic_hash_table(): capacity(defailt_capacity){
		array = new NODE[defailt_capacity];
		capacity = defailt_capacity;
		size = 0;
	}

	basic_hash_table(int n ): size(n){
		array = new NODE[n];
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

	struct NODE{
		key name;
		value parameters;
		NODE *next = nullptr;
		bool flag = false;

		NODE(){}

		NODE(key k , value v ) : name(k) , parameters(v) , flag(true){}

		NODE(const NODE& b) : name(b.name) , parameters(b.parameters) , flag(true){}

		void operator =(const NODE* b){
			name = b->name;
			parameters = b->parameters;
			flag = true;
			next = b->next;
		}
	};

	void listDelete(NODE *a){
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

	basic_hash_table& operator = (const basic_hash_table *b){
		if( this == b){
			return this;
		}
		clear();
		array = new NODE [b.capacity];
		size = b.size;
		capacity = b.capacity;
		for(int i = 0 ; i < capacity ; i++){
			if(b.array[i].flag){
				array[i] = b.array[i];
				NODE *tmpA = array[i];
				while(tmpA->next != nullptr){
					NODE *tmp = new NODE;
					tmp = tmpA->next;
					*(tmpA->next) = tmp;
					tmpA = tmpA->next;
				}
			}
		}
	}

	bool insert(const key& k , const value& v){
		int index = get_hash_key(k);
		if( !contains(k) ){
			array[index] = NODE(k , v);
			size++;
			if( size * 2 >= capacity){
				resize();
			}
			return true;
		}
		NODE *a = array+index;
		while( a->next != nullptr )
			a = a->next;
		a->next = new NODE(k ,v);
		return true;
	}

	void resize(){
		capacity *= 3;
		NODE *new_array = new NODE [capacity];
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
					NODE *a = array[index].next;
					array[index] = array[index].next;
					delete a;
				}
				else{
					NODE *a = array+index;
					while( a->next->name != k){
						a = a->next;
					}
					NODE *b = a->next;
					a->next = a->next->next;
					delete b;				}
			}
			else{
				array[index].parameters.age = 0;
				array[index].parameters.weight = 0;
				array[index].flag = false;
			}
			return true;
		}
		return false;
	}

	bool contains(const key& k){
		return (array[get_hash_key(k)].flag);
	}

	value& at(const key& k){
		if( !contains(k))
			throw 1;
		int index = get_hash_key(k);
		NODE *a = array+index;
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
				return false;
			}
		}
		return true;
	}

	int check_size(){
		return size;
	}

	int check_capacity(){
		return capacity;
	}

	friend bool operator == (const basic_hash_table &a, const basic_hash_table &b){
		if(a.size != b.size)
			return false;
		for(int i = 0 ; i < a.capacity ; i++){
			if(a.array[i].flag){
				if(!b.contains(a.array[i].name)){
					return false;
				}
			}
		}
		return true;
	};

 	friend bool operator != (const basic_hash_table & a, const basic_hash_table & b){
 		return !(a==b);
 	};

private:
	NODE *array;
	int size;
	int capacity;
};

#endif
