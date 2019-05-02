#ifndef BOARDTEST_H
#define BOARDTEST_H

#include "Autotest.h"

class BoardTest: public Test {
public:
    void testIsWin1();
    void testIsWin2();
    void testIsWin3();
    void testMove1();
    void testMove2();
    void testMove3();
    void testCanMove1();
    void testCanMove2();
    void testCanMove3();
    void runAllTests();
};

#endif
