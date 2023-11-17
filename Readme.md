# BASH-SHELL

## Parsing Guide
  

### Introduction

This is the fundamental framework used , however, there are several cases to be handled and features to be added for specific bash test cases. The way l handled them has been omitted and it simply adds to this framework building on top of this, but if you are curious, contact me.

The main data structures used are linked list and arrays.
Arrays refers to `char **` data type which contains strings `char *` at each index of the array
Linked list is a struct that is connected by a pointer  variable which we use to go to the next node in the list.

Choice of array or linked listed is individual, based on  what are you comfortable with. Linked list are better for insertion, removal of items. Array are better for   random access and have a more straightforward implementation of indexing which makes them efficient for retrieving elements at specific positions.

We have **array methods** to make things easier:
-  strjoin but for arrays to combine to arrays
- dup_array to make a copy of an array
- ft_strlen but for arrays to count number of elements in an array

Heavy use of libft functions:
- ft_split
- ft_strjoin
- ft_strchr
- ft_strcmp
- ft_strcpy (modified from ft_strlcpy
- and the linked list methods

### Part 1:  Word Splitting
---
FROM BASH MANUAL/*Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.*

Preliminary check on the line:
- Check if line has something not just spaces
-  Check if line has balanced quotes

<u>Note on Quoting:</u>

We have a struct that contains to boolean values for the single quote and double quote. This is used to manage whether we are inside single quotes or double quotes as we pass through the string given

`typedef  struct  s_quote`
`{ 	bool  single_q;`
`	bool  double_q;`
`}` 
`t_quote;`

FROM BASH MANUAL: **Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by meta-characters. Alias expansion is performed by this step (see Aliases).**

This line starts in char *,for example,
`"ls -l | grep " test.txt"> file_list.txt
"`
- then goes to an array split on spaces (`"\t  \n\v\f\b"`), these,`ft_spaces`, which produces an array `{ls,-l,|,grep,"test.txt">,file_list.txt}`

 the further splitting based on meta characters(`< << >> > |` ), `ft_strtok`, which produces `{ls,-l,|,grep," test.txt", >,file_list.txt}`

### Part 2: Tokenization and Syntax
---
FROM BASH MANUAL: *Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.*

**Create a token linked list out of the array we have.**  Free the arrays created in PART 1 after creating the list. The use of linked list comes when we need metadata (extra information about the data we have). In this case we want to know the type of token, either **PIPE, REDIR or WORD.** 

`typedef  struct  s_token`
`{`
	`t_token_type  type;`
	`char  *value;`
	`struct  s_token  *next;`
`} t_token;`

FROM BASH MANUAL: _It's necessary to **perform the expansion before creating the linked list of tokens** because we want any output we get from the environment variables to be assigned the type _WORD_ and treated as a _WORD_ even if it may be a meta-character we retrieve from the env_vars._

Creatin a tokenlist makes the syntax checks easier, because we simply compare types For example, check if the first token in the linked list is a **PIPE**, if so return parse error, check if the last item in the linked list `token->next == NULL` is  not type **WORD** then return error.

Having confirmed the syntax checks we need to perform **Quote removal**. Going through each token remove the quotes from the value.

###  Part 3:  Filling the final struct
---
FROM BASH MANUAL: *Parses the tokens into simple and compound commands (see Shell Commands).
Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.*

Here comes the final part were we fill the final struct to be used by the execution and this is the trickiest part. 

Firstly,  allocate memory for our array of simple commands. `t_command  **s_commands;` 
This is based on the number of type **PIPE** tokens we have in the **token list.** 

`typedef  struct  s_command`
`{`
	`char  *cmd;`
	`char  **args;`
	`t_redir  *redirs;`
`} t_command;`

`typedef  struct  s_redir`
`{`
	`t_redir_type  type;`
	`char  *filename;`
	`struct  s_redir  *next;`
`} t_redir;`

`cmd` is the first word in the `args` to be passed to `execve`. l have omitted some metadata. l also have `args_len; redirection_len; cmd_len`. These are simple to add and useful at times. 

As shown above, for each simple command there is a redirection list which is a linked list and contains **type of redirection** and the **filename.** and pointer to next redirection.

<u>Example:</u>
Prompt: 
`ls -l | grep " test.txt"> file_list.txt`
Desired output:
- first simple command is: `{ls,-l}`
- second simple command is: 
-- args: `{ grep,test.txt}`
-- redirs:  `{>,file_list.txt}`

From the token list in PART 2 we take a start and end token. 

_Side Note:_ The end token is either the last token in the list or the token before we encounter a type PIPE. So we use this condition (`if(token->next->type == PIPE`). If true we take the current token as our end. The next time round we skip the PIPE token and take the token after the pipe as our new start. 

We use these to fill a simple command node in the simple command array. We pass these into a function  `fill_scmnd`to fill a simple command using the token start and token end. It looks like this:
`void  fill_scmnd(t_command  *scommand, t_token  *start, t_token  *end)`

Inside the simple command function we go through the token list starting at the `start` token and stopping at the `end` token. When we encounter a token with the type **REDIR**, we take that token and the next one(which will be the filename) and create a redirection node to be added to the simple command's redirection list. This the function called to achieve this.

`void  fill_redirs(t_command  *scommand, t_token  *redir, t_token  *filename)`

If the type is **WORD** then join it to a `char **args`that will be passed to the execve. (This were strjoin but for arrays comes in). We stop at the end token. 

In summary, we allocate the memory for  a simple command array then at each index will fill it with a simple command that contains a linked list of redirections. We go through the token list filling each simple command. Deallocate the tokenlist after we finish. We no longer need it.

There it is, the your final struct.

Metadata is quiet important knowing the number of redirections, length of the command array, the value of the first command in the array or even a boolean to maintain state if a struct has been freed.
