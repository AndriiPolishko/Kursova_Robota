#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <list>

using namespace  std;

vector<vector<int>> matrixGeneator();
void matrOut(const vector<vector<int>> &);
vector<int> fromMatrToArr(const vector<vector<int>> &);
void arrOut(const vector<int> &);
bool matrixValidator(const vector<vector<int>> &);
int numberOfInversions(const vector<int> &);