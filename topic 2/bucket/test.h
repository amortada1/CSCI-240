#include <iostream>

#ifndef TEST_H
#define TEST_H

#define RED_ON "\033[1;31m"
#define GREEN_ON "\033[1;32m"
#define COLOR_OFF "\033[0m"

void testTrue(bool p, const std::string& msg)
{
    if (p) std::cout << GREEN_ON << "PASS: " << msg << COLOR_OFF;
    else std::cout << RED_ON << "FAIL: " << msg << COLOR_OFF;
    std::cout << std::endl;
}

void testFalse(bool p, const std::string& msg)
{
    testTrue(!p, msg);
}

void testPass(const std::string& msg)
{
    std::cout << GREEN_ON << "PASS: " << msg << COLOR_OFF;
    std::cout << std::endl;
}

void testFail(const std::string& msg)
{
    std::cout << RED_ON << "FAIL: " << msg << COLOR_OFF;
    std::cout << std::endl;
}

#endif