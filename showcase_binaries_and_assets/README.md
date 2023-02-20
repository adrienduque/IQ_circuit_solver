# Changelog of performance changes

This is only a visual presentation of the changes (most are added checking methods). See the [excel file](https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/IQ_circuit_solver_stats.xlsx) for detailled observations based on quantitative results.

The idea is that every screenshot presents a example of a board state that we want to invalidate with its corresponding checking method.

## V1 : baseline

Most of the pre-adding checks are already here, and the only post-adding check implemented is the one that checks for isolated empty tiles.<br>
We can quickly go through them one by one, obvious ones first.<br>

### Out of bounds check

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/normal_tile_out_of_bounds.png">

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/missing_connection_tile_out_of_bounds.png">

We are obviously not allowed to play pieces (or even connections) outside the board.

### Superposition check

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/superposed_pieces.png">

We are obviously not allowed to play pieces on top of each others.

### Connection check

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/not_matching_connections.png">

We can't play a piece next to another one, if its connections doesn't match.

### Level hints matching check

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/not_matching_level_hints_case_1.png">

The superposed tiles are not even of the same type.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/not_matching_level_hints_case_2.png">

The superposed tiles are of the same type, but their orientation doesn't match.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/not_matching_level_hints_case_3.png">

Adding this piece means that we are adding a new point to the level, which is not allowed in the game rules.<br>
This means that, a piece's side which has a point, can only be played to fill a level point.<br>

### Triple missing connection

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/triple_missing_connection.png">

We can't have this setup, because connection paths can't cross or branch from each others.

### Double missing connection

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/double_missing_connection_bend_case_1.png">

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/double_missing_connection_line_case_1.png">

In the game pieces, there are **only** 2 pieces that have tiles with **2 connections directed to the outside of the piece** (T shaped one, and one of the lines of length 2, they are both displayed above).<br>
Their corresponding double missing connection tile can only exist if the piece has not been played yet, and the piece is necessary being played to fill this tile. This is not the case in both screenshots, thus the board states displayed are not valid.<br>

### First post-adding check : isolated empty tiles case

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/isolated_empty_tile.png">

When adding a piece to the board creates an empty tile completely isolated, it makes the board state invalid, since this tile can't be filled anymore (there isn't such a piece composed of only 1 tile). The connections don't matter here.

### Important note on V1

Turns out that this version was not fully complete, since there were still false positive cases :

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/V1_wrong_solutions.png">

These are "solutions" to level 92, 98 and 119 found by the V1. Loop paths are not allowed in game rules. It's funny how it's always the 4 same pieces (to the left of the board) that makes this behavior possible.

## V2 : added no loops check (post-adding)

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/loop_path.png">

Loop paths are not allowed in game rules, the displayed board state must be invalided, this is a mandatory check as we saw above.

## V3 : added no dead-end check (post-adding)

In my opinion, this check is the main reason why this algorithm doesn't look too dumb, it can't look "stuck".<br>
Since this was the most complex check to implement so far, I'm providing a little more explanations.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/dead_end_check_case_1.png">

_Passing case, notice how the missing connections which are part of the same path are not a valid couple, we don't search for a potential path between them._

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/dead_end_check_case_2.png">

_Passing case, to show how the remaining level open points are considered the same._

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/dead_end_check_case_3.png">

_Failing case, red ink : one missing connection can't be linked with a potential path to at least another missing connection, the whole board is not valid._

This check is using a pathfinding algorithm (A-star) to find at least one potential connection path for each missing connection tile on the board, (the pathfinding algorithm can only go through empty tiles).<br>
As we can see above, all the potential couples are linked with a different color, but in reality, as soon as the pathfinding algorithm finds a valid partner tile for a particular starting tile, it doesn't search for all its potential valid partners, and the existence of both these tiles is considered valid.<br>
The most important part being : as soon as the pathfinding algorithm doesn't find any valid partner tile for a particular starting tile, the whole check fail, because this means there is a dead end (see the last screenshot above).<br>

## V3.2 : exploration of different piece order setups

Does changing the default priority order of played piece by the algorithm will affect the performance ?<br>
The answer is yes, and by a lot, for more informations, see the [excel file](https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/IQ_circuit_solver_stats.xlsx).

These screenshot all presents the first choosen combination and piece priority order for the level 120, in different priority setups.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/piece_order_A_setup.png">

A setup : This was the piece priority order by default since the beginning, from top to bottom, we can see the exact order in which I programmed the actual game pieces into code. I just didn't pay attention to the order of pieces until this point.<br>
This makes the smaller pieces be picked first, when choosing point pieces, and also to fill the remaining list of pieces the algorithm will have to play.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/piece_order_B_setup.png">

B setup : The idea was to play bigger pieces first, to make the algorithm play less pieces until a board state is found invalid, just because there is a lot more that can go wrong when playing bigger pieces (more prone to being out of bounds, superpositions, dead ends, ...).<br>
So I just reversed the order of A, meaning that bigger pieces are picked first when choosing point pieces, and also to fill the remaining list of pieces the algorithm will have to play.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/piece_order_C_setup.png">

C setup : The idea was to mix A and B, by observing that smaller pieces (all the 4 line-shaped ones) have 3 sides to play.<br>
In order to limit the number of possibilities, why not trying to pick them first as the point pieces (they are forced to play 1 side out of 3 by doing so, whereas they have 2 sides to play with, if they are not choosen as point pieces), and still prioritize bigger pieces to fill the remaining list of pieces the algorithm will have to play.<br>

Turns out B and C setups were a lot more efficient than A, and B a little more than C. **B setup is from now on the default priority order.**

## V4 : added double missing connection check (post-adding)

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/check_examples/double_missing_connection_bend_case_1.png">

As you can see, this is the same setup [here](https://github.com/adrienduque/IQ_circuit_solver/tree/master/showcase_binaries_and_assets#double-missing-connection). The only thing is that this board state would be spotted as invalid only if the last added piece between the 3 played here, was not the T-shaped one.<br>
This post-adding check is to complete the existing pre-adding check, to spot this invalid board state whatever the pieces order.<br>
Turns out this implementation was not worth adding, regarding the total average solving time of the algorithm, which has increased between V3.2B and V4, see the [excel file](https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/IQ_circuit_solver_stats.xlsx).<br>
