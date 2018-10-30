#include "config.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <cmocka_private.h>

static void mock_test_a_called(void)
{
    function_called();
}

static void mock_test_b_called(void)
{
    function_called();
}

static void mock_test_c_called(void)
{
    function_called();
}

TEST(test_does_fail_for_unexpected_call)
{
    (void)state;
    expect_function_call(mock_test_a_called);
    expect_function_call(mock_test_a_called);

    mock_test_a_called();
    mock_test_a_called();
    mock_test_a_called();
}

TEST( test_does_fail_for_unmade_expected_call)
{
    (void)state;
    expect_function_call(mock_test_a_called);
    expect_function_call(mock_test_a_called);

    mock_test_a_called();
}

TEST(test_ordering_fails_out_of_order)
{
    (void)state;
    expect_function_call(mock_test_a_called);
    expect_function_call(mock_test_b_called);
    expect_function_call(mock_test_a_called);

    mock_test_b_called();
}

TEST(test_ordering_fails_out_of_order_for_at_least_once_calls)
{
    (void)state;
    expect_function_call_any(mock_test_a_called);
    ignore_function_calls(mock_test_b_called);

    mock_test_b_called();
    mock_test_c_called();
}

/* Primarily used to test error message */
TEST(test_fails_out_of_order_if_no_calls_found_on_any)
{
    (void)state;
    expect_function_call_any(mock_test_a_called);
    ignore_function_calls(mock_test_b_called);

    mock_test_a_called();
    mock_test_c_called();
}

TEST(test_fails_if_zero_count_used)
{
    (void)state;
    expect_function_calls(mock_test_a_called, 0);

    mock_test_a_called();
}

int main(void) {
    return TEST_RUN();
}
