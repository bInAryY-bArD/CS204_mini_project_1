//-----CS204 Mini PROJECT -----

// By Akash                 2022CSB1064
//    Aniket Kumar Sahil    2022CSB1067


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>          //declaring all the libraries
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <sstream>
using namespace std;

string ItoB(int num, int s) {           // Function to convert a given a number into binary string of size s 
    string binary;
    for (int i = s-1; i >= 0; --i) 
        binary += ((num >> i) & 1) ? "1" : "0";
    return binary;
}

string BtoH(string binary){
    stringstream ss;
    for (int i = 0; i < 8; ++i) { 
        string nibble = binary.substr(i * 4, 4); 
        int decimal = stoi(nibble, nullptr, 2); // Convert binary to decimal
        ss << uppercase << hex << decimal; // Convert decimal to hexadecimal and append to stringstream
    }
    return ss.str(); 
}

string ItoH(int x){
    stringstream hx;                //converting int to hexadecimal string
    hx <<uppercase << hex << x;
    string hexa = hx.str();
    if(hexa.size() == 1)
        hexa = '0' + hexa;
    return hexa;
}

vector <string> Label;

string converted;

vector <string> R, I, S, SB, U;
string UJ;
string ins, r1, r2, rd, imm, label;                 //declaring the necessary variables

vector <string> Rfunc7, Rfunc3;
string R_opcode;

vector <string> Ifunc3, I_opcode;

vector <string> Sfunc3;
string S_opcode;

vector <string> SBfunc3;
string SB_opcode;

vector <string> U_opcode;

string UJ_opcode;



map <string, int> labels;
vector <int> label_pc;
int pc = -4;

vector <vector <int>> memory;

int memory_ptr = -1;
int memory_offset = 0;
vector <int> segment(4);

string D = ".data";
string T = ".text";
string line;
string N;

string as = ".asciiz";
string by = ".byte";
string wd = ".word";
string dw = ".dword";
string hw = ".half";


