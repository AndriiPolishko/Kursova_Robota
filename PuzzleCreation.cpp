//
// Created by ramp8 on 19.05.2021.
//

#include "PuzzleCreation.h"

void matrOut(const vector<vector<int>> &matrix)
{
    cout<<endl;
    for(size_t i = 0;i<matrix.size();i++){
        for(size_t j = 0;j<matrix[i].size();j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;}
}

vector<int> fromMatrToArr(const vector<vector<int>> &matrix)
{
    vector<int> arr;
    for(size_t i = 0;i<matrix.size();i++)
        for(size_t j = 0;j<matrix[i].size();j++)
            arr.push_back(matrix[i][j]);
    return arr;
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

void arrOut(const vector<int> &arr )
{
    cout<<endl;
    for(size_t i=0;i<arr.size();i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

bool matrixValidator(const vector<vector<int>> &matrix)
{
    vector<int> arr = fromMatrToArr(matrix);
    if(numberOfInversions(arr)%2==0)
        return true;
    else
        return false;
}

int numberOfInversions(const vector<int> &arr)
{
    int inv=0;
    for(size_t i = 0;i<arr.size()-1;i++)

        for(size_t j = i+1;j<arr.size();j++)

            if (arr[j] && arr[i] && arr[i] > arr[j]) inv++;

    return inv;
}