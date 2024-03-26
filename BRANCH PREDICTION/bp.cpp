//BRANCH PREDICTION ASSIGNMENT
// BY :
    //AKASH              2022CSB1064
    //ANIKET KUMAR SAHIL 2022CSB1067

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int flag;

map <ll , string> actual;
vector <char> actual_itr;
map <ll, string> prediction_at;
map <ll, string> prediction_ant;
map <ll, string> prediction_1b;
map <ll, string> prediction_2b;

vector <ll> pc_vector;
vector <char> prediction_itr_at,prediction_itr_ant,prediction_itr_1b,prediction_itr_2b;
vector <pair<ll, ll>> pc_target;
ll n=0;
ll one_bit_predictor = 0;
ll two_bit_predictor = 1;
ll correct_always_taken=0;
ll correct_always_not_taken=0;
ll correct_one_bit=0;
ll correct_two_bit=0;
float accuracy_always_taken=0;
float accuracy_always_not_taken=0;
float accuracy_one_bit=0;
float accuracy_two_bit=0;

void always_taken(){
    prediction_at[pc_vector[n]] += 'T';
    prediction_itr_at.push_back('T');
    if (actual_itr[n] == prediction_itr_at[n]){
        correct_always_taken++;
    }
    //cout << correct_always_taken << endl;
}

void always_not_taken(){
    prediction_ant[pc_vector[n]] += 'N';
    prediction_itr_ant.push_back('N');
    if (actual_itr[n] == prediction_itr_ant[n]){
        correct_always_not_taken++;
    }
    //cout << correct_always_not_taken << endl;
}

void one_bit(){
    if(one_bit_predictor == 0){
        prediction_1b[pc_vector[n]] += 'N';
        prediction_itr_1b.push_back('N');
    }
    else{
        prediction_1b[pc_vector[n]] += 'T';
        prediction_itr_1b.push_back('T');
    }
    if(prediction_itr_1b[n] == actual_itr[n])
        correct_one_bit++;
    if(actual_itr[n] == 'N')
        one_bit_predictor = 0;
    else
        one_bit_predictor = 1;
}

void two_bit(){
    if (two_bit_predictor == 0 || two_bit_predictor == 1){
        prediction_2b[pc_vector[n]] += 'N';
        prediction_itr_2b.push_back('N');
    }
    else if(two_bit_predictor == 2 || two_bit_predictor == 3){
        prediction_2b[pc_vector[n]] += 'T';
        prediction_itr_2b.push_back('T');
    }
    //now check whether taken or not
    if (actual_itr[n] == prediction_itr_2b[n]){
        correct_two_bit++;
        if(prediction_itr_2b[n] == 'N'){
            if(two_bit_predictor>0){
                two_bit_predictor--;
            }
    }
    else if(prediction_itr_2b[n] == 'T'){
        if(two_bit_predictor<3){
            two_bit_predictor++;
        }
    }
    }
    else if (actual_itr[n] != prediction_itr_2b[n]){
        //correct_two_bit++;
        if(prediction_itr_2b[n] == 'N'){
            if(two_bit_predictor<3){
                two_bit_predictor++;
            }
    }
    else if(prediction_itr_2b[n] == 'T'){
        if(two_bit_predictor>0){
            two_bit_predictor--;
        }
    }
    }
}

void check_accuracy(){
    accuracy_always_taken = ((float)((correct_always_taken*100.00)/(actual_itr.size()*1.00)));
    accuracy_always_not_taken = ((float)((correct_always_not_taken*100.00)/(actual_itr.size()*1.00)));
    accuracy_one_bit = ((float)((correct_one_bit*100.00)/(actual_itr.size()*1.00)));
    accuracy_two_bit = ((float)((correct_two_bit*100.00)/(actual_itr.size()*1.00)));
    
    //printing the accuracies
    cout << "Accuracy:\n";
    cout << "Always Taken: " << accuracy_always_taken << "\n";
    cout << "Always Not Taken: " << accuracy_always_not_taken << "\n";
    cout << "Accuracy One Bit: " << accuracy_one_bit << "\n";
    cout << "Accuracy Two BIt: " << accuracy_two_bit << "\n";
}




long long BintoImm(const string& binary) {
    bitset<64> bits(binary); // Assuming 64-bit binary representation for long long
    return static_cast<long long>(bits.to_ullong());
}

map <ll,ll> visited;

string hexToBinary(string hex) {
    string binary = "";
    for (char& c : hex) {
        switch(c) {
            case '0':
                binary += "0000";
                break;
            case '1':
                binary += "0001";
                break;
            case '2':
                binary += "0010";
                break;
            case '3':
                binary += "0011";
                break;
            case '4':
                binary += "0100";
                break;
            case '5':
                binary += "0101";
                break;
            case '6':
                binary += "0110";
                break;
            case '7':
                binary += "0111";
                break;
            case '8':
                binary += "1000";
                break;
            case '9':
                binary += "1001";
                break;
            case 'A':
            case 'a':
                binary += "1010";
                break;
            case 'B':
            case 'b':
                binary += "1011";
                break;
            case 'C':
            case 'c':
                binary += "1100";
                break;
            case 'D':
            case 'd':
                binary += "1101";
                break;
            case 'E':
            case 'e':
                binary += "1110";
                break;
            case 'F':
            case 'f':
                binary += "1111";
                break;
            default:
                cerr << "Invalid hexadecimal digit: " << c << endl;
                return "";
        }
    }
    return binary;
}



