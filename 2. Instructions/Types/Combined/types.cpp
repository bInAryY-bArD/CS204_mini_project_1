#include <bits/stdc++.h>
using namespace std;


string ItoB(int num, int s) {           // Function to convert a given a number into binary string of size s 
    string binary;
    for (int i = s-1; i >= 0; --i) 
        binary += ((num >> i) & 1) ? "1" : "0";
    return binary;
}

vector <string> R, I, S, SB, U, UJ;
string ins, r1, r2, rd, imm, label;

vector <string> Rfunc7, Rfunc3;
string R_opcode;

vector <string> Ifunc3, I_opcode;

vector <string> Sfunc3;
string S_opcode;

vector <string> SBfunc3;
string SB_opcode;

int main(){

        //Vector R stores the name of all the R instructions that our Compler can detect
        //Vector func7 and func3 stores the fucntion values corresponding to each instruction

    R = {"add", "and", "or", "sll", "slt", "sra", "srl", "sub", "xor", "mul", "div", "rem"};
    Rfunc7 = {"0000000", "0000000", "0000000", "0000000", "0000000", "0100000", "0000000", "0100000", "0000000", "0000001", "0000001", "0000001"};
    Rfunc3 = {"000", "111", "110", "001", "010", "101", "101", "000", "100", "000", "000", "000"};
    R_opcode = "0110011";  // the opcode is same for each instruction 


        //Vector I stores the name of all the R instructions that our Compler can detect
        //Vector I_opcode and Ifunc3 stores the opcode and the fucntion values corresponding to each instruction

    I = {"addi", "andi", "ori", "lb", "ld", "lh", "lw", "jalr"};
    I_opcode = {"0010011", "0010011", "0010011", "0000011", "0000011", "0000011", "0000011", "1100111"};
    Ifunc3 = {"000", "111", "110", "000", "011", "001", "010", "000"};


        //Vector S stores the name of all the S instructions that our Complier can detect
        //S_opcode stores the opcode which is same for all the instructions 

    S = {"sb", "sw", "sd", "sh"};
    S_opcode = "0100011";
    Sfunc3 = {"000","010","011","001"};


        //Vector SB stores the name of all the SB instructions that our Compiler can detect

    SB = {"beq", "bne", "bge", "blt"};
    SB_opcode = "1100011";
    SBfunc3 = {"000", "001", "101", "100"};



    //more here later


     if(find(R.begin(), R.end(), ins) != R.end()){               // check if the ins belongs to R or not 
        int idx = find(R.begin(), R.end(), ins) - R.begin();    // Find the corresponding index 
        // iss >> rd;
        // iss >> r1;
        // iss >> r2;
        r1.erase(0,0);
        r2.erase(0,0);                  // erasing the 'x' from the X names to get their numbers
        rd.erase(0,0);
        string r_1, r_2, r_d;
        r_1 = ItoB(stoi(r1),5);
        r_2 = ItoB(stoi(r2),5);            //converting them to binary string
        r_d = ItoB(stoi(rd),5);
        string converted;
        converted = Rfunc7[idx] + r_2 + r_1 + Rfunc3[idx] + r_d + R_opcode;       //final result stored by combining all the above
    }
    else{
        if(find(I.begin(), I.end(), ins) != I.end()){                   // Check if it belongs to I or not
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
        else{
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
        }
    }



    return 0;
}