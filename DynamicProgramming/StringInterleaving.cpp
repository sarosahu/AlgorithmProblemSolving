#include <iostream>
#include <vector>
#include <string>
using namespace std;

void
print1DVectorElements( vector<bool>& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        cout << "   " << list[i]; 
    }
    cout << endl;
}

void
print2DVectorElements( vector<vector<bool> >& list )
{
    for ( int i = 0; i < list.size(); ++i )
    {
        print1DVectorElements(list[i]);
    }
    cout << endl;
}

// Calculate if string t is a interleaving of 2 strings s1 and s2.
bool IsStringInterleavingOf2Strings( const string &s1, const string &s2, const string &t )
{
    vector<bool> d(s1.size() + 1, false);
    vector<vector<bool> > D(s2.size() + 1, d); 

    D[0][0] = true;

    // Fill up the first row
    for ( int i = 1; i <= s1.size(); ++i ) {
        if ( D[0][i-1] == true && s1[i-1] == t[i-1] ) {
            D[0][i] = true;
        }
    }

    // Fill up the first column
    for ( int i = 1; i <= s2.size(); ++i ) {
        if ( D[i-1][0] == true && s2[i-1] == t[i-1] ) {
            D[i][0] = true;
        }
    }

    for ( int i = 1; i < D.size(); ++i ) {
        for ( int j = 1; j < D[i].size(); ++j ) {
            if ( D[i-1][j] == true && s2[i-1] == t[i+j-1] ) {
                D[i][j] = true;
            }
            else if ( D[i][j-1] == true && s1[j-1] == t[i+j-1] ) {
                D[i][j] = true;
            }
        }
    }

    print2DVectorElements(D);
    return D.back().back();
}

int main() 
{
    string s1 = "atc";
    string s2 = "gtaa";

    //string t = "gattaca";
    //string t = "gtataac";
    string t = "gatacta";

    if ( IsStringInterleavingOf2Strings(s1, s2, t) ) {
        cout << "The string [" << t.c_str() << "] can be interleaved by using [" << s1.c_str() << "] and [" << s2.c_str() << "]" << endl;
    }
    else {
        cout << "The string [" << t.c_str() << "] can't be interleaved by using [" << s1.c_str() << "] and [" << s2.c_str() << "]" << endl;
    }
    return 0;
}

