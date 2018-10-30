/*
 * Copyright 2016 David Schneider <schneidav81@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Use the unit test allocators */
#define UNIT_TESTING 1

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static int setup(void **state) {
    int *answer = malloc(sizeof(int));

    assert_non_null(answer);
    *answer = 42;

    *state = answer;

    return 0;
}

static int teardown(void **state) {
    free(*state);

    return 0;
}

/* A test case that does nothing and succeeds. */
TEST_F(null_test_success, "test_group1") {
    (void) state;
}

/* A test case that does check if an int is equal. */
TEST_F(int_test_success, "test_group2", setup, teardown) {
    int *answer = *state;

    assert_int_equal(*answer, 42);
}


int main(void) {
    int result = 0;
    result += TEST_RUN("test_group1", "*");
    result += TEST_RUN("test_group2", "*");

    return result;
}
