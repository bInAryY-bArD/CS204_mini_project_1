#include<bits/stdc++.h>
using namespace std;

string ItoB(int num, int s) {
    string binary;
    for (int i = s-1; i >= 0; --i) 
        binary += ((num >> i) & 1) ? "1" : "0";
    return binary;
}

int main(){

    string S_opcode, r1, r2, ins;
                            //Vector S stores the name of all the S instructions that our Complier can detect
    vector <string> S, Sfunc3;
    S = {"sb", "sw", "sd", "sh"};
    S_opcode = "0100011";
    Sfunc3 = {"000","010","011","001"};
    if(find(S.begin(), S.end(), ins) != S.end()){
        int idx = find(S.begin(), S.end(), ins) - S.begin();
        int imm;
        // iss >> r1;
        // iss >> r2;
        for(int i = 0; i < 12; i++)
            if(r2[i] == '('){
                string temp = r2.substr(0, i);
                imm = stoi(temp);
                r2.erase(0,i+1);
                r2.erase(r2.size(), 1);
                break;
            }
        r1.erase(0,0);
        r2.erase(0,0);
        string r_1, r_2, r_d;
        r_1 = ItoB(stoi(r1),5);
        r_2 = ItoB(stoi(r2),5);
        string immB = ItoB(imm,12);
        string immB40 = immB.substr(7,5);
        string immB117 = immB.substr(0,7);
        string converted;
        converted = immB117 + r_2 + r_1 + Sfunc3[idx] + immB40 + S_opcode[idx];
    }
    return 0;
}