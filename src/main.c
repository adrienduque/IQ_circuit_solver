#include <local/search_algorithm.h>
#include <stdio.h>

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
    run_algorithm_with_display(level_num, 10);
    // run_algorithm_without_display(level_num);

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

/*
Note on a slowed run :

We could limit the number of rotations of full empty sides (the line pieces that are playable on their)
because of symmetry reasons, we are testing the same boards twice (and all sub-boards)

@todo -> make the empty side, the last playable side (side_idx = 2)
and in the solving algorithm, assume that if side_idx == 2 it is an empty side, and limit its rotations
+ warning in piece_data.h where I talk about custom pieces, because we have a strong assumption on side_idx == 2 now

+ these are the first played piece, and they all present their empty side first, it's not very fun to watch
*/
