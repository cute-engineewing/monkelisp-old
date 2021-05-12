#include "test_reader.h"
#include "reader.h"
#include "utils.h"
#include <mulib/common.h>
#include <mulib/macros.h>
#include <mulib/vec.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

void
read_str_test(void **state)
{
	vec_str_t tokens;
	char *t;
	int i;
	char *expected[] = { "(",	 "display",	  "#f", "#t", "0.1234", "-98",
						 "#\\A", "#\\x61",	  "'(", "1",  "2",		"3",
						 ")",	 "#(",		  "1",	"2",  "3",		"4",
						 ")",	 "\"Munix\"", ")" };

	UNUSED(state);
	tokens = tokenize(
		"(display #f #t 0.1234 -98 #\\A #\\x61 '(1 2 3) #(1 2 3 4) \"Munix\"");

	vec_foreach(&tokens, t, i) { assert_string_equal(expected[i], t); }

	free_token_vec(&tokens);
	vec_deinit(&tokens);
}

void
read_str_test_comment(void **state)
{
	vec_str_t tokens;
	size_t i = 0;
	char *expected[] = {
		"(", "+", "1", "2", "3", ")", "; hello comment world!"
	};
	char *expected1[] = { "; test (+ 1 2 3)" };
	char *expected2[] = { "; test", "(", "+", "1", "2", "3", ")" };

	UNUSED(state);

	/* First test */
	tokens = tokenize("(+ 1 2 3) ; hello comment world!");

	assert_int_equal(ARRLEN(expected), tokens.length);

	for (i = 0; i < ARRLEN(expected); i++)
	{
		assert_string_equal(expected[i], tokens.data[i]);
	}

	free_token_vec(&tokens);
	vec_deinit(&tokens);

	/* Second test */
	tokens = tokenize("; test (+ 1 2 3)");

	assert_int_equal(ARRLEN(expected1), tokens.length);

	for (i = 0; i < ARRLEN(expected1); i++)
	{
		assert_string_equal(expected1[i], tokens.data[i]);
	}

	free_token_vec(&tokens);
	vec_deinit(&tokens);

	/* Third test */
	tokens = tokenize("; test\n (+ 1 2 3)");

	assert_int_equal(ARRLEN(expected2), tokens.length);
	for (i = 0; i < ARRLEN(expected2); i++)
	{
		assert_string_equal(expected2[i], tokens.data[i]);
	}

	free_token_vec(&tokens);
	vec_deinit(&tokens);
}
