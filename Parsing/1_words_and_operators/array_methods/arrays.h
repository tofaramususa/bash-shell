/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:24:36 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:46:34 by tmususa          ###   ########.fr       */
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
#include  "../../Libft/libft.h"

#ifndef ARRAY_H
# define ARRAY_H

void free_array(char **array);
int ft_array_len(const char **str);
char **append_array(char const **s1, char const **s2);
bool	array_strchr(const char *s, char c);

#endif