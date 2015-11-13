#include <iostream>

using std::string;
using std::cout;

#define _DEBUG  1

void usage();
int calc_LCS(string a, string b);

int main(int argv, char **argc)
{
    if (argv != 3) {
        usage();
        exit(1);
    }

    string a, b;
    a = argc[1];
    b = argc[2];

    cout << calc_LCS(a, b) << std::endl;  
        
    return 0;
};

void usage()
{
    cout << "./lcs [word_1] [word_2]\n";
}

int calc_LCS(string a, string b)
{
    int a_len = a.length();
    int b_len = b.length();
    int lcs_len = 0;
    int lcs_mtx[a_len + 1][b_len + 1];

    // initialize dynamic programming matrix
    for (int y = 0; y < b_len + 1; y++) { lcs_mtx[0][y] = 0; }
    for (int x = 0; x < a_len + 1; x++) { lcs_mtx[x][0] = 0; }

    // populate matrix
    for (int y = 1; y <= b_len; y++) {
        for (int x = 1; x <= a_len; x++) {
           
            if (a[x - 1] == b[y - 1])
                lcs_mtx[x][y] = lcs_mtx[x - 1][y - 1] + 1;

            else {

                int above = lcs_mtx[x][y - 1];
                int left = lcs_mtx[x - 1][y];
              
                above > left ? lcs_mtx[x][y] = above :
                               lcs_mtx[x][y] = left;
            }

            if (lcs_mtx[x][y] > lcs_len)
                lcs_len = lcs_mtx[x][y];
 
        }
    }


    #ifdef _DEBUG
         // column headers (string a) 
        cout << "    ";
        for (int x = 0; x < a_len; x++)
            cout << a[x] << " ";
        cout << "\n";

        // first row of 0's
        cout << "  ";
        for (int x = 0; x < a_len + 1; x++)
            cout << "0 ";
        cout << "\n";
 
        // table and row headers (string b)
        for (int y = 1; y < b_len + 1; y++) {
            for (int x = 0; x < a_len + 1; x++) {
                
                if (x == 0)
                    cout << b[y - 1] << " ";

                cout << lcs_mtx[x][y] << " "; 
                
            }

            cout << "\n";
        }
        cout << "\n";
    #endif

    return lcs_len;

} 
