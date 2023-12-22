#pragma once
#include<iostream>

template<typename T>
struct listnode
{
	T data;
	listnode* next;
};

template<typename T>
class list_stack
{
public:
	listnode<T> * head;
	int size;

	list_stack();

	void push(T data);//��ջ

	void pop();//��ջ

	bool isempty();//�ж��Ƿ�Ϊ��

	T gettop();//��ȡջ��Ԫ��

	void printf();//����

	~list_stack();


};
template <typename T>
list_stack<T>::list_stack()
{
	head = new listnode<T>;
	head->data = NULL;
	head->next = NULL;
	size = 0;

}
template <typename T>
void list_stack<T>::push(T data)//��ջ
{
	listnode<T>* newnode = new listnode<T>;
	newnode->data = data;
	newnode->next = head->next;
	head->next = newnode;
	size++;

}
template <typename T>
void list_stack<T>::pop()//��ջ
{
	if (size == 0)return;
	listnode<T>* pdel = head->next;
	head->next = pdel->next;
	delete pdel;
	size--;
}
template <typename T>
bool list_stack<T>::isempty()//�ж��Ƿ�Ϊ��
{
	if (size == 0)return true;
	return false;
}
template <typename T>
T list_stack<T>::gettop()//��ȡջ��Ԫ��
{
	return head->next->data;
}
template <typename T>
void list_stack<T>::printf()//����
{
	listnode<T>*pcurrent = head->next;
	std::cout << "Ԫ��Ϊ" << std::endl;
	while (pcurrent)
	{
		std::cout << pcurrent->data << std::endl;
		pcurrent = pcurrent->next;
	}
}
template <typename T>
list_stack<T>::~list_stack()
{
	if (head == NULL)
	{
		return;
	}
	listnode<T>*pcurrent = head;
	while (pcurrent)
	{
		listnode<T>*pnext = pcurrent->next;
		delete pcurrent;
		pcurrent = pnext;
	}
	size == 0;
	std::cout << "���ٳɹ�" << std::endl;
}