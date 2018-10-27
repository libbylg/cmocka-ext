#include <cmocka.h>

/* A test case that does nothing and succeeds. */
TEST(null_test_success) {
    (void) state; /* unused */
}

int main(void) {
    return TEST_RUN();
}
