#include "StringProduction.hpp"
#include "Dictionary.hpp"
#include<iostream>
using namespace std;

int main(int argc, const char* argv[]){
    if(argc != 3){
        cout<<"prog word1 word2" <<endl;
        return 1;
    }

    Dictionary dic(3);
    dic.addElement("lob");
    dic.addElement("dog");
    dic.addElement("log");
    dic.addElement("car");
    dic.addElement("dog");
    dic.addElement("cat");
    dic.addElement("cob");
    dic.addElement("cab");
    dic.addElement("cag");

    dic.buildAdjencyMatrix();

    vector<string> path;
    StringProduction sp(dic);
    if(sp.produces(argv[1], argv[2], path)){
        cout<< "-- the first string produces the second"<<endl;
        cout<<" -- the path has size "<<path.size() <<":\n";
        for(unsigned i=0; i<path.size(); i++){
            cout<< path[i] <<";";
        }
    }else{
        cout<<" the second string does not produce the second "<<endl;
    }
    return 0;
}


//for terminal output
//g++ StringProduction.cpp Dictionary.cpp main.cpp -o output.exe
//then
//output.exe cat dog

