#include "Ford_and_Fulkerson.h"
#include <fstream>
void Ford_and_Fulkerson::readList(string file_name) {
	fstream file;
	char first_name, second_name;
	int weight;
	int edge;
	int count_name_of_vert = 0;

	file.open(file_name, ios::in);
	file >> vert >> edge;

	if (file.eof() || vert == 0) 
		throw out_of_range("Graph is empty");

	name_of_vert = new char[vert];
	int** checking_array;
	checking_array = (int**)malloc(sizeof(int*) * vert);

	if (!checking_array) {
		throw std::out_of_range("Allocation error");
		return;
	}
	else 
		matrix_for_graph = checking_array;

	for (size_t i = 0; i < vert; i++)
	{
		checking_array[i] = (int*)malloc(vert * sizeof(int));
		if (!checking_array[i]) { 
			throw std::out_of_range("Allocation error");
			return; 
		}
		else 
			matrix_for_graph[i] = checking_array[i];

		for (size_t j = 0; j < vert; j++)
			matrix_for_graph[i][j] = 0;

	}

	int first_found, second_found;
	for (size_t i = 0; i < edge; i++)
	{
		file >> first_name >> second_name >> weight;

		first_found = -1;
		for (size_t j = 0; j < count_name_of_vert; j++)
			if (name_of_vert[j] == first_name)
				first_found = j;

		if (first_found == -1)
		{
			name_of_vert[count_name_of_vert] = first_name;
			first_found = count_name_of_vert;
			count_name_of_vert++;
		}

		second_found = -1;
		for (size_t j = 0; j < count_name_of_vert; j++)
			if (name_of_vert[j] == second_name)
				second_found = j;

		if (second_found == -1)
		{
			name_of_vert[count_name_of_vert] = second_name;
			second_found = count_name_of_vert;
			count_name_of_vert++;
		}

		matrix_for_graph[first_found][second_found] = weight; //save in matrix
	}

	for (size_t i = 0; i < vert; i++)  //search for source and sink
	{
		if (name_of_vert[i] == 'S')
			from = i;
		else if (name_of_vert[i] = 'T')
			to = i;
	}
}

int Ford_and_Fulkerson::maxFlow() {
	int result_stream = 0;
	int to_add = 0;
	int temp_Ve, temp_price;
	bool* visited = new bool[vert];
	do
	{
		for (size_t i = 0; i < vert; i++)
			visited[i] = false;
		to_add = dfs(from, INT_MAX, visited);
		result_stream += to_add;
	} while (to_add > 0);  //while there is something to add

	return result_stream;
}

int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

int Ford_and_Fulkerson::dfs(int u, int c_min, bool* visited) {
	if (u == to)
		return c_min;
	visited[u] = true;
	int delt;
	for (size_t v = 0; v < vert; v++)
	{
		if (!visited[v] && (matrix_for_graph[u][v] > 0))
		{
			delt = dfs(v, min(c_min, matrix_for_graph[u][v]), visited);
			if (delt > 0) //change the network
			{
				matrix_for_graph[u][v] -= delt;
				matrix_for_graph[v][u] += delt;
				return delt;
			}
		}
	}

	return 0;
}