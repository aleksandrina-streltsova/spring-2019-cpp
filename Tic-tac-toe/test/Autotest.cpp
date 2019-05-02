#include <iostream>
#include "Autotest.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    if (!expr) {
        failedNum++;
        printf("test failed: %s in %s:%u\n", func, filename, lineNum);
    }
    totalNum++;
}

void Test::showFinalResult() {
    if (failedNum == 0)
        printf("All tests passed.\n");
    else {
        printf("Failed %u of %u tests.\n", failedNum, totalNum);
    }
}