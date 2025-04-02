# Pico Shell

Pico Shell is a simple command-line shell implemented in C. It supports built-in commands like `echo`, `pwd`, `cd`, and `exit`, while also allowing users to execute external commands using `fork()` and `execvp()`.

## Features
- **Built-in commands:**
  - `echo`: Prints the given text.
  - `pwd`: Displays the current working directory.
  - `cd <directory>`: Changes the current directory.
  - `exit`: Exits the shell.
- **External command execution:**
  - Runs commands like `ls`, `cat`, and `grep` using `execvp()`.
- **Command-line parsing:**
  - Splits input into arguments based on spaces.
  - Supports multiple spaces between arguments.
- **Memory management:**
  - Uses dynamic allocation to handle varying input lengths.

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/pico-shell.git
   cd pico-shell
   ```
2. Compile the source code:
   ```sh
   gcc -o picoshell picoshell.c
   ```
3. Run the shell:
   ```sh
   ./picoshell
   ```

## Usage
```
PicoShell > echo Hello, World!
Hello, World!

PicoShell > pwd
/home/user

PicoShell > cd ..
PicoShell > pwd
/home

PicoShell > ls
Desktop  Documents  Downloads

PicoShell > exit
Goodbye!
```

## File Structure
```
📁 pico-shell
 ├── 📄 picoshell.c  # Main source code
 ├── 📄 README.md    # Documentation
```

## Future Improvements
- Support for pipes (`|`) and redirection (`>`, `<`).
- Improved command history using `readline`.
- Environment variable support.







