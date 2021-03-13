#include "gtest/gtest.h"
#include "hashmap.hpp"
#include <iostream>
#include <string>
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
}

TEST(HashMapTest, PutRemoveManyLargeSize)
{
    HashMap<int, int> * map_sized_large = new HashMap<int, int>(2048);
    for (int i = 0; i < 10000; i++)
    {
        cout << i << endl;
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
