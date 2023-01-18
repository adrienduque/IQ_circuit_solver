#include <local/search_algorithm.h>
#include <stdio.h>

int main(void)
{

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

    //    I feel like 100 ms is a good delay between each frame to see what's the algorithm doing
    run_algorithm_with_display(level_num, 0.01);
    // run_algorithm_without_display(level_num);

    return 0;
}