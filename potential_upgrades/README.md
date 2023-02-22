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

## Reorder combinations :

### Observation

Maybe switch the first priority piece first when going to the next combination, instead of switching the last choosen point piece. Because when a combination contains no solution, it means that starting point pieces were not compatible to begin with, and especially when we have a lot of level points to fill :

the current setup tests the 4 starting piece -> incompatibility -> switch to the next combination -> but the 4 starting piece of the next combination are still the same ! because only the 6th one is changed. See example screenshots.

### Example

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/potential_upgrades/dumb_combination_order_1.png">

The 5th piece can't be played if these 4 previous pieces are played before it (we tested all positions possibilities of these 4 pieces).

<img src="https://github.com/adrienduque/IQ_circuit_solver/blob/master/potential_upgrades/dumb_combination_order_2.png">

But when we switch between combinations, the next combination has the same 4 starting pieces. The difference between the two combinations being the 6th piece.

### Hypothesis

This might be a big free improvement, as we might find the right combination earlier without any added computational cost.

### Reevaluation

In fact, this might have the opposite effect, to prioritize changing the first piece to go to the next combination means to bring smaller pieces earlier in the global combination order.

In wrong starting combinations (the ones that don't correspond to the combination of the actual level solution), there is a huge difference in the number of useless explored board states, e.g. : starting combinations composed of smaller pieces have a lot more than the others.

Thus, instead of changing the order of combinations tested, I'm rather going to setup a system in which the next combination is skipped depending on its common pieces with the current combination, and of course, the depth at which the current combination failed. E.g : still have the combination of the second screenshot be generated after the first one, but skipped even before the algorithm tries to play it, because we know from previous experience it will fail.

I'm not sure if I make the "previous experience memory" to only come from the previously tested combination, or if I store all new different failed combination data. Finally, I think I'll try to implement the first solution, and make new observations from it.
