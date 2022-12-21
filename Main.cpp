#include <iostream>

#include "CapycitySim.h"
#include "Building.h"

int main()
{
    int len, wid;

    std::cout << "Length: ";
    std::cin >> len;
    std::cout << "Width: ";
    std::cin >> wid;

    auto c1 = CapycitySim(len,wid);
    c1.start_menu();

    return 0;
}
