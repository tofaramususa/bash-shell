/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scommand_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:56:11 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/05 21:38:38 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_commandNode *go_to_start(t_commandNode *current_node)
{
    while (current_node && current_node->prev)
        current_node = current_node->prev;
    return current_node;
}

//using the 
t_commandNode *init_command_node(t_token *start, t_token *end)
{
    t_commandNode *command;

    command = (t_commandNode *) malloc(sizeof(t_commandNode));
    if(!command)
        return(NULL);
    command->args = token_to_array(start, end);
    command->path = NULL;
    command->infile = NULL;
    command->outfile = NULL;
    command->next = NULL;
    command->prev = NULL; //might not need this
    return (command);
}


void create_command_nodes(t_token *tokenList, shellNode *shellinfo)
{
    t_token *start;
    t_token *end;
    t_token *temp;

    temp = tokenList //use to traverse through list
    start = tokenList;
    end = tokenList;
    while (temp->next != NULL)
    {
           
        while(temp->next != NULL && temp->type != PIPE)
        {
            end = end->next; //end value
            temp = temp->next;
        }
        //add the new_create simple_command at the end of the shellinfo->simple_commands list using addtoback
        add_node_to_compound_command(shellinfo->simplecommands, init_command_node(start, end)); //note we also have a previous;
        //iterate to next item if next->null
        if (temp->next != NULL && temp->type == PIPE); //skip the pipe
            temp = temp->next;
        start = temp; //
        end = temp;
    }
    //call freetokenList but we need to go to the head node
}

//We turn the tokens->values we checked for syntax and add them to an array and return the array
//need a second function which l will combine later that identifies redirs and adds it to the redir struct of the simple command, we dont want redirects in the args list
char **tokens_to_array(t_token *start, t_token *end)
{
    t_token *current_token;
    int num_args;
    char **args;
    int i;

    num_args = 0;
    i = -1;
    current_token = start;
    while (current_token != end->next)
    {
        num_args++; //change this to an if statement for when only a word then add to args
        current_token = current_token->next;
    }
    args = (char **) malloc((num_args + 1) * sizeof(char *));
    current_token = start;

    while (current_token != end->next)
    {
        args[++i] = ft_strdup(current_token->value);
        current_token = current_token->next;
    }
    args[i] == NULL;
    return(args);
}

//We add a simplecommand to the list of simple commands
void	add_node_to_compound_command(t_commandNode **lst, t_commandNode *new)
{
	t_commandNode	*to_last;

	if (*lst)
	{
		to_last = ft_lstlast(*lst);
		to_last->next = new;
		new->prev = to_last;
		new->next = NULL;
	}
	else
		*lst = new;
}