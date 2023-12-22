
#include<iostream>
#include"list_stackT.hpp"
#include"function.h"

int main()
{
	//std::string str = "2 3 5 + * 7 1 / + 4 -";
	
	
	std::string infixexp = "2*(5+3)+7/1-4";
	std::string sufixexp;
	sufixexp.resize(100);// = "   //‘§¡Ùø’º‰£¨±‹√‚‘ΩΩÁ ";
	 frofix_to_backfix_exp(infixexp, sufixexp);

	double d=calculateback(sufixexp);
	std::cout << d << std::endl;
	//std::cout << sufixexp;
	/*for (int i = 0; i < 100; i++)
	{
		std::cout << sufixexp.at(i) ;
	}*/
	

	


	system("pause");
	return 0;
}