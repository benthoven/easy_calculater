#pragma once
#include"list_stackT.hpp"
#include<iostream>



char* frofix_to_backfix_exp(char* frofix, char backfix[]);//��׺���ʽת��׺���ʽ

bool isnumber(char x);//�ж��Ƿ�������

double chartonumber(char x);//�ַ�ת����

double calculate(char op, double m, double n);//�� ��׺���ʽ���м���

//bool canpush(char newoper, list_stack stack);//�ж��·����Ƿ������ջ

double calculateback(char* lastexp);//�� �����׺���ʽ

bool islegalexpression(char* infixexp);//�жϱ��ʽ�Ƿ�Ϸ�

bool checkexpression(char* infixexp);//���ַ�ɨ������ʽ

bool checkbrackets(char* infixexp);//��������Ƿ�ƥ��

bool isbasicoper(char i);//����Ƿ��ǼӼ��˳���������

bool isnegative(char* infixexp, int pos);//�ж��Ƿ��Ǹ��Ŷ����Ǽ���
