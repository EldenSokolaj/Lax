#include <iostream>
#include <fstream>
#include "parser.h"
#include "functions.h"
using namespace std;

int main(){
    log func{};

    ifstream in{"test.code"};
    ofstream out{"test.bf"};
    char buf;
    string scope = "";
    string data = "";
    int line = 1;
    do{
        in >> noskipws >> buf;
        if(buf != ';' && buf != ':'){
            if(buf == '\n'){
                line++;
            } else if(buf != '\t' && !(data.length() == 0 && buf == ' ')){
                data += buf;
            }
        } else {
            //function def case
            if(data.substr(0, 3) == "def"){
                
                size_t loc = data.find(' ');
                if(loc == string::npos){
                    cout << "Error on line " << line << endl;
                } else {
                    data = data.substr(loc + 1);
                    func.set(data);
                    scope = data;
                }

            } else if(data == "ret"){

                scope = "";

            } else if(data.substr(0, 4) == "call"){

                data = data.substr(5);
                data = func.get(data);

                if(scope == ""){
                    out << data;
                } else {
                    func.add(scope, data);
                }

            } else {

                //normal case
                data = instuction_to_code( data );
                if(data == "INVALID"){
                    cout << "Error on line " << line << endl;
                    cout << "Data: " << data << endl;
                } else {
                    if(scope == ""){
                        out << data;
                    } else {
                        func.add(scope, data);
                    }
                }
            }
            data = "";
        }
    } while(!in.eof());
    in.close();
    out.close();
    return 0;
}
