# 🐚🧪 Minishell Test Suite 🧪🐚
### This file contains a test suite with 95 execution commands to evaluate the behavior of the Minishell. The tests are designed to cover all the requirements defined by the project's guidelines, ensuring compliance with the expected specifications.
### Run the tests and check if your Minishell is working correctly in all expected scenarios! 🚀

## <<< TEST SUITE 01 || Compile >>>
#### 1: check if the compilatio uses **-Wall -Wextra -Werror**
``1.1``
```bash
make -n
```
``1.2``
#### 2: Check norminette
```bash
norminette .
```
``1.3``
#### 3: Check if Minishell compile without any error
```bash
make
```

## <<< TEST SUITE 02 || Signal >>>
#### 4
> Ctrl+C

> Ctrl+\

> Ctrl+D

## <<< TEST SUITE 03 || Simple Command & Global variables >>>

#### 5: Execute a simple command with an absolut path
``5.1:``
```bash
/bin/ls
```
``5.2:``
```bash
/bin/clear
```
``5.3:``
```bash
/bin/sleep 2
```
``5.4:``
```bash
ls
```
``5.5:``
```bash
clear
```
``5.6:``
```bash
sleep 2
```
#### 6: Execute and empty command
```bash
```
#### 7: Execute only spaces or tabs
> Spaces
```bash
    
```
> Tabs
```bash
				
```

## <<< TEST SUITE 04 || Arguments >>>
#### 8: Execute a simple command with an absolut path and argument but without quotes
``8.1``
```bash
/bin/ls -l
```
``8.2``
```bash
/bin/ls -a
```
``8.3``
```bash
/bin/ls -la
```
``8.4``
```bash
/bin/touch testing.txt
```
``8.5``
```bash
/bin/cat testing.txt
```
``8.6``
```bash
/bin/rm testing.txt
```
``8.7``
```bash
ls -l
```
``8.8``
```bash
ls -a
```
``8.9``
```bash
ls -la
```
``8.10``
```bash
touch testing.txt
```
``8.11``
```bash
cat testing.txt
```
``8.12``
```bash
rm testing.txt
```
## <<< TEST SUITE 05 || echo >>>
#### 9: Execute the command echo with and without arguments
``9.1 [must work]``
```bash
echo hello
```
``9.2 [must work]``
```bash
echo 'hello'
```
``9.3 [must work]``
```bash
echo "hello"
```
``9.4 [must work]``
```bash
ec'ho' hello
```
``9.5 [must work]``
```bash
ec"ho" hello
```
``9.6 [must work]``
```bash
"echo" hello
```
``9.7 [must NOT work]``
```bash
ech"o hello"
```
``9.8 [must NOT work]``
```bash
echo"hello world"
```
``9.9 [must work]``
```bash
echo hello "                " world
```
``9.10 [must work]``
```bash
echo hello              world
```
``9.11 [must work]``
```bash
echo -n "hello"
```
``9.12 [must work]``
```bash
echo -n -n -n Testing
```
``9.13 [must NOT work]``
```bash
echo 'hello
```
``9.14 [must NOT work]``
```bash
echo "hello
```
## <<< TEST SUITE 06|| Return value of a process >>>
#### 10: Execute the command echo with and without arguments
``10.1``
```bash
/bin/ls
```
plus
```bash
echo $?
```
``10.2``
```bash
ls
```
plus
```bash
echo $?
```
``10.3``
```bash
/bin/ls notaflag
```
plus
```bash
echo $?
```
``10.4``
```bash
ls notaflag
```
plus
```bash
echo $?
```
## <<< TEST SUITE 07|| Quotes >>>

#### 11 : Execute a simple command but with double quotes
``11.1 [must work]``
```bash
ls "-l"
```
``11.2 [must work]``
```bash
"clear"
```
``11.3 [must NOT work]``
```bash
ls "-la
```
``11.4 [must NOT work]``
```bash
clear"
```
``11.5 [must work] - this dir will be used soon``
```bash
mkdir "testing dir"
```
#### 12: Execute a simple command but with single quotes
``12.1 [must work]``
```bash
ls '-l'
```
``12.2 [must work]``
```bash
'clear'
```
``12.3 [must NOT work]``
```bash
ls '-la
```
``12.4 [must NOT work]``
```bash
'clear
```
``12.5 [must display user value]``
```bash
echo $USER
```
``12.6 [must display user value]``
```bash
echo "$USER"
```
``12.7 [must display $USER]``
```bash
echo '$USER'
```

