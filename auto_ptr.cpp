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
	smartPointer(){

	}

	smartPointer(A *a) : a_(a) {

	}

	smartPointer( smartPointer & ptr){
		a_ = ptr.a_;
		ptr.a_ = NULL;
		//1. скопировать указатель из ptr
		//2. занулить указатель в ptr
	}

	smartPointer& operator=(smartPointer& ptr){
		if( a_ == ptr.a_){
			
		}
		delete a_;
		a_ = ptr.a;
		ptr.a_ = NULL;
		// 0. проверка присваивания самому себе
		// 1. освободить свой ресурс (если есть)
		// 2. далее см констуктор копирования
	}
	
	A *get(){}

	A *release(){}

	~smartPointer() {
		std :: cout << "smartPointer destructor" << std :: endl;
		delete a_;
	}
private:
	A *a_;
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