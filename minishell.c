/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:34:02 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/31 20:02:56 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//write functions to start signals and write signal handlers

//the start of the execution:
/**
 * start_execution: 
*/
int g_error_status = 0;

bool	start_execution(t_shell *bash, t_compound *cpmd_node) //for each compound_node
{

    // write_to_funcfile("start_execution_called");
	if (cpmd_node->cmd_len >= 220) //calculate command length
	{
		ft_putstr_fd("Sorry too many commands\n", 2); //change this
		g_error_status = 1 //this maybe problematic on exit we free everything??
        return(false);
	}
	if (check_and_update_heredoc(cpmd_node->s_commands, bash) == 1) //there is somekind or error here
	{
        //free all the functions
		return (true);
	}
	signal(SIGINT, SIG_IGN); //reset signal
	signal(SIGINT, sig_handler); //
	g_error_status = pipex(cpmd_node->cmd_len, cpmd_node->s_commands, bash); //here is were the execution happens
	unlink(".tmp"); //remove the tmp file
	return (false);
}

bool    should_execute(t_compound *node)
{
    if(temp->split_on == AND && g_error_status == 0)
            return(true);
    else if (temp->split_on == OR && g_error_status != 0)
            return(true);
    else
        return(false);
    return(false);
}

int process_parens(t_compound **nodes, int start, t_shell *bash)
{
    int end;
    int counter;

    end = start;
    counter = 0;
    while (end)
    {
        if (nodes[end]->paren == AFTER_OPEN_PAREN && counter == 0)
        {
            if(should_execute(nodes[end]))
                start_execution(bash, nodes[end]);
        }
        else if(nodes[end]->paren == AFTER_OPEN_PAREN)
        {
            end = process_parens(nodes, end, bash);
            continue ;
        }
        else
        {
            if (should_execute(nodes[end]))
                start_execution(bash, nodes[end])
            if (nodes[end]->paren == BEFORE_OPEN_PAREN)
            {
                end++;
                break;
            }
        }
        end++;
        counter++;
    }


    return(end);
}

void    execute(t_shell *bash)
{
    t_compound **temp;
    int i;

    temp = bash->cmpd_node;
    i = 0;

    while(temp[i])
    {
        if(temp[i]->paren == AFTER_OPEN_PAREN)
        {
            i = process_parens(temp, i, bash);
            continue ;
        }
        else if(i == 0)
            start_execution(bash, temp[i]);
        else if (temp[i] && should_execute(temp[i]))
            start_execution(bash, temp[i]);
        i++;
    }
}

// Parse function takes a str and turns it to an array of simple commands
bool parse(t_shell *bash)
{
	// char *word = "$PAT";
    // write_to_funcfile("parse function called");
    char **final_result;
    if (!check_line(bash->line)) //no memory allocation
    {
        return (false);
    }
    add_history(bash->line);
    final_result = ft_split_on_delims(bash->line); //memory allocation here
    // write_to_debugfile(ft_strjoin("","ARRAY CREATED"));
    // print_array(final_result);
    if (!final_result)
	{
        return (false);
    }
	bash->tokenlist = ft_tokenise(bash, final_result); //memory allocation here;
    if (!bash->tokenlist)
        return(false);
    // print_tokens(bash->tokenlist);
	create_scmnd_array(bash, bash->tokenlist); //here we have the tokenlist left
    // print_scommands(bash->s_commands);
    // garbage_collector(&bash); //at this point we have allocated tokenlist and scmnd_array
    // free_env_list(&bash->env_list);
    return (true);
}

void init_bash(t_shell *bash) //set different values;
{
    bash->dont = 0; //convert envp to an array 
    bash->s_commands = NULL;
    bash->env_vars = NULL;
    bash->temp_list = NULL;
    bash->line = NULL;
    bash->tokenlist = NULL;
    bash->isfreed = false;
}

void line_prompt(t_shell *bash)
{
    char *temp_str;
    char *prompt;

    prompt = NULL;
    temp_str = NULL;
    if(g_error_status == 0)
    {
        temp_str = ft_strjoin("🏀", getcwd(bash->pwd, 1024));
        prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
        bash->line = readline(prompt);
    }
    else
    {
        temp_str = ft_strjoin("🗑️ ", getcwd(bash->pwd, 1024));
        prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
        bash->line = readline (prompt);
    }
    if(prompt)
        safe_free(prompt);
    if(temp_str)
        safe_free(temp_str);
}
//the int main
int main(int ac, char **av, char **envp)
{
    t_shell *bash; //initialise the shell instance

    if(envp[0] == NULL) //no evnp variables
        exit(printf("Error: No environment variables found"));
    if (ac > 1 || ft_array_len(av) > 1) //can only run with no parameter
    exit(printf("To start x1b[38;5;122m[TheBash]$\x1b[0m enter: ./minishell"));
	bash = (t_shell *) malloc(sizeof(t_shell)); //allocate the memory for the struct
    if(!bash)
        exit(printf("Memory allocation failure"));
    signal(SIGQUIT, SIG_IGN); //ignore any signals given by the user
    create_envlist(bash, envp); //use the environment variables to create linked list
    while(1)
    {
        init_bash(bash);
        init_signals(); //handle the signals
        line_prompt(bash);
        // write_to_debugfile(ft_strjoin("","----------------------"));
        // write_to_debugfile(ft_strjoin("COMMAND: ", bash->line));
        if(parse(bash))
        {
            execute(bash);
        }
        garbage_collector(&bash);
    }
        free_env_list(&bash->env_list);
        free(bash);
}

//what we need to free for free_shell:
//the exit points: at each exit point we need to update the exit status
//X0 - signals to interrupt the function
//X1 -- when the string contains nothing, nothing has been allocated yet;
//X2 -- when the syntax check fails, at this point we have a linked_list of envp and array of envp; also have the tokenlist and array of tokens;
// -- X3 considering the bonus we may need the no matches found exit;
// X4 -- This is the final step of where we search for commands if they are there, if the word is not found then we need to exit, there are cases where there no commands just redirections
// X5 -- If too many commands have been entered -- at the start of execution we have the environment variables and the simple commands


// Free the s_commands. The key is that we need to iterate to every allocated thing but check if its not NULL then we free
//items to free are the command, the path which are strings, the args which are an array, then go into redirections 
// and free the filename and the heredoc_data;
