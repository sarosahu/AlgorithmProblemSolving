#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//enum class Operation { INSERT, DELETE, SUBSTITUTE };

void
printVectorElements( vector<int>& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        cout << "   " << list[i]; 
    }
    cout << endl;
}

void FetchOperations( string &A, string& B, const vector<vector<int> >& d, vector<string>& opList )
{

    int i = d.size() - 1, j = d[0].size() - 1;
    while ( i > 0 && j > 0 )
    {
        if ( d[i][j] == d[i-1][j] + 1 ) {
            string s(1, A[i-1]);
            s.append(" DELETED" );
            opList.emplace_back(s);
            --i;
        } else if ( d[i][j] == d[i][j-1] + 1 ) {
            string s(1, B[j-1]);
            s.append(" INSERTED" );
            opList.emplace_back(s);
            --j;
        } else {
            if ( d[i][j] == d[i-1][j-1] + 1 ) {
                string s(1, A[i-1]);
                s.append(" SUBSTITUTED WITH ");
                s.append(1, B[j-1]);
                opList.emplace_back(s);
            }
            --i, --j;
        }
    }
    cout << endl;
}

int
LevensteinDistance( string A, string B )
{
    if ( A.size() < B.size() )
    {
        swap( A, B );
    }

    vector<int> d(B.size() + 1, 0);
    vector<vector<int> > D( A.size() + 1, d );

    // Initialization
    iota(D[0].begin(), D[0].end(), 0);
    for ( size_t i = 0; i < D.size(); ++i )
    {
        D[i][0] = i;
    }

    for ( int i = 1; i <= A.size(); ++i )
    {
        for ( int j = 1; j <= B.size(); ++j )
        {
            D[i][j] = A[i-1] == B[j-1] ? D[i-1][j-1]: 1 + min ( D[i-1][j-1], min( D[i][j-1], D[i-1][j] ) );
        }
    }

    for ( int i = 0; i < D.size(); ++i ) {
        printVectorElements(D[i]);
    }

    // To find out what exact operations are needed to convert from A to B
    vector<string> opList;
    FetchOperations( A, B, D, opList );

    for ( const auto & op : opList )
    {
        cout << op.c_str() << endl;
    }
    return D.back().back();
}

int main()
{
    //string A = "sarojsa";
    //string B = "manoj";
    string A = "Orchestra";
    string B = "Carthorse";

    int d = LevensteinDistance( A, B );
    cout << "Levenstein distance = " << d << endl;
    return 0;
}
