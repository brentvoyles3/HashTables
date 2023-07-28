# hashTable
Implemented two different version of hash tables collisions in C++

Description:
    This program takes 8 elements(numbers) via user input. Each element should be
    entered on its own line.
    The program contains two different ways to handle collisions occurring in a hash
    table. The first function handles collisions by performing separate chaining with
    a linked list at the index of the hash table where multiple hash function values
    collide. Separate chaning uses the the hash function h(x) = (x+1) mod 13. The
    second hash table uses open addressing (linear probing) to handle collisions.
    The hash function used for linear probingis also h(x) = (x+1) mod 13.

    How to compile my code:
    g++ hashTable.cpp -o hashTable.out