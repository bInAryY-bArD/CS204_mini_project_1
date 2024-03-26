#include<bits/stdc++.h>
using namespace std;
bool last_taken=false;
string two="";
// int ccc=0;
// long int cc=0;

bool two_bit_current=false, two_bit_prev=false;
long long int num_single=0,num_double=0,num_all_taken=0,num_all_not=0;
map<long long int , string> single_bit_history, taken_history, not_history, two_bit_history;
map<long long int,pair<bool,bool>>two_bit_state;
map<long long int,string> history;


void single_bit(long long int pc,bool taken){
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
void always_taken(long long int pc,bool taken){
    if(taken==true){
        num_all_taken++;
    }
    taken_history[pc]+="T";
}
void always_not_taken(long long int pc,bool taken){
    if(taken==false){
        num_all_not++;
    }
    not_history[pc]+="N";
}

void two_bit(long long int pc, bool taken){
    if(two_bit_history[pc].size()==0){
        two_bit_state[pc]={false, false};
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

string HexToBin(string hexdec)
{
    // ccc++;
      //Skips "0x" if present at beggining of Hex string
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
            // cout<<hexdec<<" "<<ccc<<endl;
            // cout<<"line "<<cc<<endl;
            cout << "\nInvalid hexadecimal digit "<<endl;
        }
        i++;
    }
    return bin;
}

int main(){
    ll it = 0;
    string ifilename = "input.txt";
    ifstream ifile(ifilename);
    // ifstream ifile2(filename2);
    if (!ifile.is_open()) {
        cout << "Error opening files." << endl;
        return 1;
    }
    bool t=false;
    vector<long long int> pc;
    string line;
    vector<long long int> target;
    
    while (getline(ifile, line)) {
        it++;
        if(it > 1000000)
            break;
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
        int flag=0;
        int k=0;
        while(k<lineVec.size()){
            if(lineVec[k]=="core"){
                break;
            }
            k++;
        }
        if(k==lineVec.size()) continue;
        if(lineVec.size()<4+k || lineVec[2+k].substr(0,2)!="0x" || lineVec[3+k].substr(0,3)!="(0x"){
            continue;
        }
        string pc_temp= HexToBin(lineVec[2+k]);
        long long int value = 0;
        for(int i=0;i<32;i++){
            value+= (pc_temp[i]-'0')*powl(2,31-i);
        }
        pc.push_back(value);
        if(t){
            target.push_back(pc[target.size()+1]-pc[target.size()]);
            t=false;
        }
        string inst= HexToBin(lineVec[3+k].substr(1,10));
        string opcode = inst.substr(32-7, 7);
        // branch
        if(opcode == "1100011"){
            string imm(13, '0');
            imm[12-12] = inst[31-31];
            imm[12-11] = inst[31-7];
            for(int i = 31-25, j = 12-5; i >= 31-30, j >= 12-10; i--, j--){
                imm[j] = inst[i];
            }
            for(int i = 31-8, j = 12-1; i >= 31-11, j >= 12-4; i--, j--){
                imm[j] = inst[i];
            }
            long long int value = stoi(imm, nullptr, 2);
            if(imm[0]=='1'){
                value= value - pow(2,13);
            }
            target.push_back(value);

        }
        // jal
        else if(opcode=="1101111"){
            // cout<<"JAL"<<" "<<pc[target.size()]<<endl;
            // target.push_back(pc[target.size()]);
            t=true;
        } 
        // jalr
        else if(opcode=="1100111"){
            // target.push_back(pc[target.size()]);
            t=true;
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
    map<long long int,long long int> target_;
    long long int j=0;
    long long int branch=0;
    string abc="";
    for(long long int i=0;i<target.size();i++){
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
    cout << "Overall H  istory :\n" << abc << endl;
    cout<<"Branch wise history"<<endl;

    for(auto it=history.begin();it!=history.end();it++){
        cout<<"PC= "<<it->first<<" History= "<<it->second<<endl;
    }cout<<endl;
    cout<<"Two Bit predictor"<<two<<endl;
    for(auto it=two_bit_history.begin();it!=two_bit_history.end();it++){
        cout<<"PC= "<<it->first<<" Prediction History= "<<it->second<<endl;
    }cout<<endl;
    cout<<"One Bit predictor"<<two<<endl;
    for(auto it=single_bit_history.begin();it!=single_bit_history.end();it++){
        cout<<"PC= "<<it->first<<" Prediction History= "<<it->second<<endl;
    }cout<<endl;
    cout<<"Always taken predictor"<<two<<endl;
    for(auto it=taken_history.begin();it!=taken_history.end();it++){
        cout<<"PC= "<<it->first<<" Prediction History= "<<it->second<<endl;
    }cout<<endl;
    cout<<"Always not taken predictor"<<two<<endl;
    for(auto it=not_history.begin();it!=not_history.end();it++){
        cout<<"PC= "<<it->first<<" Prediction History= "<<it->second<<endl;
    }
    cout<<"Accuracy of single bit branch predictor: "<<((float)num_single/branch)*100<<endl;
    cout<<"Accuracy of two bit branch predictor: "<<((float)num_double/branch)*100<<endl;
    cout<<"Accuracy of always not taken bit branch predictor: "<<((float)num_all_not/branch)*100<<endl;
    cout<<"Accuracy of always taken bit branch predictor: "<<((float)num_all_taken/branch)*100<<endl;
    ifile.close();
}