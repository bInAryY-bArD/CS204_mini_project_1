#include<bits/stdc++.h>
using namespace std;

int main(){
    
    ifstream inputfile("test.asm");             // enter the input file name here 
    ofstream converted_code("machinecode.mc");  // filename of the machine code


    string line, converted_line;
    while(getline(inputfile, line)){      // reads from the test file line by line 
        
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos)      //Erasing the commas for convenience
            line.erase(pos, 1);
        
        istringstream iss(line);            // tokenizing the string line so we can have each aspect separately
        string instruction;
        iss >> instruction;         // extracting the isntruction which is the first word


        
                //ENTER THE 
                //CODE
                //HERE

        converted_line = "Replace it with the string of machine code";
        converted_code << converted_line << "\n";                       // writing it in the file you are creating

    }
    inputfile.close();
    converted_code.close();
    return 0;
}