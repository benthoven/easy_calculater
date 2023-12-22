#pragma once
#include"list_stackT.hpp"
#include<iostream>



void frofix_to_backfix_exp(std::string &frofix, std::string &backfix);//中缀表达式转后缀表达式

bool isnumber(char x);//判断是否是数字

double chartonumber(char x);//字符转数字

double calculate(char op, double m, double n);//分 后缀表达式进行计算

//bool canpush(char newoper, list_stack stack);//判断新符号是否可以入栈

double calculateback(std::string lastexp);//总 计算后缀表达式

bool islegalexpression(std::string infixexp);//判断表达式是否合法

bool checkexpression(std::string infixexp);//逐字符扫描检查表达式

bool checkbrackets(std::string infixexp);//检查括号是否匹配

bool isbasicoper(char i);//检查是否是加减乘除基本运算

bool isnegative(std::string infixexp, int pos);//判断是否是负号而不是减号
