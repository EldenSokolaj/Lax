#ifndef FUNCTIONS_H
#define FUNCTION_H

#include <iostream>
using namespace std;

class log{
    private:
        struct item{
            string name;
            string val;

            item(string n){
                name = n;
                val = "";
            }

            item(){
                name = "";
                val = "";
            }
        };

        item* list;
        int max, len;
    
    public:
        log(){
            max = 1;
            len = 0;
            list = new item[1];
        }

        void set(string name){
            if(len == max){
                max *= 2;
                item *temp = new item[max];
                for(int i = 0; i < len; i++){
                    temp[i] = list[i];
                }
                delete[] list;
                list = temp;
            }
            list[len] = item(name);
            len++;
        }

        void add(string name, string data){
            for(int i = 0; i < len; i++){
                if(list[i].name == name){
                    list[i].val += data;
                    i = len;
                }
            }
        }

        string get(string function){
            for(int i = 0; i < len; i++){
                if(list[i].name == function){
                    return list[i].val;
                }
            }
            return "";
        }
};

#endif