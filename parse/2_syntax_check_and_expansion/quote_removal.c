

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
	free_str(str); //need to put this for replace_heredocs don't change
	return(new_str);
}
