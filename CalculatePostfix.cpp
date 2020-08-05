#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>

bool is_digit(std::string& str) {
    for (char ch: str){
        if (ch < '0'  || ch > '9') return false;
    }
    return true;
}


float calculate(std::string& postfix){
    std::stack<float> stack;
    std::string token;
    char delimiter = ' ';
    size_t pos = 0;
    while ((pos = postfix.find(delimiter)) != std::string::npos){
        token = postfix.substr(0, pos);
        postfix.erase(0, pos + 1);

        if (is_digit(token)) {
            stack.push(atof(token.c_str()));
            continue;
        }
        
        float a = stack.top();
        stack.pop();
        float b = stack.top();
        stack.pop();
        if (token == "+") {
            stack.push(a + b);
        }
        else if (token == "-")
        {
            stack.push(b - a);
        }
        else if (token == "*")
        {
            stack.push(a * b);
        }
        else if (token == "/")
        {
            stack.push(b / a);
        }
        else
        {
            std::cerr << "Я еще не знаю такой операции:: ошибка парсинга" << std::endl;
        }
    }
    return stack.top();
}

int main(){
    std::string str;
    std::ifstream input("./test2");
    if (input.is_open()){
        while (!input.eof()){
            std::getline(input, str);
            std::cout << calculate(str) << std::endl;
        }
        
    }
    return 0;
}