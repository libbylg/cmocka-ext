#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

struct test_segv {
    int x;
    int y;
};

TEST(test_segfault_recovery)
{
    struct test_segv *s = NULL;

    (void) state; /* unused */

    s->x = 1;
}

TEST(test_segfault_recovery1)
{
    test_segfault_recovery(state);
}

TEST( test_segfault_recovery2)
{
    test_segfault_recovery(state);
}

TEST( test_segfault_recovery3)
{
    test_segfault_recovery(state);
}

int main(void) {
    return TEST_RUN();
}
