// voir : https://youtu.be/vEICc0zygWQ
#ifndef __MINUNIT_H__
#define __MINUNIT_H__

extern int tests_run;

#define mu_assert(message, test_cond) \
    do                                \
    {                                 \
        if (!(test_cond))             \
            return message;           \
    } while (0)

#define mu_run_test(test)       \
    do                          \
    {                           \
        char *message = test(); \
        tests_run++;            \
        if (message)            \
            return message;     \
    } while (0)

#endif