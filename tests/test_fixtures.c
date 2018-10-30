#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

TEST_SETUP(setup_only)
{
    *state = malloc(1);

    return 0;
}

TEST_TEARDOWN(teardown_only)
{
    free(*state);

    return 0;
}

TEST(malloc_setup_test)
{
    assert_non_null(*state);
    free(*state);
}

TEST(malloc_teardown_test)
{
    *state = malloc(1);
    assert_non_null(*state);
}

TEST_SETUP(prestate_setup)
{
    int *val = (int *)*state, *a;

    a = malloc(sizeof(int));
    *a = *val + 1;
    *state = a;

    return 0;
}

TEST(prestate_teardown)
{
	free(*state);

	return 0;
}

TEST(prestate_setup_test)
{
    int *a = (int *)*state;

    assert_non_null(a);
    assert_int_equal(*a, 43);
}

TEST(prestate_test)
{
    int *a = (int *)*state;

    assert_non_null(a);
    assert_int_equal(*a, 42);
}

int main(void) {
    int prestate = 42;
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(malloc_setup_test, setup_only),
        cmocka_unit_test_setup(malloc_setup_test, setup_only),
        cmocka_unit_test_teardown(malloc_teardown_test, teardown_only),
        cmocka_unit_test_teardown(malloc_teardown_test, teardown_only),
        cmocka_unit_test_teardown(malloc_teardown_test, teardown_only),
        cmocka_unit_test_teardown(malloc_teardown_test, teardown_only),
        cmocka_unit_test_prestate(prestate_test, &prestate),
        cmocka_unit_test_prestate_setup_teardown(prestate_setup_test, prestate_setup, prestate_teardown, &prestate),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
