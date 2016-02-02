#include "Items.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc > 0)
    {
        for (unsigned int i = 1; i < static_cast<unsigned int>(argc); ++i)
            MECPP::runItem(atoi(argv[i]));
    }
    return 0;
}