#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace  std;

vector<vector<int>> matrixGeneator();
void matrOut(const vector<vector<int>> &);
vector<int> fromMatrToArr(vector<vector<int>> matrix);
void arrOut(vector<int>);
bool matrixValidator(vector<vector<int>> );
int numberOfInversions(vector<int> matrix);

////////////////////////////////////////////
int main()
{
    vector<vector<int>> matrix = matrixGeneator();
    matrOut(matrix);
    bool res = matrixValidator(matrix);
    char choice;

    if(res == false){
        cout<<"This puzzle is unsolvable.\nPrint 'Y' if you want to generate new puzzle.\n";
    cin>>choice;
    if(choice=='Y')
    {
        do
            {
            matrix = matrixGeneator();
            res = matrixValidator(matrix);
            }
        while(res== false);
    }
    cout<<"\nYour new puzzle : ";
    matrOut(matrix);}
    return 0;
}
////////////////////////////////////////////
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

void matrOut(const vector<vector<int>> & inp)
{
    cout<<endl;
    for(const auto & i : inp)
    {
        for(int j : i)
            cout<<j<<" ";
        cout<<endl;
    }
    cout<<endl;
}

vector<int> fromMatrToArr(vector<vector<int>> matrix)
{
    vector<int> res;
    for(size_t i = 0;i<3;i++)
    {
        for(size_t j = 0;j<3;j++)
        {
            //cout<<matrix[i][j]<<" ";
            res.push_back(matrix[i][j]);
        }

    }

    return res;
}
void arrOut(vector<int>arr)
{
    cout<<endl;
    for(size_t i=0;i<arr.size();i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}
bool matrixValidator(vector<vector<int>> matrix)
{
    vector<int> arr = fromMatrToArr(matrix);
    if(numberOfInversions(arr)%2==0)
        return true;
    else
        return false;
}
int numberOfInversions(vector<int> arr)
{
    int inv=0;
    for(size_t i = 0;i<arr.size()-1;i++)

        for(size_t j = i+1;j<arr.size();j++)

            if (arr[j] && arr[i] && arr[i] > arr[j]) inv++;

    return inv;
}