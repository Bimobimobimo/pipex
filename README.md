# Pipex

## Description
The Pipex project is focused on handling pipes between two shell commands, simulating how data is passed between processes in a shell. The program should behave like the following shell command:

```bash
$> < file1 cmd1 | cmd2 > file2
```
In other words, it should take input from a file, pass it through two commands connected by a pipe, and write the output to another file. The project focuses on process management, file management and handling inter-process communication through pipes.

## Features
- Pipe Management: The program uses pipes to connect two commands.
- File Handling: It takes input from a file and writes the result to another file.
- Shell Command Simulation: It simulates the behavior of shell commands using file redirection (`<` and `>`) and pipes (`|`).
- Command Execution: It runs two shell commands with parameters and passes data between them via a pipe.

## Installation
Clone the repository:
```bash
git clone https://github.com/your-username/pipex.git
```
Navigate to the project directory:
```bash
cd pipex
```
Compile the project using make:
```bash
make
```

## Usage
To run the program, use the following command format:

```bash
./pipex file1 cmd1 cmd2 file2
```
Where:

- `file1` is the input file.
- `cmd1` and `cmd2` are the shell commands you want to execute (with parameters).
- `file2` is the output file.

## Example
Running the following command:

```bash
./pipex infile "ls -l" "wc -l" outfile
```
Should behave the same as the shell command:

```bash
< infile ls -l | wc -l > outfile
```
Another example:

```bash
./pipex infile "grep a1" "wc -w" outfile
```
Should behave the same as:

```bash
< infile grep a1 | wc -w > outfile
```

## Expected Behavior
The program will:
- Open `file1` and redirect it as input for the first command (`cmd1`).
- Execute `cmd1`, passing its output through a pipe to `cmd2`.
- Execute `cmd2` and redirect its output to `file2`.
