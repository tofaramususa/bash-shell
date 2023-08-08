/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:48:42 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/04 17:52:54 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

//not sure if l am using enum the right way
typedef enum 
{
    WORD,
    REDIR,
    PIPE,
}   token_type;

typedef struct t_token
{
    token_type type;
    char *value;
    struct t_token *next;
} t_token;
