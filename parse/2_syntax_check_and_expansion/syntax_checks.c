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

static bool check_for_background(t_token *headtoken)
{
	t_token *temp;

	temp = headtoken;
	while(temp)
	{
		te
	}
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

bool	token_syntax_check(t_token *headtoken) // Check grammar rules
{
  if (!headtoken)
    return (false);                     // handle what to do if theres nothing
  if (check_sytnax(headtoken) == false) //
  {
    return (false);
  }
  return (true); // may have to change here to adjust for returns
}
