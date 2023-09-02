# minishell


`Pipeline.c` the main file that takes a string and turns a linked list of simple commands

## Words and Operators
1. The first step after receiving the string from the user is to check if they are any commands or just spaces and just return the prompt. We also check for balanced quotes if not print error and return
2. Then we take away the spaces obeying the Quoting rules using `ft_space` this produces an **Array**
3. Then we split the arguments of the array further based on metacharacters << , >>, >, <, | obeying Quoting rules. This is done in `ft_strtok`. The two functions called in `ft_split_on_delims`.
4. We perform any necessary **Expansion** on the values of the array elements using `expand_array`. If the current token is a heredoc we skip the next token and do not attempt to expand it. We return a newly expanded str for each token.
5. Lastly we use the final array to produce a **tokenlist**, which is a linked list with each word and operator assigned a type of REDIR, WORD, PIPE. then free the array we had
Everything in this stage is brought together in the `ft_tokenize` function

## Syntax Check and Expansion
1. At this stage we perform a sytnax check on the tokenlist we need to show of three things:
 - There is no type PIPE at the start or end of the list and no two PIPES next to each other
 - that a REDIR is always followed by a word.
 - There is no REDIR or PIPE at the end
 If any of these errors are found, the list is freed and error produced and exit status updated, then wait for the next command
2. Then we perform **Quote Removal**. This is done in `remove_quotes`

## Simple Commands and Redirections
1. Taking the tokenlist we produce a linked list of simple commands. These commands are separated based on token type PIPE. In a single command struct we have the command name, an executable path,
the array of arguments for the execve function. We also have a list of redirections(infile and outfile), they contain the type INPUT, APPEND, HEREDOC, OUTPUT, also the filename. We also free the tokenlist as we no longer need to use it
2. 

-- At the end of parsing the tokens into simple commands the only allocated memory should be the simple commands list. At each stage free the array and list we are no longer using