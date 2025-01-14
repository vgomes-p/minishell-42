![cover](images/cover-minishell.png)


# RUNNING MINISHELL
![print_minishell](images/minishell_print.png)
## Requirements
#### - Linux, macOS or Windows with WSL installed
#### - cc or another compatible compiler
#### - 'make' installed
#### - 'readline' installed (see the end of readme)
### 1 - Clone this repository
```bash
git clone git@github.com:vgomes-p/minishell-42.git
```

### 2 - Get into the project dir
```bash
cd minishell-42/project
```

### 3 - Run the command make
```bash
make
```

### 4 - Now call the program and map you want to play
The maps you can call the program:
#### Map test:
```bash
./minishell
```

# CLEANING MINISHELL
### 1 - Go to the main dir
```bash
cd minishell-42/project
```
### 2 - Run the command clean or full clean
```bash
make clean
```
or
```bash
make fclean
```

### 3 - Close the terminal
```bash
exit
```
# INSTALLING READLINE
### 1 - Run the following commands
### Linux and Windows with WSL installed
```bash
sudo apt-get update
```
```bash
sudo apt install libreadline-dev
```
### macOS
```bash
brew install readline

```