/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:05:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:40:04 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
//START AT THE BOTTOM

static char *get_env_var(char *str, int start)
{
	char *search_var; //the variable to search for
	char *env_var; //the value we return
	
	search_var = ft_substr(str, start + 1, get_search_var_end(str, start) - start); //we say plus one because we dont want $ in our search variable
    // printf("search_var: %s\n", search_var);
    if (search_var && search_var[0] == '?' && search_var[1] == '\0') //aka is $?
		env_var = "77";
	// else if (search_var[0] = "$" && search_var[1] == '\0')
	// 	env_var = getpid(); //get process id  
	else
		env_var = getenv(search_var); //use the getenv to get return value
    if(env_var == NULL) //if not found return empty string
        return ("");
    free(search_var); //it was allocated at the start
	return(env_var); //return the env_var we have
}

//use the string passed to identify and replace environment variables
static char *new_expanded_str(char *str) //
{
    int start;
    char *expanded_str;
    char *temp_str;
    int count;

    start = 0;
    count = 0;
    expanded_str = NULL;
    temp_str = NULL;

    while(str[start] && ++count) //two conditions, if we have a $ or not
    {
        if (str[start] == '$' && !array_strchr("\" ''\0'", str[start + 1])) //$ not followed by these characters;
        {
            temp_str = ft_strdup(get_env_var(str, start)); //call get env var, we make copy because it does return an dynamically allocated value, only string literals
            start = get_search_var_end(str, start) + 1; ////We need to add plus one because the get_end stops at the last letter of the search variable
            // printf("start: %c\n", str[start]);
        }
        else
        {
            temp_str = ft_substr(str, start, get_end_index_expan(str, start) - start); //need to get the characters till the next $ and not followed by these characters
            start = get_end_index_expan(str, start); //stops at the end or next $
        }
        expanded_str = strjoin_env_var(temp_str, expanded_str, count); //join the temp_str to expanded_str if already there
        // printf("temp_str: %s\n", temp_str);
        // exit(0);  
        // printf("temp_str: %s\n", expanded_str);
    }
    // printf("the expanded_str: %s\n", expanded_str);
    // exit(0);
    return (expanded_str);
}

static char	*final_expanded_str(char *str) //function to get the final expanded str
{
	char *final_str; //the fully expanded str;
	char *expand_temp; //this a temporary holder of the returned value from new_expanded_str;
	
	final_str = ft_strdup(str); //initialised to parameter passed; 
	while (needs_expansion(final_str) == true) //we need to be checking if the current final string needs to be expanded further
	{
		expand_temp = new_expanded_str(final_str); //function to replace $ with env variables
		free(final_str); //we need to replace the final_str with new returned one
		final_str = ft_strdup(expand_temp); //put the most recent expanded str to final_str
		free(expand_temp);
	}
	return(final_str);
}

// We start here, we want to produce a new array from previous array but with $VARS replaced
char **expand_array(char **str)
{
    char **expanded_str; //declare new array
    int i;

    // if (!str)
    //     return (NULL);
    i = 0;
    expanded_str = (char **) malloc(sizeof(char *) * (ft_array_len((const char **) str) + 1)); // point of memory allocation new length same as old length
    if (!expanded_str)
		return (NULL);
	while (i < ft_array_len((const char **) str))
    {
        expanded_str[i] = final_expanded_str(str[i]); //fill new array item with expanded variables
        i++;
    }
    expanded_str[i] = NULL; //end with NULL terminator
    free_array(str); //we have no use of the old str which came from part 1 so we free it
    return(expanded_str);
}