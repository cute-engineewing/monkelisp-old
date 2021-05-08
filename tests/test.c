#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void 
test(void **state)
{
    (void) state;
    assert_true(1);
}

int
main(void)
{
    const struct CMUnitTest tests[] = 
    {
        cmocka_unit_test(test),
    };

    cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
