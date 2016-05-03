#include "Items.h"

//#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc > 0)
    {
        for (unsigned int i = 1; i < static_cast<unsigned int>(argc); ++i)
            EMCPP::runItem(atoi(argv[i]));
    }
	else
	{
		std::cout << "You didn't select any items." << std::endl;
	}
    return 0;
}