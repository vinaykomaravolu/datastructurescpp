#include <iostream>
#include <string>
#include <assert.h>
#include "hashmap.hpp"

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
        cout << i << endl;
        map_default.put(i, i);
    }
}
