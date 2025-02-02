1. Generate valid (satisfying hard constraints) solution with degree saturation algorithm 
(some events can end up unplaced, denote set of such events as $U$).
2. Use partial coloring algorithm (basically simulated annealing) to improve results of step 1, i.e. minimize
cardinality of $U$.
3. Process soft constraints.
