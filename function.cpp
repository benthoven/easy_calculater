#include"function.h"
#include<memory>

//中缀表达式转后缀表达式 
// 
// 中缀表达式转后缀表达式
//从左至右依次遍历中缀表达式各个字符（需要准备一个字符栈存储操作符和括号）
//
//1、字符为 运算数 ：
//直接送入后缀表达式（注：需要先分析出完整的运算数）。
//
//2、字符为 左括号 ：
//直接入栈（注：左括号入栈后优先级降至最低）。
//
//3、字符为 右括号 ：
//直接出栈，并将出栈字符依次送入后缀表达式，直到栈顶字符为左括号（左括号也要出栈，但不送入后缀表达式）。
//总结：只要满足 栈顶为左括号 即可进行最后一次出栈。
// 
//4、字符为 操作符 ：
//若栈空，直接入栈。
//若栈非空，判断栈顶操作符，若栈顶操作符优先级低于该操作符，该操作符入栈；否则一直出栈，并将出栈字符依次送入后缀表达式，直到栈空或栈顶操作符优先级低于该操作符，该操作符再入栈。
//总结：只要满足 栈空 或者 优先级高于栈顶操作符 即可停止出栈，并将该操作符入栈。
// 
//5、重复以上步骤直至遍历完成中缀表达式，接着判断字符栈是否为空，非空则直接出栈，并将出栈字符依次送入后缀表达
//注：中缀表达式遍历完成，栈中可能还有字符未输出，故需要判断栈空。



bool canpush(char newoper, list_stack<char>& stack)//判断新符号是否可以入栈
{
	if (stack.isempty())//栈为空，直接入栈
	{
		return true;
	}
	char top = stack.gettop();
	if (newoper == '(' || top == '(')//如果是左括号直接入栈，入栈后优先级降到最低，所以只要顶部是（皆可满足优先级入栈条件
	{
		return true;
	}
	if ((newoper == '*' || newoper == '/') && (top == '+' || top == '-'))//只要入栈符号优先级大于栈顶即可入栈
	{
		return true;
	}
	return false;

}
//中缀转后缀正确运算的前提是：
//① 输入的中缀表达式合法
//② 运算数非负数

//  参数一为 传入的表达式字符数组  参数二为转换后的字符数组
//char*传入的参数只能读取，数组名[] 传入的可读可写
void frofix_to_backfix_exp(std::string &frofix, std::string &backfix)
{
	int len = frofix.size();//计算字符串长度
	//std::shared_ptr<char[]>backfix1(new char[100 * len + 200]);
	//backfix = new char[100 * len + 200];//防止内存溢出
	//backfix = (char*)backfix1;
	int writeloc = 0;
	list_stack<char> stack_oper;//字符栈
	for (int i = 0; i < len; i++)
	{
		char temp = frofix[i];
		if (temp == ' ')//忽略表达式中的多余空格
		{
			continue;
		}
		if (isnegative(frofix, i))//若是负数 负号入后缀表达式
		{
			backfix[writeloc++] = '-';
			//std::cout << backfix << std::endl;
			continue;
		}
		if (isnumber(temp))//若是数字
		{
			int j = i;
			while (isnumber(frofix[j]) || frofix[j] == '.')//将后续数字全部入后缀表达式
			{
				backfix[writeloc++] = frofix[j];
				//std::cout << *backfix << std::endl;
				j++;
			}
			i = j - 1;//i回到最后指向的一个位置，避免继续从初始位置遍历
			backfix[writeloc++] = ' ';//将一整个运算数分隔开
		}
		else//若为运算符
		{
			if (canpush(frofix[i], stack_oper))//满足压栈条件
			{
				char t = frofix[i];
				stack_oper.push(t);
				//delete t;
				//stack_oper.printf();
			}
			else//不满足压栈条件
			{
				if (frofix[i] == ')')//1.遇到右括号 就一直出栈，出栈元素放入后缀表达式，直到遇到左括号
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
				else//2.栈顶优先级大于新符号优先级
				{
					for (; !canpush(frofix[i], stack_oper); stack_oper.pop())//只要不满足入栈条件就一直出栈，直到满足 入栈
					{
						char top = stack_oper.gettop();
						backfix[writeloc++] = top;
						backfix[writeloc++] = ' ';
						//std::cout << *backfix << std::endl;
						stack_oper.pop();
						
					}
					stack_oper.push(frofix[i]);//入栈
				}
			}
			
		}
	}
	while(!stack_oper.isempty())//栈内剩余的字符放入后缀表达式
	{
		char top =stack_oper.gettop();
		backfix[writeloc++] = top;
		backfix[writeloc++] = ' ';
		//std::cout << *backfix << std::endl;
		stack_oper.pop();
	}
	//return backfix;
}

bool isnumber(char x)//判断是否是数字
{
	if (x >= '0' && x <= '9')//数字也是字符
	{
		return true;
	}
	return false;
}

double chartonumber(char x)//字符转数字
{
	return (x - '0');//字符转整型

}

double calculate(char op, double m, double n)//分部计算
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
	std::cout << "符号输入有误" << std::endl;
}

