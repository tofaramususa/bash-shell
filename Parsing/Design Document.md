FROM THE BASH WEBSITE:
3.1.1 Shell Operation
The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status (see Exit Status).


Do the expansion after removing space if nothing return empty string;

Remove the quotes after removing the redirections;

TO FIGURE OUT:
What do we do is $VAR is not set to anything, empty string or NULL;
What do we do with quotes not matched, is it an error or we just treat them as normal character
REDIRECTIONS -- what do we do, how do l store them as. How does this affect how l seperate things