#include <fstream>
#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <cctype>

std::map<char, int> priority = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
    {'(', 0},
    {')', 4},
}; 

std::string delSpaces(std::string& str){
    std::string tmp;
    for(char ch: str){
        if (ch != ' '){
            tmp += ch;
        }
    }
    return tmp;
}

std::string toPostfix(std::string& infix){
    std::string result;
    std::stack<char> stack;
    for (int i = 0; i < infix.length(); ++i){
        if (std::isdigit(infix[i])) {
            result.push_back(infix[i]);
            result.push_back(' ');
            continue;
        }
        if (infix[i] == '('){
            stack.push('(');
            continue;
        }
        if (infix[i] == ')'){
            char ch = stack.top();
            while (ch != '('){
                result.push_back(ch);
                result.push_back(' ');
                stack.pop();
                ch = stack.top();
            }
            stack.pop();
            continue;
        }
        char ch = infix[i];
        if (stack.empty()) {
            stack.push(ch);
            continue;
        }
        if (priority[ch] > priority[stack.top()]){
            stack.push(ch);
        }
        else
        {
            char oper = stack.top(); 
            while (priority[ch] <= priority[oper]){
                result.push_back(oper);
                result.push_back(' ');
                stack.pop();
                if (stack.empty()){
                    break;
                }
                oper = stack.top();
            }
            stack.push(ch);
        }
        
    }
    while (!stack.empty())
    {
        result.push_back(stack.top());
        result.push_back(' ');
        stack.pop();
    }
    
    return result;
}

int main(){
    std::ifstream input;
    std::string str;
    input.open("./test");
    if (input.is_open()){
        while (!input.eof()){
            std::getline(input, str);
            std::string del = delSpaces(str);
            std::cout << toPostfix(del) << std::endl;
        }
    }
    input.close();
    return 0;
}
