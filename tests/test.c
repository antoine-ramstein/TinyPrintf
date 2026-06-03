#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>

#include "../src/tinyprintf.h"

TestSuite(tinyprintf, .init = cr_redirect_stdout);

// ==== %d ====
Test(tinyprintf, simple_d)
{
    tinyprintf("%d", 42);
    fflush(stdout);
    cr_assert_stdout_eq_str("42");
}

Test(tinyprintf, negative_d)
{
    tinyprintf("%d", -123);
    fflush(stdout);
    cr_assert_stdout_eq_str("-123");
}

Test(tinyprintf, zero_d)
{
    tinyprintf("%d", 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("0");
}

Test(tinyprintf, multiple_d)
{
    tinyprintf("%d %d %d", 1, 2, 3);
    fflush(stdout);
    cr_assert_stdout_eq_str("1 2 3");
}

// ==== %u ====
Test(tinyprintf, simple_u)
{
    tinyprintf("%u", 123);
    fflush(stdout);
    cr_assert_stdout_eq_str("123");
}

Test(tinyprintf, zero_u)
{
    tinyprintf("%u", 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("0");
}

Test(tinyprintf, big_u)
{
    tinyprintf("%u", 4294967295u);
    fflush(stdout);
    cr_assert_stdout_eq_str("4294967295");
}

// ==== %s ====
Test(tinyprintf, simple_s)
{
    tinyprintf("%s", "hello");
    fflush(stdout);
    cr_assert_stdout_eq_str("hello");
}

Test(tinyprintf, empty_s)
{
    tinyprintf("%s", "");
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}

Test(tinyprintf, null_s)
{
    tinyprintf("%s", NULL);
    fflush(stdout);
    cr_assert_stdout_eq_str("(null)");
}

Test(tinyprintf, multiple_s)
{
    tinyprintf("%s %s", "foo", "bar");
    fflush(stdout);
    cr_assert_stdout_eq_str("foo bar");
}

// ==== %c ====
Test(tinyprintf, simple_c)
{
    tinyprintf("%c", 'A');
    fflush(stdout);
    cr_assert_stdout_eq_str("A");
}

Test(tinyprintf, multiple_c)
{
    tinyprintf("%c%c%c", 'a', 'b', 'c');
    fflush(stdout);
    cr_assert_stdout_eq_str("abc");
}

Test(tinyprintf, c_number)
{
    tinyprintf("%c", 65);
    fflush(stdout);
    cr_assert_stdout_eq_str("A");
}

// ==== %o ====
Test(tinyprintf, simple_o)
{
    tinyprintf("%o", 10);
    fflush(stdout);
    cr_assert_stdout_eq_str("12");
}

Test(tinyprintf, zero_o)
{
    tinyprintf("%o", 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("0");
}

Test(tinyprintf, big_o)
{
    tinyprintf("%o", 511);
    fflush(stdout);
    cr_assert_stdout_eq_str("777");
}

// ==== %x ====
Test(tinyprintf, simple_x)
{
    tinyprintf("%x", 42);
    fflush(stdout);
    cr_assert_stdout_eq_str("2a");
}

Test(tinyprintf, zero_x)
{
    tinyprintf("%x", 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("0");
}

Test(tinyprintf, big_x)
{
    tinyprintf("%x", 3735928559u);
    fflush(stdout);
    cr_assert_stdout_eq_str("deadbeef");
}

// ==== %% ====
Test(tinyprintf, simple_percent)
{
    tinyprintf("%%");
    fflush(stdout);
    cr_assert_stdout_eq_str("%");
}

Test(tinyprintf, percent_in_text)
{
    tinyprintf("100%% ok");
    fflush(stdout);
    cr_assert_stdout_eq_str("100% ok");
}

// ==== Mixed ====
Test(tinyprintf, mixed_all)
{
    tinyprintf("%c%c is %s... %d too.", '4', '2', "the answer", 42);
    fflush(stdout);
    cr_assert_stdout_eq_str("42 is the answer... 42 too.");
}

Test(tinyprintf, tricky)
{
    tinyprintf("Good morning %t world", 12);
    fflush(stdout);
    cr_assert_stdout_eq_str("Good morning %t world");
}

Test(tinyprintf, text_no_format)
{
    tinyprintf("hello world");
    fflush(stdout);
    cr_assert_stdout_eq_str("hello world");
}

Test(tinyprintf, multiple_mixed)
{
    tinyprintf("%d %u %o %x %s %c %%", -1, 123u, 8u, 255u, "yo", 'Z');
    fflush(stdout);
    cr_assert_stdout_eq_str("-1 123 10 ff yo Z %");
}

// ==== Edge / weird ====
Test(tinyprintf, empty_format)
{
    tinyprintf("");
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}

Test(tinyprintf, only_percent_end)
{
    tinyprintf("%");
    fflush(stdout);
    cr_assert_stdout_eq_str("%");
}

Test(tinyprintf, space_and_percent)
{
    tinyprintf(" %d % ", 42);
    fflush(stdout);
    cr_assert_stdout_eq_str(" 42 % ");
}

Test(tinyprintf, multiple_nulls)
{
    tinyprintf("%s %s", NULL, NULL);
    fflush(stdout);
    cr_assert_stdout_eq_str("(null) (null)");
}

Test(tinyprintf, long_string)
{
    tinyprintf("%s", "abcdefghijklmnopqrstuvwxyz");
    fflush(stdout);
    cr_assert_stdout_eq_str("abcdefghijklmnopqrstuvwxyz");
}

Test(tinyprintf, d_u_mix)
{
    tinyprintf("%d %u", -42, 42u);
    fflush(stdout);
    cr_assert_stdout_eq_str("-42 42");
}

Test(tinyprintf, c_and_s)
{
    tinyprintf("%c %s", 'X', "test");
    fflush(stdout);
    cr_assert_stdout_eq_str("X test");
}

Test(tinyprintf, multiple_percent)
{
    tinyprintf("%%%%");
    fflush(stdout);
    cr_assert_stdout_eq_str("%%");
}

Test(tinyprintf, many_args)
{
    tinyprintf("%d %d %d %d", 1, 2, 3, 4);
    fflush(stdout);
    cr_assert_stdout_eq_str("1 2 3 4");
}

Test(tinyprintf, number_and_text)
{
    tinyprintf("num=%d txt=%s", 99, "ok");
    fflush(stdout);
    cr_assert_stdout_eq_str("num=99 txt=ok");
}

Test(tinyprintf, char_and_percent)
{
    tinyprintf("%c%%", 'X');
    fflush(stdout);
    cr_assert_stdout_eq_str("X%");
}

Test(tinyprintf, hex_and_octal)
{
    tinyprintf("%x %o", 64, 64);
    fflush(stdout);
    cr_assert_stdout_eq_str("40 100");
}
