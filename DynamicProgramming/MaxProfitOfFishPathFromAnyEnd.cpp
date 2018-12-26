/** 
 * A fisherman is in a rectangular sea. The value of the fish at point (i,j) in the
 * sea is specified by an nxm array path. Write a program that computes the maximum
 * value of fish a fisherman can catch on a path from any end point to any end point.
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
FetchPathOfMaxProfit( const vector<vector<int> >&path, vector<pair<int, int> > &idx_path, int row_idx, int col_idx, const pair<int, int>& max_val_idx )
{

    //int i = path.size() - 1, j = path[path.size() - 1].size() - 1;
    int i = max_val_idx.first, j = max_val_idx.second;
    idx_path.emplace_back(i,j);
    while ( i > row_idx && j > col_idx ) {
        int profit_val = path[i][j];
        if ( path[i][j-1] > path[i-1][j] ) {
            --j;
        }
        else {
            --i;
        }
        idx_path.emplace_back(i,j);
    }

    while ( i > row_idx ) {
        idx_path.emplace_back(i-1,j);
        --i;
    }

    while ( j > col_idx ) {
        idx_path.emplace_back(i,j-1);
        --j;
    }
}

int 
ComputeMaxProfit( vector<vector<int> > path, vector<pair<int,int> >& idx_path, int row_idx, int col_idx )
{

    pair<int, int> max_value_idx(-1,-1);
    for ( int i = row_idx; i < path.size(); ++i ) {
        for ( int j = col_idx; j < path[i].size(); ++j ) {
            path[i][j] += max( i<row_idx+1 ? 0 : path[i-1][j], j<col_idx+1 ? 0 : path[i][j-1] );
            if ( i == 0 || i == path.size()-1 || j == 0 || j == path[i].size()-1 ) {
                if ( (max_value_idx.first == -1 && max_value_idx.second == -1) || 
                     (path[max_value_idx.first][max_value_idx.second] < path[i][j]) )
                {
                    max_value_idx.first = i, max_value_idx.second = j;
                }
            }
        }
    }
    print2DVectorElements(path);

    // Backtrack the path and keep into idx_path
    FetchPathOfMaxProfit(path, idx_path, row_idx, col_idx, max_value_idx);
    return path.back().back();
}

int main()
{
    vector<vector<int> > path;
    vector<int> d1({0,0,10,-5,10});
    vector<int> d2({0,0,-5,2,60});
    vector<int> d3({0,50,-30,0,-30});
    vector<int> d4({0,0,11,10,-5});
    vector<int> d5({0,5,-20,30,-20});
    path.emplace_back(d1);
    path.emplace_back(d2);
    path.emplace_back(d3);
    path.emplace_back(d4);
    path.emplace_back(d5);
    //cout << "size : " << d1.size() << endl;

    vector<pair<int, int> > idx_path;
    int result = ComputeMaxProfit(path, idx_path, 0, 2);
    cout << "The max profit is : " << result << endl;

    for ( int i = 0; i < idx_path.size(); ++i ) {
        cout << "(" << idx_path[i].first << ", " << idx_path[i].second << ")" << endl;
    }

    return 0;
}
