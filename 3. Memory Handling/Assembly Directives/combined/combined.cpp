#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>





vector <vector <int>> memory;

int memory_ptr = -1;
int memory_offset = 0;
vector <int> segment(4);


string line;

string as = ".asciiz";
string by = ".byte";
string wd = ".word";
string dw = ".dword";
string hw = ".half";

string data;
int num;




using namespace std;
 int main(){

    segment = {0};
    
    // if(line == ".data" || line == ".text")
    //     continue;
    if(line.find(as) != string::npos){
        // iss >> as_data;
        // iss >> nxt;
        // iss >> data;
        data.erase(0, 1);
        data.erase(data.size()-1, 1);
        for(int i = 0; i < data.size(); i++){
            if(i%4 == 0){
                memory.push_back(segment);
                memory_ptr++;
            }
            memory[memory_ptr][memory_offset%4] = int(data[i]);
            memory_offset++;
        }
        memory_offset++;
    }
    else{
        if(line.find(by) != string::npos){
            // iss >> as_data;
            // iss >> nxt;
            // iss >> data;
            //while(iss >> num){
                if(memory_offset%4 == 0){
                    memory.push_back(segment);
                    memory_ptr++;
                    memory_offset = 0;
                }
                memory[memory_ptr][memory_offset] = num;
                memory_offset++;
            //}
        }
        else{
            if(line.find(wd) != string::npos){
                // iss >> as_data;
                // iss >> nxt;
                // iss >> data;
                int k;
                //while(iss >> num){
                    for(int i = 0; i < 4; i++){
                        if(memory_offset%4 == 0){
                            memory.push_back(segment);
                            memory_ptr++;
                            memory_offset = 0;
                        }
                        k = num%256;
                        memory[memory_ptr][memory_offset] = k;
                        num = num >> 8;
                        memory_offset++;
                    }
                //}
            }
            else{
                 if(line.find(dw) != string::npos){
                    // iss >> as_data;
                    // iss >> nxt;
                    // iss >> data;
                    long long int dn;
                    int k;
                    //while(iss >> dn){
                        for(int i = 0; i < 8; i++){
                            if(memory_offset%4 == 0){
                                memory.push_back(segment);
                                memory_ptr++;
                                memory_offset = 0;
                            }
                            k = num%256;
                            memory[memory_ptr][memory_offset] = k;
                            num = num >> 8;
                            memory_offset++;
                        }
                    //}
                }
                else{
                    if(line.find(hw) != string::npos){
                        // iss >> as_data;
                        // iss >> nxt;
                        // iss >> data;
                        int k;
                        //while(iss >> num){
                            for(int i = 0; i < 2; i++){
                                if(memory_offset%4 == 0){
                                    memory.push_back(segment);
                                    memory_ptr++;
                                    memory_offset = 0;
                                }
                                k = num%256;
                                memory[memory_ptr][memory_offset] = k;
                                num = num >> 8;
                                memory_offset++;
                            }
                        //}
                    }
                }
            }
        }
    }
    for(int i = memory.size()-1 ; i >= 0; i--){
        for(int j = 0; j < 4; j++)
            cout << memory[i][3-j] << " ";
        cout << endl;
        }

    return 0;
 }