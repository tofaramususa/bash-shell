/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:57:26 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 21:58:19 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "words.h"

//this function is where we get from a single line to a array for the next stage
//after we remove spaces, we get an array, and we need to go inside each element and further split it on metacharacters
const char	**ft_tokenize(char *str)
{
	char	**temp_tokens; //temporary store of initial array produced from removing spaces
	const char	**final_tokens; //our return value with seperated array
	const char	**next_tokens; 
	int		i;

	i = 0;
    if (check_unmatched_quotes(str) == true) //if true we need to return a syntax error
        return (printf("unbalanced quotes"), NULL);
    temp_tokens = ft_space(str); //remove spaces
    if (temp_tokens == NULL)
        return (NULL);
	while (temp_tokens[i] != NULL)
	{
        if (i == 0)
		    final_tokens = (const char **) ft_strtok(temp_tokens[i]); //add the first split array to final
        else
        {
            next_tokens =  (const char **) ft_strtok(temp_tokens[i]); //retrieve a new split array
            final_tokens = (const char **) append_array(final_tokens, next_tokens); //append that array to our final_tokens, like strjoin but for array
            free_array((char **) (next_tokens)); //free the array produced from ft_strtok so we can use the variable when the loop com
        }
            i++;
	}
	return (free_array((char **) temp_tokens), final_tokens); //no longer need array from ft_space at this point we have one malloced array
}


// int main(int ac, char **av)
// {
//     int i = -1;

//     char *test = "exit | exit | ckuvfrdku | exit 66";
//     const char **final_result;

//     if (ac < 1 || av[1] != NULL)
//         return(1);
//     // final_result = ft_space((const char *) test);
//     // if (!final_result)
//     //     return (1);
//     // while(final_result[++i])
//     //         printf("%s\n", final_result[i]);
//     final_result = ft_tokenize(test);
//     if (!final_result)
//         return (1);
//     while(final_result[++i])
//             printf("%s\n", final_result[i]);
//     return (0);
// }

// int main(int ac, char **av)
// {
//     int i = -1;

//     char *test = "   ' word  ";
//     const char **final_result;

//     if (ac < 1 || av[1] != NULL)
//         return(1);
//     final_result = (const char **) ft_tokenize(test);
//     if (!final_result)
//         return (1);
//     while(final_result[++i])
//             printf("%s\n,", final_result[i]);
//     return (0);
// }