#include "Items.h"

//#include <stdlib.h>
#include <iostream>

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        for (unsigned int i = 1; i < static_cast<unsigned int>(argc); ++i)
            EMCPP::runItem(atoi(argv[i]));
    }
	else
	{
		std::cout << "Please select the Item to run:";
		int itemNumber = 0;
		std::cin >> itemNumber;
		EMCPP::runItem(itemNumber);
	}
    return 0;
}