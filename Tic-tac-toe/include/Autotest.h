#ifndef TEST_H
#define TEST_H

#include <cstddef>
#define DO_CHECK(expr) check(expr, __FUNCTION__, __FILE__, __LINE__)

class Test {
protected:
    static int failedNum;
    static int totalNum;
public:
    static void check(bool expr, const char *func, const char *filename, size_t lineNum);
    static void showFinalResult();
    virtual void runAllTests() = 0;
};

#endif
