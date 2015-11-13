/******************************************************************************
 *                                                                            *
 *                              SIMILAR WORDS                                 *
 *                                                                            *
 ******************************************************************************/

/* 
 * GOAL: Find the 10 most similar words to a user-input word in the default
 *       Unix dictionary
 */

#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::cout;

// number of similar words to find
#define TOP_NUM     10

using std::string;
using std::cout;

struct s_index {
    string word;
    int edit_dist;
};

void usage();
int calc_edit_dist(string a, string b);
int calc_LCS(string a, string b);
void bubble(s_index top[], s_index word);

int main(int argv, char **argc)
{
    if (argv != 2) {
        usage();
        exit(1);
    }

    string word = argc[1];
    s_index top[TOP_NUM]; 

    // initialize most similar list
    for (int i = 0; i < TOP_NUM; i++) {
        top[i].word = "";
        top[i].edit_dist = INT_MAX;
    }
 
    // initialize list of words
    ifstream dict;
    dict.open("words.txt");

    // traverse through dictionary, searching for similar words
    while(!dict.eof()) {
        
        string curr_word;
        getline(dict, curr_word);
      
        // if there is an empty line in the dictionary, skip it 
        if(curr_word.find_first_not_of(' ') == string::npos)
            continue;

        int edit_dist = calc_edit_dist(word, curr_word);

        // if the current word in the dictionary is more similar to our word
        // than one of the entries in our top list, update our top list
        if (edit_dist < top[TOP_NUM - 1].edit_dist) {

            s_index new_word;
            new_word.word = curr_word;
            new_word.edit_dist = edit_dist;

            bubble(top, new_word);
        }

    }

    // print the results
    for (int i = 0; i < TOP_NUM; i++) {
        cout << top[i].word << "\n";
    }

    return 0; 
}

void usage()
{
    cout << "./similar_words [word]\n";
}

/*
 * calc_edit_dist
 *
 * PURPOSE: counts the number of actions it takes to modify word a to word b
 *          
 *          actions include:
 *          1) deleting letters
 *          2) adding letters
 *
 */

int calc_edit_dist(string a, string b)
{
    return abs((int) b.length() - (int) a.length()) - calc_LCS(a, b); 
}

/*
 * calc_LCS
 *
 * PURPOSE: counts the length of the longest common subsequence in strings a and b
 *
 */

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

    return lcs_len;
}

/*
 * bubble
 *
 * PURPOSE: given a word to add to our top list, bubbles the word up into its
 *          its correct position (think insertion sort) 
 *
 */

void bubble(s_index top[], s_index word)
{
    int i = 9;
    while (word.edit_dist < top[i].edit_dist && i != 0) {
        i--; 
        top[i + 1] = top[i]; 
    }
    top[i] = word;
} 
