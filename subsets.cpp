#include <bits/stdc++.h> 
#include <errno.h>
#include <stdlib.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


using namespace std;

int numberOfAssignments = 0;
int sumOfSubset = 0;

// check whether an array can be 
// partitioned into k subsets of equal sum 

// Recursive Utility method to check k equal sum 
// subsetition of array 
/** 
	array		 - given input array 
	subsetSum array - sum to store each subset of the array 
	taken		 - boolean array to check whether element 
					is taken into sum partition or not 
	k			 - number of partitions needed 
	n			 - total number of element in array 
	curIdx		 - current subsetSum index 
	limitIdx	 - lastIdx from where array element should 
					be taken */
bool iskPartitionPossibleRec(int array[], int subsetSum[], bool taken[], 
				int subset, int k, int n, int curIdx, int limitIdx) 
{
	if (subsetSum[curIdx] == subset) 
	{ 
		// current index (k - 2) represents (k - 1) subsets of equal sum
		// last partition will already remain with sum 'subset'
		if (curIdx == k - 2)
		{
			return true;
		}

		// recursive call for next subsetition
		return iskPartitionPossibleRec(array, subsetSum, taken, subset, 
											k, n, curIdx + 1, n - 1); 
	} 

	// start from limitIdx and include elements into current partition 
	for (int i = limitIdx; i >= 0; i--) 
	{ 
		// if already taken, continue 
		if (taken[i])
		{
			continue;
		}
		
		//check the sum of current subset and the next element
		int tmp = subsetSum[curIdx] + array[i];

		// if temp is less than subset then only include the element 
		// and call recursively 
		if (tmp <= subset)
		{ 
			// mark the element and include into current partition sum 
			taken[i] = true;
			//assignment
			subsetSum[curIdx] += array[i];
			numberOfAssignments += 1;
			bool nxt = iskPartitionPossibleRec(array, subsetSum, taken, subset, k, n, curIdx, i - 1); 

			// after recursive call unmark the element and remove from 
			// subset sum 
			taken[i] = false; 
			subsetSum[curIdx] -= array[i]; 
			if (nxt) 
				return true; 
		} 
	} 
	return false; 
} 


// Function to check if all subsets are filled or not
bool checkSum(int sumLeft[], int k)
{
	int r = true;
	for (int i = 0; i < k; i++)
	{
		if (sumLeft[i] != 0)
			r = false;
	}

	return r;
}

// Helper function for solving k partition problem
// It return true if there exists k subsets with given sum
bool countSubsetSum1(int S[], int n, int sumLeft[], int A[], int k)
{
	// base case: no items left
	if (n < 0)
	{

		// return true if subset is found
		if (checkSum(sumLeft, k))
		{
			return true;
		}
		else
		{
			cout << "No items left; State: \n";
			for (int i = 0; i < k; i++)
			{
				std::cout << "Partition " << i << " is: ";
			   	for (int j = 0; j < n; j++)
			 		if (A[j] == i + 1)
			 			std::cout << S[j] << " ";
			 	std::cout << std::endl;
			}
			return false;
		}
	}

	bool res = false;

	// consider current item S[n] and explore all possibilities
	// using backtracking
	for (int i = 0; i < k; i++)
	{
		if (!res && (sumLeft[i] - S[n]) >= 0)
		{
			// mark current element subset
			A[n] = i + 1;

			// add current item to i'th subset
			sumLeft[i] = sumLeft[i] - S[n];
			//assignment
			numberOfAssignments += 1;
			
			// recur for remaining items
			res = countSubsetSum1(S, n - 1, sumLeft, A, k);
			
			// backtrack - remove current item from i'th subset
			sumLeft[i] = sumLeft[i] + S[n];
		}
	}

	// return true if we get solution
	return res;
}

// Helper function for solving k partition problem
// It return true if there exists k subsets with given sum
bool countSubsetSum2(int S[], int n, int sumLeft[], int A[], int k)
{
	// return true if subset is found
	if (checkSum(sumLeft, k))
		return true;

	// base case: no items left
	if (n < 0)
	{
		cout << "No items left; State: \n";
		for (int i = 0; i < k; i++)
		{
			std::cout << "Partition " << i << " is: ";
		   	for (int j = 0; j < n; j++)
		 		if (A[j] == i + 1)
		 			std::cout << S[j] << " ";
		 	std::cout << std::endl;
		}
		return false;
	}

	bool res = false;

	// consider current item S[n] and explore all possibilities
	// using backtracking
	for (int i = 0; i < k; i++)
	{
		if (!res && (sumLeft[i] - S[n]) >= 0)
		{
			// mark current element subset
			A[n] = i + 1;

			// add current item to i'th subset
			sumLeft[i] = sumLeft[i] - S[n];
			//assignment
			numberOfAssignments += 1;
			
			// recur for remaining items
			res = countSubsetSum2(S, n - 1, sumLeft, A, k);
			
			// backtrack - remove current item from i'th subset
			sumLeft[i] = sumLeft[i] + S[n];
		}
	}

	// return true if we get solution
	return res;
}


