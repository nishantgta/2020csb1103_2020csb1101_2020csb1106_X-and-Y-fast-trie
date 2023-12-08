# CS-201-Project

## Analysis and Implementation of X-fast-trie and Y-fast-trie

An x-fast-trie is a data structure for storing integers from a bounded domain. It supports exact and predecessor or successor queries in time O(log log M), using O(n log M) space, where n is the number of stored values and M is the maximum value in the domain. A y-fast-trie is a data structure used to store integers from a bounded domain. It is a bitwise trie, i.e., a binary tree where each subtree stores values having binary representations with a common prefix. It is considered an upgrade to X-fast tries, allowing more efficient memory usage and faster insertions/deletions. Y-fast trie also treats integers as if they were words of w bits, allowing storing integers as a trie of words.

During the project, debugging was crucial, and we extensively used gdb for this purpose. We also regularly used GitHub for version control by pushing our code.

---

## Files Present in Our Project:

1. `readme.md`
2. `trie.c` (Basic structure/introduction for trie)
3. `x_fast_trie.cpp`
4. `y_fast_trie.cpp`

---

## Input Instructions for X-fast and Y-fast trie:

1. First, it will ask to enter the size of the universe.
2. Then, it will give you a menu with different options: Insert, Predecessor, Successor, Search, Delete, and Exit.

---
