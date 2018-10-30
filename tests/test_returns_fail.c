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

TEST(test_will_return_fails_for_no_calls)
{
    (void) state;

    will_return(mock_function, 32);
}

TEST(test_will_return_count_fails_for_unreturned_items)
{
    int value;
    size_t numberOfCalls;

    (void) state;

    value = rand();
    numberOfCalls = (size_t) ((rand()) % 20 + 2);

    will_return_count(mock_function, value, numberOfCalls);
    mock_function_call_times(numberOfCalls - 1u, value);
}

TEST(test_will_return_always_fails_for_no_calls)
{
    int value;

    (void) state;

    value = rand();

    will_return_always(mock_function, value);
}

TEST_TEARDOWN(teardown) {
    free(*state);

    return 0;
}

int main(int argc, char **argv) {
    return TEST_RUN();
}
