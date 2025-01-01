#include <bits/stdc++.h>
/*
Tips
1. iota(vector.begin,vector.end,startnum) function
    The iota function fills the range [first, last) with sequentially increasing values, starting from the value specified by the third parameter.
    It is much faster than using a for loop to fill the range.
    The function is defined in the <numeric> header file.

2. std::max(a,b) function
    The std::max function returns the greater of the two values passed to it.
    It is defined in the <algorithm> header file.
*/

using namespace std;

int sol(int num, int weight, vector<pair<int, int>> &testVec)
{
    // initialize the dp vector with the size of weight
    vector<int> dp(weight + 1, 0);
    /*
    there was no need to use iota function
    why? because the dp vector is already initialized with 0
    and i don't need to fill the vector elements with actual wegihts
    cause i will use the index of the vector as the weight
    */
    // iota(dp.begin(), dp.end(), 0);

    // sort the items based on weight
    vector<pair<int, int>> items = testVec;
    for (int i = 0; i < num - 1; i++)
    {
        pair<int, int> temp = testVec[i];
        if (testVec[i].first > testVec[i + 1].first)
        {
            testVec[i] = testVec[i + 1];
            testVec[i + 1] = temp;
        }
    }

    /*
    weight = 7

    items  weight value
            3       6
            4       8
            5       12
            6       13

        Process

        1. Create an int[] with the size of weight
        2. Set the values of the array from index 0 to weight
        3. Starting from first item of dp vector and subtract the weight of the first item's weight from itmes vector
        4. if the result of the subtraction bigger than 0, set the value of the dp vector to the value of the first item in the items vector
        5. Repeat the process for the rest of the items

        0   1   2   3   4   5   6   7
    3   0   0   0   6   6   6   12  14
    4                   8   8   8   14
    5                       12  12  12
    6                           13  13  14
    */

    int maxValue = 0;

    for (int i = 0; i < items.size(); i++)
    {
        for (int j = weight; j >= items[i].first; j--)
        {
            dp[j] = max(dp[j], dp[j - items[i].first] + items[i].second);
        }
    }

    for (int i = 0; i <= weight; i++)
    {
        if (dp[i] > maxValue)
            maxValue = dp[i];
    }

    return maxValue;
}

void PrintItems(std::vector<std::pair<int, int>> &vec)
{
    cout << "W" << " " << "V" << endl;
    for (pair<int, int> p : vec)
        cout << p.first << " " << p.second << endl;
}

int main()
{
    int num = 4;
    int weight = 7;
    vector<pair<int, int>> items = {{6, 13}, {4, 8}, {3, 6}, {5, 12}};
    cout << sol(num, weight, items);
}