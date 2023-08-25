
//function to free string:
void free_str(void *str)
{
    if(str)
        free(str);
    str = NULL;
}

//function to free t_list list which is in libft envrionement variables and free_array env
void	free_env_list(t_list *head)
{
	t_list	*current;
	t_list	*next;
	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_str(current->key);
		free_str(current->value);
		free_str(current);
		current = next;
	}
	head = NULL;
}
//function to free redirections list which means calling filename/ free_str
void free_redirs_list(t_redir *redirlist)
{
    t_redir *current_node;
    t_redir *next_node;

    current_node = redirlist;
    if (tokenlist)
    {
        while (current_node)
        {
            next_node = current_node->next;
            free_str(filename);
            current_node = next_node;
        }
        *redirlist = NULL;
    }
}
//function to free_simple commands which simple commands
// free_str command and path, free_array for args, call free redirs
void free_scommand(t_command *s_commands)
{
    int i;

    i = -1;
    while(s_commands[++i])
    {
        free_str(s_commands[i]->cmd);
        free_str(s_commands[i]->path);
        free_array(s_commands[i]->args);
        free_redirs_list(s_commands[i]->redirs);
    }
    s_commands = NULL;
}

//function to free the shell which calls environment array and environment linked list, function to free s_commands, 

//function to free 

//memory recovery function;

void garbage_collector(t_shell *bash)
{
    if(bash)
    {
        //call function to free env_vars;
        free_array(bash->env_vars);
        //call function to free s_commands;
        free_scommand(bash->s_commands);
        //call function to free env_list;
        free_env_list(bash->env_list);
        //call function to free line;
        free_str(bash->line);
        //call function to free token;
        free_token_list(bash->tokenlist);
    }

}