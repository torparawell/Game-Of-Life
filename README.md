# CPSC350-fall2020-Assignment1
Name: Tor Parawell
Student ID#: 002354234
Chapman email: parawell@chapman.edu
Course Number and Section: CPSC 350-2
Assignment: 2

Brief Overview of Program:
Conway's game of life in C++.  The premise of this code is create cells in a grid (either uploaded or randomly populated) that represent cell growth.
Based on certain conditions, the cells can either grow, die, or stay in their same state upon each generation.  This particular program has three
different modes to deal with boundaries.  
  a) Classic mode - Boundaries are boundaries, no cells go off the grid.
  b) Donut mode - Boundaries make a donut shape where the opposite boundaries are counted as cells.
  c) Mirror mode - Boundaries are reflected on themselves.

2) A list of all source	files submitted	for the	assignment
game.cpp, classic.cpp, mirror.cpp, donut.cpp, main.cpp, assignment-2.h, Makefile

3)A description	of any known compile or	runtime	errors,	code limitations, or deviations
from the assignment specification (if applicable)
No applicable runtime errors

4) A list of all references used to complete the assignment, including peers (if applicable)
N/A

5) Instructions	for	running	the	assignment.	(Typically	applicable	in	advanced	courses	using
build	systems	or	third	party	libraries)
make all 
enter the instructions as prompted.
