// #include "Includes/minishell.h"

// void print_array(char **str)
// {
// 	int i = -1;

// 	while(str[++i])
// 		// write_to_debugfile(ft_strjoin("array_item: ", str[i]));
// }

// void print_tokens(t_token *tokens)
// {
// 	t_token *temp;

// 	temp = tokens;
// 	while(temp)
// 	{
// 		if(temp->type == REDIR)
// 		{
// 			// write_to_debugfile(ft_strjoin("redir: ", temp->value));
// 		}
// 		if(temp->type == WORD)
// 		{
// 			// write_to_debugfile(ft_strjoin("word: ", temp->value));
// 		}
// 		if(temp->type == PIPE)
// 		{
// 			// write_to_debugfile(ft_strjoin("pipe: ", temp->value));
// 		}
// 		temp = temp->next;
// 	}
// }

// void print_redir_list(t_redir *redirs)
// {
//     t_redir *out = redirs;
//     int i;
//     char *char_i;

//     i = 1;
//     while (out)
//     {
//         char_i = ft_itoa(i);
//         // write_to_debugfile(ft_strjoin("REDIRECTION", char_i));
//         if (out->type == OUTPUT)
//             // write_to_debugfile(ft_strjoin("output to: ", out->filename));
//         else if (out->type == APPEND)
//             // write_to_debugfile(ft_strjoin("append: ", out->filename));
//         if (out->type == INPUT)
//             // write_to_debugfile(ft_strjoin("input from: ", out->filename));
//         else if (out->type == HEREDOC)
//             // write_to_debugfile(ft_strjoin("heredoc delimiter: ", out->filename));
//         out = out->next;
//         safe_free(char_i);
//     }
// }

// void print_scommands(t_command **simpleCmnds)
// {
//     int i = 0;
//     char *cmd_len; 
//     char *args_len; 
//     char *total_redirs;
//     while(simpleCmnds[i] && simpleCmnds[i] != NULL)
//     {
//         // exit(0);
//         // write_to_debugfile(ft_strjoin("","S_COMMAND CREATED:"));
//         cmd_len = ft_itoa(simpleCmnds[i]->cmd_len);
//         args_len = ft_itoa(simpleCmnds[i]->args_len);
//         total_redirs = ft_itoa(simpleCmnds[i]->total_redirs);
//         if (simpleCmnds[i]->args->array)
//         {
//             print_array(simpleCmnds[i]->args->array);
//         }
//         // write_to_debugfile(ft_strjoin("command: ", simpleCmnds[i]->cmd));
//         // write_to_debugfile(ft_strjoin("cmd_len: ", cmd_len));
//         // write_to_debugfile(ft_strjoin("args_len: ", args_len));
//         // write_to_debugfile(ft_strjoin("total_redirs: ", total_redirs));
//         print_redir_list(simpleCmnds[i]->redirs);
//         safe_free(cmd_len);
//         safe_free(args_len);
//         safe_free(total_redirs);
//         i++;
//     }
// }

// void // write_to_debugfile(char *str)
// {
//     time_t current_time;
//     struct tm *time_info;
//     char *time_string = NULL;
//     FILE *debug_file = NULL;

//     time(&current_time);
//     time_info = localtime(&current_time);
//     time_string = (char *)malloc(100 * sizeof(char));
//     if (time_string == NULL) {
//         perror("Memory allocation failed");
//         exit(1);
//     }
//     debug_file = fopen("debug.txt", "a");
//     if (debug_file == NULL) {
//         perror("Error1 opening file");
//         exit(1); // Or handle the error as needed
//     }
//     strftime(time_string,100, "%d/%m/%Y %H:%M", time_info);
//     if (debug_file != NULL) 
//     {
//         fprintf(debug_file, "%s ", time_string);
//         fprintf(debug_file, "%s\n", str);
//     }
//     safe_free(time_string);
//     if (debug_file != NULL) 
//     {
//         fclose(debug_file);
//         debug_file = NULL;
//     }
//     safe_free(str);
// }

// void // write_to_funcfile(char *str)
// {
//     time_t current_time;
//     struct tm *time_info;
//     char *time_string = NULL;
//     FILE *function_file = NULL;

//     time(&current_time);
//     time_info = localtime(&current_time);
//     time_string = (char *)malloc(20 * sizeof(char));
//     if (time_string == NULL) {
//         perror("Memory allocation failed");
//         exit(1);
//     }
//     function_file = fopen("functions.txt", "a");
//     if (function_file == NULL) {
//         perror("Error1 opening file");
//         exit(1); // Or handle the error as needed
//     }
//     strftime(time_string, 20, "%d/%m/%Y %H:%M", time_info);
//     if (function_file != NULL) 
//     {
//         fprintf(function_file, "%s ", time_string);
//         fprintf(function_file, "%s\n", str);
//     }
//     // safe_free(time_string);

//     if (function_file != NULL) 
//     {
//         fclose(function_file);
//         function_file = NULL;
//     }
// }