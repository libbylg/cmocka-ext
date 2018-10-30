#include "config.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <cmocka_private.h>

#include <stdlib.h>

int mock_function(void);
void mock_function_call_times(size_t times, int expectedValue);

int mock_function(void)
{
  return (int) mock();
}

void mock_function_call_times(size_t times, int expectedValue)
{
    size_t i;
    for (i = 0u; i < times; ++i)
    {
        assert_int_equal(expectedValue, mock_function());
    }
}

TEST(test_will_return_maybe_for_no_calls)
{
    (void) state;

    will_return_maybe(mock_function, 32);
}

TEST(test_will_return_maybe_for_one_mock_call)
{
    int value;

    (void) state;

    value = rand();
    will_return_maybe(mock_function, value);
    mock_function_call_times(1u, value);
}

TEST(test_will_return_maybe_for_more_than_one_call)
{
    int value;
    size_t numberOfCalls;
    (void)state;

    value = rand();
    numberOfCalls = (size_t) ((rand()) % 20 + 2);
    will_return_maybe(mock_function, value);
    mock_function_call_times(numberOfCalls, value);
}

int main(int argc, char **argv) {
    return TEST_RUN();
}
