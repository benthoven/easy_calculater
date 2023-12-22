
#include<iostream>
#include"list_stackT.hpp"
#include"function.h"

int main()
{
	/* char str[] = "2 3 5 + * 7 1 / + 4 -";
	double d=calculateback(str);
	std::cout << d << std::endl;*/
	
	char infixexp[] = "2*(3+5)+7/1-4";
	char sufixexp[25];


	char* b = frofix_to_backfix_exp(infixexp, sufixexp);
	int len = strlen(b);
	std::cout << *b;
	for (int i = 0; i < len; i++)
	{
		std::cout << sufixexp[i] ;
	}
	

	


	system("pause");
	return 0;
}