/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:05:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:40:04 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "expansion.h"


static void set_quote_flag_expan(t_quote *value, char c) //set single_quote flag to true only if we not already inside a double quote
{
    // if((value) && c != NULL)
    // {
        if(c == '\'' && value->double_q == false)
            value->single_q = !value->single_q;
        else if (c == '"' && value->single_q == false)
            value->double_q = !value->double_q;
    // }
}

bool needs_expansion(char *str)
{
    t_quote quotes;
    int start;

    start = 0;

    quotes.single_q = false;
    quotes.double_q = false;
    while(str[start] != '\0') //iterate through the string
    {
        set_quote_flag_expan(&quotes, str[start]); //set true if in quotes
        if (str[start] == '$' && !quotes.single_q && !array_strchr("\" ' '\0'", str[start + 1])) //we need to make sure the $ is not followed by these characters, we can add more
            return(true) ;
        start++;
    }
    return (false);
}

// we need to know the index of the last letter of our search_var so we can take a substring of it 
int get_search_var_end(char *str, int start)
{
    if (str[start + 1] && array_strchr("$?", str[start + 1])) //means we have to get exit status or process id
        return (start + 1);
    start++; 
    while (str[start]) //we end when one of these are found to be the next character
    {
        if (array_strchr("\"' $'\0'", str[start + 1]))
            break ;
        start++;
     }   
     return (start);
}
int	get_end_index_expan(char *str, int start)
{
	t_quote quotes;
	
	quotes.single_q = false;
	quotes.double_q = false;
    while (str[start])
    {
        set_quote_flag_expan(&quotes, str[start]);
        if (str[start] == '$' && !quotes.single_q && !array_strchr("\" ' '\0'", str[start + 1])) //stop when $ is found and not in quotes and not followed by these characters
            break ;
        start++;
     }
	return(start);
}

char *strjoin_env_var(char *temp_str, char *expanded_str, int count)
{
    char *temp;

    temp = NULL; //tell compiler not assigned yet
    if (count > 1 && expanded_str) //this means we already have an expanded str and we need to join to it the temp_str
        {
            temp = ft_strjoin(expanded_str, temp_str); //make a copy of expanded_str
            if (temp)
                free(expanded_str);
        }
        else
            temp = ft_strdup(temp_str);
        if(temp)
            free(temp_str); //we need to free as we are done using it
    // EVERY IMPORTANT: Memory Leaks: If ft_strdup or ft_strjoin fails to allocate memory, they may return NULL. In that case, calling free on expanded_str before assigning it a new value could result in a memory leak.Always check the return values of memory allocation functions before proceeding to avoid memory leaks.
    return(temp);
}