## <<< TEST SUITE 08 || env >>>
#### 13: Execute env and check if it shows you the current environment variables
```bash
env
```

## <<< TEST SUITE 09 || export >>>
#### 14: Execute export to create new env. variables or replace one
``14.1 [must work]``
```bash
export
```
``14.2 [must work]``
```bash
export TEST=123
```
``14.3 [must work]``
```bash
export TEST1="1 2 3"
```
``14.4 [must NOT work]``
```bash
export -TEST2=321
```
``14.5 - check if the variables were created``
```bash
env
```
``14.6 [must work]``
```bash
export TEST=312
```
``14.7 [must work]``
```bash
export TEST1="3 2 1"
```
``14.8 - check if the variables were changed``
```bash
env
```

## <<< TEST SUITE 10 || unset >>>
#### 15: Execute unset to delete variables
``15.1 [must return error]``
```bash
unset NOTEXIT
```
``15.2 [must work]``
```bash
unset TEST
```
``15.3 [must work]``
```bash
unset TEST1
```
``15.4 - check if the variables were deleted``
```bash
env
```



## <<< TEST SUITE 11 || cd >>>
#### 16: Execute cd to navigate between directories
``16.1 [must work]``
```bash
cd "testing dir"
```
``16.2 [must work]``
```bash
cd ..
```
``16.3 [must return error]``
```bash
cd "this dir do not exit"
```
``16.4 - check if OLDPWD and PWD are different``
```bash
env
```

## <<< TEST SUITE 12 || pwd >>>
#### 17: Execute pwd to show your current path
```bash
pwd
```

## <<< TEST SUITE 13 || Redirections >>>
#### 18: Execute redirections
``18.1``
```bash
echo "test" > testing.txt
```
``18.2``
```bash
echo "append" >> testing.txt
```
``18.3``
```bash
ls > ls.txt
``` 
``18.4``
cat < Makefile
```bash
grep NAME < Makefile
```
``18.5``
```bash
cat < Makefile > out.txt
```
``18.6``
```bash
cat << EOF
```

``18.7``
```bash
cat << 'EOF'
```
> input a $VAR, it must not expand

``18.8``
```bash
cat << "EOF"
```
> input a $VAR, it must not expand

``18.9``
```bash
cat << EOF > testing.txt
```
> input things, including a $VAR then check the file `testing.txt`
```bash
cat testing.txt
```

``18.10``
```bash
cat << EOF >> testing.txt
```
> input things, including a $VAR then check the file `testing.txt`
```bash
cat testing.txt
```

## <<< TEST SUITE 14 || Pipes >>>
#### 19: Execute commands with pipes
``19.1``
```bash
ls | grep .c
```
``19.2``
```bash
cat Makefile | grep a | wc -l
```
``19.3``
```bash
echo "testing" | cat | cat -e
```
``19.4``
```bash
ls | notacmd
```
``19.5``
```bash
cat | cat | ls
```


## <<< TEST SUITE 15 || Say bye >>>
#### 20: These must not work
``20.1``
```bash
false_cmd
```
``20.2``
```bash
ls -notflag
```
``20.3``
```bash
cat notafile
```
``20.4``
```bash
echo "unclosed quote
```
``20.5``
```bash
echo 'unclosed quote
```
``20.6``
```bash
| ls
```

#### 21: Time to say goodbye
``21.1 - Must return error and not close Minishell (see notes)``
```bash
exit bye
```
``21.2 - must exit``
```bash
exit 42
```
> Notes: Bash does not treat `exit` with an invalid argument as an error; it just states that the argument is invalid and exits anyway. However, some other shells handle it differently (they return an error for the invalid argument and do not close the program). Check if the group has handled this case. If they haven't, it is **NOT** a reason to reject their Minishell, since the subject states that we must use Bash as a reference.