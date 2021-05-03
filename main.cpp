#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace  std;
vector<vector<int>> matrixGeneator();
void vecOut(const vector<vector<int>> &);
bool matrixValidator(vector<vector<int>>);
int main()
{
    vector<vector<int>> matrix = matrixGeneator();
    vecOut(matrix);
    return 0;
}

vector<vector<int>> matrixGeneator()
{
    vector<int> nums = {1,2,3,4,5,6,7,8,0};
    int num ,ind;
    srand(time(nullptr));
    vector<vector<int>> res(3,vector<int> (3));
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
                num = rand() % 9;
                while(find(nums.begin(), nums.end(), num) == nums.end() || num ==-1 )
                    num = rand() % 9;
                ind = find(nums.begin(),nums.end(),num) - nums.begin();
                nums[ind] = -1;
            res[i][j]=num;
        }
    }
    return res;
}

void vecOut(const vector<vector<int>> & inp)
{
    cout<<endl;
    for(const auto & i : inp)
    {
        for(int j : i)
            cout<<j<<" ";
        cout<<endl;
    }
}

bool matrixValidator(vector<vector<int>> matrix)
{

}