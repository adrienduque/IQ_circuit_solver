#include <local/search_algorithm.h>
#include <stdio.h>
#include <stdlib.h> // system

int main(void)
{
#ifndef AUTOMATED_RUNS
    int level_num;

    printf("Welcome to Spaghetti solver.\n\n");
    printf("Enter the level number you want to solve (49 to 120 included) : ");
    scanf("%3d", &level_num);
    while (level_num < 49 || level_num > 120)
    {
        system("cls");
        printf("Enter the level number you want to solve (49 to 120 included) : ");
        scanf("%3d", &level_num);
    }

    //    I feel like 10 fps is a good delay between each frame to see what's the algorithm doing
    // run_algorithm_with_display(level_num, 10);
    // run_algorithm_without_display(level_num);

    run_algorithm_with_extra_display(level_num, 10);

    printf("\n");

#else

    for (int level_num = 49; level_num <= 120; level_num++)
        run_algorithm_without_display(level_num);

    printf("\n\nPart with display\n\n");

    for (int level_num = 49; level_num <= 120; level_num++)
        run_algorithm_with_display(level_num, 0);

#endif

    return 0;
}

/**
 * @todo
 *
 * Maybe have a D configuration where we change the order of the pieces in the default priority list once again (but same idea as B configuration)
 * and priorize bigger pieces, that actually have a point on their first side to reduce again the number of valid boards
 *
 * i.e : move square from default index 6 to 8, the other pieces stay in the same order
 *
 *
 */