int main(){
    // prediction_itr_ant.push_back('N');
    // prediction_itr_1b.push_back('N');
    // prediction_itr_2b.push_back('N');
    // prediction_itr_at.push_back('T');
    ll it = 0;
    string filename = "input.txt";
    ifstream inputfile(filename);
    string line;
    ll imm;
    char status;
    string imm_b = "";
    flag = 0;
    ll prev_pc;
    while(getline(inputfile, line)){      // reads from the test file line by line 
        
        
        // it++;
        // if(it > 10004)       //this part was added to find the errors in the txt file
        //     break;
        
        istringstream iss(line);            // tokenizing the string line so we can have each aspect separately
        string core, colon,pc, ins;

        iss >> core;
        iss >> colon;

        iss >> pc;
        iss >> ins;

        pc.erase(0,2);
        ins.erase(0,3);
        ins.erase(ins.size()-1, 1);

        //cout << pc << " " << ins << endl;
        ll pc_num = stoll(pc, nullptr, 16);
        
        if(flag == 1){
            if(prev_pc + imm != pc_num)
                status = 'N';
            else
                status = 'T';
            actual_itr.push_back(status);
            pc_vector.push_back(prev_pc);
            actual[prev_pc] += status;
        }
        if(flag == 2){
            if(visited[prev_pc] == 0 ){
                visited[prev_pc]++;
                pc_target.push_back({prev_pc, pc_num});
            }
            actual_itr.push_back('T');
            pc_vector.push_back(prev_pc);
            actual[prev_pc] += 'T';
        }
        string bin_ins = hexToBinary(ins);
        string opcode = bin_ins.substr(25, 7);
        
        if(opcode == "1100011"){ //branch
            imm_b.push_back(bin_ins[0]);
            imm_b.push_back(bin_ins[24]);
            imm_b += bin_ins.substr(1,6) + bin_ins.substr(20, 4) + "0";
            imm = BintoImm(imm_b);
            flag = 1;
            if(visited[pc_num] == 0){
                pc_target.push_back({pc_num, pc_num +imm});
            }
            flag = 1;
            //cout << imm << endl;
        }
        else{
            if(opcode == "1100111" || opcode == "1101111"){ //jalr
                flag = 2;
            }
            else{
                flag = 0;
            }
        }
        if(visited[pc_num] == 0 && flag != 0){
            pc_target.push_back({pc_num, pc_num +imm});
            visited[pc_num]++;
        }
        prev_pc = pc_num;

        // if(opcode == "1101111")    //jal   
    }
    //cout << actual_itr.size(); 
    for(ll i = 0; i < actual_itr.size(); i++){
        //if(actual[i].size() != 0)
            cout << pc_vector[i] << " : " << actual_itr[i] << endl; ;
    }
    
    cout << endl;

    for(n = 0; n < actual_itr.size(); n++){
        always_taken();
    }for(n = 0; n < actual_itr.size(); n++){
        always_not_taken();
    }for(n = 0; n < actual_itr.size(); n++){
        one_bit();
    }for(n = 0; n < actual_itr.size(); n++){
        two_bit();
    }
    // cout << prediction_itr_at.size() << endl;
    // for(char a : prediction_itr_at){
    //     cout << a << " ";
    // }
    // cout << prediction_itr_ant.size() << endl;
    // for(char a : prediction_itr_ant){
    //     cout << a << " ";
    // }
    // cout << prediction_itr_1b.size() << endl;
    // for(char a : prediction_itr_1b){
    //     cout << a << " ";
    // }
    // cout << prediction_itr_2b.size() << endl;
    // for(char a : prediction_itr_2b){
    //     cout << a << " ";
    // }

    cout << "\n\nBRANCH TARGET BUFFER : \n" ;
    cout << "\n\tFROM\t TARGET ADDRESS\tACTUAL\n\n";
    for(auto i  = pc_target.begin(); i != pc_target.end(); i++)
        cout << (i-pc_target.begin()) + 1 << ". "  << i->first  << "\t" << i->second << " " << actual[i->first] << endl;
    
    cout << "\n PREDICTIONS : \n\n";
    cout << "ALWAYS TAKEN : \n";
     for(auto i  = pc_target.begin(); i != pc_target.end(); i++)
        cout << (i-pc_target.begin()) + 1 << ". "  << i->first  << "\t"<< prediction_at[i->first] << endl;
    cout << "\n\nALWAYS NOT TAKEN : \n";
     for(auto i  = pc_target.begin(); i != pc_target.end(); i++)
        cout << (i-pc_target.begin()) + 1 << ". "  << i->first  << "\t"<< prediction_ant[i->first] << endl;
    cout << "\n\nONE BIT : \n";
     for(auto i  = pc_target.begin(); i != pc_target.end(); i++)
        cout << (i-pc_target.begin()) + 1 << ". "  << i->first  << "\t"<< prediction_1b[i->first] << endl;
    cout << "\n\nTWO BIT: \n";
     for(auto i  = pc_target.begin(); i != pc_target.end(); i++)
        cout << (i-pc_target.begin()) + 1 << ". "  << i->first  << "\t"<< prediction_2b[i->first] << endl;
    cout << endl << endl;
    check_accuracy();
    cout << endl;

    inputfile.close();
    return 0;
}