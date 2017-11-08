#include <gtest/gtest.h>
#include <assert.h>
#include <string.h>
#include "HashTable.h"

TEST( contains , table){
	hash_table H;
	value V(28 , 80);
	ASSERT_EQ(H.contains("Timoti") , 0);
	H.insert("Timoti" , V);
	ASSERT_EQ(H.contains("Timoti") , 1);
	H.insert("itomiT" , V);
	ASSERT_EQ(H.contains("itomiT") , 1);
	ASSERT_EQ(H.contains("Timoti") , 1);
}

TEST(insert , table){
	hash_table H;
	value V(28 , 80);
	ASSERT_EQ(H.insert("BlackJack" , V) , 1);
	ASSERT_EQ(H.insert("BlackJakc" , V) , 1);
}

TEST ( at , table){
	hash_table H;
	value V(33 , 50);
	value B(55 , 77);
	ASSERT_ANY_THROW(H.at("Norris"));
	H.insert("sirroN" , B);
	H.insert("Norris", V);
	ASSERT_EQ(H.at("Norris") , V);
}

TEST ( empty , table){
	hash_table H;
	value V(33 , 50);
	value B(55 , 77);
	ASSERT_EQ(H.empty() , 1);
	H.insert("MC Donald" , V);
	ASSERT_EQ(H.empty() , 0);
	H.erase("MC Donald");
	ASSERT_EQ(H.empty() , 1);
}

TEST (erase , table){
	hash_table H;
	value V(33 , 50);
	value B(55 , 77);
	ASSERT_EQ(H.erase("Jagger") , 0);
	H.insert("reggaJ" , V);
	H.insert("Jagger" , B);
	ASSERT_EQ(H.erase("Jagger") , 1);
	ASSERT_ANY_THROW(H.at("Jagger"));
	H.insert("Jagger" , B);
	ASSERT_EQ(H.erase("reggaJ") , 1);
	ASSERT_EQ(H.at("Jagger") , B);
}

TEST ( resize , table){
	hash_table H(2);
	value V(33 , 50);
	ASSERT_EQ( H.check_capacity() , 2);
	H.insert("Bean" , V);
	ASSERT_EQ( H.check_capacity() , 6);
}

int main(int argc, char *argv[])
{
 	testing::InitGoogleTest(&argc, argv);
 	return RUN_ALL_TESTS();
}
