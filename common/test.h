#include <iostream>

#ifndef TEST_H
#define TEST_H

void testTrue(bool p, const std::string& msg)
{
    if (p) std::cout << "PASS: " << msg;
    else std::cout << "FAIL: " << msg;
    std::cout << std::endl;
}

void testFalse(bool p, const std::string& msg)
{
    testTrue(!p, msg);
}

void testPass(const std::string& msg)
{
    std::cout << "PASS: " << msg;
    std::cout << std::endl;
}

void testFail(const std::string& msg)
{
    std::cout << "FAIL: " << msg;
    std::cout << std::endl;
}

#endif