#include <QtCore/QCoreApplication>
#include "functions.h"
#include <iostream>
#include <vector>

void testModInverse(const int a, const int m, const int expectedResult)
{
    int result = modInverse(a, m);
    if (result == expectedResult) {
        std::cout << "Test passed: a = " << a
                  << ", m = " << m
                  << ", expected result: " << expectedResult
                  << ", actual result: " << result << std::endl;
    } else {
        qCritical("Test failed: a = %d, m = %d, expected result: %d, actual result: %d",
                  a, m, expectedResult, result);
    }
}

void testdeterminant(vector<vector<int> > a, const int N, const int n, const int expectedResult){
    int result = determinant(a, N, n);
    if (result == expectedResult) {
        std::cout << "Test passed: a = ";
        for(const auto& x : a){
            for(const auto& y : x){
                cout << y << ' ';
            }
        }
        std::cout << ", N = " << N
            << ", expected result: " << expectedResult
            << ", actual result: " << result << std::endl;
    } else {
        qCritical("Test failed: a = %d, N = %d, expected result: %d, actual result: %d",
                  a, N, expectedResult, result);
    }
}

int lmain(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testModInverse(2,  3,  2);
    testdeterminant({{2,3}, {5, 7}}, 2, 2, -1);
}