//三、后缀表达式的计算
//从左至右依次遍历后缀表达式各个字符（需要准备一个运算数栈存储运算数和操作结果）
//
//1、字符为 运算数 ：
//
//直接入栈（注：需要先分析出完整的运算数并将其转换为对应的数据类型）
//
//2、字符为 操作符 ：
//
//连续出栈两次，使用出栈的两个数据进行相应计算，并将计算结果入栈
//
//e.g：第一个出栈的运算数为 a ，第二个出栈的运算数为 b ，此时的操作符为 - ，则计算 b - a  （注：a和b顺序不能反），并将结果入栈。
//
//3、重复以上步骤直至遍历完成后缀表达式，最后栈中的数据就是中缀表达式的计算结果。

double calculateback(std::string lastexp)//计算后缀表达式
{
	int len = lastexp.size();
	char temp=' ';
	list_stack<double> nums;//存放数据
	
	for (int j = 0; j < len; j++)
	{
		std::string name ="result" ;
		temp = lastexp[j];
		if (temp == '-' && isnumber(lastexp[j + 1]))continue;//负号

		if (isnumber(temp))//数字
		{
			list_stack<double> t_stack;
			
			 double lastnum = 0;
			double n = 0;//方便进制数位
			int flag = 1;//标记负号
			int i = j;
			 
			if (j != 0 && lastexp[i - 1] == '-')flag = -1;//此时为负数
			while (isnumber(lastexp[i]))//存入整个数据字符
			{
				t_stack.push(lastexp[i]);
				
				++i;
			}
			while (!t_stack.isempty())
			
			{
				lastnum += chartonumber(t_stack.gettop())*pow(10,n);//累加得出整个数字,而不是单个字符
				
				++n;
				t_stack.pop();
			}
			double m = 1;
			if (lastexp[i] == '.')
			{
				++i;//向前一位
				
				while (isnumber(lastexp[i]))
				{
					lastnum += chartonumber(lastexp[i])  * pow(0.1, m);
					++m;
					++i;
				}
			}
			
			//std::unique_ptr<double>name(new double (lastnum * flag));
			double last=lastnum * flag;
			nums.push(last);//存入数字栈中
			
			nums.printf();
			
			j = i - 1;//回到末位置
		}
		else//为符号时
		{
			nums.printf();
			double pop1 = nums.gettop();//第一个出栈元素
			
			nums.pop();
			double pop2 = nums.gettop();
			
			nums.pop();
			double result=calculate(temp,pop2,pop1);//计算
			nums.push(result);
			nums.printf();
		}
		if (lastexp[j+1] == ' ')//忽略空格
		{
			++j;
		}
	}
	return nums.gettop();//返回最终值
	
}


bool islegalexpression(std::string infixexp)//判断表达式是否合法
{
	if (infixexp == " ")
	{
		std::cout << "islegalexpression表达式不存在" << std::endl;
	}
	if (checkbrackets(infixexp) && checkexpression(infixexp))
	{
		return true;
		std::cout << "表达式验证通过" << std::endl;
	}
	std::cout << "表达式验证失败" << std::endl; 
	return false;

}

bool checkexpression(std::string infixexp)//逐字符扫描检查表达式
{
	bool nonumber = true;//没有数字标志
	//先判断第一个元素

	if (infixexp[0] != '(' && !isnumber(infixexp[0]) && infixexp[0] != '-')return false;
	int len = infixexp.size();
	//遍历后续元素
	for (int j = 0; j < len; j++)//如果运行到此处，没有调用上述函数，证明第一个格式没问题，再进行常规判断
	{
		char temp = infixexp[j];
		if (isnumber(temp))nonumber = false;//有数字
		if (temp == ' ')continue;
		if (!isnumber(temp) &&!isbasicoper(temp)&& temp !='('&& temp !=')'&& temp !='.') return false;//不能存在其他符号
		if (isbasicoper(temp))//判断符号两边
		{
			char left = infixexp[j - 1];
			char right = infixexp[j + 1];
			if (temp == '.')//.前后只能是数字（判断.情况）
			{
				if (!isnumber(left) ||!isnumber(right))return false;
			}
			if (temp == '/')//  /号右边不能是0
			{
				if (right == '0')return false;
			}
			if (isbasicoper(left) || isbasicoper(right)) return false;//相邻元素不能是符号
			if (temp != '-' && (left == '(' || right == ')'))return false;//括号周围不能是符号（.的不合法情况已经被排除）
			if (temp == '-' && right == ')')return false;//此时是减号情况

		}
	}
	if (nonumber)return false;//没有数字存在
	return true;
}

bool checkbrackets(std::string infixexp)//检查括号是否匹配
{
	list_stack<char> stack_bra;
	int len = infixexp.size();
	for (int j = 0; j < len; j++)
	{
		char temp = infixexp[j];
		if (temp == '(')//左括号入栈，右括号出栈
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

bool isbasicoper(char i)//检查是否是加减乘除基本运算
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



bool isnegative(std::string infixexp, int pos)//判断是否是负号而不是减号  参数一字符串，参数二 索引  改进部分
{
	if (infixexp[pos] == '-')//若为负号有两种可能
	{
		if (pos == 0)//1.开头位置必为-号
			return true;
		if (infixexp[pos - 1] == '(')//2.单独被括号包围，或者括号中的第一个元素  共同点都是前面是（
			return true;
	}
	return false;
}
