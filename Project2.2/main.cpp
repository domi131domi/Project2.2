#include "ElementWrapper.h"
#include <vld.h>

//Example of ElementWrapper
int main() {
	{
		ElementWrapper<double> el1, el2;
		el1 = 3.8;
		el2 = el1;
		std::cout << el2.count() << std::endl;
		{
			ElementWrapper<double> el3;
			el3 = el2;
			std::cout << el2.count() << std::endl;
		}
		std::cout << el2.count() << std::endl;
	}
	{
		ElementWrapper<double> el1(new double);
		std::cout << el1.count() << std::endl;
	}
	{
		ElementWrapper<double> el1, el2, el3;
		el1 = 3.8;
		el2 = 1.7;
		el3 = el1;
		std::cout << el1.count() << std::endl;
		std::cout << el2.count() << std::endl;
		std::cout << el3.count() << std::endl;
	}

	system("pause");
	return 0;
}