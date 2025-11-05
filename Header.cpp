#include "Header.h"

Hearder::Hearder()
{
}

Hearder::Hearder(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Hearder::print()
{
    std::cout << "x = " << x_ << "; " << "y = " << y_ << std::endl;
}
