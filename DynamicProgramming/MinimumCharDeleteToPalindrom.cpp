#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

void
print1DVectorElements( vector<int>& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        cout << "   " << list[i]; 
    }
    cout << endl;
}

void
print2DVectorElements( vector<vector<int> >& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        print1DVectorElements(list[i]);
    }
    cout << endl;
}

void FetchCharsInOrder( const vector<vector<int> >& D, string& result, const string& A, const string& B )
{
    int i = D.size() -1, j = D[D.size()-1].size() - 1;
    while ( i > 0 && j > 0 ) {
        if ( D[i][j] == D[i-1][j-1] && A[i-1] == B[j-1] ) {
            --i, --j;
        }
        else if ( D[i][j] == D[i-1][j] + 1 && D[i][j] == D[i][j-1] + 1 ) {
            result.append(1, A[i-1]);
            result.append(1, B[j-1]);
            --i, --j;
        }
        else if ( D[i][j] == D[i-1][j] + 1 || D[i][j] == D[i][j-1] + 1 ) {
            if ( D[i][j] == D[i-1][j] + 1 ) {
                result.append(1, A[i-1]);
                --i;
            }
            else {
                result.append(1, B[j-1]);
                --j;
            }
        }
    }

    //std::reverse( result.begin(), result.end() );
}

int
MinimumCharDeleteToPalindrom( const string& B )
{

    int sz = B.size()/2 + 1;
    vector<int> d(sz+1, 0);
    vector<vector<int> > D(sz+1, d );
    string A = B.substr(sz - 1, sz);
    std::reverse(A.begin(), A.end());

    cout << B.c_str() << endl;
    cout << A.c_str() << endl;

    iota(D[0].begin(), D[0].end(), 0);
    for ( int i = 0; i < D.size(); ++i )
    {
        D[i][0] = i;
    }

    for ( int i = 1; i < D.size(); ++i ) {
        for ( int j = 1; j < D[i].size(); ++j ) {
            if ( A[i-1] == B[j-1] ) {
                D[i][j] = D[i-1][j-1];
            }
            else {
                D[i][j] = min(D[i-1][j], D[i][j-1]) + 1;
            }
        }
    }

    print2DVectorElements(D);
    string result;
    FetchCharsInOrder(D, result, A, B);
    cout << result.c_str() << endl;
    
    assert( D.back().back() == result.size() );
    return D.back().back();
}

int main()
{
    //string str = "aejbcgbda";
    string str = "abcba";
    //string str = "aejbcgbdas";
    int i  = MinimumCharDeleteToPalindrom(str);
    return 0;
}
