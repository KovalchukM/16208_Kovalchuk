#include <gtest/gtest.h>
#include <assert.h>
#include <string.h>
#include "HashTable.h"

TEST( contains , table){
	hash_table H;
	value V(28 , 80);
	std :: string s = "Timoti";
	ASSERT_EQ(H.contains(s) , 0);
	H.insert(s , V);
	ASSERT_EQ(H.contains(s) , 1);
}

TEST (insert , table){
	std :: string s = "BlackJack";
	hash_table H;
	value V(28 , 80);
	ASSERT_EQ(H.insert(s , V) , 1);
	H.insert( s , V);
	ASSERT_EQ(H.insert(s , V) , 0);
}

TEST (erase , table){
	hash_table H;
	value V(33 , 50);
	std :: string s = "Jagger";
	ASSERT_EQ(H.erase(s) , 0);
	H.insert(s , V);
	ASSERT_EQ(H.erase(s) , 1);
}

TEST ( empty , table){
	hash_table H;
	value V(33 , 50);
	std :: string s = "MC Donald";
	ASSERT_EQ(H.empty() , 1);
	H.insert(s , V);
	ASSERT_EQ(H.empty() , 0);
	H.erase(s);
	ASSERT_EQ(H.empty() , 1);
}

TEST ( at , table){
	hash_table H;
	value V(33 , 50);
	std :: string s = "Norris";
	ASSERT_ANY_THROW(H.at(s));
	H.insert(s , V);
	ASSERT_EQ(H.at(s) , V);

}

int main(int argc, char *argv[])
{
 	testing::InitGoogleTest(&argc, argv);
 	return RUN_ALL_TESTS();
}
