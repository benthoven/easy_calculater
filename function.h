#pragma once
#include"list_stackT.hpp"
#include<iostream>



void frofix_to_backfix_exp(std::string &frofix, std::string &backfix);//��׺���ʽת��׺���ʽ

bool isnumber(char x);//�ж��Ƿ�������

double chartonumber(char x);//�ַ�ת����

double calculate(char op, double m, double n);//�� ��׺���ʽ���м���

//bool canpush(char newoper, list_stack stack);//�ж��·����Ƿ������ջ

double calculateback(std::string lastexp);//�� �����׺���ʽ

bool islegalexpression(std::string infixexp);//�жϱ��ʽ�Ƿ�Ϸ�

bool checkexpression(std::string infixexp);//���ַ�ɨ������ʽ

bool checkbrackets(std::string infixexp);//��������Ƿ�ƥ��

bool isbasicoper(char i);//����Ƿ��ǼӼ��˳���������

bool isnegative(std::string infixexp, int pos);//�ж��Ƿ��Ǹ��Ŷ����Ǽ���
