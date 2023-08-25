/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scommand_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:56:11 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/12 18:23:29 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parse.h"

//in our tokens list we know the start and stop of our simple command now we parse it to the tokens into our simple commands
t_command create_scmnd_node(t_token *start, t_token *end)
{
    t_command *command;

    command = malloc(sizeof(t_command));
    if (!command)
        return(NULL);
    command.redir = NULL;
    command.cmd = NULL;
    command.args = NULL;
    command.command = NULL;
    fill_scmnd(&command, start, end);
    return (command);
}


static void add_token_to_args(t_command *scommand, t_token *current_token)
{
    char **temp_array;

    if (scommand->args == NULL) //create our initial array with the first word
    {
        scommand->args = (char **)malloc(sizeof(char *) * 2); //create malloc function;;
        scommand->args[0] = ft_strdup(current_token->value);
        scommand->args[1] = NULL; 
    }
    else
    {
        temp_array = (char **)malloc(sizeof(char *) * 2);
        temp_array[0] = ft_strdup(current_token->value);
        temp_array[1] =  NULL;;
        scommand->args = append_array(scommand->args, temp_array);// l need to understand something here, where is the copy of ft_strdup store and how do l free it
        free_array(temp_array);
    }
}

    //else we add to args array, then we take the first arg and make a copy of that for char *command;
void fill_scmnd(t_command *scommand, t_token *start, t_token *end)
{
    t_token *current_token;

    current_token = start;
    while(current_token && current_token != end->next)
    {
        if(current_token->type == REDIR)
        {
            fill_redirs(scommand, current_token, current_token->next); //fill redirection str struct with redirection and file name;
            current_token = current_token->next->next; //skip the next two;
        }
    //add array to while not at the end no redirection found;
        while (current_token && (current_token != end->next && current_token->type != REDIR))
        {
            add_token_to_args(scommand, current_token);
            current_token = current_token->next;
        }
    }
    scommand->cmd = scommand->args[0];
}

// We add a simplecommand to the list of simple commands, like lstaddtoback;
// static t_command *get_to_last(t_command *node)
// {
// 	t_command	*to_last;

// 	to_last = node;
// 	while (to_last != NULL && to_last->next != NULL)
// 		to_last = to_last->next;
// 	return (to_last);
// }

// void	add_to_scmnd_list(t_command **cmndList, t_command *newCommand)
// {
// 	t_command	*to_last;

// 	if (*cmndList)
// 	{
// 		to_last = get_to_last(*cmndList); //we cannot use the actual ftlstlast but create own version
// 		to_last->next = newCommand;
// 		newCommand->next = NULL;
// 	}
// 	else
// 		*cmndList = newCommand;
// }

//need to create a function to free the simple commands create
