## Backtracking problem

# Partition of a set into K subsets with equal sum

### Comparing simple and optimized backtracking methods
- backtracking (1)
- backtracking + MVR + forward checking (2)
- backtracking + MVR + AC-3 (3)

### Usage
```
$ ./subsets sizeofarray nrofsubsets method
```
Example: 

```
$ ./subsets 15 5 1
```

### Algorithm

The task is to divide an array of N elements into K non-empty subsets such that the sum of each subset is the same and all elements should be part of exactly one partition.

#### Main()
We get the size of array(N), number of subsets(K) and the method number as input.
Our array will contain N number,  from 1 to N in undefined order.

#### isKPartitionPossible()
This function returns true if an array can be partitioned into K subsets.
There are some obvious cases which do not even have to be tested (K=1, K>N).
With the help of K and total sum of the array we can calculate the sum each subset should have.
If the total sum of array can't be divided by K, there is no solution.

#### Simple backtracking
Gets the randomized array of N elements; value of K; an array of K elements represeting the actual complementary sum of each subset;
the position we begin the algorithm at (n-1); an array with size of N which we will be able to generate the subsets at the end with.
This method calls the recursive function ```countSubsetSum1()```, which will explore all possibilities using backtracking. When no item remains and the solution satisfies the contraints ```true``` is returned.

#### Backtracking + MVR + forward checking
As a difference this method gets an ascending ordered array, so that if we start from the end of array (index n-1) the method will fulfill the MVR principle. 
The forward checking technique reveals in using an array ```bool taken[n]``` which tells if an element was already used in a subset or not.

### Result
The results are remarkably better in the case of ```method 2``` regarding the number of assignments and elapsed time. (An array of N will only have solution if the sum of array can be divided by the number of subsets(K): ((N*(N+1))/2)%K=0 )
#### Input1

```
./subsets 15 5 1
```
- number of assignments: 282
- time: 146 µ

```
./subsets 15 5 2
```
- number of assignments: 9
- time: 23 µ

#### Input2

```
./subsets 25 5 1
```
- number of assignments: 3497824
- time: 193297 µ

```
./subsets 25 5 2
```
- number of assignments: 15
- time: 38 µ


#### Input3
```
./subsets 118 7 1
```
- number of assignments: -
- time: - (more than 12 m)

```
./subsets 118 7 2
```
- number of assignments: 1003
- time: 48 µs



