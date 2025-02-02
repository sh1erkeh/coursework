![Figure 1](~/Pictures/courcework.png)
1. Construct Data Bases.
2. Construct Graph of conflicts.\
    Hard Constraints:
    * There must be no conflicts in groups' schedule.
    * Room properties must satisfy subject conditions.
    * Teacher's schedule must match with group's schedule.
    
    Soft Constraints:
    * No group should take one class in a day.
    * The gap between classes should be minimized.

    Special cases:
    * Hard constraint 1 should not be applied to lectures.
    * Hard constraint 1 is optional for subgroups of the same group.
3. Generate imperfect solution with Dsatur.
4. Improve solution with simulated annealing.
5. Tackle soft constraints.
