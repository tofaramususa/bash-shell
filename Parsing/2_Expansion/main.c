/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:10:25 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/04 18:11:23 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int main(int ac, char **av)
{
    int i = -1;

    char *test = "\"word$_'s\"";
    const char **final_result;
    char **expanded_result;

    if (ac < 1 || av[1] != NULL)
        return(1);
    // final_result = ft_space((const char *) test);
    // if (!final_result)
    //     return (1);
    // while(final_result[++i])
    //         printf("%s\n", final_result[i]);
    final_result = ft_tokenize(test);
    if (!final_result) //if we dont handle the case for NULL then we will have segfaults, need to handle the case for every return
        return (1);
    // while(final_result[++i])
    //         printf("%s\n", final_result[i]);
    expanded_result = expand_array((char **) final_result);
    i = -1;
    while(expanded_result[++i])
            printf("%s\n", expanded_result[i]);
    return (0);
}


// int main(int ac, char **av)
// {
//     int i = 0;
//     char **final_result;
// char *test[2][3] = {
//     { "This is a \"'\"$WORD'\"'test. $WORD\0", "Another $VAR1 test.\0", NULL},
//     { "This is a $VAR2 test.\0", "Another $VAR2 test.\0", NULL},
// };

//                 // exit(0);
//     final_result = expand_array(test[0]);

//     if (ac < 1 || av[1] != NULL)
//         return(1);
//     if (!final_result)
//         return (1);
//     while(final_result[i])
//     {
//         if (!final_result[i + 1])
//             printf("%s", final_result[i]);
//         else
//             printf("%s,", final_result[i]);
//         i++;
//     }
//     printf("\n");
//     return (0);
// }