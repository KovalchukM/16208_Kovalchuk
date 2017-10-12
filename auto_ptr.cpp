#include <iostream>

struct A {
	A() {
		std :: cout << "A constructed" << std :: endl;
	}
	~A() {
		std :: cout << "A destructed" << std :: endl;
	}
};


class smartPointer{
public:
	smartPointer(){}

	smartPointer(A *a) : a(a_) {

	}

	smartPointer( smartPointer & ptr){
		a = ptr.a;
		ptr.a = NULL;
		//1. скопировать указатель из ptr
		//2. занулить указатель в ptr
	}

	smartPointer& operator = (smartPointer& ptr){
		if( a != ptr.a){
			if( a != NULL)
				delete a;
			a = ptr.a;
			ptr.a = NULL;
		}
		// 0. проверка присваивания самому себе
		// 1. освободить свой ресурс (если есть)
		// 2. далее см констуктор копирования
	}
	
	A *get(){
		if(a == NULL)
			return NULL;
		return (a);
	}

	A *release(){
		A *b = a;
		return( b.get());
	}

	~smartPointer() {
		std :: cout << "smartPointer destructor" << std :: endl;
		delete a;
	}
private:
	A *a;
};

void f(){
	throw 1;
}

void x(smartPointer){

}

void g(){
	smartPointer ptr(new A);
	x(ptr);
	f();
}

int main(){
	try{
		g();
	} catch (int x){
		std :: cout << "caught x = " << x << std :: endl;
	}
	return 0;
}