# Algorithm-Engineering

## Summary
Algorithm Engineering lecture programming projects for hard problems and their implementation using C++ and optimization tools

- The Exercises 1,2,3 solved with different approaches than Exercises 4 and 5
- This version shows solutions to first three exercises 
- To see the full complete solution to the all problems see [Version 2](https://github.com/mertsaner/AlgorithmEngineering_v2.0 "Github Repo of Version 2")


## Implemented Features and Methods
- In this Algorithm Engineering project, C++ programming language is used. C++high-level, high-performance, object-oriented programming language. Portability, scalability, multi-paradigm programming, low-level manipulation, and large community support were some of the reasons that made it a reasonable choice for our project. C++ also provided more control over hardware aspects like memory management and CPU usage.
- But, the most important reason to choose C++ was the speed.  In research that compares execution time performance with a different number of threads, four programming languages were used. These were C, C++ with Threading Building Blocks (TBB), C Sharp, and Java.  Results show that C++ has the highest speedup of all the benchmarks.
- According to the latest researches, the difference is most obvious while large data sets are used.  
In real-world and real applications it is faster than java, mainly because of the lighter memory footprint that results in better cache performance.  Particularly,  for sorting and processing the data, C++ is noticeably faster.\cite{Goran2013} 
- The same logic goes for Python as well.  Python is interpreted, while C++ is compiled.  Compiled languages are converted directly into machine code that the processor can execute.  Interpreted code is always slower than direct machine code because it takes a lot more instructions to implement an interpreted instruction than to implement an actual machine instruction. As a result, compiled languages tend to be faster and more efficient to execute than interpreted languages. 

## Problem and Data Structures
- The NP-hard Cluster Editing problem is among the best-studied parameterized problems.  The Cluster Editing problem is defined in a way that given an undirected, loopless graph, it is needed to find a set of edge modifications (insertions and deletions) of minimum cardinality,  such that the modified graph consists of disjoint cliques.
- An undirected graph $G= (V, E)$ and a non-negative integer, the NP-hard Cluster Editing problem asks whether can be transformed into a disjoint union of cliques by modifying at most edges.
- In this project, our goal was to implement the simple search tree algorithm from the lecture and compile the final implement in machines of the university. 
In order to implement our program, we used some C++ libraries. Those are math.h to implement mathematical operations, vector to create and implements vectors, and finally string to use a string in our program. Even for graphs with constant maximum degree Cluster Editing and Cluster Deletion are NP-hard and that this implies NP-hardness even if every vertex is incident with only a constant number of edge modifications.

## Experiments 
- While implementing our project we created adjacent matrices and counted for a number of vertices and clusters. We also calculated the cost of each such change. We answered one of the important questions of how does the running time depend on the number of vertices of the input graph, the answer is,  for 10 vertices, we need to test $ 2^((((vertexcount - 1)^2)(vertexcount-1)) / 2)$ computations. For normal computers, it would be too time-consuming to calculate. 
- We also answered the second important question of how does the running time depends on the minimum cost to obtain a cluster graph.
With the naive approach, there is no dependence, with the recursive approach, the running time increases with the cost.  With each cost, we need to build a new recursive tree with one additional layer, while it depends on the cost of the vertex change. 
