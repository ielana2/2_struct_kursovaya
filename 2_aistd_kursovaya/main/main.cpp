#include <iostream>
#include "Ford_and_Fulkerson.h"
using namespace std;

int main()
{
    Ford_and_Fulkerson Alg;
    Alg.readList("test.txt");
    cout << Alg.maxFlow();
}