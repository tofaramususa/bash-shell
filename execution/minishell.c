
#include "minishell.c"


//write functions to start signals and write signal handlers



//the start of the execution:
/**
 * start_execution: 
*/
bool	start_execution(t_shell *bash) //function to execute and free everything
{
	if (bash->total_scommands >= 220) //calculate command length
	{
		ft_putstr_fd("Sorry too many command\n", 2); //change this
		exit(1);
	}
	if (check_and_update_heredoc(bash->s_commands, bash) == 1) //there is somekind or error here
	{
		garbage_collector(bash); //free all the functions
		return (true);
	}
	signal(SIGINT, SIG_IGN); //reset signal
	signal(SIGINT, sig_handler); //
	error_status = pipex(bash->total_scommands, bash->s_commands, bash); //here is were the execution happens
    garbage_collector(bash);
	unlink(".tmp"); //remove the tmp file
	return (false);
}

// Parse function takes a str and turns it to an array of simple commands
bool parse(t_shell bash)
{
	// char *word = "$PAT";
    char **final_result;
    add_history(bash.line);
    final_result = ft_split_on_delims(bash.line);
    if (!final_result)
	{
        return (false);	
    }
	bash.tokenlist = ft_tokenise(final_result);
	bash.s_commands = create_scmnd_array(&bash.tokenlist);
    bash.total_scommands = array_len(bash.s_commands) + 1;
    return (true);
}

//the int main
int main(int ac, char **av, char **envp)
{
    t_shell bash;

    if (ac > 1)
    exit(printf("To start [TheBash] enter: ./minishell"), 35);
    error_status = 0;
    signal(SIGQUIT, SIG_IGN);
    if(envp[0] == NULL)
        exit(printf("Error: No environment variables found"));
    ft_array_to_linked_list(envp) //convert envp to an array 
    while(1)
    {
        init_signals(); //handle the signals
        bash.line = readline ("[TheBash]$")
        if (!check_line(bash.line))
        {
            error_status = 0;
            continue ;
        }
        if(parse(bash))
        {
            start_execution(&bash)
        }
        garbage_collector(&bash);

        //parse the line
//at the end of the parsing stage we have only allocated memory for the simple commands, 
//take note we have not assigned the command line
        //execute the line
    }
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
