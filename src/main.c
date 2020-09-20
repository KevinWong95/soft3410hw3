#include "../test/tests.c"
#include <stdio.h>

int main() {
    testIntSimple();
    testIntLarge();
    testSimpleStruct();

    printf("All tests succeeded.\n");
    
    return 0;
}