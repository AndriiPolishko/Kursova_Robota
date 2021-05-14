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

struct Puzzle
{
    vector<int> state;
    vector<int> ancestor;
};

const vector<int> SOLVED = { 1,2,3,4,5,6,7,8,0 };
//ancestor for given puzzle to detect last step
const vector<int> F_ANC = {0,0,0,0,0,0,0,0};
vector<Puzzle> route;


class node
        {
    vector<int> curState;
    int gap;
    //check where gap is curently is
    int gapDetector(vector<int>curState);

    //moving the gap on the puzzle
    vector<int> toLeft(vector<int> curState);
    vector<int> toRight(vector<int> curState);
    vector<int> toUp(vector<int> curState);
    vector<int> toDown(vector<int> curState);

    void state_out(vector<int> state);
    vector<Puzzle> steps;

    //check of available moves
    static bool canLeft(int &gap);
    static bool canRight(int &gap);
    static bool canUp(int &gap);
    static bool canDown(int &gap);

    //function for nice visualisation of puzzle state
    void arrToMatr(vector<int> arr);

    //function to show steps needed to get to the finale state
    void showSteps(vector<vector<int>> path);

public:
    Puzzle solved_node;

    node(vector<int> curState)
    {
        this->curState = curState;
    }

    node()
    {this->curState = SOLVED;}

    //function for BFS search
    void BFS();

    //function to get the path to the result state
    void path();
        };


int main()
{
    vector<vector<int>> matrix = matrixGeneator();
    bool res = matrixValidator(matrix);
    if(!res)
    {
        do
            {
            matrix = matrixGeneator();
            res = matrixValidator(matrix);
            }
        while(!res);
    }
    //puzzle that can be solved : {2,5,3,1,0,7,4,8,6} , {2,8,4,1,0,3,7,6,5}
    vector<int> arr = fromMatrToArr(matrix);
    node test(arr);
    test.BFS();
    cout<<endl<<"Steps to solution :";
    test.path();
    return 0;
}

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

bool node::canLeft(int &gap) {return gap!=0 && gap!=3 && gap!=6;}
bool node::canRight(int &gap) {return gap!=2 && gap!=5 && gap!=8;}
bool node::canUp(int &gap) {return gap>2;}
bool node::canDown(int &gap) {return gap<6;}

void node::BFS() {
    Puzzle branch,temp_branch;
    branch.state = curState;
    branch.ancestor = F_ANC;
    vector<int> temp_state;
    list<Puzzle> queue;
    queue.push_back(branch);
    while(!queue.empty())
    {
        branch = queue.front();
        route.insert(route.begin(),branch);
        if(branch.state == SOLVED)
        {
            solved_node = branch;
            break;
        }
        queue.pop_front();
        gap = gapDetector(branch.state);
        if(canRight(gap))
        {
            temp_state = toRight(branch.state);
            if(temp_state !=branch.ancestor)
            {
                temp_branch.ancestor = branch.state;
                temp_branch.state = temp_state ;
                queue.push_back(temp_branch);
            }
        }
        if(canUp(gap))
        {
            temp_state  = toUp(branch.state);
            if(temp_state !=branch.ancestor)
            {
                temp_branch.ancestor = branch.state;
                temp_branch.state = temp_state ;
                queue.push_back(temp_branch);
            }
        }
        if(canDown(gap))
        {
            temp_state  = toDown(branch.state);
            if(temp_state !=branch.ancestor)
            {
                temp_branch.ancestor = branch.state;
                temp_branch.state = temp_state ;
                queue.push_back(temp_branch);
            }
        }
        if(canLeft(gap))
        {
            temp_state  = toLeft(branch.state);
            if(temp_state !=branch.ancestor)
            {
                temp_branch.ancestor = branch.state;
                temp_branch.state = temp_state ;
                queue.push_back(temp_branch);
            }
        }
    }
}

void node::arrToMatr(vector<int> arr) {
    for(int i = 0;i<arr.size();i++)
    {
        cout<<arr[i]<<" ";
        if((i+1)%3==0)
            cout<<endl;

    }
}

void node::showSteps(vector<vector<int>> path) {
    for(int i = 0;i<path.size();i++)
    {
        cout<<endl;
        arrToMatr(path[i]);

    }
}

void node::path() {
    vector<vector<int>> steps;
    Puzzle state = route[0];
    steps.insert(steps.begin(),state.state);
    for(Puzzle i : route)
    {
        if(i.state==state.ancestor)
        {
            state = i;
            steps.insert(steps.begin(),state.state);
            //state_out(state.state);
        }
        if(i.ancestor == F_ANC)
            break;
    }
    showSteps(steps);
}

vector<int> node::toDown(vector<int> curState) {
    int gap_lock = gapDetector(curState);
    int temp = curState[gap_lock+3];
    curState[gap_lock+3] = 0;
    curState[gap_lock] = temp;
    return curState;
}

vector<int> node::toUp(vector<int> curState) {
    int gap_lock = gapDetector(curState);
    int temp = curState[gap_lock-3];
    curState[gap_lock-3] = 0;
    curState[gap_lock] = temp;
    return curState;
}

vector<int> node::toRight(vector<int> curState) {
    int gap_lock = gapDetector(curState);
    int temp = curState[gap_lock+1];
    curState[gap_lock+1] = 0;
    curState[gap_lock] = temp;
    return curState;
}

vector<int> node::toLeft(vector<int> curState) {
    int gap_lock = gapDetector(curState);
    int temp = curState[gap_lock-1];
    curState[gap_lock-1] = 0;
    curState[gap_lock] = temp;
    return curState;
}

int node::gapDetector(vector<int> curState) {
    for(size_t i = 0;i<curState.size();i++)
        if(curState[i]==0)
            return i;
}

void node::state_out(vector<int> state) {
    cout<<endl;
    for(int i : state)
        cout<<i<<" ";
}
