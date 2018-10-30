/*
 * Copyright 2018 Andreas Schneider <asn@cryptomilk.org>
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

#include "config.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/cmocka.c"

TEST(test_strmatch_null)
{
    int rc;

    (void)state;

    rc = c_strmatch(NULL, NULL);
    assert_int_equal(rc, 0);

    rc = c_strmatch("", NULL);
    assert_int_equal(rc, 0);

    rc = c_strmatch(NULL, "");
    assert_int_equal(rc, 0);
}

TEST(test_strmatch_empty)
{
    int rc;

    (void)state;

    rc = c_strmatch("", "");
    assert_int_equal(rc, 1);

    rc = c_strmatch("wurst", "");
    assert_int_equal(rc, 0);

    rc = c_strmatch("", "wurst");
    assert_int_equal(rc, 0);
}

TEST(test_strmatch_single)
{
    int rc;

    (void)state;

    rc = c_strmatch("wurst", "wurs?");
    assert_int_equal(rc, 1);

    rc = c_strmatch("wurst", "w?rs?");
    assert_int_equal(rc, 1);

    rc = c_strmatch("wurst", "wur?");
    assert_int_equal(rc, 0);
}

TEST(test_strmatch_wildcard)
{
    int rc;

    (void)state;

    rc = c_strmatch("wurst", "wurst*");
    assert_int_equal(rc, 1);

    rc = c_strmatch("wurstbrot", "wurst*");
    assert_int_equal(rc, 1);

    rc = c_strmatch("wurstbrot", "w*t");
    assert_int_equal(rc, 1);
}

int main(void) {
    return TEST_RUN();
}
