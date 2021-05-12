#include <mulib/common.h>
#include <mulib/macros.h>
#include <mulib/vec.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "reader.h"
#include "test_reader.h"
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

	/* First test */
	vec_str_t tokens;
	size_t i = 0;
	char *expected[] = {
		"(", "+", "1", "2", "3", ")", "; hello comment world!"
	};

	UNUSED(state);
	tokens = tokenize("(+ 1 2 3) ; hello comment world!");

	for (i = 0; i < sizeof(expected) / sizeof(expected[0]); i++)
	{

		assert_int_equal(sizeof(expected) / sizeof(expected[0]), tokens.length);
		assert_string_equal(expected[i], tokens.data[i]);
	}

	free_token_vec(&tokens);
	vec_deinit(&tokens);

	/* Second test */
	char *expected1[] = { "; test (+ 1 2 3)" };

	tokens = tokenize("; test (+ 1 2 3)");

	for (i = 0; i < sizeof(expected1) / sizeof(expected1[0]); i++)
	{

		assert_int_equal(sizeof(expected1) / sizeof(expected1[0]),
						 tokens.length);
		assert_string_equal(expected1[i], tokens.data[i]);
	}

	free_token_vec(&tokens);
	vec_deinit(&tokens);
	/* Third test */
	char *expected2[] = { "; test", "(", "+", "1", "2", "3", ")" };

	tokens = tokenize("; test\n (+ 1 2 3)");

	for (i = 0; i < sizeof(expected2) / sizeof(expected2[0]); i++)
	{

		assert_int_equal(sizeof(expected2) / sizeof(expected2[0]),
						 tokens.length);
		assert_string_equal(expected2[i], tokens.data[i]);
	}

	free_token_vec(&tokens);
	vec_deinit(&tokens);
}
