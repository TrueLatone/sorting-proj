FOR TESTING PURPOSE
======================================================================
1. Head to folder "FOR_TESTING" in this main repo
2. Open the folder in cmd
3. Updated test command:
   + To run ALL algorithms in ALL sizes and orders: test.exe -t
   + To run desired algorithm but in ALL sizes and orders: test.exe -t [YOUR ALGORITHM]
   + To run desired algorithm in custom size in all orders: test.exe -t [YOUR ALGORITHM] [SIZE]
  
**Second and Third command prints results directly on terminal**

**The first one exports results into 6 files corresponding to 6 different sizes**


P/S: MUST FOLLOW THE FOLLOWING COMMAND TO WORK

**IF THERE IS ANY PROBLEM WITH "test.exe" PLEASE RE-COMPILE IT WITH FOLLOWING COMMAND: *g++ "-Wl,--stack,36777216" main.cpp funcs/*.cpp -o test.exe***

ALL AVAILABLE SORTING AL:
"selection-sort", "insertion-sort", "shell-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort", "counting-sort", "binary-insertion-sort", "shaker-sort", "flash-sort"

SIZE: 10000, 30000, 50000, 100000, 300000, 500000
