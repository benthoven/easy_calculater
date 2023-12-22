#include"function.h"
#include<memory>

//��׺���ʽת��׺���ʽ 
// 
// ��׺���ʽת��׺���ʽ
//�����������α�����׺���ʽ�����ַ�����Ҫ׼��һ���ַ�ջ�洢�����������ţ�
//
//1���ַ�Ϊ ������ ��
//ֱ�������׺���ʽ��ע����Ҫ�ȷ���������������������
//
//2���ַ�Ϊ ������ ��
//ֱ����ջ��ע����������ջ�����ȼ�������ͣ���
//
//3���ַ�Ϊ ������ ��
//ֱ�ӳ�ջ��������ջ�ַ����������׺���ʽ��ֱ��ջ���ַ�Ϊ�����ţ�������ҲҪ��ջ�����������׺���ʽ����
//�ܽ᣺ֻҪ���� ջ��Ϊ������ ���ɽ������һ�γ�ջ��
// 
//4���ַ�Ϊ ������ ��
//��ջ�գ�ֱ����ջ��
//��ջ�ǿգ��ж�ջ������������ջ�����������ȼ����ڸò��������ò�������ջ������һֱ��ջ��������ջ�ַ����������׺���ʽ��ֱ��ջ�ջ�ջ�����������ȼ����ڸò��������ò���������ջ��
//�ܽ᣺ֻҪ���� ջ�� ���� ���ȼ�����ջ�������� ����ֹͣ��ջ�������ò�������ջ��
// 
//5���ظ����ϲ���ֱ�����������׺���ʽ�������ж��ַ�ջ�Ƿ�Ϊ�գ��ǿ���ֱ�ӳ�ջ��������ջ�ַ����������׺���
//ע����׺���ʽ������ɣ�ջ�п��ܻ����ַ�δ���������Ҫ�ж�ջ�ա�



bool canpush(char newoper, list_stack<char>& stack)//�ж��·����Ƿ������ջ
{
	if (stack.isempty())//ջΪ�գ�ֱ����ջ
	{
		return true;
	}
	char top = stack.gettop();
	if (newoper == '(' || top == '(')//�����������ֱ����ջ����ջ�����ȼ�������ͣ�����ֻҪ�����ǣ��Կ��������ȼ���ջ����
	{
		return true;
	}
	if ((newoper == '*' || newoper == '/') && (top == '+' || top == '-'))//ֻҪ��ջ�������ȼ�����ջ��������ջ
	{
		return true;
	}
	return false;

}
//��׺ת��׺��ȷ�����ǰ���ǣ�
//�� �������׺���ʽ�Ϸ�
//�� �������Ǹ���

//  ����һΪ ����ı��ʽ�ַ�����  ������Ϊת������ַ�����
//char*����Ĳ���ֻ�ܶ�ȡ��������[] ����Ŀɶ���д
void frofix_to_backfix_exp(std::string &frofix, std::string &backfix)
{
	int len = frofix.size();//�����ַ�������
	//std::shared_ptr<char[]>backfix1(new char[100 * len + 200]);
	//backfix = new char[100 * len + 200];//��ֹ�ڴ����
	//backfix = (char*)backfix1;
	int writeloc = 0;
	list_stack<char> stack_oper;//�ַ�ջ
	for (int i = 0; i < len; i++)
	{
		char temp = frofix[i];
		if (temp == ' ')//���Ա��ʽ�еĶ���ո�
		{
			continue;
		}
		if (isnegative(frofix, i))//���Ǹ��� �������׺���ʽ
		{
			backfix[writeloc++] = '-';
			//std::cout << backfix << std::endl;
			continue;
		}
		if (isnumber(temp))//��������
		{
			int j = i;
			while (isnumber(frofix[j]) || frofix[j] == '.')//����������ȫ�����׺���ʽ
			{
				backfix[writeloc++] = frofix[j];
				//std::cout << *backfix << std::endl;
				j++;
			}
			i = j - 1;//i�ص����ָ���һ��λ�ã���������ӳ�ʼλ�ñ���
			backfix[writeloc++] = ' ';//��һ�����������ָ���
		}
		else//��Ϊ�����
		{
			if (canpush(frofix[i], stack_oper))//����ѹջ����
			{
				char t = frofix[i];
				stack_oper.push(t);
				//delete t;
				//stack_oper.printf();
			}
			else//������ѹջ����
			{
				if (frofix[i] == ')')//1.���������� ��һֱ��ջ����ջԪ�ط����׺���ʽ��ֱ������������
				{
					char top = stack_oper.gettop();
					stack_oper.pop();
					while (top != '(')
					{
						backfix[writeloc++] = top;
						backfix[writeloc++] = ' ';
						//std::cout << *backfix << std::endl;
						top = stack_oper.gettop();
						stack_oper.pop();
					}

				}
				else//2.ջ�����ȼ������·������ȼ�
				{
					for (; !canpush(frofix[i], stack_oper); stack_oper.pop())//ֻҪ��������ջ������һֱ��ջ��ֱ������ ��ջ
					{
						char top = stack_oper.gettop();
						backfix[writeloc++] = top;
						backfix[writeloc++] = ' ';
						//std::cout << *backfix << std::endl;
						stack_oper.pop();
						
					}
					stack_oper.push(frofix[i]);//��ջ
				}
			}
			
		}
	}
	while(!stack_oper.isempty())//ջ��ʣ����ַ������׺���ʽ
	{
		char top =stack_oper.gettop();
		backfix[writeloc++] = top;
		backfix[writeloc++] = ' ';
		//std::cout << *backfix << std::endl;
		stack_oper.pop();
	}
	//return backfix;
}

