/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:59:07 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/30 18:57:39 by marvin           ###   ########.fr       */
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
	// write_to_debugfile(ft_strjoin("","TOKENS CREATED:"));
	if(token_syntax_check(tokenlist) == false) //X2
	{
		g_error_status = 127;
		free_array(str_tokens);
		return (NULL);
	}
	token_quote_removal(tokenlist);
	// quote removal on each token
	free_array(str_tokens);
	return (tokenlist);
}

int count_commands(t_token *start, t_token *end)
{
	int i;
	t_token *temp;

	temp = start;
	i = 1;
	while (temp && temp->value != NULL && temp != end->next)
	{
		if(temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return(i);
}

// 4. Create simple commands from the tokenlist and then free the token list at the end
void create_scmnd_array(t_compound *node, t_token *start, t_token *end , t_token_type split_on)
{
	t_token *temp;
	t_token *temp_start;
	t_token *temp_end;
	int i;

	node->s_commands = (t_command **) malloc(sizeof(t_command *) * (count_commands(start, end) + 1));
	// if(!scmndList)
		//do something
	temp = start;
	temp_start = NULL;
	temp_end = NULL;
	i = -1;
	while(++i < count_commands(start, end))
	{
		temp_start = temp;
		temp_end = temp;
		while(temp_end->next != NULL && temp_end->next->type != PIPE)
			temp_end = temp_end->next;
		node->s_commands[i] = create_scmnd_node(temp_start, temp_end);
		node->s_commands[i]->cmd_len = count_commands(start, end);
		node->s_commands[i]->isfreed = false;
		if (temp_end->next != NULL)
		{
			temp = temp_end->next->next;
		}
		else
			temp = NULL;
	}
	node->split_on = split_on;
	node->s_commands[i] = NULL;
	node->cmd_len = count_commands(start, end);
	// free_token_list(tokenlist);
		// exit(0);
}
