Homework 2
Name: Luxi Han
Cnet: hluxi


1. Problem 1
Time for serial: 0.850708 seconds
Time for parallelization: 0.377524 seconds

Threads used in this problem is 4.
We can see that this gives us a speed up approximate equal to 2.2.

2. Problem 2
Time for serial: 6.678022 seconds
Time for parallelization: 3.335149 seconds

3. Problem 3
Serial version took 12.084368 seconds.
OMP Static version took 10.475670 seconds.
OMP Dynamic version took 8.227713 seconds.

+---------+---------+------------+-------------+
| Version | Serial  | OMP Static | OMP dynamic |
+---------+---------+------------+-------------+
| Time    | 12.08 s | 10.48 s    | 8.67 s      |
+---------+---------+------------+-------------+

The plot generated for the Mandelbrot set is saved as “mset_plot.png” in the enclosing folder.


4. Problem 4


6.Problem 6
We get the following running for the search kernel for the three data structure.

Set number of iteration to: 1000000
Original Method takes: 6.372312
Union Method takes: 1.144349
Augment Method takes: 2.093133

For 1000000 iterations (generating random search each iteration), the runtime for the unionized array is the least. Then following by the augmented array. The slowest implementation is the binary search on the original list of arrays. This in fact make sense.
Denote the number of arrays as k and the average array size as n. The complexity for the original method is O(k*log(n)) = O(log(n)*k). The complexity for the unionized array should be O(log(n * k) + k) = O(log(n) + log(k) + k). The complexity for the augmented array is approximately O(log(n) + k). 
Since for our case, the array size is considerably larger than the number of array. Then we can see that the original method should run the slowest. But exactly because of this reason, the augmented array search is slower than the unionized array search. The run time for the unionized array search should approximately be the same as the unionized method judging by the complexity analysis. But since we break down the arrays into different pieces, the memory prefetcher will cost extra time. Then the difference between the second and third method is a reflection of the way how computer hardware works.