bool isnumber(char x)//�ж��Ƿ�������
{
	if (x >= '0' && x <= '9')//����Ҳ���ַ�
	{
		return true;
	}
	return false;
}

double chartonumber(char x)//�ַ�ת����
{
	return (x - '0');//�ַ�ת����

}

double calculate(char op, double m, double n)//�ֲ�����
{
	switch (op)
	{
	case '+':
		return m + n;
		break;
	case '-':
		return m - n;
		break;
	case '*':
		return m * n;
		break;
	case '/':
		return m / n;
		break;
	}
	std::cout << "������������" << std::endl;
}

//������׺���ʽ�ļ���
//�����������α�����׺���ʽ�����ַ�����Ҫ׼��һ��������ջ�洢�������Ͳ��������
//
//1���ַ�Ϊ ������ ��
//
//ֱ����ջ��ע����Ҫ�ȷ�����������������������ת��Ϊ��Ӧ���������ͣ�
//
//2���ַ�Ϊ ������ ��
//
//������ջ���Σ�ʹ�ó�ջ���������ݽ�����Ӧ���㣬������������ջ
//
//e.g����һ����ջ��������Ϊ a ���ڶ�����ջ��������Ϊ b ����ʱ�Ĳ�����Ϊ - ������� b - a  ��ע��a��b˳���ܷ��������������ջ��
//
//3���ظ����ϲ���ֱ��������ɺ�׺���ʽ�����ջ�е����ݾ�����׺���ʽ�ļ�������

double calculateback(std::string lastexp)//�����׺���ʽ
{
	int len = lastexp.size();
	char temp=' ';
	list_stack<double> nums;//�������
	
	for (int j = 0; j < len; j++)
	{
		std::string name ="result" ;
		temp = lastexp[j];
		if (temp == '-' && isnumber(lastexp[j + 1]))continue;//����

		if (isnumber(temp))//����
		{
			list_stack<double> t_stack;
			
			 double lastnum = 0;
			double n = 0;//���������λ
			int flag = 1;//��Ǹ���
			int i = j;
			 
			if (j != 0 && lastexp[i - 1] == '-')flag = -1;//��ʱΪ����
			while (isnumber(lastexp[i]))//�������������ַ�
			{
				t_stack.push(lastexp[i]);
				
				++i;
			}
			while (!t_stack.isempty())
			
			{
				lastnum += chartonumber(t_stack.gettop())*pow(10,n);//�ۼӵó���������,�����ǵ����ַ�
				
				++n;
				t_stack.pop();
			}
			double m = 1;
			if (lastexp[i] == '.')
			{
				++i;//��ǰһλ
				
				while (isnumber(lastexp[i]))
				{
					lastnum += chartonumber(lastexp[i])  * pow(0.1, m);
					++m;
					++i;
				}
			}
			
			//std::unique_ptr<double>name(new double (lastnum * flag));
			double last=lastnum * flag;
			nums.push(last);//��������ջ��
			
			nums.printf();
			
			j = i - 1;//�ص�ĩλ��
		}
		else//Ϊ����ʱ
		{
			nums.printf();
			double pop1 = nums.gettop();//��һ����ջԪ��
			
			nums.pop();
			double pop2 = nums.gettop();
			
			nums.pop();
			double result=calculate(temp,pop2,pop1);//����
			nums.push(result);
			nums.printf();
		}
		if (lastexp[j+1] == ' ')//���Կո�
		{
			++j;
		}
	}
	return nums.gettop();//��������ֵ
	
}


