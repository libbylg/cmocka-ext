#define UNIT_TESTING 1

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static int setup_fail(void **state) {
    *state = NULL;

    /* We need to fail in setup */
    return -1;
}


static int teardown(void **state) {
    free(*state);

    return 0;
}


static int setup_ok(void **state) {
    int *answer;

    answer = malloc(sizeof(int));
    if (answer == NULL) {
        return -1;
    }
    *answer = 42;

    *state = answer;

    return 0;
}


TEST(int_test_ignored, setup_fail, teardown) {
    /* should not be called */
    assert_non_null(*state);
}

/* A test case that does check if an int is equal. */
TEST(int_test_success, setup_ok, teardown) {
    int *answer = *state;

    assert_int_equal(*answer, 42);
}

int main(void) {
    return TEST_RUN();
}
