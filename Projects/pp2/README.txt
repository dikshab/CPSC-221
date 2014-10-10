README.txt file documenting a CPSC 221 programming project.

Please fill out each TODO item in the header but change nothing else,
particularly nothing before the colon ":" on each line!

=================== HEADER =======================

Student #1, Name: Calvin Cheng
Student #1, ugrad.cs.ubc.ca login: o7x8
Student #1, ID: 36090132

Student #2, Name: Stephanie Dong
Student #2, ugrad.cs.ubc.ca login: p1e9
Student #2, ID: 31136138

Team name (for fun!): Everything is awesome

Project: Modifying a Modular Timing Module

Acknowledgment that you understand and have followed the course's
collaboration policy (READ IT at
http://www.ugrad.cs.ubc.ca/~cs221/current/syllabus.shtml#conduct):

Signed: Calvin Cheng
        Stephanie Dong

=================== BODY =======================

Plese fill in each of the following:

Approximate hours on Project: 1.23

Acknowledgment of assistance (per the collab policy!): N/A

For teams, rough breakdown of work: The workload was fairly even.

=================== RESPONSES =======================

1. Good Big-O bound on mod_exp1 in terms of x: O(x)

Justification: The loop runs x times, so the complexity is linear.


2. Good Big-O bound on mod_exp2 in terms of x: O(lg x)

Justification: The function is recursive, where the recursive call reduces the
               size of x by a factor of 2 after each call, and the base case
               runs in constant time.


3. Good Big-O bound on mod_exp2o in terms of x: O(x)

Justification: For the base case, T(1) = c, so the base case runs in constant
               time. For the recursive call, the time complexity is
               T(x) = 2 T(x/2) + C
                    = 4 T(x/4) + 3C
                    = 8 T(x/8) + 7C
                    = ...
               In general, then, we can see that the general form of the
               function follows
               T(x) = 2^k T(x / 2^k) + (2^k - 1) * C
               The recurrence continues until the base case, where we want to
               find T(1). At this point, x = 2^k. Substituting this into the
               recurrence gives
               T(x) = x T(1) + (x-1) * C
               Because the base case runs in constant time, the function
               reduces to the asymptotic complexity O(x).


4. Bounds in terms of m.

Good Big-O bound on mod_exp1 in terms of m: O(1)

Justification: Regardless of the size of m, the loop will still run the
               same number of times (assuming x is constant). Therefore,
               the function runs in O(1) time.


5. For a 10-20 second run of mod_exp1, I needed:

b = 2

x = 20

m = 1000

The run took this many seconds: 12.457 s

Computer details (just what I can find easily): Mac OS 10.9
                                                2.2 Ghz Intel Core i7
                                                16 Gb RAM

JUST FOR FUN: You might want to find out details about your computer.
For example, on a Unix (or Mac) machine, try running "uname -a".  On
some machines, you may also be able to look at the file /proc/cpuinfo.
On Windows, you can probably right-click on "My Computer" and find
similar info.



6. I anticipate mod_exp1 will take about twice as long with the same
values of b and m as above and this value of x: 40

The actual runtime in seconds was: 26.485 s

Discussion of the estimate versus the measured result:
Our estimate was fairly accurate, given that the actual runtime for the second
trial was just slightly longer than twice that of the first trial.


7. For a 10-20 second run of mod_exp2, I needed:

b = 2

x = 400

m = 1000

The run took this many seconds: 13.608 s

Computer details (just what I can find easily): See above (Question 5).



8. I anticipate mod_exp2 will take about twice as long with the same
values of b and m as above and this value of x: 400^2 = 160000

The actual runtime in seconds was: 26.939 s

Discussion of the estimate versus the measured result:
Our estimate was fairly accurate, given that the actual runtime for the second
trial was just about twice that of the first trial.



8. For a 10-20 second run of mod_exp2o, I needed:

b = 2

x = 10

m = 1000

The run took this many seconds: 11.039 s

Computer details (just what I can find easily): See above (Question 5 and/or 7).



10. I anticipate mod_exp2o will take about twice as long with the same
values of b and m as above and this value of x: 20

The actual runtime in seconds was: 23.809 s

Discussion of the estimate versus the measured result:
Our estimate was fairly accurate, given that the actual runtime for the second
trial was just slightly longer than twice that of the first trial.


11. The graph of the run-time of mod_exp2() vs. x is given in plot.pdf.