bool islegalexpression(std::string infixexp)//�жϱ��ʽ�Ƿ�Ϸ�
{
	if (infixexp == " ")
	{
		std::cout << "islegalexpression���ʽ������" << std::endl;
	}
	if (checkbrackets(infixexp) && checkexpression(infixexp))
	{
		return true;
		std::cout << "���ʽ��֤ͨ��" << std::endl;
	}
	std::cout << "���ʽ��֤ʧ��" << std::endl; 
	return false;

}

bool checkexpression(std::string infixexp)//���ַ�ɨ������ʽ
{
	bool nonumber = true;//û�����ֱ�־
	//���жϵ�һ��Ԫ��

	if (infixexp[0] != '(' && !isnumber(infixexp[0]) && infixexp[0] != '-')return false;
	int len = infixexp.size();
	//��������Ԫ��
	for (int j = 0; j < len; j++)//������е��˴���û�е�������������֤����һ����ʽû���⣬�ٽ��г����ж�
	{
		char temp = infixexp[j];
		if (isnumber(temp))nonumber = false;//������
		if (temp == ' ')continue;
		if (!isnumber(temp) &&!isbasicoper(temp)&& temp !='('&& temp !=')'&& temp !='.') return false;//���ܴ�����������
		if (isbasicoper(temp))//�жϷ�������
		{
			char left = infixexp[j - 1];
			char right = infixexp[j + 1];
			if (temp == '.')//.ǰ��ֻ�������֣��ж�.�����
			{
				if (!isnumber(left) ||!isnumber(right))return false;
			}
			if (temp == '/')//  /���ұ߲�����0
			{
				if (right == '0')return false;
			}
			if (isbasicoper(left) || isbasicoper(right)) return false;//����Ԫ�ز����Ƿ���
			if (temp != '-' && (left == '(' || right == ')'))return false;//������Χ�����Ƿ��ţ�.�Ĳ��Ϸ�����Ѿ����ų���
			if (temp == '-' && right == ')')return false;//��ʱ�Ǽ������

		}
	}
	if (nonumber)return false;//û�����ִ���
	return true;
}

bool checkbrackets(std::string infixexp)//��������Ƿ�ƥ��
{
	list_stack<char> stack_bra;
	int len = infixexp.size();
	for (int j = 0; j < len; j++)
	{
		char temp = infixexp[j];
		if (temp == '(')//��������ջ�������ų�ջ
		{
			stack_bra.push(temp);
		}
		if (temp == ')')
		{
			stack_bra.pop();
		}
		if (stack_bra.isempty())
		{
			return true;
		}
		return false;
	}
}

bool isbasicoper(char i)//����Ƿ��ǼӼ��˳���������
{
	if (i == '+' || i == '-' || i == '*' || i == '/')
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool isnegative(std::string infixexp, int pos)//�ж��Ƿ��Ǹ��Ŷ����Ǽ���  ����һ�ַ����������� ����  �Ľ�����
{
	if (infixexp[pos] == '-')//��Ϊ���������ֿ���
	{
		if (pos == 0)//1.��ͷλ�ñ�Ϊ-��
			return true;
		if (infixexp[pos - 1] == '(')//2.���������Ű�Χ�����������еĵ�һ��Ԫ��  ��ͬ�㶼��ǰ���ǣ�
			return true;
	}
	return false;
}
