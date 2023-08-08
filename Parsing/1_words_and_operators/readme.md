This folder contains the code to handle the second point from bash shell operation:
Breaks the INPUT into WORDS and OPERATORS, obeying the QUOTING rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).

We have two main functions to do this:
ft_space - takes the prompt which will be a line and splits it on any kind of space not inside quotes
ft_strok - this takes a line and splits it on metacharaters in our case(redirs and pipes). Difference is 
we dont want to discard the metacharacters, instead add them to the array produced. Also do not split if metacharacter is inside quotes

Improvements:
-- Need to handle edge cases for example if line from prompt is just empty spaces or empty string
-- The two functions perform a similar operations of splitting, only difference is ft_strok keeps the delimiters,
-- ideally it would be great if we had only one function to do all the spliting spaces then splitting on metacharacters



Points of memory allocation:
ft_space --> for our new array;
ft_strtok

