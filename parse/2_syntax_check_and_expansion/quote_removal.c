//after we have our args we need to remove the quotes before execution
// May need to perform quote removal before creating the tokens
//3.5.9 Quote Removal
// After the preceding expansions, all unquoted occurrences of the characters ‘\’, ‘'’, and ‘"’ 
// that did not result from one of the above expansions are removed
// After these expansions are performed, quote characters 
// present in the original word are removed unless they have been quoted themselves (quote removal).
//use realloc


// "word"
// zsh: command not found: word
// tofaramususa@Tofaras-Air 1_words_and_operators % ""word""
// zsh: command not found: word
// tofaramususa@Tofaras-Air 1_words_and_operators % """word"""
// zsh: command not found: word
// tofaramususa@Tofaras-Air 1_words_and_operators % """wor""d 
// dquote> 
// tofaramususa@Tofaras-Air 1_words_and_operators % """word""""
// dquote> 
// tofaramususa@Tofaras-Air 1_words_and_operators % """wo""rd"""
// zsh: command not found: word
// tofaramususa@Tofaras-Air 1_words_and_operators % ""word"d"
// zsh: command not found: wordd
// tofaramususa@Tofaras-Air 1_words_and_operators % ""wor'd' 
// zsh: command not found: word
// tofaramususa@Tofaras-Air 1_words_and_operators % 
// echo """""""""""""""""""""""wo'''''rd""""""""""""""""""""'"
// wo'''''rd'

#include "../Parse.h"

static int count_chars(char *str)
{
    int i;
    int count;
    t_quote quotes;

	quotes.single_q = false;
	quotes.double_q = false;

    i = -1;
    count = 0;
    while(str[++i])
    {
        set_quote_flag(&quotes, str[i]);
		if((str[i] == '"' && !quotes.single_q) || (str[i] == '\'' && !quotes.double_q))
            continue;
        count++;
    }
    return (count);
}

char *remove_quotes(char *str)
{
	char *new_str;
	int	i;
	int	j;
	t_quote quotes;

	quotes.single_q = false;
	quotes.double_q = false;

	i = -1;
	j = 0;
	new_str = (char *) malloc(sizeof(char *) * (count_chars(str) + 1));
	while (str[++i])
	{
		set_quote_flag(&quotes, str[i]);
		if((str[i] == '"' && !quotes.single_q) || (str[i] == '\'' && !quotes.double_q))
            continue;
        new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	free(str); //need to put this for replace_heredocs don't change
	return(new_str);
}


// int main(void)
// {
//     char *test_var = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"wo'''''rd\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"'\"";
//     char *result = remove_quotes(test_var);
//     while(*result)
//     {
//         printf("%c", *result);
//         result++;
//     }

// }