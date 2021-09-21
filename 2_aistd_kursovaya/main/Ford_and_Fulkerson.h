#pragma once
#include <iostream>
using namespace std;
class Ford_and_Fulkerson
{
private:
    int vert;
    int** matrix_for_graph;
    int from, to;
    int result_stream;
    char* name_of_vert;
    int dfs(int, int, bool*);
public:
    void readList(string);
    int maxFlow();
};