

/*Quotes Struct*/
typedef struct s_quote
{
    bool single_q;
    bool double_q;
} t_quote;

/*Tokens Struct*/
typedef enum 
{
    WORD,
    REDIR,
    PIPE,
}   token_type;

typedef struct s_token
{
    token_type type;
    char *value;
    struct t_token *next;
} t_token;

/*Simple Command and Redirections Struct*/
typedef enum {
    INPUT,
    OUTPUT,
    APPEND,
    HEREDOC,
} t_redir_type;

typedef struct s_redir {
    t_redir_type type;
    char *filename;
    struct t_redir *next;
} t_redir;

typedef struct s_command 
{
	char *cmd;
    int  cmd_len;
    int args_len;
    char **args;
    int total_redirs;
    t_redir *redirs;
} t_command;

typedef struct s_shell
{

    t_command *s_commands;
    char **env_vars;
    t_list *env_list;
    int total_scommands;
    int error_no;
    char pwd[1024];
    int fd[256][2];
    int pid1;
    int pid2;
    int total_pipes;
    int middle_scommand;
    int scommand_index;
    int counter;
    int process_id //id1
    int process_id1
    char *line;
    t_token *tokenlist;
    t_list temp_list;
    int flag;
    int flag_out;
    int flag_in;
    int check;
    int x;

} t_shell;

typedef struct s_heredoc_var //structure for heredoc
{
	int		file1; //thinking file descriptor
	char	*tmp; //not sure
	char	*delimiter; //not sure
	int		ret; //not sure
}	t_heredoc_var; //not sure

typedef struct s_exp_var
{
	char		*cp;
	char		*tmp;
	char		*tmp_ex;
	int			x;
	int			y;
	int			start;
	int			flag_sq;
	int			flag_dq;
	int			flag_pwd;
	int			flag_shlvl;
	int			flag_oldpwd;
	int			flag;
	int			last_index;
	int			last_pos;
	t_list		*tmp_list;

}		t_exp_var; //this may be about expansion variables


int error_status;