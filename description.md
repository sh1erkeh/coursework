1. Construct Data Bases.
2. Construct Graph of conflicts:
    Hard Constraints:
    1. There must be no conflicts in groups' schedule.
    2. Room properties must satisfy subject conditions.
    3. Teacher's schedule must match with group's schedule.
    Soft Constraints:
    1. No group should take one class in a day.
    2. The gap between classes should be minimized.
    Special cases:
    1. Hard constraint 1 should not be applied to lectures.
    2. Hard constraint 1 is optional for subgroups of the same group.
3. Generate imperfect solution with Dsatur.
4. Improve solution with simulated annealing.
5. Tackle soft constraints.