// Method returns true if array can be partitioned into k subsets 
// with equal sum 
bool iskPartitionPossible(int array[], int n, int k, int method) 
{ 
	// If k is 1, then complete array will be our answer 
	if (k == 1)
	{
		return true; 
	}

	// If total number of partitions are more than n, then division is not possible 
	if (n < k)
	{	
		return false; 
	}

	// if array sum is not divisible by k then we can't divide array into k partitions 
	int sum = 0; 
	for (int i = 0; i < n; ++i) 
	{
		sum += array[i];
	}
	
	if (sum % k != 0)
	{
		return false;
	}

	// the sum of each subset should be subset (= sum / k)
	int subset = sum / k;
	sumOfSubset = subset;
	//current sum of each subset
	int subsetSum[k],A[n];
	//true/false an element was already taken into a subset
	bool taken[n]; 

	// Initialize sum of each subset to subset 
	for (int i = 0; i < k; i++)
	{
		subsetSum[i] = subset; 
	}

	// mark all elements as not taken 
	for (int i = 0; i < n; i++)
	{
		taken[i] = false;
	}

	if(method ==1)
	{
		bool res = countSubsetSum1(array,n-1,subsetSum,A,k);
		if (!res)
		{
			//std::cout << "k-Partition of set S is not Possible";
			return false;
		}

		// print all k-partitions
		for (int i = 0; i < k; i++)
		{
			std::cout << "Partition " << i << " is: ";
		   	for (int j = 0; j < n; j++)
		 		if (A[j] == i + 1)
		 			std::cout << array[j] << " ";
		 	std::cout << std::endl;
		}
		return true;
	}
	else
	{
		//bool res = countSubsetSum2(array,n-1,subsetSum,A,k);
		// initialize first subsubset sum as last element of 
		// array and mark that as taken 
		//assignment
		subsetSum[0] = array[n - 1];
		numberOfAssignments += 1; 
		taken[n - 1] = true; 

		// call recursive method to check k-substitution condition 
		return iskPartitionPossibleRec(array, subsetSum, taken, subset, k, n, 0, n - 1); 
	}

} 



void syserr ( const char * msg )  
{  
    perror ( msg ); /* kiírja az errno változóban található hibakódot
                    és egy rövid hiba üzenetet */
    exit (errno); 
}  

int main(int argc, char * argv[]) 
{ 
	if (argc!=4)
	{
		syserr("Usage: ./subsets sizeofarray nrofsubsets method\n");
		exit(1);
	}
	
	// first argument: size of array
	int n = atoi(argv[1]);
	int array[n];
	// generate numbers [1,n] into array
	for (int i=1; i<=n; ++i)
	{
		array[i-1] = i;
	}
 
	// second argument: number of subsets
	int k = atoi(argv[2]);

	// third argument: number of method to call
	if(atoi(argv[3]) == 1)
	{
		cout << "-Method: SIMPLE BACKTRACKING" << "\n-\n";
		
		//shuffle array so it won't be the MVR method
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  		shuffle (&array[0], &array[n], std::default_random_engine(seed));

		/*for (int i=0; i<n; ++i)
		{
			cout << array[i] << " ";
		}*/

		if (iskPartitionPossible(array, n, k, 1))
		{
			cout << "-Partitions into equal sum is possible.  :)\n-\n";
			cout << "-Number of assignments: " << numberOfAssignments <<"\n-\n";
			cout << "-Sum of each subset: " << sumOfSubset << "\n";
		}
		else
		{
			cout << "-Partitions into equal sum is not possible.  :(\n";
		}
	}
	else if (atoi(argv[3]) == 2)
	{
		cout << "-Method: BACKTRACKING + MVR + FORWARD CHECKING" << "\n-\n";
		if (iskPartitionPossible(array, n, k, 2))
		{
			cout << "-Partitions into equal sum is possible.  :)\n-\n";
			cout << "-Number of assignments: " << numberOfAssignments <<"\n-\n";
			cout << "-Sum of each subset: " << sumOfSubset << "\n";
		}
		else
		{
			cout << "-Partitions into equal sum is not possible.  :(\n";
		}
		
	}
	else if (atoi(argv[3]) == 3)
	{
		cout << "-Method: BACKTRACKING + MVR + AC-3" << "\n-\n";
		cout << "-Error 404" << "\n";
	}
} 

