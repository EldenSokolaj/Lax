#ifndef PARSER_LESS_ESOTERIC_LANG_H
#define PARSER_LESS_ESOTERIC_LANG_H

#include <iostream>
using namespace std;

string eval_string_value(string in){
    string ret = "";
    size_t loc = in.find(' ');
    if(loc == string::npos){
        cout << "Write command error!" << endl;
        return "ERROR!\0";
    }
    in = in.substr(loc + 1);

    for(int i = 0; i < in.length(); i++){
        if(in[i] == ' '){} else if(in[i] == '"'){
            i++;
            while(in[i] != '"'){
                if(in[i] == '\\'){
                    i++;
                }
                ret += in[i];
                i++;
            }
            i++;
        } else if(in[i] == '\''){
            i++;
            ret += in[i];
            i += 2;
        } else {
            ret += (char)stoi(in.substr(i));
            in = in.substr(in.find(' '));
        }
    }
    
    return ret;
}

string tolower(string in){
    int len = in.length();
    string ret = "";
    for(int i = 0; i < len; i++){
        ret += tolower(in[i]);
    }
    return ret;
}

int opcode(string in){
    string codes[] = {"add", "sub", "movr", "movl", "while", "end", "set", "print", "get", "inc", "dec"};
    size_t pos = in.find(' ');
    string temp;
    if(pos == string::npos){
        temp = in;
    } else {
        temp = in.substr(0, pos);
    }
    temp = tolower(temp);
    for(int i = 0; i < 11; i++){
        if(temp == codes[i]){
            return i;
        }
    }
    return -1;
}

int eval_segment(string seg){
    //helps for negative numbers
    if(seg.length() == 0){
        return 0;
    }

    char ops[] = {'+', '-', '*', '/'};
    size_t loc;
    int type = -1;
    //search for split
    for(int i = 0; i < seg.length(); i++){
        for(int j = 0; j < 4; j++){
            if(seg[i] == ops[j]){
                loc = i;
                type = j;
            }
        }
    }
    //if split does not exist, return value of const
    if(type == -1){
        loc = seg.find('\'');
        if(loc == string::npos){
            return stoi(seg);
        }
        return (int)seg[loc + 1];
    }
    //if split does exist, type and both sides
    string two = seg.substr(0, loc);
    string one = seg.substr(loc + 1);
    
    int o, t;

    //figure out value of const one
    loc = one.find('\'');
    if(loc == string::npos){
        o = stoi(one);
    } else {
        o = (int)one[loc + 1];
    }

    //figure out the value of possibly non-const two
    t = eval_segment(two);

    int ret;

    switch(type){
        case 0:
            ret = t + o; break;
        case 1:
            ret = t - o; break;
        case 2:
            ret = t * o; break;
        case 3:
            ret = t / o; break;
    }

    return ret;
}

int eval_opcode_value(string in){
    size_t pos = in.find(' ');
    if(pos == string::npos){
        return 0;
    }
    return eval_segment( in.substr(pos + 1) );
}

string instuction_to_code(string op){
    char t;
    string ret = "";

    //impliment write function
    if(op.find("write") != string::npos){
        string data = eval_string_value(op);
        string ret = "";
            for(int i = 0; i < data.length(); i++){
                ret += "[-]";
                int val = data[i];
                t = (val > 0) ? '+' : '-';
                if(val < 0){
                    val = -val;
                }
                for(int i = 0; i < val; i++){ ret += t; }
                ret += ">";
            }
            for(int i = 0; i < data.length(); i++){
                ret += "<";
            }
        return ret;
    }

    //else impliment all other opcodes
    int val;
    try{
        val = eval_opcode_value(op);
    } catch (exception &e){
        cout << "ERROR: " << op << endl;
    }

    switch(opcode(op)){
        case -1: //error case
            ret = "INVALID"; break;
        case 0: //add case
            t = (val > 0) ? '+' : '-';
            if(val < 0){
                val = -val;
            }
            for(int i = 0; i < val; i++){ ret += t; } break;
        case 1: //sub case
            t = (val > 0) ? '-' : '+';
            if(val < 0){
                val = -val;
            }
            for(int i = 0; i < val; i++){ ret += t; } break;
        case 2: //movr case
            t = (val > 0) ? '>' : '<';
            if(val < 0){
                val = -val;
            }
            for(int i = 0; i < val; i++){ ret += t; } break;
        case 3: //movl case
            t = (val > 0) ? '<' : '>';
            if(val < 0){
                val = -val;
            }
            for(int i = 0; i < val; i++){ ret += t; } break;
        case 4: //while case
            ret = "["; break;
        case 5: //end case
            ret = "]"; break;
        case 6: //set case
            t = (val > 0) ? '+' : '-';
            if(val < 0){
                val = -val;
            }
            ret = "[-]"; for(int i = 0; i < val; i++){ ret += t; } break;
        case 7: //print case
            ret = "."; break;
        case 8: //get case
            ret = ','; break;
        case 9: //inc case
            ret = '+'; break;
        case 10: //dec case
            ret = '-'; break;
    }
    return ret;
}

#endif
