/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:59:07 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 14:30:14 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
/*Turn a string into a list of simple commands*/
/* One function that calls the four bottom functions */
//1. check if string contains arguments and the quotes are balanced
//
bool check_line(char *str)
{
	int i;

	i = -1;
	if(!str)
		return(false);
    if (check_unmatched_quotes(str) == true)
	{
        return (printf("unbalanced quotes\n"), false);	
	}
	while(str[++i])
	{
		if(!array_strchr("\t  \n\r\v\f\b", str[i]))
			break ;
	}
	if (str[i] == '\0')
	{
		return (false);
	}
	return(true);
}

//2. Produce an array from the string that split into words and metacharacters
char	**ft_split_on_delims(char *str)
{
	char	**temp_tokens;
	char	**final_tokens;
	char	**next_tokens; 
	int		i;

	i = -1;
    temp_tokens = ft_space(str);
    if (temp_tokens == NULL)
	{
        return (NULL);	
	}
	while (temp_tokens[++i] != NULL)
	{
        if (i == 0)
		    final_tokens = ft_strtok(temp_tokens[i]);
        else
        {
            next_tokens = ft_strtok(temp_tokens[i]);
            final_tokens = append_array(final_tokens, next_tokens);
            free_array(next_tokens); 
        }
	}
	return (free_array(temp_tokens), final_tokens);
}
//3. Create a token list from the array, free the array, check for syntax, if error then free array, then perform expansion and quote removal
t_token *ft_tokenise(t_shell *bash, char **str_tokens)
{
	t_token *tokenlist;

	str_tokens = expand_array(bash, str_tokens);
	// print_array(tokens);
	tokenlist = create_token_list(str_tokens);
	//l may need a function to remove empty string tokens
	// if(tokenlist == NULL)
		//do something
	write_to_debugfile(ft_strjoin("","TOKENS CREATED:"));
	if(token_syntax_check(tokenlist) == false) //X2
	{
		error_status = 127;
		return (NULL);
	}
	token_quote_removal(tokenlist);
	// quote removal on each token
	return (tokenlist);
}

int count_commands(t_token *tokenlist)
{
	int i;
	t_token *temp;

	temp = tokenlist;
	i = 1;
	while (temp && temp->value != NULL)
	{
		if(temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return(i);
}

// 4. Create simple commands from the tokenlist and then free the token list at the end
void create_scmnd_array(t_shell *bash, t_token *tokenlist)
{
	t_token *temp;
	t_token *start;
	t_token *end;
	int i;

	bash->s_commands = (t_command **) malloc(sizeof(t_command *) * (count_commands(tokenlist) + 1));
	// if(!scmndList)
		//do something
	temp = tokenlist;
	start = NULL;
	end = NULL;
	i = 0;
	while(i < count_commands(tokenlist))
	{
		start = temp;
		end = temp;
		while(end->next != NULL && end->next->type != PIPE)
			end = end->next;
		bash->s_commands[i] = create_scmnd_node(start, end);
		bash->s_commands[i]->cmd_len = count_commands(tokenlist);
		if (end->next != NULL)
		{
			temp = end->next->next;
		}
		else
			temp = NULL;
		i++;
	}
	bash->s_commands[i] = NULL;
	bash->cmd_len = count_commands(tokenlist);
	free_token_list(tokenlist);
		// exit(0);
}
