#include<bits/stdc++.h>
using namespace std;

string ItoB(int num, int s) {
    string binary;
    for (int i = s-1; i >= 0; --i) 
        binary += ((num >> i) & 1) ? "1" : "0";
    return binary;
}

vector <int> X(32);


// void perform_function(int r1, int r2, int rd, int f){   //performing functions based on their indexes
//     if(rd != 0)
//         switch (f){
//             case 0:
//                 X[rd] = X[r1] + X[r2];      //add
//                 break;
//             case 1:
//                 X[rd] = X[r1] & X[r2];      //and
//                 break;
//             case 2:
//                 X[rd] = X[r1] | X[r2];      //or
//                 break;
//             case 3:
//                 X[rd] = X[r1] << X[r2];       //shift left
//                 break;
//             case 4:
//                 X[rd] = (X[r1] < X[r2])? 1 : 0;     //set less than
//                 break;
//             case 5:
//                 X[rd] = (X[r1]%2 == 0)? X[r1] >> X[r2] : -2147483648 + X[r1] >> X[r2];          //shift right airthmetic
//                 break;
//             case 6:
//                 X[rd] = X[r1] >> X[r2];         //shift right
//                 break;
//             case 7:
//                 X[rd] = X[r1] - X[r2];          //sub
//                 break;
//             case 8:
//                 X[rd] = X[r1] ^ X[r2];           //xor
//                 break;
//             case 9:
//                 X[rd] = X[r1] * X[r2];          //multiply
//                 break;
//             case 10:
//                 X[rd] = X[r1] / X[r2];          //divide
//                 break;
//             case 11:
//                 X[rd] = X[r1] % X[r2];          //remainder
//                 break;          
//         }

// }

int main(){
                
                
            // Format of a R type instruction is : 31:FUNC7:25::24:R2:20::19:R1:15::14:FUNC3:12::11:RD:7::6:OPCODE:0

    X = {0};
    string ins, r1, r2, rd, R_opcode;
    vector <string> R, func7, func3;

        //Vector R stores the name of all the R instructions that our Compler can detect
        //Vector func7 and func3 stores the fucntion values corresponding to each instruction

    R = {"add", "and", "or", "sll", "slt", "sra", "srl", "sub", "xor", "mul", "div", "rem"};
    func7 = {"0000000", "0000000", "0000000", "0000000", "0000000", "0100000", "0000000", "0100000", "0000000", "0000001", "0000001", "0000001"};
    func3 = {"000", "111", "110", "001", "010", "101", "101", "000", "100", "000", "000", "000"};

    R_opcode = "0110011";  // the opcode is same for each instruction 


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
        converted = func7[idx] + r_2 + r_1 + func3[idx] + r_d + R_opcode;       //final result stored by combining all the above
    }
    return 0;
}