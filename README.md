# Overview
This project is a hands-on assignment designed to help understand how buffer overflow vulnerabilities work and how they can be exploited to manipulate the program’s execution flow and memory. The goal of this project is to explore how data is passed in a C program, how buffer overflows occur, and how they can be used to manipulate control flow and variables.

## Program Breakdown
The assignment consists of three C programs:
- ```createdata3.c```: Identifying the buffer overflow threshold.
- ```createdata6.c```: Manipulating the program's flow control to change the grade to ```6```.
- ```createdata9.c```: Directly modifying the grade to ```9```.

Each program increases in difficulty, allowing you to gradually build your understanding of buffer overflows and memory manipulation.

## Program Outputs
Each program outputs a payload file that corresponds to the specific phase. These payloads are used to exploit the buffer overflow vulnerability. The files are named as follows:
- ```payload3```
- ```payload6```
- ```payload9```

To use the payload, simply pass the corresponding file as input to the vulnerable program:
```bash
vulnerable < payload3
```

This command will run the program with the exploit contained in the ```payload3``` file. The same process applies for ```payload6``` and ```payload9```.

## Compilation
In order to compile the programs use:
```bash
make all
```


# Detailed Explanations for Each Phase
## Phase 1: ```createdata3.c``` - Identifying the Buffer Overflow Threshold
In this first phase, the goal is to explore how much data can be passed into the program before it crashes. The program asks for the user's name, and we can see how much input it accepts before reaching a segmentation fault (segfault). This helps to identify the point at which a buffer overflow occurs.

__Steps Taken:__
- I experimented with various input sizes to determine the maximum amount of data the program could handle without causing a crash.
- By gradually increasing the size of the input, I observed at what point the program would fail, providing insight into the size of the buffer and its limits.
- The exact point at which the program fails serves as the buffer's overflow threshold, highlighting how much data can overwrite adjacent memory and cause unpredictable behavior, such as crashes or potential vulnerabilities.

## Phase 2: ```createdata3.c``` - Manipulating Flow Control to Set the Grade to 6
In this phase, the objective was to exploit the buffer overflow to manipulate the program’s flow and change the grade to 6. I started by analyzing the program with gdb (GNU Debugger) to understand its memory layout and control flow.

__Steps Taken:__
1. __Analyzing the Program with gdb:__
    - I opened the program in ```gdb``` and set a breakpoint at the readString function, specifically before the ```ret``` instruction is called.
2. __Identifying the Buffer Overflow:__
    - Upon running the program, I was prompted to enter a name. Based on the findings from the previous phase (```createdata3.c```), I knew that the buffer could hold 67 characters before overflowing. To test the limit, I input 69 'A's, which exceeded the buffer size and caused the overflow to reach the RSP register.
3. __Observing the RSP Register:__
    - I used the gdb command ```x/10xg $rsp``` to examine the RSP register. The program had successfully overflowed, and the RSP was now pointing to the area I needed to modify in order to control the program’s execution flow.
4. __Exploiting the Overflow to Control Flow:__
    - Since the ```ret``` instruction would jump to the memory address stored in RSP, I could now redirect the program’s control flow. To do this, I constructed a payload consisting of 68 'A's followed by the address where the program would change the grade to ```6```—this address was found by inspecting the program’s memory and identifying the location of the ```if``` statement that checks for the special input.
    - The address was encoded in little-endian format (since the system uses little-endian byte ordering), ensuring that when the ```ret``` instruction was executed, it jumped to the correct memory location where the grade was set to ```6```.
5. __Executing the Payload:__
    - Once I crafted the payload, I passed it as input to the program, successfully changing the grade to ```6``` by forcing the program to jump to the memory
    location that modifies the grade.

## Phase 3: ```createdata9.c``` - Injecting Shellcode to Set Grade to 9
In this final phase, the goal was to modify the program’s behavior at a deeper level—specifically by injecting and executing custom shellcode to set the
```grade``` variable to ```9```. This phase demonstrated a more advanced exploitation technique involving code injection and control of execution flow.

__Steps Taken:__
1. __Writing Custom Shellcode:__
I began by writing a small assembly program (```code.asm```) whose purpose was to directly modify the ```grade``` variable in memory. The key instruction was:
```asm
mov byte [0x404034], 0x39
```
This writes the ASCII value of ```9``` (0x39) to the memory address of the grade variable (```0x404034```).

2. __Converting to Shellcode:__
After assembling the program, I used ```objdump``` to extract the raw opcodes (machine code), converting the compiled instructions into hexadecimal shellcode
that could be injected into the vulnerable program.

3. __Constructing the Payload:__
The full payload was structured as follows:
```
[shellcode] + [padding] + [return address]
```
- Shellcode: The raw machine code to change the grade and return safely.
- Padding: A series of bytes to fill the buffer until the return address is reached (calculated as buffer size - shellcode length).
- Return Address: The address pointing to the start of the buffer (i.e., the ```Name``` variable), so that execution jumps to the injected shellcode after ```ret```.

4. __Ensuring Normal Program Termination:__
To ensure the program would continue and exit gracefully after executing the shellcode, I manually added instructions to:
```asm
push 0x40122a
ret
```
This pushes the return address (the instruction immediately after the call to ```readString```) onto the stack and then performs a ```ret```, effectively
simulating a clean return to the main execution flow.

5. __Executing the Exploit:__
The final payload successfully changed the ```grade``` to ```9``` and allowed the program to proceed normally without crashing or triggering a segmentation fault.

This project was developed as part of an academic assignment for the HY255 (Systems Programming Lab) course at the University of Crete.