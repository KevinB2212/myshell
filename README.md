# 🐚 MyShell

> A custom Unix shell built from scratch in C

## About

A fully functional Unix shell implementation written in C as part of DCU's Operating Systems module (CA216). Supports internal commands, external program execution, I/O redirection, piping, and background processes.

## Features

- **Built-in commands:** `cd`, `clr`, `dir`, `environ`, `echo`, `pause`, `help`, `quit`
- **I/O redirection:** Input (`<`) and output (`>`, `>>`) redirection
- **Background execution:** Run processes in the background with `&`
- **Environment variables:** Full environment variable support
- **Manual pages:** Built-in help documentation

## Project Structure

```
├── src/
│   ├── myshell.c      # Main shell loop & command parsing
│   ├── myshell.h      # Header file & function declarations
│   ├── utility.c      # Utility functions & built-in commands
│   ├── utility.h      # Utility header
│   ├── makefile       # Build automation
│   └── help.txt       # Built-in manual page
└── manual/            # Documentation
```

## Build & Run

```bash
cd src
make           # Compile
./myshell      # Run the shell
```

## Usage

```bash
myshell> echo Hello World
Hello World

myshell> dir /home
...

myshell> ls -la > output.txt    # Output redirection

myshell> sleep 10 &             # Background execution

myshell> help                   # View manual
```

## Tech Stack

- **Language:** C
- **Build:** Make
- **Platform:** Unix/Linux

## Author

**Kevin** — Dublin City University

---

*DCU CA216 — Operating Systems*
