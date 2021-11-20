# CS-201-Project
Analysis and Implementation of X-fast-trie and Y-fast-trie:-

An x-fast-trie is a data structure for storing integers from a bounded domain. It supports 
exact and predecessor or successor queries in time O(log log M), using O(n log M) space, 
where n is the number of stored values and M is the maximum value in the domain.A y-fast-trie 
is a data structure used to store integers from a bounded domain. It is a bitwise trie, i.e. 
a binary tree where each subtree stores values having binary representations with common prefix. 
It is considered as an upgrade to X-fast tries, allowing more efficient memory usage and faster 
insertion/deletions. Y-fast trie also treats integers as if they were words of w bits which 
allows storing integers as a trie of words.

During the project, at many points, we had to debug our program using gdb and hence there 
was immense use of debugging in our project. Also we regularly used github for pushing our 
code.
---------------------------------------------------------------------------------------------------
Files present in our project:
1. readme.txt
2. trie.c(Basic structure/introduction for trie)
3. x_fast_trie.cpp 
4. y_fast_trie.cpp

Input Instructions for X-fast and Y-fast trie:
1. First it will ask to enter the size of the universe
2. Then it will give you a menu with different options:
   Insert, Predecessor, Successor, Search, Delete, and Exit

Sample Input for X-fast-trie:

Enter the size of the universe: 16
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to delete a given element
Press 6 to Exit
Enter your choice: 1
Enter element to insert: 1
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to delete a given element
Press 6 to Exit
Enter your choice: 1
Enter element to insert: 4
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to delete a given element
Press 6 to Exit
Enter your choice: 1
Enter element to insert: 9
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to delete a given element
Press 6 to Exit
Enter your choice: 5
Enter element to be deleted: 4
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to delete a given element
Press 6 to Exit
Enter your choice: 2 
Enter the value: 9
Predecessor of the key 9: Predecessor of the key 9 is 9
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to delete a given element
Press 6 to Exit
Enter your choice: 2
Enter the value: 8
Predecessor of the key 8: Predecessor of the key 8 is 1

Sample Input for Y-fast-trie:

Enter the size of the universe: 16
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 1
Enter element to insert: 1
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 1
Enter element to insert: 4
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 1
Enter element to insert: 9
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 2
Enter the value: 2
Predecessor of the key 2: 1
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 3
Enter the value: 5
Successor of the key 5: 9
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 4
Enter the element to be searched: 9
Element is present
---MENU---
Press 1 to insert
Press 2 to print predecessor
Press 3 to print successor
Press 4 to search for a given element
Press 5 to Exit
Enter your choice: 5




