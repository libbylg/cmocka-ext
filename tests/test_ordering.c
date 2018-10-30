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


TEST(test_does_succeed_for_expected)
{
    (void)state;
    expect_function_call(mock_test_a_called);
    expect_function_call(mock_test_a_called);

    mock_test_a_called();
    mock_test_a_called();
}

TEST(test_does_succeed_for_multiple_calls)
{
    (void)state;
    expect_function_call(mock_test_a_called);
    expect_function_calls(mock_test_a_called, 2);
    expect_function_call(mock_test_a_called);

    mock_test_a_called();
    mock_test_a_called();
    mock_test_a_called();
    mock_test_a_called();
}

TEST(test_ordering_does_ignore_calls)
{
    (void)state;

    ignore_function_calls(mock_test_a_called);

    mock_test_a_called();
    mock_test_a_called();
    mock_test_a_called();
}

TEST(test_ordering_does_ignore_no_calls)
{
    (void)state;
    ignore_function_calls(mock_test_a_called);
}

TEST(test_ordering_does_expect_at_least_one_call)
{
    (void)state;
    expect_function_call_any(mock_test_a_called);

    mock_test_a_called();
    mock_test_a_called();
    mock_test_a_called();
}

TEST(test_ordering_does_work_across_different_functions)
{
    (void)state;
    expect_function_call(mock_test_a_called);
    expect_function_call(mock_test_b_called);
    expect_function_call(mock_test_a_called);

    mock_test_a_called();
    mock_test_b_called();
    mock_test_a_called();
}

TEST(test_ordering_ignores_out_of_order_properly)
{
    (void)state;
    ignore_function_calls(mock_test_a_called);
    ignore_function_calls(mock_test_b_called);
    expect_function_calls(mock_test_c_called, 2);


    mock_test_c_called();
    mock_test_b_called();
    mock_test_c_called();
}

int main(void) {
//     const struct CMUnitTest tests[] = {
//         cmocka_unit_test(test_does_succeed_for_expected)
//         , cmocka_unit_test(test_does_succeed_for_multiple_calls)
//         , cmocka_unit_test(test_ordering_does_ignore_no_calls)
//         , cmocka_unit_test(test_ordering_does_ignore_calls)
//         , cmocka_unit_test(test_ordering_does_expect_at_least_one_call)
//         , cmocka_unit_test(test_ordering_does_work_across_different_functions)
//         , cmocka_unit_test(test_ordering_ignores_out_of_order_properly)
//     };
// 
    return TEST_RUN();
}
