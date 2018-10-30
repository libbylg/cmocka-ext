/* Use the unit test allocators */
#define UNIT_TESTING 1

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

TEST_SETUP(group_setup_failing)
{
    (void) state; /* unused */
    return 1; /* To indicate the failure */
}

TEST(test_true)
{
    (void) state; /* unused */
    assert_true(1);
}

TEST(test_false)
{
    (void) state; /* unused */
    assert_false(0);
}

int main(void) {
    return TEST_RUN();
}
