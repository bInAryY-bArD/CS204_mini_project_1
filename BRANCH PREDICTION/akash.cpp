#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;
typedef long long int ll;
/*
bool last_taken=false;
string two="";
bool two_bit_current=false, two_bit_prev=false;
int num_single=0,num_double=0,num_all_taken=0,num_all_not=0;
map<int,string> single_bit_history, taken_history, not_history, two_bit_history;
map<int,pair<bool,bool> >two_bit_state;
map<int,string> history;

void always_taken(int pc,bool taken);
void always_not_taken(int pc,bool taken);
void single_bit(int pc,bool taken);
void two_bit(int pc, bool taken);
string HexToBin(string hexdec);

int main(){
    //open the input file
    string inputfilename = "input.txt";
    ifstream inputfile(inputfilename);
    if (!inputfile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    vector<int> pc;
    vector<int> target;
    string line;
    
    while(getline(inputfile, line)){
        if(line.size() == 0){  //skip blank line
            continue;
        }
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
        //check opcode for jal
        else if(opcode=="1101111"){
            target.push_back(pc[target.size()]);
        }
        //check opcode for jalr
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
    cout<<"overall history "<<abc<<endl;
    cout<<"Two "<<two<<endl;
    for(auto it=history.begin();it!=history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=two_bit_history.begin();it!=two_bit_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=single_bit_history.begin();it!=single_bit_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=taken_history.begin();it!=taken_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }cout<<endl;
    for(auto it=not_history.begin();it!=not_history.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
    cout<<"Accuracy of single bit branch predictor: "<<((float)num_single/branch)*100<<endl;
    cout<<"Accuracy of two bit branch predictor: "<<((float)num_double/branch)*100<<endl;
    cout<<"Accuracy of always not taken bit branch predictor: "<<((float)num_all_not/branch)*100<<endl;
    cout<<"Accuracy of always taken bit branch predictor: "<<((float)num_all_taken/branch)*100<<endl;
    inputfile.close();
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
    //Skip "0x" if present at beggining of Hex string
    size_t i = (hexdec[1] == 'x' || hexdec[1] == 'X')? 2 : 0;
    string bin="";
    while (hexdec[i]) {
        switch (hexdec[i]){
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
            cout << "\nInvalid hexadecimal digit "
                 << hexdec[i];
        }
        i++;
    }
    return bin;
}
*/

vector <pair<ll, ll>> pc_target;
map <ll, string> prediction;
map <ll, string> actual;
vector<char> actual_itr;
vector<char> prediction_itr;
vector<ll> pc_vector;
ll n=0;
ll one_bit_predictor = 0;
ll two_bit_predictor = 0;
ll correct_always_taken=0;
ll correct_always_not_taken=0;
ll correct_one_bit=0;
ll correct_two_bit=0;
ll accuracy_always_taken=0;
ll accuracy_always_not_taken=0;
ll accuracy_one_bit=0;
ll accuracy_two_bit=0;

void always_taken(){
    if (actual_itr[n] == prediction_itr[n-1]){
        correct_always_taken++;
    }
    prediction[pc_vector[n]] += 'T';
    prediction_itr[n] = 'T';
}

void always_not_taken(){
    if (actual_itr[n] != prediction_itr[n-1]){
        correct_always_not_taken++;
    }
    prediction[pc_vector[n]] += 'N';
    prediction_itr[n] = 'N';
}

void one_bit(){
    if(one_bit_predictor == 0){
        prediction[pc_vector[n]] += 'N';
        prediction_itr[n] = 'N';
    }
    else if(one_bit_predictor == 1){
        prediction[pc_vector[n]] += 'T';
        prediction_itr[n] = 'T';
    }
    //now check whether taken or not taken
    if (actual_itr[n] == prediction_itr[n-1]){
        one_bit_predictor = 1;
        correct_one_bit++;
        
    }
    else{
        one_bit_predictor = 0;
    }
}

void two_bit(){
    if (two_bit_predictor == 0 || two_bit_predictor == 1){
        prediction[pc_vector[n]] = 'N';
        prediction_itr[n] = 'N';
    }
    else if(two_bit_predictor == 2 || two_bit_predictor == 3){
        prediction[pc_vector[n]] = 'T';
        prediction_itr[n] = 'T';
    }
    //now check whether taken or not
    if (actual_itr[n] == prediction_itr[n-1]){
        correct_two_bit++;
        if(two_bit_predictor<3){
            two_bit_predictor++;
        }
    }
    else{
        if(two_bit_predictor>0){
            two_bit_predictor--;
        }
    }
}

void check_accuracy(){
    accuracy_always_taken = ((correct_always_taken/actual_itr.size())*100);
    accuracy_always_not_taken = ((correct_always_not_taken/actual_itr.size())*100);
    accuracy_one_bit = ((correct_one_bit/actual_itr.size())*100);
    accuracy_two_bit = ((correct_two_bit/actual_itr.size())*100);
    
    //printing the accuracies
    cout << "Accuracy:\n";
    cout << "Always Taken: " << accuracy_always_taken << "\n";
    cout << "Always Not Taken: " << accuracy_always_not_taken << "\n";
    cout << "Accuracy One Bit: " << accuracy_one_bit << "\n";
    cout << "Accuracy Two BIt: " << accuracy_two_bit << "\n";
}
