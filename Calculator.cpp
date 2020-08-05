#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <cctype>
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

std::map<char, int> priority = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
    {'(', 0},
    {')', 4},
};

void delSpaces(std::string& str){
    std::string tmp;
    for(char ch: str){
        if (ch != ' '){
            tmp += ch;
        }
    }
    std::swap(str, tmp);
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

int main() {
    bool stop = false;
    std::string str;
    while (!stop){
        int n = 0;
        std::cout << "Меню:" << std::endl 
        << "Нажмите 1 для вычислений" << std::endl 
        << "Нажмите любую клавишу для выхода" << std::endl;
        std::cin >> n;
        switch (n)
        {
        case 1:
            std::cout << "Введите выражение -> ";
            std::cin >> str;
            delSpaces(str);
            str = toPostfix(str);
            std::cout << calculate(str) << std::endl;
            break;
        
        default:
            stop = true;
            break;
        }
    }
    std::cout << "Досвидания!" << std::endl;
    return 0;
}