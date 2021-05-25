#include "gtest/gtest.h"
#include "cache.hpp"
#include <iostream>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <random>

using namespace std;

TEST(LRUCacheTest, Initialize)
{
    LRUCache<int, int> cache = LRUCache<int, int>(10);
    EXPECT_EQ(10, cache.size());
}

TEST(LRUCacheTest, PutOne)
{
    LRUCache<int, int> cache = LRUCache<int, int>(10);
    EXPECT_EQ(0, cache.currentsize());
    cache.put(10, 10);
    EXPECT_EQ(1, cache.currentsize());
}

TEST(LRUCacheTest, PutMany)
{
    LRUCache<int, int> cache = LRUCache<int, int>(10);
    EXPECT_EQ(0, cache.currentsize());
    for (int i = 0; i < 1000; i++)
    {
        cache.put(i, i);
    }
    EXPECT_EQ(10, cache.currentsize());
}

TEST(LRUCacheTest, GetOne)
{
    LRUCache<int, int> cache = LRUCache<int, int>(10);
    cache.put(10, 100);
    int val = cache.get(10);
    EXPECT_EQ(100, val);
}

TEST(LRUCacheTest, GetMany)
{
    LRUCache<int, int> cache = LRUCache<int, int>(10);
    cache.put(0, 0);
    for (int i = 1; i < 100; i++)
    {
        cache.put(i, i);
        EXPECT_EQ(i - 1, cache.get(i - 1));
    }
}

TEST(LRUCacheTest, PutGetLeastUsed)
{
    LRUCache<int, int> cache = LRUCache<int, int>(10);
    for (int i = 0; i < 5; i++)
    {
        cache.put(i, i);
    }
    EXPECT_EQ(0, cache.LRUValue());
    EXPECT_EQ(4, cache.MRUValue());
    EXPECT_EQ(2, cache.get(2));
    EXPECT_EQ(2, cache.MRUValue());
}

TEST(LRUCacheTest, StressTest)
{
    LRUCache<int, int> cache = LRUCache<int, int>(50);
    for (int i = 0; i < 10000; i++)
    {
        cache.put(i, i);
        EXPECT_EQ(i, cache.get(i));
        cache.put(0, 0);
    }
    EXPECT_EQ(0, cache.MRUValue());
}