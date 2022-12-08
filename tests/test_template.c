#include <local/template.h>
#include <minunit.h>
#include <stdio.h>

int tests_run = 0;

char *test_print_helloworld()
{
    mu_assert("should return 0", print_helloworld() == 0);
    return 0;
}

char *all_tests()
{
    mu_run_test(test_print_helloworld);
    return 0;
}

int main(void)
{
    char *test_results = all_tests();
    if (test_results != 0)
        printf("Error. Test failed. Msg : %s\n", test_results);
    else
        printf("All tests passed! (%d total tests)\n", tests_run);

    return 0;
}