int num;

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

                        //Vector U and U_opcode stores the information of U instructions
    U = {"auipc", "lui"};
    U_opcode = {"0010111", "0110111"};

    
                //String UJ and UJ_opcode storing the instruction of UJ type 
    UJ = "jal";
    UJ_opcode = "1101111";

    


    ifstream read_labels("test.asm");
     while(getline(read_labels, line)){      // reading once for the labels specifically 
            if( line[line.size()-2] == ':'){
                // cout << line  << endl;
                line.erase(line.size()-1, 1);
                Label.push_back(line);
                label_pc.push_back(pc+4);           //pushing their positions along with their names
                labels.insert({line, pc+4});
                // cout << line << endl;
            }
            else
                if(line.find(':') == string::npos && line.find(T) == string::npos  && line.find(D) == string::npos){
                    pc += 4;        //else increment the counter
                }
                //cout << line <<endl;
    }
    
    read_labels.close();
    pc = -4;
    int p;

    // for(int i = 0; i < Label.size(); i++)
    //     cout << Label[i] << " "<< label_pc[i] << " \n";
    // if(find(Label.begin(), Label.end(), Label[0]) != Label.end())
    //     cout << "i am fucked " << Label[0] <<endl;

    ifstream inputfile("test.asm");             // enter the input file name here 
    ofstream converted_code("machinecode.mc");  // filename of the machine code


    string line, converted_line;
    while(getline(inputfile, line)){      // reads from the test file line by line 
        //cout << line << endl;
        if(line.empty())
            continue;
        if( line[line.size()-2] == ':' || line[line.size()-1] == ':')
            continue;

        size_t pos = 0;
        // while ((pos = line.find('\"')) != string::npos)      //Erasing the commas for convenience
        //     line.erase(pos, 1);
        
        istringstream iss(line);            // tokenizing the string line so we can have each aspect separately
        string instruction;
       
        
            
        segment = {0};
        string data;
        string nm;          //variables for eliminating the useless tokens
        string cln;
        string var;
        if(line.find(T) != string::npos  || line.find(D) != string::npos)
            continue;
        if(line.find(as) != string::npos){      //if storing data via .asciiz
            iss >> var;
            iss >> cln;
            iss >> nm;
            while(iss >> data){
                while (((pos = data.find(char(34))) != string::npos))      //Erasing the quotes for convenience
                    data.erase(pos, 1);
                //cout << data << endl; 

                for(int i = 0; i < data.size(); i++){
                    if(memory_offset%4 == 0){
                        memory.push_back(segment);
                        memory_ptr++;
                        memory_offset = 0;
                    }
                    //cout << data[i] << " " << memory_offset << " " << memory_ptr << "\n";
                    memory[memory_ptr][memory_offset] = int(data[i]);
                    memory_offset++;
                }
                if(memory_offset != 4)
                    memory[memory_ptr][memory_offset] = 32;
                else{
                    memory.push_back(segment);
                    memory_ptr++;
                    memory[memory_ptr][0] = 32;
                }
                memory_offset = (memory_offset + 1)%4;
            }
            //cout << memory_ptr << " " <<memory_offset << "\n";
            if(memory_offset != 0)
                memory[memory_ptr][memory_offset-1] = 0;
            else
                memory[memory_ptr][3] = 0;
            continue;
        }
        else{
            while (((pos = line.find(',')) != string::npos))      //Erasing the commas for convenience
                    line.erase(pos, 1);
            if(line.find(by) != string::npos){      //if storing data using .byte
                iss >> var;
                iss >> cln;
                iss >> nm;
                while(iss >> N){
                    num = stoi(N);
                    if(num < 0)
                        num += 256;
                    if(memory_offset%4 == 0){
                        memory.push_back(segment);
                        memory_ptr++;
                        memory_offset = 0;
                    }
                    memory[memory_ptr][memory_offset] = num;
                    memory_offset++;
                }
                continue;
            }
            else{
                if(line.find(wd) != string::npos){
                    //cout << line;                     //if storing a word
                    iss >> var;
                    iss >> cln;
                    iss >> nm;
                    int k;
                    while(iss >> N){
                        //cout << num << endl;
                        num = stoi(N);
                        for(int i = 0; i < 4; i++){
                            if(memory_offset%4 == 0){
                                memory.push_back(segment);
                                memory_ptr++;
                                memory_offset = 0;
                            }
                            k = num%256;        //for each byte
                            if(num < 0)                 //if negative
                                k += 256;
                            memory[memory_ptr][memory_offset] = k;
                            num = num >> 8;
                            memory_offset++;
                            //cout << k << " " << memory_offset << " " << memory_ptr << endl;
                        }
                    }
                    continue;
                }
                else{
                    if(line.find(dw) != string::npos){          //if storing double word
                        iss >> var;
                        iss >> cln;
                        iss >> nm;
                        //cout << line << endl;
                        long long int dn;
                        int k;
                        while(iss >> N){
                            dn = stoi(N);
                            //cout << dn;
                            for(int i = 0; i < 8; i++){
                                if(memory_offset%4 == 0){
                                    memory.push_back(segment);
                                    memory_ptr++;
                                    memory_offset = 0;
                                }
                                k = dn%256;
                                if(dn < 0)
                                    k += 256;
                                memory[memory_ptr][memory_offset] = k;
                                dn = dn >> 8;
                                memory_offset++;
                            }
                        }
                        continue;
                    }
                    else{
                        if(line.find(hw) != string::npos){
                            iss >> var;                     //if storing half word
                            iss >> cln;
                            iss >> nm;
                            int k;
                            while(iss >> N){
                                num = stoi(N);
                                for(int i = 0; i < 2; i++){
                                    if(memory_offset%4 == 0){
                                        memory.push_back(segment);
                                        memory_ptr++;
                                        memory_offset = 0;
                                    }
                                    k = num%256;
                                    if(num < 0)
                                        k += 256;
                                    memory[memory_ptr][memory_offset] = k;
                                    num = num >> 8;
                                    memory_offset++;
                                }
                            }
                            continue;
                        }
                    }
                }
            }
        }
        while (((pos = line.find(',')) != string::npos))      //Erasing the commas for convenience
                line.erase(pos, 1);
        iss >> ins;         // extracting the instruction which is the first word
        pc += 4;
        if(find(R.begin(), R.end(), ins) != R.end()){               // check if the ins belongs to R or not 
            int idx = find(R.begin(), R.end(), ins) - R.begin();    // Find the corresponding index 
            iss >> rd;
            //cout << 2 << endl;
            iss >> r1;
            iss >> r2;
            r1.erase(0,1);
            r2.erase(0,1);                  // erasing the 'x' from the X names to get their numbers
            rd.erase(0,1);
            string r_1, r_2, r_d;
            r_1 = ItoB(stoi(r1),5);
            r_2 = ItoB(stoi(r2),5);            //converting them to binary string
            r_d = ItoB(stoi(rd),5);
            converted = Rfunc7[idx] + r_2 + r_1 + Rfunc3[idx] + r_d + R_opcode;       //final result stored by combining all the above
        }
        else{
            if(find(I.begin(), I.end(), ins) != I.end()){                   // Check if it belongs to S or not
                int idx = find(I.begin(), I.end(), ins) - I.begin();        // saving its index
                int imm;
                //cout << 1 << endl;
                if(ins[0] != 'l'){              //if it is a load instruction 
                    iss >> rd;
                    iss >> r1;
                    iss >> N;
                    imm = stoi(N);
                }
                else{
                    iss >> rd;
                    iss >> r1;
                    int f = find(r1.begin(), r1.end(), '(') - r1.begin();
                    imm = stoi(r1.substr(0,f));
                    r1.erase(0,f+1);
                    r1.erase(r1.size()-1,1);
                }
                
                r1.erase(0,1);
                rd.erase(0,1);
                string r_1, r_2, r_d;
                r_1 = ItoB(stoi(r1),5);         //convert register number to binary
                r_d = ItoB(stoi(rd),5);
                converted = ItoB(imm, 12)  + r_1 + Ifunc3[idx] + r_d + I_opcode[idx];   //Appending all the resources
        }
            else{
                if(find(S.begin(), S.end(), ins) != S.end()){               //if it is of S type 
                    int idx = find(S.begin(), S.end(), ins) - S.begin();    //find idx
                    int imm;
                    iss >> r2;      //take input
                    iss >> r1;
                    for(int i = 0; i < 12; i++)
                        if(r1[i] == '('){                   //extract the offset
                            string temp = r1.substr(0, i);
                            imm = stoi(temp);
                            r1.erase(0,i+1);
                            r1.erase(r1.size()-1, 1);
                            break;
                        }
                    r1.erase(0,1);
                    r2.erase(0,1);
                    //cout << r1 << r2 << endl;
                    string r_1, r_2;
                    r_1 = ItoB(stoi(r1),5);
                    r_2 = ItoB(stoi(r2),5);                 //convert to binary
                    //cout << r_1 << " " << r_2 << endl;
                    string immB = ItoB(imm,12);
                    //cout << immB << endl;
                    string immB40 = immB.substr(7,5);
                    string immB117 = immB.substr(0,7);
                    converted = immB117 + r_2 + r_1 + Sfunc3[idx] + immB40 + S_opcode;     //append all 
                }
                else{
                    if(find(SB.begin(), SB.end(), ins) != SB.end()){            //if it is of SB type 
                        int idx = find(SB.begin(), SB.end(), ins) - SB.begin();     //find idx
                        iss >> r1;
                        iss >> r2;      //read all the necessary information
                        iss >> label;
                        label.push_back(':');
                        r1.erase(0,1);
                        r2.erase(0,1);
                        p = find(Label.begin(), Label.end(), label) - Label.begin();        //find the label
                        //cout << "idx : " << p << endl;
                        int diff =  label_pc[p] - pc ;          //calculate the difference of the jump
                        //cout << label <<" " << label_pc[p-1] <<endl;
                        //cout << diff << endl;
                        string bdiff = ItoB(diff, 13);
                        bdiff.erase(bdiff.size()-1,1);      //append all
                        converted = bdiff[0] +  bdiff.substr(2, 6) + ItoB(stoi(r2), 5) + ItoB(stoi(r1), 5) + SBfunc3[idx] + bdiff.substr(8, 4) + bdiff[1] + SB_opcode;
                    }
                    else{
                        if(find(U.begin(), U.end(), ins) != U.end()){   //if it is of U type
                            int idx = find(U.begin(), U.end(), ins) - U.begin();    //find idx
                            int imm;
                            iss >> rd;
                            iss >> imm;
                            rd.erase(0,1);
                            converted = ItoB(imm, 20) + ItoB(stoi(rd), 5) + U_opcode[idx];      //append all
                        }
                        else{
                            if(ins == UJ){      //if it is of UJ type
                                iss >> rd;
                                iss >> label;
                                //cout << label << endl;
                                label.push_back(':');
                                rd.erase(0,1);
                                int x = find(Label.begin(), Label.end(), label) - Label.begin();    //find label
                                //cout << "idx : " << x << endl;
                                //cout << label_pc[x];
                                int off = label_pc[x] - pc;     //calculate offset
                                //cout << off << endl;
                                string bimm = ItoB(off, 21);
                                bimm.erase(20,1);           //append all
                                converted = bimm[0] + bimm.substr(10, 10) + bimm[9] + bimm.substr(1,8) + ItoB(stoi(rd), 5) + UJ_opcode;
                            }
                        }
                    }
                }
            }
        }

        //cout << converted << endl;
        converted_line = BtoH(converted);       //converting the instruction to hexadecimal
        stringstream _pc_;
        _pc_ << uppercase << hex << pc;         //converting pc to hexadecimal
        string PC = _pc_.str();
        converted_code << "0x"<< PC << "\t:\t0x" <<converted_line << "\n";           // writing it in the file you are creating
       // cout << pc << "\t" <<converted_line <<endl;  

    }
    converted_code << endl << endl << endl << "MEMORY : \n\n";          //uploading memory
    converted_code << "\t\t" << "+3   "<< "+2   " << "+1   " << "+0\n";  
     for(int i = memory.size()-1 ; i >= 0; i--){
        converted_code << "0x" << ItoH(268435456 + 4*i) << "\t";        //uploading byte by byte
        for(int j = 0; j < 4; j++){
            converted_code << ItoH(memory[i][3-j]) << "   ";
        }
        converted_code << endl;
        }
    cout << "Converted Sucessfully!\n";        
    inputfile.close();                      //closing the files
    converted_code.close();
    return 0;
}


