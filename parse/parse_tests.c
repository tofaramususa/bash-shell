/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:28:13 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/16 16:07:34 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"

void print_array(char **str)
{
	int i = -1;
	
	while(str[++i])
		printf("%d: %s\n", i + 1, str[i]);
}

void print_tokens(t_token *tokens)
{
	t_token *temp;

	temp = tokens;
	while(temp)
	{
		if(temp->type == REDIR)
		{
			printf("REDIR: %s\n", temp->value);
		}
		if(temp->type == WORD)
		{
			printf("WORD: %s\n", temp->value);
		}
		if(temp->type == PIPE)
		{
			printf("PIPE: %s\n", temp->value);
		}
		temp = temp->next;
	}
}

void print_redir_list(t_command *scommand)
{
    t_redir *out = scommand->outfile;
    t_redir *in = scommand->infile;

	printf("\nAll OUTFILES:\n");
    while (out) {
        if (out->type == OUTPUT)
            printf("OUTPUT TO-> \"%s\"\n", out->filename);
        else if (out->type == APPEND)
            printf("APPEND TO-> \"%s\"\n", out->filename);
        out = out->next;
    }
	printf("\nAll INFILES:\n");
    while (in) {
        if (in->type == INPUT)
            printf("INPUT FROM-> \"%s\"\n", in->filename);
        else if (in->type == HEREDOC)
            printf("HEREDOC EOF-> \"%s\"\n", in->filename);
        in = in->next;
    }
}

int main(int ac, char **av)
{
	// char *word = "$PAT";
    char **final_result;
	t_token *tokenlist;
	t_command **simpleCmnds;
	int i = 0;

	if(ac < 2)
		return(1);
	(void)ac;
	if(check_line(av[1]) == false)
		return (1);
    final_result = ft_split_on_delims(av[1]);
    if (!final_result)
	{
        return (1);	
	}
	printf("SPLIT ON METAS:\n");
	print_array(final_result);
	tokenlist = ft_tokenise(final_result);
	printf("                             \n");
	printf("TOKENS WITH TYPES:           \n");
	print_tokens(tokenlist);
	simpleCmnds = create_scmnd_array(&tokenlist);
	while(simpleCmnds[i] && simpleCmnds[i] != NULL)
	{
		printf("                             \n");
		printf("SIMPLE COMMANDS %d      \n", i + 1);
		printf("-------------------\n");
		if (simpleCmnds[i]->args)
		{
			printf("ARGS TO EXECUTE:\n ");
			print_array(simpleCmnds[i]->args);
		}
		printf("REDIRECTIONS:         \n");
		printf("-------------------\n");
		print_redir_list(simpleCmnds[i]);
		i++;
	}
    return (0);
}