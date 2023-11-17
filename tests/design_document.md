Here is a guide to parsing for minishell:
l need to add visualisation. 

/*INTRODUCTION*/
The main data structures to be used are linked list and arrays.
Arrays refers to char ** data type which contains strings (char *) at each index of the array
Linked list is a struct that is connected by a pointer named next which points to the next struct.
Choice of array or linked listed is individual, what are you comfortable with, linked list are better for insertion, removal of items, expansion. Array are better for 
This is the fundamental framework used however there are several cases to be handle several cases and changes to be made

/*DATA STRUCTURES - ARRAYS AND LINKED LISTS METHODS AND QUOTING*/
Array Methods --> array_join function to join two arrays;
Main libft functions -> 
Libft Linked List methods used ->

/* Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal. */
Peliminary check on the line: 
if it contains just spaces, if quotes on balanced

Quoting:
We have a struct that contains to boolean values for the single quote and double quote, 

/* Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases). */
This line starts in char *, 
then goes to an array split on spaces, the further splitting based on metacharacters;

/* Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments. */

Its necessary to perform the expansion before creating the linked list token because we want any output we get from the environment variables to be assigned the type WORD and treated as a WORD even if it may be a pipe (|)

The use of linked list comes when we need metadata(extra information about the data we have) In this case 
assign a type --> PIPE, REDIRECTION, WORD. and a linked list of each data; each token represents an char * in the array of strings(char *) we had. Do not add empty strings to our token list, skip them.

This makes the syntax easier, simply compare types for example check if the first token in the linked list is a PIPE,
if so return parse error, check if the last item in the linked list(token->next == NULL) is a type WORD.


Having confirmed the syntax checks we need to perform several operations on the token items

/* Parses the tokens into simple and compound commands (see Shell Commands).

Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list. */

For each token item remove the quotes this is performing the necessary quote removal required in the bash.
for each token word, create new word without the qoutes and replace the word

Here comes the final part were we fill the final struct to be used by the execution:
As we traverse through the token list to take each argument based on the type we have: We have an array of simple commands;
Each simple commands contains mainly the command array to be parsed to the 
Firstly we take each token up until the PIPE or the end and pass it to a create simple command function which that takes a start token and end token. 
Inside the simple command function we go through it again taking away REDIR type and the next token which will be the filename with associated redirection. If the type is WORD then join it to a char ** that will be passed to the execve

After we create the simple command function:
We skip the PIPE(token->next->next) and redo the process till reaching the end of the tokenlist
Ideally you want to deallocated the tokenlist since it will be of no use anymore

There it is, the your final struct.
Metadata is quiet important knowing the number of redirections, length of the command array, the value of the first command in the array or even a boolean to maintain state if a struct has been freed.


3.1.1 Shell Operation
The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

Optionally waits for the command to complete and collects its exit status (see Exit Status).