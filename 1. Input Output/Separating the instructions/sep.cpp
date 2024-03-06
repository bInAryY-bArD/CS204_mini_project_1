#include<bits/stdc++.h>
using namespace std;
int main(){

    string code = "add add x5, x6, x7";
    size_t pos = 0;
    while ((pos = code.find(',')) != string::npos) {
        code.erase(pos, 1);
    }
    istringstream iss(code);
    vector<string> words;
    string word;

    string k;
    iss >> k;
    while (iss >> word)
        words.push_back(word);

    string word1, word2, word3, word4;          //saving the words separately in a vector
    word1 = words[0];
    word2 = words[1];
    word3 = words[2];
    word4 = words[3];

    cout << k << "\n";
    cout << "Instruction: " << word1 << endl;   //printing them to verify our results
    cout << "rd :" << word2 << endl;
    cout << "r1 :" << word3 << endl;
    cout << "r2 :" << word4 << endl;

    return 0;
}
