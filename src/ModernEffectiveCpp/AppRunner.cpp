#include "Items.h"

#include <stdlib.h>

int main(int argc, const char *argv[])
{
    if (argc > 0)
    {
        for (unsigned int i = 1; i < static_cast<unsigned int>(argc); ++i)
            EMCPP::runItem(atoi(argv[i]));
    }
    //
    return 0;
}