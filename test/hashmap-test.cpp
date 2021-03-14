#include "gtest/gtest.h"
#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <random>

using namespace std;

TEST(HashMapTest, Initialize)
{
    HashMap<int, int> map_default = HashMap<int, int>();
    HashMap<int, int> map_sized_large = HashMap<int, int>(2048);
    HashMap<int, int> map_sized_small = HashMap<int, int>(16);
    HashMap<int, int> map_sized_single = HashMap<int, int>(1);
    EXPECT_EQ(0, map_default.size());
    EXPECT_EQ(0, map_sized_large.size());
    EXPECT_EQ(0, map_sized_small.size());
    EXPECT_EQ(0, map_sized_single.size());
}

TEST(HashMapTest, Put)
{
    HashMap<int, int> map_default = HashMap<int, int>();
    map_default.put(1, 1);
    EXPECT_EQ(1, map_default.size());
}

TEST(HashMapTest, Remove)
{
    HashMap<int, int> map_default = HashMap<int, int>();
    map_default.put(1, 1);
    map_default.remove(1);
    EXPECT_EQ(0, map_default.size());
}

TEST(HashMapTest, PutRemoveManyDefaultSize)
{
    HashMap<int, int> map_default = HashMap<int, int>();
    for (int i = 0; i < 10000; i++)
    {
        map_default.put(i, i);
    }
    EXPECT_EQ(10000, map_default.size());
    for (int i = 0; i < 10000; i++)
    {
        map_default.remove(i);
    }
    EXPECT_EQ(0, map_default.size());
}

TEST(HashMapTest, PutRemoveManyLargeSize)
{
    HashMap<int, int> * map_sized_large = new HashMap<int, int>(2048);
    for (int i = 0; i < 10000; i++)
    {
        map_sized_large->put(i, i);
    }
    EXPECT_EQ(10000, map_sized_large->size());
    for (int i = 0; i < 10000; i++)
    {
        map_sized_large->remove(i);
    }
    EXPECT_EQ(0, map_sized_large->size());
}


TEST(HashMapTest, PutRemoveManySmallSize)
{
    HashMap<int, int> map_sized_small = HashMap<int, int>(16);
    for (int i = 0; i < 10000; i++)
    {
        map_sized_small.put(i, i);
    }
    EXPECT_EQ(10000, map_sized_small.size());
    for (int i = 0; i < 10000; i++)
    {
        map_sized_small.remove(i);
    }
    EXPECT_EQ(0, map_sized_small.size());
}

TEST(HashMapTest, PutRemoveManySingleSize)
{
    HashMap<int, int> map_sized_single = HashMap<int, int>(1);
    for (int i = 0; i < 10000; i++)
    {
        map_sized_single.put(i, i);
    }
    EXPECT_EQ(10000, map_sized_single.size());
    for (int i = 0; i < 10000; i++)
    {
        map_sized_single.remove(i);
    }
    EXPECT_EQ(0, map_sized_single.size());
}

TEST(HashMapTest, GetValueFromKey)
{
    HashMap<string, int> map = HashMap<string, int>();
    map.put("testA", 1);
    map.put("testB", 2);
    int * A = map.get("testA");
    int * B = map.get("testB");
    EXPECT_EQ(1, *A);
    EXPECT_EQ(2, *B);
}

TEST(HashMapTest, GetValueFromUndefinedKey)
{
    HashMap<string, int> map = HashMap<string, int>();
    map.put("testA", 1);
    int * A = map.get("testB");
    EXPECT_EQ(NULL, A);
}

TEST(HashMapTest, DifferentTypes)
{
    HashMap<string, int> map_string_int = HashMap<string, int>();
    HashMap<int, string> map_int_string = HashMap<int, string>();
    HashMap<string, bool> map_string_bool = HashMap<string, bool>();
    HashMap<int *, string> map_intp_string = HashMap<int *, string>();

    map_string_int.put("testA", 1);
    map_int_string.put(1, "testA");
    map_string_bool.put("testA", true);
    int * testA = new int(1);
    int * testB = testA;
    map_intp_string.put(testA,"testA");

    EXPECT_EQ(1, *map_string_int.get("testA"));
    EXPECT_EQ("testA", *map_int_string.get(1));
    EXPECT_EQ(true, *map_string_bool.get("testA"));
    EXPECT_EQ("testA", *map_intp_string.get(testB));
}

TEST(HashMapTest, StressTest){
    HashMap<int, int> map = HashMap<int, int>(1);
    srand(time(0));
    int rando_iteration_size = rand() % 1000 + 500;
    for(int i = 0; i < 1000; i++){
        int random_item_size = rand() % 500;
        int random_multiplier = rand() % 100;
        cout << rando_iteration_size << " " << random_item_size << endl;
        for(int y = 0; i < random_item_size; i++){
            map.put(i*random_multiplier,i*random_multiplier);
        }
        for(int y = 0; y < random_item_size; y++){
            map.remove(y*random_multiplier);
        }
    }
    EXPECT_EQ(0, map.size());
}
