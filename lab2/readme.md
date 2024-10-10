# Operating Systems Lab 2

This lab focuses on the use of shared memory in the context of parallelism and concurrency. Below is a description of each exercise:

## 1. Creating Multiple Processes with Shared Memory
The first exercise involves the creation of 10 processes, each working on different parts of a large array. Each process multiplies values in its assigned segment and returns the results to a coordinating process.

## 2. Concurrent Workers Checking Array Consistency
In the second exercise, two worker processes operate simultaneously on the entire array. They work to verify if all positions in the array hold equal values, testing concurrency and synchronization mechanisms.

## 3. Inter-Process Communication with Shared Memory
The third task focuses on inter-process communication through shared memory. In this exercise, one process saves a message into shared memory, and another process retrieves and displays it using the same memory space.
