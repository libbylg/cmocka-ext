#include <cmocka.h>

/* A test case that does nothing and succeeds. */
TEST(null_test_success) {
    (void) state; /* unused */
}

int main(void) {
    TEST_RUN("", "");
    getchar();
//     const struct CMUnitTest tests[] = {
//         cmocka_unit_test(null_test_success),
//     };
// 
//     return cmocka_run_group_tests(tests, NULL, NULL);
}
