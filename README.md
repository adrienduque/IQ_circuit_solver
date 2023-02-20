<a name="readme-top"></a>
# IQ_circuit_solver

## Introduction

**This is yet another puzzle solver project**

This project is the result of a self-imposed challenge, to see if I could make a program that can automatically solve the hardest levels of the puzzle "IQ circuit", while being a learning experience in C language.

Of course, I recommend to check out the actual puzzle, which has such a cool design and is very pretty :

<img src = "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/SmartGames_IQ-467_IQ-Circuit_lifestyle-shot_cfb270.jpg" align="left" width = "200px">

  Commercial site : https://www.smartgames.eu/uk/one-player-games/iq-circuit
  
  Author's commentaries : https://www.smartgamesandpuzzles.com/iq-circuit.html
  <br>
  <br>
  <br>
  <br>
  <br>
  <br>
  <br>

This is my first big and "official" project not only in C, but in general. I'm pretty much self-taught and learned a lot through the making of this project. I'm open to upgrade suggestions on the actual code, and especially on the whole presentation/convention side of things, as I feel I'm missing on. I'm not a native English speaker as well, so let me know if you spot any mistake.

So if you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

### Screenshots

#### Important Note :

I don't feel like these assets are rightfully representing this project, because I mostly focused on its **speed** and that is what I want to show.
Thus I really recommend to run yourself the demo **(see : [next section](https://github.com/adrienduque/IQ_circuit_solver#how-to-play-with-the-demo))**. Solving 1 level takes at most a few seconds on my mid range laptop, to give you an idea.

+ @todo animated gif of the final version

+ @todo maybe do a demo video in real time (ytb unlisted) ? with like a timer next to it, in order to better show the speed, regarding the note I just made

<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_selection_screen.png">
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/game_screen.png">
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/solver_screen.png">

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## How to play with the demo

<a name="readme-top"></a>

First download the files in this directory (zip) or clone this repo locally on your machine :
    
    git clone https://github.com/adrienduque/IQ_circuit_solver.git

- If you are on a Windows 64-bit machine, there are already built binaires in [**showcase_binaries_and_assets**](https://github.com/adrienduque/IQ_circuit_solver/tree/master/showcase_binaries_and_assets) directory, that you can simply run as-is, latter versions the better. The main demo is called **"spaghetti_solver"** _(If you can run the solver algorithm above 60 fps you might see why)_.

- If you are on a different OS, you can try to build it yourself, see the [makefile](https://github.com/adrienduque/IQ_circuit_solver/blob/master/makefile), the actual code I wrote might be compatible between OS, and the below informations might help you too. (**Warning : I didn't test it**).

I originally built this project for Windows 64-bit, with MinGW-w64 10.0.0 (URCT) (gcc 12.2.0) provided by https://winlibs.com/.

The only non-standard library I used is called [raylib](https://github.com/raysan5/raylib) (Version 4.2) (licensed under an unmodified zlib/libpng license).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Algorithm Explanation

First, I suggest reading the game rules in the booklet if you have not already, I will assume them as **known** from now on.
(game rules can be found [here](https://www.smartgamesandpuzzles.com/iq-circuit.html) too).

We can summarize this algorithm by describing it as a **"brute force algorithm with backtracking"**. The main idea is to test every possibility to find the correct one, but in a particular order so that it tests the less possibilities as possible (this is where the backtracking plays an important role).

(We can roughly (over)estimate the total number of possibilities by noticing that there are 10 pieces, each piece has 2 playable sides in average, and each side can be played with 4 different rotations, there is a number of 32 tile on the game board (8 width * 4 height), then we can play a piece in (32 x 4 x 2 = 256) different positions on the board, with 10 pieces, the total number of possibilities (number of different boards) become 256^10 = 2^80 = about 10^24.)

---

### 1) First we select a level 

The type of level hints depens on the difficulty, and they consist of pre-added pieces on the board + or/and obligatory tiles on the board, or at least I generalized it like that.

(I only implemented the 3 last difficulties)

- Expert levels (from 49 to 72 included) : board is completely filled with obligatory tiles of different types (all paths are shown)
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/expert_level_example.png" width="200px">

- Master levels (from 73 to 96 included) : board has pre-added pieces and obligatory open point tiles (point tiles that are missing, but we know their numbers and positions)
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/master_level_example.png" width="200px">

- Wizard levels (from 97 to 120 included) : board only has obligatory open point tiles
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/wizard_level_example.png" width="200px">

---

### 2) Setup the main algorithm, preprocessing of level hints

- According to the level hints, we need to choose which pieces will fill the open points, and which pieces won't, and the remaining pieces to test (priority list).

  It's a way to stay pretty organized, it determines which sides of which pieces can be played and limit the number of possibilities tested.

  **(e.g : The choosen pieces that will fill open points can only play their side with a point, other ones can play all their sides except the ones with a point)**

  Note : at this step, we also have to account for the pre-added pieces by level hints, the preprocessing will not include them in the list of pieces to play.

- As there are a lot more pieces with a point than potential points to fill on the board, we might not choose the right pieces the first time, that is why we need to record all the choices we could have made for the pieces, and explore all of them one at a time. 

  My algorithm makes up a preprocessed list of combinations, each combination has different choosen point pieces, different priority list of pieces to play. (see examples below for level 86).

<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_86_first_tested_combination.png">
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_86_second_tested_combination.png">
<img src= "https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_86_actual_solution_combination.png">

This last combination leads to the solution ! Meaning that this is the correct choice (combination) to the question : "What pieces should we pick to fill the open points in level 86 ?".

---

### 3) Actual backtracking algorithm

Setup : 
  - For each piece, we can define a global position on the board, composed of (which side, horizontal position, vertical position, rotation)
  - Each piece keeps track of its current global position, and moves from it when we backtrack, it doesn't restart from the base global position, unless we "reset" the piece.
  - We have an ordered list of combinations to test, and for each combination, have a priority list of pieces to play.

We kickstart the algorithm by choosing the first piece of the first combination as the current piece to play. All pieces are also reset.

**Basically, it tries every global position of the current piece one by one, and play it as soon as it can.**<br>
<ol>
  <li>
  normal output cases :
  <ul>
    <li>the piece is successfully played -> try the same thing for the next piece in the priority list</li>
	<li>the piece can't be played (it reached the end of global position possibilities without being playable) -> reset the piece position, then backtrack and try to move the previous piece in the priority list.</li>
  </ul>
  </li>
  <br>
  <li>
  edge cases : 
  <ul>
    <li>the algorithm has successfully played the last piece and try to move on to the next one -> there isn't a next one, it has found the solution to the level !</li>
	<li>the algorithm can't play the first piece and try to backtrack to the previous one -> there isn't a previous one (meaning that there is no solution to be found with the current combination of pieces) -> try again with the next combination.</li>
  </ul>
  </li>
</ol>


With this algorithm, we can safely say that it will eventually try all valid position possibilities starting from level hints, as the solution is one of them, it can find the solution 100% of the time.

Notice in each combination, how the first piece's position is never reset, and will continue to be incremented until the solution to the level is found or until there is no position left to play.

---

### 4) Game board checking/validation

How does it know when a piece can be added to the board or not ? -> it rather knows the cases where a piece can't be added, and by default it can.

- we can skip obvious positions of a piece (if the side choosen is set to not be playable : see step [2) Setup](https://github.com/adrienduque/IQ_circuit_solver#2-setup-the-main-algorithm-preprocessing-of-level-hints)) (or if we know the board is already filled at the position we want to try).

- The method to add a piece to the board has a few checks before the piece is blitted to the board, (connection checking, superposition of tiles, match of level hints,...) (that is what I call **"pre-adding checks"**).
<br>(of course if one of the checks doesn't pass, the piece is not added to the board)

- After the piece has been successfully added, a list of checks is applied to the board (do the paths contains loops ? (which are not allowed), is there an isolated empty tile ?(which we know can't be filled), ...). (that is what I call **"post-adding checks"**).
(if one of these checks doesn't pass, the piece is instantly removed from the board, it's as if it was never added).

Thus, in summary, this is where I implemented vanilla game rules, as well as, my own rules to try to detect early if a board state is worth continuing or not (they are part of post-adding checks). See [Changelog of performance changes](https://github.com/adrienduque/IQ_circuit_solver/tree/master/showcase_binaries_and_assets#readme) for more informations on each check.

You can directly interact with those rules, by playing the demo in "assisted" game mode, where my checks are run on each of the user's move, and the demo shows various information messages based on them.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/assisted_game_mode_example.png">

_The last piece I tried to add was the square shaped one, in this example.<br>_

### Note :

Of course, the goal for making these checks, is to not make too big assumptions on what we know of the actual game abritrary informations (these are in the *_data.c files in my codebase for example), or else anyone can just make a program that gives the solution to levels by looking for them in the game booklet.

This is what I would call "overfitting" rules.

Some of my checking methods are questionnable on this point, because I'm only thinking of this looking back at it. I feel like I naturally fixed the limit to the statement : "The algorithm knows the exact game rules, and the exact game pieces (shapes,connections,...), everything else is not assumed as known".

---

### Concrete walkthrough step by step

<details>

<summary>Show details</summary>
	
Note : This is made from the version 5.2 of the program.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/first_combination.png">

Here, the algorithm is trying to solve level 50. You can see the first combination and its priority list on the far left of the screen (priority to higher pieces).<br>
Keep in mind that, in the expert levels like this one, the main check that determines if we can play a piece or not is the level hints matching check, because the board is filled with level hints. There are more complex and important checks that come into play in harder levels (see [step 4) Game board checking](https://github.com/adrienduque/IQ_circuit_solver#4-game-board-checkingvalidation)).<br>

We can see that the first piece can't even be played here, thus the algorithm goes to the next combination. Since this is still the case for a couple more combinations, let's jump directly to a combination where pieces can be played.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_0.png">
<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_1.png">

It found a valid location to play the 1st piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_2.png">

It found a valid location to play the 2nd piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_3.png">

It found a valid location to play the 3rd piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_4.png">

It didn't found a valid location to play the 4th piece in this board state, thus the 4th piece has been reset, and the 3rd piece removed from the board.<br>
The algorithm will now try to find a next valid location to play the 3rd piece, and try again. **(This is what is called the "backtracking part")**.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_5.png">

It didn't found either a next valid location to play the 3rd piece in this board state, thus the 3rd piece has been reset, and the 2nd piece removed from the board.<br>
The algorithm will now try to find a next valid location to play the 2nd piece, and try again.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_6.png">

It didn't found a next valid location to play the 2nd piece in this board state, backtracked again to the 1st piece, that didn't have either a next valid location and can't be played anymore.<br>
It means that the previous combination was not the right one, the algorithm will try again with a new combination (which is displayed here).<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_7.png">

It found a valid location to play the 1st piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_8.png">

It found a valid location to play the 2nd piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_9.png">

It found a valid location to play the 3rd piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_10.png">

It found a valid location to play the 4th piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_11.png">

It found a valid location to play the 5th piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_12.png">

It found a valid location to play the 6th piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_13.png">

It didn't found a valid location to play the 7th piece in this board state, thus the 7th piece has been reset, and the 6th piece removed from the board.<br>
The algorithm will now try to find a next valid location to play the 6th piece, and try again.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_14.png">

It didn't found either a next valid location to play the 6th piece in this board state, thus the 6th piece has been reset, and the 5th piece removed from the board.<br>
The algorithm will now try to find a next valid location to play the 5th piece, and try again.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_15.png">

It found the next valid location to play the 5th piece, thus it will try to add the 6th piece again.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_16.png">

It found a valid location to play the 6th piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_17.png">

It found a valid location to play the 7th piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_18.png">

It found a valid location to play the 8th piece, thus it will try to do the same for the next piece.<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_19.png">

It found a valid location to play the 9th piece, thus it will try to do the same for the next piece.<br>
(I marked the remaining hole that we can't really see as the piece drawings blend in).<br>

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/level_50_walkthrough/step_20.png">

It found a valid location to play the 10th piece, thus it will try to do the same for the next piece.<br>
Actually, there is not a next piece, meaning that the last piece has been added, passing all the board validation checks, meaning that it found the solution !

Note : 
- When the actual demo runs, it will skip a few of these displays, displaying only board states where a new piece has just been successfully added or if a new combination is being tested (to save time).
- The "valid board count" is the number of times that the algorithm successfully added a piece to the board, thus creating a new valid board state. It is a measure of the algorithm's performance, which is more discussed in the conclusion below.

</details>

---

### Conclusion :

We can see this as a depth first search algorithm, in a tree without loops, in which we search for the correct path from root to the correct leaf node.
Where each middle node of the tree is an incomplete state of the board (board that don't have all the game pieces on it).
Each leaf node is a complete state of the board (all the pieces are here), but there is only 1 valid complete board per level (we can imagine many of them are complete but with superposed pieces for example, thus invalid)
The current piece the algorithm is trying to add, represents the depth in the tree.
Each new combination is a new tree.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/tree_example.png">

Example of a tree (which is not fully represented of course).

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/showcase_binaries_and_assets/presentation_assets/tree_example_path.png">

The path that the algorithm is taking to explore this tree, based on the decisions made in [step 4) Game board checking](https://github.com/adrienduque/IQ_circuit_solver#4-game-board-checkingvalidation).

While this project is still in development, we can mesure the pure logic performance of the algorithm by counting the number of valid boards that it had to go through to find the final one that is the solution to the level.
It's like counting the number of explored nodes that the algorithm didn't close.

How did I improved its performance ?

- Having more and smarter checks to not add a piece, is the way we cut down computational costs and time. By closing a node, we don't have to explore its children.
  Smarter checks will detect earlier that a board is not completeable <=> the higher on the tree, we close nodes, the lesser remaining nodes to explore.
  Of course, the more checks it has when doing board validation, the more computation and time needed on each node. It's a trade-off and one that is almost always worth, regarding total solving time.

- Another way of improving it, is smarter **order** to explore all the possibilities (Which pieces do we tend to add first ? Can we order the different combinations to check ?)

**This is the most important part of my project, in my opinion :** 

- See the evolution of my algorithm performance in the [showcase_binaries_and_assets](https://github.com/adrienduque/IQ_circuit_solver/tree/master/showcase_binaries_and_assets) directory.

- And for more information about the future improvements, see [potential_upgrades](https://github.com/adrienduque/IQ_circuit_solver/tree/master/potential_upgrades) directory.

- (To give you a glimpse of it, in the first complete version of the algorithm, the number of valid boards goes to tens of millions (level 120).
Whereas, V5.2 only has 2365 valid boards to explore before finding the solution.)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## License

Distributed under the MIT License. See [LICENSE.txt](https://github.com/adrienduque/IQ_circuit_solver/blob/master/LICENSE.txt) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

Adrien Duqué - adrienduquepro@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Acknowledgments

- Video of another algorithm with backtracking that reminded me of this project : [Computerphile sudoku solver](https://youtu.be/G_UYXzGuqvM)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
