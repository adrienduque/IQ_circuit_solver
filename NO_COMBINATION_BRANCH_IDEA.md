# Intro

This branch is coming from the V7 commit in master branch.

The idea is to explore alternative algorithm schemes.

The branch is currently at prototype stage, quick and dirty tests to serve as proofs of concepts.

# Can the same algorithm, without the notion of having different combinations to test, could be efficient ?

## Explanation

Why not give up on the idea of combinations and just have one priority list of pieces to test. The open points of the level will just fill up naturally (e.g. : the pre-adding checks will make that, pieces can play their point side if there is still an open point on the board, but as soon as they are all filled up, they can't anymore).

I can see a few advantages :

- Algorithm is much simpler

- No need to determine playable sides per piece, all pieces can play all their sides.

- There is only 1 tree to explore

- Meaning that there is no duplicate computation to avoid between combinations (see master branch > V8), since there is no combination at all.

- We can play the pieces in a fixed order which always promote creating the less sub-trees as possible (e.g.: we don't have to play the smaller pieces in first sometimes, just because they are the "point pieces" of the current combination (and this is what is causing most of the useless board states exploration in the master branch algorithm)).

## Different versions and results

See main.c and search_algorithm_alternative.c

You can see built binaries and their stats in showcase_binaries_and_assets/no_combination_branch_stats directory @todo:link.

V1 differs from V0, as I wanted to not allow the superposition of missing connections to open points of a level, because there is a lot of valid boards with this pattern in V0.

But this was only a valid change if I played the CORNER_1 piece in first, as it's the only piece with a point tile which has a connection to the direct outside of the piece.

So I made a custom default priority array to play the pieces in V1, starting by the CORNER_1 one, then the pieces with the less number of valid potential positions (4 tiles pieces with a point (one side doesn't have much possibilities since it has a point), 3 tiles pieces with a point except those which have 3 sides, the other 4 tiles pieces, then the remaining pieces, bigger ones first).

V0 actually performs better than V1 (45092 vs 65428 total valid board states), and is competitive with the last master branch version of the algorithm (V7 has 48106, even if I feel like V8 will performs much better).

V1 is too focused on the CORNER_1 piece.

If I would like to make this version of the algorithm actually perfect, I would make a system to only allow 1 superposition of a missing connection and an open level point, then try to play CORNER_1 point side immediatly after and see if it fits. e.g.: making the adding of CORNER_1 separated from the priority piece array.

But I feel like it's over-engineered.

# Depth first search vs Breadth first search

In the main algorithm explanation (see README.md), I describe this algorithm as "depth-first search", but what would a breadth-first search algorithm look like here ?

1. Find all the position possibilities of the first piece in the priority list, without trying to add the second one yet.

2. From these valid positions, try to add the second piece, and filter the ones where we can't add it. Try all the position possibilities of the second piece, in every valid scenario of the first piece play (sub-trees). We don't try to add the third piece yet.

3. Repeat these simple steps until a solution is found.

As "finding the solution" means to find the right path from root node (empty board filled only with level hints) to a valid leaf node (level solution), the breadth first search doesn't make much sense, it would obviously create valid board states in an exponential manner, most of them are useless as they don't lead to the solution.

The purpose of the depth-first search is to skip these useless computations, and, therefore, is suited to the problem.

# Conclusion

As we can see, the design choices I made in the master branch, are reinforced by the findings here.

The main one being the notion of combinations.

To make the algorithm explore as less valid board states as possible, we must create the less sub-trees as possible. We do it by playing first, the pieces that are likely to not have much possibilites of play on the board.

This is what explained the fact that giving the priority to bigger pieces, was an efficient choice.

But it also applies to point pieces. If a piece is forced to play its side with a point, and if there is not much open level points on the board, the piece have very few playable positions. Therefore having a system to play point pieces first is efficient, even if we have to switch between multiple priority list of pieces to play (to test different point pieces to play first).

The only real improvement of having only 1 tree to explore is that we don't have the issue where the algorithm may have duplicate computations (between different combinations). But this is what V8 of the master branch is built for.
