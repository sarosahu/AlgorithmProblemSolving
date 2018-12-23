#include <iostream>
#include <vector>
#include <string>
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

void
FindCommonSubsequence(vector<vector<int> >&D, string& result, const string& A, const string& B )
{
    int i = D.size()-1, j = D[D.size() - 1].size() - 1;

    while ( i > 0 && j > 0 ) {
        //cout << i << j << endl;
        if ( D[i][j] == D[i-1][j-1] + 1 && D[i][j] > D[i][j-1] && D[i][j] > D[i-1][j] && A[i-1] == B[j-1] ) 
        {
            result.append(1, A[i-1]);
            --i, --j;
        }
        else if ( D[i][j] == D[i-1][j] && D[i][j] == D[i][j-1] ) {
            --j;
        }
        else if ( D[i][j] == D[i-1][j] || D[i][j] == D[i][j-1] ) {
            if ( D[i][j] == D[i-1][j] ) {
                --i;
            } else {
                --j;
            }
        }
    }

    std::reverse(result.begin(), result.end());
    return;
}

string
ComputeLongestCommonSubsequence( const string& A, const string& B ) {

    vector<int> d (B.size() + 1, 0);
    vector<vector<int> > D(A.size() + 1, d);
    
    for ( int i = 1; i <= A.size(); ++i ) {
        for ( int j = 1; j <= B.size(); ++j ) {

            D[i][j] = A[i-1] == B[j-1] ? max(D[i-1][j-1] + 1, max(D[i][j-1], D[i-1][j]))
                                       : max(D[i][j-1], D[i-1][j]) ;
        }
    }

    print2DVectorElements(D);

    string result;

    FindCommonSubsequence(D, result, A, B);
    cout << "Result : " << result.c_str() << endl;
    return result;
}

int main()
{
    //string A = "Saroj";
    //string B = "Manoja";
    string A = "Sarojkumar";
    //string B = "Saroj";
    string B = "Satyabrata";
    string result = ComputeLongestCommonSubsequence(A,B);
    return 0;
}
