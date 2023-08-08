/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:04:11 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/04 18:05:05 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../1_words_and_operators/words.h"
# include <stdlib.h>

#ifndef EXPAN_H
# define EXPAN_H

//Main function
char **expand_array(char **str);

//helpers
bool needs_expansion(char *str);
int	get_end_index_expan(char *str, int start);
char *strjoin_env_var(char *temp_str, char *expanded_str, int count);
int get_search_var_end(char *str, int start);

#endif


