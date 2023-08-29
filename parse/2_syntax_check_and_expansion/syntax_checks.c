/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:12:17 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 17:09:16 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// check the sytnax
static bool	check_sytnax(t_token *headToken) {
  t_token *temp;

  // if(!headToken)
  // return something
  temp = headToken;
  if (temp &&
      temp->type ==
          PIPE) // NOTE that a redirection can be at the start but pipe cant
  {
    return (false);
  }
  // else if(temp->type == WORD)
  //     check if the command is valid
  while (temp && temp->next != NULL) {
    if (temp->type == REDIR &&
        temp->next->type !=
            WORD) // there has to be word after a redirection or pipe else error
      return (printf("Parse error near %c\n", temp->value[0]), false);
    if ((temp->type == PIPE) && temp->next->type == PIPE)
      return (printf("Parse error near %c\n", temp->value[0]), false);
    temp = temp->next;
  }
  if (temp->next == NULL) // so we are at the end and we need to make sure the   // last thing is a word
  {
    if (temp->type != WORD)
      return (printf("Parse error near \\n\n"), false);
  }
  return (true);
}

bool	token_syntax_check(t_token *headToken) // Check grammar rules
{
  if (!headToken)
    return (false);                     // handle what to do if theres nothing
  if (check_sytnax(headToken) == false) //
  {
    return (false);
  }
  return (true); // may have to change here to adjust for returns
}
