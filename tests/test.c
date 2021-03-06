#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "test_reader.h"

int
main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(read_str_test),
		cmocka_unit_test(read_str_test_comment),
	};

	cmocka_run_group_tests(tests, NULL, NULL);

	return 0;
}
