#include <bits/stdc++.h>
#include<iostream>
#include<map>
#include<fstream>
#include<sstream>

using namespace std;

bool last_taken=false;
string two="";
bool two_bit_current=false, two_bit_prev=false;
int num_single=0,num_double=0,num_all_taken=0,num_all_not=0;
map<int,string> single_bit_history, taken_history, not_history, two_bit_history;
map<int,pair<bool,bool> >two_bit_state;
map<int,string> history;


void single_bit(int pc,bool taken);
string HexToBin(string hexdec);
void always_taken(int pc,bool taken);
void always_not_taken(int pc,bool taken);
void two_bit(int pc, bool taken);

int main(){
    string ifilename = "input.txt";
    ifstream ifile(ifilename);
    // ifstream ifile2(filename2);
    if (!ifile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    vector<int> pc;
    string line;
    vector<int> target;
    
    while (getline(ifile, line)) {
        // cc++;
        if(line.size() == 0) continue;
        vector<string> lineVec;
        string seg = "";
        for(int i=0;i<line.size();i++){
            if(line[i]==' '){
                if(seg!=""){
                    lineVec.push_back(seg);
                    seg="";
                }
                continue;
            }
            seg+=line[i];
            if(i == line.size()-1) lineVec.push_back(seg);
        }
        if(lineVec.size()<4 || lineVec[2].substr(0,2)!="0x" || lineVec[3].substr(0,3)!="(0x"){
            continue;
        }
        string pc_temp= HexToBin(lineVec[2]);
        long int value = stoll(pc_temp, nullptr, 2);
        pc.push_back(value);
        string inst= HexToBin(lineVec[3].substr(1,10));
        string opcode = inst.substr(32-7, 7);
        // branch
        if(opcode == "1100011"){
            string imm(13, '0');
            imm[12-12] = inst[31-31];
            imm[12-11] = inst[31-7];
            for(int i = 31-25, j = 12-5; static_cast<void>(i >= 31-30), j >= 12-10; i--, j--){
                imm[j] = inst[i];
            }
            for(int i = 31-8, j = 12-1; static_cast<void>(i >= 31-11), j >= 12-4; i--, j--){
                imm[j] = inst[i];
            }
            int value = stoi(imm, nullptr, 2);
            if(imm[0]=='1'){
                value= value - pow(2,13);
            }
            target.push_back(value);

        }
        // jal
        else if(opcode=="1101111"){
            target.push_back(pc[target.size()]);
        }
        // jalr
        else if(opcode=="1100111"){
            target.push_back(pc[target.size()]);
        }
        else {
            target.push_back(0);
        }
    }

    vector<bool> choice;

    for(int i = 0; i < pc.size()-1; i++){
        if(pc[i+1]-pc[i] == target[i]){
            choice.push_back(1);
        } else {
            choice.push_back(0);
        }
    }
    map<int,int> target_;
    int j=0;
    int branch=0;
    string abc="";
    for(int i=0;i<target.size();i++){
        if(target[i]){
            target_[pc[i]]=target[i];
            single_bit(pc[i],(bool)choice[i]);
            two_bit(pc[i],(bool)choice[i]);
            always_taken(pc[i],(bool)choice[i]);
            always_not_taken(pc[i],(bool)choice[i]);
            if(choice[i]){
                history[pc[i]].push_back('T');
                abc+='T';
            }
            else{
                history[pc[i]].push_back('N');
                abc+='N';
            }
            branch++;
        }
    }

    cout<<"OVERALL : "<<abc<<endl;
    //cout<<"Two "<<two<<endl;

    for(auto it=history.begin();it!=history.end();it++)
        cout << it->first << " " << it->second << endl;

    cout << endl;

    for(auto it=two_bit_history.begin();it!=two_bit_history.end();it++)
        cout << it->first << " " << it->second << endl;

    cout << endl;

    for(auto it=single_bit_history.begin();it!=single_bit_history.end();it++)
        cout << it->first << " " << it->second << endl;
    cout << endl;

    for(auto it=taken_history.begin();it!=taken_history.end();it++)
        cout << it->first << " " << it->second << endl;
    
    cout << endl;

    for(auto it=not_history.begin();it!=not_history.end();it++)
        cout << it->first << " " << it->second << endl;
    
    cout << "ACCURACY OF : \n";

    cout <<"\tSINGLE BIT : "<<((float)num_single/branch)*100 << endl;
    cout <<"\tTWO BIT : "<<((float)num_double/branch)*100 << endl;
    cout<<"\tALWAYS NOT TAKEN :  "<<((float)num_all_not/branch)*100 << endl;
    cout<<"\tALWAYS TAKEN : "<<((float)num_all_taken/branch)*100<<endl;
    
    ifile.close();
    return 0;
}



void single_bit(int pc,bool taken){
    if(single_bit_history[pc].size()==0){
        last_taken= false;
    }
    else if(history[pc][history[pc].size()-1]=='T'){
        last_taken=true;
    }
    else{
        last_taken= false;
    }
    if(taken==last_taken){
        num_single++;
    }
    if(last_taken){
        single_bit_history[pc]+="T";
    }
    else{
        single_bit_history[pc]+="N";
    }
    last_taken=taken;
    
}

void always_taken(int pc,bool taken){
    if(taken==true){
        num_all_taken++;
    }
    taken_history[pc]+="T";
}
void always_not_taken(int pc,bool taken){
    if(taken==false){
        num_all_not++;
    }
    not_history[pc]+="N";
}

void two_bit(int pc, bool taken){
    if(two_bit_history[pc].size() == 0){
        two_bit_state[pc].first = false;
        two_bit_state[pc].second = false;
    }
    bool predict;
    if(two_bit_state[pc].first == two_bit_state[pc].second ){
        predict = two_bit_state[pc].first;
        two_bit_state[pc].first=taken;
    }
    else{
        predict = two_bit_state[pc].second;
        if(taken == two_bit_state[pc].first){
            two_bit_state[pc].second= taken;
        }
        else{
            two_bit_state[pc].first= taken;
        }
    }
    if(predict){
        two_bit_history[pc]+="T";
        two+="T";
    }
    else{
        two+="N";
        two_bit_history[pc]+="N";
    }
    if(predict == taken) num_double++;
}

string HexToBin(string hexdec){
    size_t i = (hexdec[1] == 'x' || hexdec[1] == 'X')? 2 : 0;
    string bin="";
    while (hexdec[i]) {
 
        switch (hexdec[i]) {
        case '0':
            bin+= "0000";
            break;
        case '1':
            bin+= "0001";
            break;
        case '2':
            bin+= "0010";
            break;
        case '3':
            bin+= "0011";
            break;
        case '4':
            bin+= "0100";
            break;
        case '5':
            bin+= "0101";
            break;
        case '6':
            bin+= "0110";
            break;
        case '7':
            bin+= "0111";
            break;
        case '8':
            bin+= "1000";
            break;
        case '9':
            bin+= "1001";
            break;
        case 'A':
        case 'a':
            bin+= "1010";
            break;
        case 'B':
        case 'b':
            bin+= "1011";
            break;
        case 'C':
        case 'c':
            bin+= "1100";
            break;
        case 'D':
        case 'd':
            bin+= "1101";
            break;
        case 'E':
        case 'e':
            bin+= "1110";
            break;
        case 'F':
        case 'f':
            bin+= "1111";
            break;
        case '.':
            bin+= ".";
            break;
        default:
            cerr << "\nInvalid hexadecimal digit "
                 << hexdec[i];
        }
        i++;
    }
    return bin;
}
