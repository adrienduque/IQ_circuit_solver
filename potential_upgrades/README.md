# Intro

---

This folder is meant to be dynamically filled and unfilled between software versions.

1 upgrade implementation = 1 commit (+ dump the upgrade observation in the commit).
And a new update of showcase_binaries_and_assets > IQ_circuit_solver_statx.xlsx, with quantified results and hypotheses re-evaluation.

Future potential upgrades mostly consist of adding more post-adding checking methods.
That discard out currently considered valid boards, that we know aren't.

Each new check might or might not be worth doing in terms of "solving the puzzle in the less amount of time".
By adding a new check, the algorithm will have to explore less boards, but the computational time of evaluating the validity of each board state necessarily increases.

---

## Case 1

### Observation

    Missing connections can't go on a level point hint, unless if CORNER_1 can play its side with a point.
    2 missing connections on 2 different level points is always an invalid case (I actually never saw this sub-case anyway).

### Hypothesis

    My guess is that, it's such a rare case, that the check might not be worth adding. Furthermore, I think that even if the case happens, the board is discarded pretty quickly, as the algorithm realizes with the next pieces that the board state is not valid. (And filling the points is the first thing that the algorithm does).

    But it's actually pretty simple to implement it as a sub-check of "check_no_dead_ends", we are already messing around with open point and missing connection tiles here. It might be worth, as it costs almost nothing more.
    If I implement it, I also should make the function returns a few more error codes, as it has nothing to do with dead ends.

### Example

    Image 1.1

---

# Other upgrades ?

---

### Observation

- Reorder combinations :
  Maybe switch the first priority piece first when going to the next combination, instead of switching the last choosen point piece. Because when a combination contains no solution, it means that starting point pieces were not compatible to begin with, and especially when we have a lot of level points to fill : the current setup tests the 4 starting piece -> incompatibility -> switch to the next combination -> but the 4 starting piece of the next combination are still the same ! because only the 6th one is changed. See example screenshots.

### Hypothesis

    This might be a big free improvement, as we might find the right combination earlier without any added computational cost.

### Example

    Image dumb_combination_order @todo
