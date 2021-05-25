#include "gtest/gtest.h"
#include "linkedlist.hpp"
#include <iostream>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <random>

using namespace std;

TEST(LinkedList, Initialize)
{
    LinkedList<int> ll;
    EXPECT_EQ(0, ll.size());
}

TEST(LinkedList, PushOne)
{
    LinkedList<int> ll;
    ll.push(1);
    EXPECT_EQ(1, ll.size());
}

TEST(LinkedList, PushMany)
{
    LinkedList<int> ll;
    for (int i = 0; i < 100; i++)
    {
        ll.push(i);
    }
    EXPECT_EQ(100, ll.size());
}

TEST(LinkedList, PopOne)
{
    LinkedList<int> ll;
    ll.push(1);
    ll.pop();
    EXPECT_EQ(0, ll.size());
}

TEST(LinkedList, PopMany)
{
    LinkedList<int> ll;
    for (int i = 0; i < 100; i++)
    {
        ll.push(i);
    }
    for (int i = 0; i < 100; i++)
    {
        ll.pop();
    }
    EXPECT_EQ(0, ll.size());
}

TEST(LinkedList, InsertOne)
{
    LinkedList<int> ll;
    for (int i = 0; i < 10; i++)
    {
        ll.push(i);
    }
    ll.insert(99, 5);
    EXPECT_EQ(99, ll.get(5));
    EXPECT_EQ(11, ll.size());
}

TEST(LinkedList, InsertMany)
{
    LinkedList<int> ll;
    for (int i = 0; i < 100; i++)
    {
        ll.push(i);
        ll.insert(99, 0);
        EXPECT_EQ(99, ll.get(0));
    }
}

TEST(LinkedList, RemoveOne)
{
    LinkedList<int> ll;
    for (int i = 0; i < 10; i++)
    {
        ll.push(i);
    }
    ll.remove(2);
    EXPECT_EQ(9, ll.size());
}

TEST(LinkedList, RemoveMany)
{
    LinkedList<int> ll;
    for (int i = 0; i < 100; i++)
    {
        ll.push(i);
    }
    for (int i = 0; i < 100; i++)
    {
        ll.remove(0);
    }
    EXPECT_EQ(0, ll.size());
}

TEST(LinkedList, StressTest)
{
    LinkedList<int> ll;
    int n = 10000;
    for (int i = 0; i < n; i++)
    {
        ll.push(i);
        EXPECT_EQ(i, ll.get(ll.size() - 1));
        ll.insert(i * 2, i / 2);
        ll.push(i);
        ll.insert(i * 2, i / 2);
        ll.push(i);
        ll.insert(i * 2, i / 2);
        ll.remove(0);
        ll.pop();
    }
    EXPECT_EQ(n * 4, ll.size());
}
