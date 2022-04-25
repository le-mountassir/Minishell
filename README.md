# Introduction

- The existence of shells is linked to the very existence of IT.
- At the time, all developers agreed that communicating with a computer using aligned
1/0 switches was seriously irritating.
- It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat
close to the human language.
- Thanks to Minishell, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist.

# Minishell
- The goal of Minishell is to create your own shell.

- What is a shell? Basically in an operating system there are these two elements:

- The kernel (= kernel): which performs the fundamental functions of the operating system such as the management of memory, processes, files...
- The shell: the interface between the user and the kernel, which allows the user to communicate with the operating system through a command language. The user can enter commands in the terminal. Thanks to the command line interpreter (such as bash or zsh which are shells), the commands entered are executed. 

# Rules

- Can only use C
- Must respect the school imposed coding style (The Norme)
- No memory leaks
- Implement a series of builtins: echo, cd, setenv, unsetenv, env, exit
- Manage the errors without using errno, by displaying a message adapted to the error output
- Can only use these standard library functions:
      malloc, free, access, open, close, read, write, opendir, readdir, closedir, getcwd, chdir, fork, execve, wait, waitpid, signal, kill
- Must have a Makefile to build the program
