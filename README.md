# Minishell

### Objective
The objective of this project is to create shell, based on bash. This shell has been made using C programming language.

### Instalation

1. Clone this repository
```
git clone git@github.com:marco-kraemer/minishell.git
```

2. **CD** into root and compile
```
cd minishell
```
```
make
```

3. Run project  ( _Maybe it's neccessary to install libreadline-dev_ )
```
./minishell
```

### Functionalities
* Not interpret unclosed quotes or unspecified special characters like \ or ;.
* Show a prompt when waiting for a command.
* Has a history.
* Launchs executable.
* Executes builtins commands (echo, cd, pwd, export, unset, env, exit).
* Works with single and double quotes.
* Works with redirections(>, <, >>, <<)
* Works with pipes
* Prints enviroments variables
* Crlt-C, Crlt-D, and Crlt-\ work like in bash

