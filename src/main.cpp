#include <iostream>
#include <string>
#include <assert.h>
#include "hashmap.hpp"
#include "linkedlist.hpp"

using namespace std;

int main(int, char **)
{
    int size = 1;
    HashMap<int, string> map(size);
    map.put(-121, "121");
    map.put(-120, "120");
    map.put(-122, "122");
    map.put(-121, "42");
    HashMap<int, int> map_default = HashMap<int, int>();
    for (int i = 0; i < 100; i++)
    {
        map_default.put(i, i);
    }
    for (int i = 0; i < 100; i++)
    {
        map_default.remove(i);
    }

    LinkedList<int> ll;
    for (int i = 0; i <= 1000; i++)
    {
        ll.push(i * i);
        ll.remove(0);
        ll.push(i * i);
        ll.pop();
    }
    return 0;
}