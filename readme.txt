# Banker's Algorithm — Deadlock Avoidance (C++ Implementation)

This project implements the **Banker’s Algorithm** to determine whether a system is in a safe state.  
It uses an input file describing:
- Allocation matrix  
- Max matrix  
- Available vector  

The program:
1. Reads the input file.
2. Computes the Need matrix.
3. Runs the safety algorithm.
4. Prints whether the system is **safe**.
5. If safe, prints a **safe sequence**.

