/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:20:14 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:22:08 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "array_methods/arrays.h"

// struct with quote flags
typedef struct t_quote
{
    bool single_q;
    bool double_q;
} t_quote;

#ifndef WORD_H
# define WORD_H

//Quote functions
bool check_unmatched_quotes(const char *str);
void set_quote_flag(t_quote *value, char c);

//functions to split
char	**ft_space(char const *s);
char	**ft_strtok(char const *s);
const char	**ft_tokenize(char *str);

#endif