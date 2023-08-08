/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:12:17 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/05 21:36:03 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int token_syntax_check(t_token *headToken) // Check grammar rules
{
    if(!headToken)
        return (NULL); //handle what to do if theres nothing
    if (check_sytnax(headToken) == false) //
        return (printf("Sytnax error near %s", headToken), NULL);
}

//
bool check_sytnax(t_token *headToken)
{
    t_token *temp;

    if(!headToken)
    //return something
    temp = headToken;
    if(temp->type == PIPE && temp) //NOTE that a redirection can be at the start but pipe cant
        return (false);
    // else if(temp->type == WORD)
     //     check if the command is valid
     while(temp->next != NULL)
    {
        if ((temp->type == REDIR || temp->type == PIPE) && temp->next != WORD) //there has to be word after a redirection or pipe else error
            return (false);
        temp = temp->next;
    }
    if(temp->next == NULL) //so we are at the end and we need to make sure the last thing is a word
    {
        if(temp->type != WORD)
            return (false);
    }
    return true;
 }