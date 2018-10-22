/*
 * Copyright 2008 Google Inc.
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
#include <stdio.h>

#ifdef _MSC_VER
#define INITIALIZER(f)							\
	static void f();							\
	static int __##f##_wrapper(){ f(); return 0; }	\
	__pragma(data_seg(".CRT$XIU"))				\
	static int(*__##f##2##__COUNTER__) () = __##f##_wrapper;	\
	__pragma(data_seg())						\
	static void f()
#else
#define INITIALIZER(f) \
	__attribute__((constructor)) static void f()
#endif


struct cm_unit_test_cases
{
	int                 cap;
	int                 len;
	struct CMUnitTest*  cases;
};


struct  cm_unit_test_cases  global_cm_unit_test_cases = { 0 };

void    cm_unit_test_cases_add(char* name, CMUnitTestFunction ftest, CMFixtureFunction fsetup, CMFixtureFunction* fteardown, void* state)
{
	struct  cm_unit_test_cases* cases = (struct  cm_unit_test_cases*)(&global_cm_unit_test_cases);
	if (cases->len >= cases->cap)
	{
		int new_cap = cases->cap + 100;
		struct CMUnitTest* new_cases = (struct CMUnitTest*)malloc(new_cap * sizeof(struct CMUnitTest));
		//TODO ÄÚ´æ²»×ãÕ¦°ì£¿
		memcpy(new_cases, cases, (cases->len * sizeof(struct CMUnitTest)));
		struct CMUnitTest* old_cases = cases->cases;
		free(old_cases);
		cases->cases = new_cases;
		cases->cap = new_cap;
	}

	struct CMUnitTest   new_test =
	{
		name,
		ftest,
		fsetup,
		fteardown,
		state
	};
	cases->cases[cases->len++] = new_test;
}

#define TEST(suite,test)							\
	static void suite##_##test(void **state);       \
	INITIALIZER(init_##suite##_##test)              \
{                                               \
	cm_unit_test_cases_add(#suite "." #test, \
	suite##_##test, NULL, NULL, NULL);			\
}                                               \
	static void suite##_##test(void **state)

#define	TEST_RUN()	\
	_cmocka_run_group_tests("", global_cm_unit_test_cases.cases, global_cm_unit_test_cases.len, NULL, NULL)

// # define cmocka_run_group_tests(group_tests, group_setup, group_teardown) \
// 	_cmocka_run_group_tests(#group_tests, group_tests, sizeof(group_tests) / sizeof((group_tests)[0]), group_setup, group_teardown)


TEST(case1, int_test_successyy)
{
	int *answer = *state;

	assert_int_equal(*answer, 42);
}

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
TEST(suite1, null_test_success)
{
    (void) state;
}

/* A test case that does check if an int is equal. */
TEST(suite1, int_test_success)
{
    int *answer = *state;

    assert_int_equal(*answer, 42);
}
#define DISABLED	0
TEST(test)
TEST(test, suite)
TEST(test, suite, DISABLED)
TEST(test, suite, setup, teardown, DISABLED)
SETUP(suite)
TEARDOWN(suite)

#define DISABLED	0
TEST(test)
TEST(test, DISABLED)
TEST(test, setup, teardown, DISABLED)
SETUP(setup)
TEARDOWN(teardown)

#define DISABLED	0
TEST(test)
TEST(test, DISABLED)
TEST(test, setup, teardown, DISABLED)
SUITE_SETUP(setup)
SUITE_TEARDOWN(teardown)
TEST_SETUP(setup)
TEST_TEARDOWN(teardown)


#define DISABLED	0
TEST(test, suite)
TEST_F(test, suite, setup, teardown)
SETUP(suite)
TEARDOWN(suite)

// TEST(int_test_success)
// {
//     int *answer = *state;
// 
//     assert_int_equal(*answer, 42);
// }

// static int a = 100;
// 
// INITIALIZER(f)
// {
//     a = 222;
// }
// 

int main(void) {
//     printf("a=%d",a);
//     getchar();

//     const struct CMUnitTest tests[] = {
//         cmocka_unit_test(null_test_success),
//         cmocka_unit_test_setup_teardown(int_test_success, setup, teardown),
//     };

    return cmocka_run_group_tests(tests, NULL, NULL);
	return TEST_RUN();
}
