This folder contains the code to handle the forth point from bash shell operation:
Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.

How to tacklet this:
From the previous stage we produced an array, note that the length of the array does not change
but the value of each element does

Function Name and Definition:
1. expand_array
2. set_expand_str
3. get_expansion_variable
4. get_index_expan
5. no_name_yet
6. set_quote_flag_expan
7. get_expand_str 
8. get_exit_status
9. needsExpansion