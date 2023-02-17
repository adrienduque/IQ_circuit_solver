# IQ_circuit_solver

@todo formatting of this file on github, with actual preview

## Introduction

**This is yet another puzzle solver project**

This project is the result of a self-imposed challenge, to see if I could make a program that can automatically solve the hardest levels of the puzzle "IQ circuit", while being a learning experience in C language.

Of course, I recommend to check out the actual puzzle, which has such a cool design and is very pretty :

- Commercial site : https://www.smartgames.eu/uk/one-player-games/iq-circuit
- Author's commentaries : https://www.smartgamesandpuzzles.com/iq-circuit.html

This is my first big and "official" project not only in C, but in general. I'm pretty much self-taught and learned a lot through the making of this project. I'm open to upgrade suggestions on the actual code, and especially on the whole presentation/convention side of things, as I feel I'm missing on.

### Screenshots

@todo + animated gif of the final version

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## How to play with the demo

First download the files in this directory (zip) or clone this repo locally on your machine :

    ```sh
    git clone https://github.com/adrienduque/IQ_circuit_solver.git
    ```

- If you are on a Windows 64-bit machine, there are already built binaires in "**showcase_binaries_and_assets**" @todo:link directory, that you can simply run as-is, latter versions the better. The main interactive demo is called **"spaghetti_solver"** _(If you can run the solver algorithm above 60 fps you might see why)_.

- If you are on a different OS, you can try to build it yourself, see the makefile @todo:link, the actual code I wrote might be compatible between OS, and the below informations might help you. (**Warning : I didn't test it**).

I originally built this project for Windows 64-bit, with MinGW-w64 10.0.0 (URCT) (gcc 12.2.0) provided by https://winlibs.com/.

The only non-standard library I used is called [raylib](https://github.com/raysan5/raylib) (Version 4.2) (licensed under an unmodified zlib/libpng license).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Algorithm Explanation

**"Brute force algorithm with backtracking"**

First I suggest reading the game rules in the booklet if you didn't have already, I will assume them as knew from now on.
(game rules can be found here too : https://www.smartgames.eu/uk/one-player-games/iq-circuit)

1. First we select a level and see which hints it has, I only implemented the 3 last difficulties :

They consist of pre-added pieces on the board + or/and obligatory tiles on the board, or at least I generalized it like that.

- Expert levels (from 49 to 72 included) : board is completely filled with obligatory tiles of different types (all paths are shown)
- Master levels (from 73 to 96 included) : board has pre-added pieces and obligatory open point tiles (point tiles that are missing, but we know their numbers and positions)
- Wizard levels (from 97 to 120 included) : board only has obligatory open point tiles

@todo : example screenshot for each difficulty

2. According to the level hints, we need to choose which pieces will fill the open points, and which pieces won't

It's a way to stay pretty organized, it determines which sides of which pieces we can play and limit the number of possibilities.
(the choosen pieces that fill points can only play their side with a point, other ones can play all their sides except the ones with a point)

(also at this point in time, we assume that we don't have the already played pieces at our disposition (the pre-added pieces by level hints))

As there are a lot more pieces with a point than potential points to fill on the board, we might not choose the right pieces the first time

That is why we need to record all the choices we could have made for the pieces, and explore all of them one at a time.

My algorithm makes up a preprocessed list of combinations for the choosen point pieces, then make an ordered list of pieces to play (starting by the point ones) for each combination.

@todo example screenshot for level 86 combinations

3. Testing and backtracking (for one choice, one ordedred list)

For each piece, we can define a global position vector on the board, for example composed of (which side, horizontal position, vertical position, rotation)

Basically, the algorithm try every global position of the current piece, and play it as soon as it can.
2 cases :
a. the piece is successfully played -> try the same thing for the next piece in the ordered list
b. the piece can't be played (it reached the end of global position possibilities) -> backtrack and try to move the previous piece in the ordered list
(the piece that can't be played is also reset to the base global position to try all over again in another configuration of the previous pieces.)

Each piece keeps track of its global position, and moves from it when we backtrack, it doesn't restart from the base global position.

2 cases :
a. the algorithm has successfully played the last piece and try to move on to the next one -> there isn't a next one, it has found the solution to the level !
b. the algorithm can't play the first piece and try to backtrack to the previous one -> there isn't a previous one, the choice it made about the point pieces was not the right one, try all over again in the next choice (next combination).

With this algorithm, we can safely say that it will eventually try all position possibilities starting from level hints, as the solution is one of them, it can find the solution 100% of the time.

4. How does it know when a piece can be added to the board or not ? -> it rather knows the cases where a piece can't be added, and by default it can

a. we can skip obvious position of a piece (if the side choosen is set to not be playable : see step 2)) (or if we know the board is already filled at the horizontal/vertical position we want to try)

b. The method to add a piece to the board has a few checks before the piece is blitted to the board, (connection checking, superposition of tiles, match of level hints,...) see board.c for more informations (that is what I call "pre-adding checks")
(of course if one of the checks doesn't pass, the piece is not added to the board)

c. After the piece has been successfully added, a list of checks is applied to the board (do the paths contains loops ? (which are not allowed), is there an isolated empty tile ?(which we know can't be filled), ...) see check_board.c (that is what I call "post-adding checks")
(if one of these checks doesn't pass, the piece is instantly removed from the board, it's as if it was never added)

Brief example step by step
@todo 114_steps screenshots with explanation of why pieces are played in this order
and so on...

Conclusion :

We can see this as a depth first search algorithm, in a tree without loops, in which we search for the right path from root to the correct leaf node.
Where each middle node of the tree is an incomplete state of the board (board that don't have all the game pieces on it).
Each leaf node is a complete state of the board (all the pieces are here), but there is only 1 valid complete board per level (we can imagine many of them are complete but with superposed pieces for example, thus invalid)
The current piece the algorithm is trying to add, represents the depth in the tree.
Each combination is a new tree.

@todo tree_example.png and tree_example_path.png
-> explain that "can't be added with current board state", is purely a decision of the algorithm
according to pre-adding or post-adding checks it "can't"

- we don't see the other side of the pieces in this example, but when the T piece "can't be added", it makes sure to have check both sides, the piece order only display one of the side, don't be mistaken

Having more and smarter checks to not add a piece, is the way we cut down computational costs and time. By closing a node, we don't have to explore its children.

Smarter checks will detect earlier that a board is not completeable <=> the higher on the tree, we close nodes, the lesser remaining nodes to explore.

Another way of improving it is smarter checking order among all the possibilities (which pieces do we tend to add first, can we order the different combinations to check ?)

see potential_upgrades directory @todo:link

While this project is still in development, we can mesure the pure logic performance of the algorithm by counting the number of valid boards that it had to go through to find the final one that is the solution to the level.
It's like counting the number of explored nodes that the algorithm didn't close.

Of course, the more checks it has to apply to a board, the more computation and time nedded on each node.
It's a trade-off and one that is almost always worth.

See the evolution of my algorithm performance stats in the excel file in showcase_binaries_and_assets directory.

In the first complete version of the algorithm, the number of valid boards goes to tens of millions (level 120) for example.
There isn't much post-adding checks yet.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## License

Distributed under the MIT License. See LICENSE.txt @todo:link for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

Adrien Duqué - adrienduquepro@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Acknowledgments

- Another algorithm with backtracking that reminded me of this project : [Computerphile sudoku solver](https://youtu.be/G_UYXzGuqvM)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
