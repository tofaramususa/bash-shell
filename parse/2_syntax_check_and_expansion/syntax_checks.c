/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:12:17 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/31 20:45:32 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static bool check_parens_match(t_token *headtoken)
{
    t_token *temp;
    int stack;

    temp = headtoken;
    stack = 0;

    while(temp)
    {
      if(temp->type == OPEN_PAREN)
        stack += 1;
      if(temp->type == CLOSE_PAREN)
        stack -= 1;
      temp = temp->next;
    }
    return(stack == 0);
}

static bool check_for_background(t_token *headtoken)
{
	t_token *temp;

	temp = headtoken;
	while(temp)
	{
    if(ft_strcmp(temp->value, "&") == 0)
      return (printf("Bash: background processes not supported %c\n", temp->value[0]), false);
		temp = temp->next;
	}
  return(true);
}

// check the sytnax
static bool	check_sytnax(t_token *headtoken)
{
  t_token *temp;

  // if(!headtoken)
  // return something
  temp = headtoken;
  if (temp && (temp->type == PIPE || temp->type == AND || temp->type == OR)) // NOTE that a redirection can be at the start but pipe cant
  {
    return (false);
  }
  // else if(temp->type == WORD)
  //     check if the command is valid
  while (temp && temp->next != NULL)
  {
    if (temp->type == REDIR && temp->next->type != WORD)
      return (printf("Parse error near %c\n", temp->value[0]), false);
    if ((temp->type == PIPE || temp->type == AND || temp->type == OR) \
			&& !(temp->type == WORD || temp->type == REDIR))
      return (printf("Parse error near %c\n", temp->value[0]), false);
    temp = temp->next;
  }
  if (temp->next == NULL)
  {
    if (temp->type != WORD)
      return (printf("Parse error near \\n\n"), false);
  }
  return (true);
}

//handle paren parse errors; -- we cannot have a type paren next to type pipe, and or
// we can though have a type pipe, or, and after closing paren and  before type opening paren
//only things that can be after close paren is and, or, pipe and we have reached the end

bool	token_syntax_check(t_token *headtoken) // Check grammar rules // we may need to check grammar rules for each type. Note that parens open and close paren cannot be next to each other
{
  if (!headtoken)
    return (false);
  if(check_parens_match(headtoken) == false || check_for_background(headtoken) == false)
      return (false);                     // handle what to do if theres nothing
  if (check_sytnax(headtoken) == false) //
    return (false);
  return (true); // may have to change here to adjust for returns
}
