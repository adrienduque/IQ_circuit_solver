# Intro

This directory is meant to be dynamically filled and unfilled between software versions.

- 1 upgrade implementation = 1 commit (+ dump the upgrade observation in the commit).
  And a new update of showcase_binaries_and_assets > IQ_circuit_solver_statx.xlsx, with quantified results and hypotheses re-evaluation.

---

Future potential upgrades mostly consist of adding more post-adding checking methods.
That discard out currently considered valid boards, that we know aren't.

Each new check might or might not be worth doing in terms of "solving the puzzle in the less amount of time".
By adding a new check, the algorithm will have to explore less boards, but the computational time of evaluating the validity of each board state necessarily increases.

---

## Case 1

### Observation

Missing connections can't go on a level point hint, unless if CORNER_1 can play its side with a point.
2 missing connections on 2 different level points is always an invalid case (I actually never saw this sub-case anyway).

### Example

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/potential_upgrades/1.1.png">

### Hypothesis

My guess is that, it's such a rare case, that the check might not be worth adding. Furthermore, I think that even if the case happens, the board is discarded pretty quickly, as the algorithm realizes with the next pieces that the board state is not valid. (And filling the points is the first thing that the algorithm does).

But it's actually pretty simple to implement it as a sub-check of "check_no_dead_ends", we are already messing around with open point and missing connection tiles here. It might be worth, as it costs almost nothing more.
If I implement it, I also should make the function returns a few more error codes, as it has nothing to do with dead ends.

### Reevaluation

I was wrong, it is simpler to implement it like a double missing connection case (e.g : record in pre-adding if the corner 1 piece has been played, + the position of a missing connection on a open level point if there is + post-adding check to make sure the current values of these variables are compatible).

And I'm pretty confident from experience, that this is 100% not worth adding, regarding total solving time of a level.

---

# Other upgrades ?

## Board savestates between combinations

This is still mostly unclear for me, this is only a draft explanation.

### Example and observations

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/potential_upgrades/combination_savestates_1.png">

This is the first board state composed of these first 4 pieces, that we can even attempt to play the 5th piece, it took 12 valid board states to go to this particular states, and a little more to realizes that this was not the combination of the solution (but couldn't attempt to play the 5th after). Thus, this is the **only** state where we can even attempt to play a 5th piece with the current 4 first pieces.

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/potential_upgrades/combination_savestates_2.png">

With V7, the next combination is this one, since the previous maximum depth was 4 (we didn't successfully added the 5th piece), we can see it switched the 5th piece to test a new one.

But the algorithm will have to go through again all the 12 valid board states, to return to the one composed of the 4 common first piece, where we can attempt to play the 5th piece !

**My goal here is to prevent doing the same computations between combinations.**

I want to make a system that record all of the board states where we reached a new maximum depth (and everytime we reach it, not only when this is a new maximum).

Then, the algorithm could look into previous data, and if the starting pieces are common to a previous savestate, start directly from it, (I.e : direct test of the 5th piece in the example above). Based on its "similarity_depth".

### Hypothesis

I think it would speed up a lot of the combinations to be evaluated as wrong combinations.

### Implementation plan

Not only does it work for a "similarity_depth" with the same value as the "maximum depth reached", but for all the depths below. We only have to reset savestates that are beyond current "similarity_depth" as the concerned pieces will not be played anymore. (I mean, the current combination may have only a few common starting pieces with the previous combination, we could skip all computations done to play these common starting pieces).

In the function "is_current_combination_skippable", we can know the "similarity_depth" of the current combination from its direct predecessor.

The algorithm will now have to begin from the found savestates (to test the first piece that is not common) (and there can be multiple savestates to test here). and make "piece_selected" in agreement with the savestate. -> thus, this is a new loop between the setup of the next combination to test, and before testing the first piece in the actual algorithm.

(and not display the switch between combinations anymore ? It would make this switch stuttery ?)

## Reorder pieces again ?

The issue with the board savestates improvement is that it will only improves performance of the algorithm in levels which have a lot of open point pieces. Indeed, they are the one in which consecutive combinations can have a lot of pieces in common.

Why don't we try to have a fixed priority order of pieces to play, the combination will only decide which pieces play their side with a point, and which don't.

It would make the overall solver benefit more from the board savestates improvement.

## Trying a better(?) default piece priority order

In my other branch, I tried other default priority orders, the one that performed best was {Z_PIECE, SQUARE, T_PIECE, L_PIECE, CORNER_2, CORNER_1, LINE3_2, LINE3_1, LINE2_2, LINE2_1}. (E.g: 4 tiles point pieces, then the remaining 4 tiles pieces, then the 3 tiles pieces with only 2 playable sides, then 3 tiles pieces with 3 playable side, then the remaining smaller pieces).

The current order is {Z_PIECE, T_PIECE, L_PIECE, SQUARE, CORNER_2, CORNER_1, LINE3_2, LINE3_1, LINE2_2, LINE2_1}.

Thus this means promoting the square-shaped piece to an higher priority, because it has a point (compared to T and L shaped pieces), which constrains a lot of this side playable positions.

## Reworking again double missing connection checks

In my other branch, I realized that a superposition between a missing connection tile and an open level point, can be considered the same as a double missing connection case. (This is Case 1 of this readme @todo:link).

And I successfully made a system which works as such : "as soon as a piece is making a superposition between a missing connection tile and an open level point, immediatly try to add the only piece that can fill this tile (i.e. : the CORNER 1 piece), and if it doesn't fit, remove the piece as if a check didn't pass".

It was ugly, and seemed like over-specialized, but it worked well. And the same principle can be applied to the T and Line2 2 pieces, since they are the only pieces that can respectively fill a bend-shaped double missing connection tile, and a line-shaped double missing connection tile.
