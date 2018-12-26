/** 
 * A fisherman is in a rectangular sea. The value of the fish at point (i,j) in the sea is
 * specified by an nxm array path. Write a program that computes the maximum value of fish a
 * fisherman can catch on a path from the upper leftmost point to the lower rightmost point.
 */
#include <iostream>
#include <vector>
using namespace std;

void
print1DVectorElements( const vector<int>& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        cout << "   " << list[i]; 
    }
    cout << endl;
}

void
print2DVectorElements( const vector<vector<int> >& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        print1DVectorElements(list[i]);
    }
    cout << endl;
}

void
FetchPathOfMaxProfit( const vector<vector<int> >&path, vector<pair<int, int> > &idx_path)
{

    int i = path.size() - 1, j = path[path.size() - 1].size() - 1;
    idx_path.emplace_back(i,j);
    while ( i > 0 && j > 0 ) {
        int profit_val = path[i][j];
        if ( path[i][j-1] > path[i-1][j] ) {
            --j;
        } //else if ( path[i-1][j] > path[i][j-1] ) {
        else {
            --i;
        }
        idx_path.emplace_back(i,j);
    }
    idx_path.emplace_back(0,0);
}

int 
ComputeMaxProfit( vector<vector<int> > path, vector<pair<int,int> >& idx_path )
{

    //print2DVectorElements(path);
    for ( int i = 0; i < path.size(); ++i ) {
        for ( int j = 0; j < path[i].size(); ++j ) {
            path[i][j] += max( i<1 ? 0 : path[i-1][j], j<1 ? 0 : path[i][j-1] );
        }
    }
    print2DVectorElements(path);

    // Backtrack the path and keep into idx_path
    FetchPathOfMaxProfit(path, idx_path);
    return path.back().back();
}

int main()
{
    vector<vector<int> > path;
    vector<int> d1({0,0,10,5,0});
    vector<int> d2({0,20,15,0,0});
    vector<int> d3({0,5,5,10,20});
    vector<int> d4({10,0,30,0,5});
    vector<int> d5({5,5,5,0,1});
    path.emplace_back(d1);
    path.emplace_back(d2);
    path.emplace_back(d3);
    path.emplace_back(d4);
    path.emplace_back(d5);
    //cout << "size : " << d1.size() << endl;

    vector<pair<int, int> > idx_path;
    int result = ComputeMaxProfit(path, idx_path);
    cout << "The max profit is : " << result << endl;

    for ( int i = 0; i < idx_path.size(); ++i ) {
        cout << "(" << idx_path[i].first << ", " << idx_path[i].second << ")" << endl;
    }

    return 0;
}
