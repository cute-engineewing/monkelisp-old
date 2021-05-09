#include <mulib/macros.h>
#include <mulib/vec.h>
#include <mulib/common.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test_reader.h"
#include "reader.h"

void
read_str_test(void **state)
{
    vec_str_t tokens;
    char *t;
    int i;
    char *expected[] = {"(", "display", "#f", "#t", "0.1234", "-98", "#\\A", "#\\x61", 
                        "'(", "1", "2", "3", ")", "#(", "1", "2", "3", "4", ")", "\"Munix\"", ")"};

    UNUSED(state);
    tokens = tokenize("(display #f #t 0.1234 -98 #\\A #\\x61 '(1 2 3) #(1 2 3 4) \"Munix\"");

    vec_foreach(&tokens, t, i)
    {
        assert_string_equal(expected[i], t);
    }

    free_token_vec(&tokens);
    vec_deinit(&tokens);
}