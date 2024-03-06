#include<bits/stdc++.h>
using namespace std;

string ItoB(int num, int s) {
    string binary;
    for (int i = s-1; i >= 0; --i) 
        binary += ((num >> i) & 1) ? "1" : "0";
    return binary;
}





vector <int> X(32);

// void peform_function(int rd, int r1, int imm, int f){
//     switch (f){
//         case 0:
//             X[rd] = X[r1] + imm;
//             break;
//         case 1:
//             X[rd] = X[r1] & imm;
//             break;
//         case 2:
//             X[rd] = X[r1] | imm;
//             break;
//         case 3:
//             X[rd] = X[r1] + imm;
//             break;
//         case 4:
//             X[rd] = X[r1] + imm;
//             break;
//         case 5:
//             X[rd] = X[r1] + imm;
//             break;
//         case 6:
//             X[rd] = X[r1] + imm;
//             break;
//         case 7:
//             X[rd] = X[r1] + imm;
//             break;
//     }
// }

int main(){

    string ins, I_opcode, r1,rd;
    vector <string> I, Ifunc3, I_opcode;

    //Vector I stores the name of all the R instructions that our Compler can detect
    
    I = {"addi", "andi", "ori", "lb", "ld", "lh", "lw", "jalr"};

    //Vector I_opcode and Ifunc3 stores the opcode and the fucntion values corresponding to each instruction
    
    I_opcode = {"0010011", "0010011", "0010011", "0000011", "0000011", "0000011", "0000011", "1100111"};
    Ifunc3 = {"000", "111", "110", "000", "011", "001", "010", "000"};

    if(find(I.begin(), I.end(), ins) != I.end()){                   // Check if it belongs to S or not
        int idx = find(I.begin(), I.end(), ins) - I.begin();        // saving its index
        int imm;
        // iss >> rd;
        // iss >> r1;
        // iss >> imm;
        r1.erase(0,0);
        rd.erase(0,0);
        string r_1, r_2, r_d;
        r_1 = ItoB(stoi(r1),5);
        r_d = ItoB(stoi(rd),5);
        string converted;
        converted = ItoB(imm, 12)  + r_1 + Ifunc3[idx] + r_d + I_opcode[idx];
    }
    return 0;
}