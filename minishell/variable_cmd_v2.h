#ifndef __VARIABLE_CMD_V2__
#define __VARIABLE_CMD_V2__

extern int env_num;
extern char **environ;
extern char **minishell_var;

int is_variable_cmd(char *argv[]);
int env_init_cmd(char **minishell_var);
int env_free_cmd(char **minishell_var);
int run_set_cmd(char **minishell_var);
int run_unset_cmd(char *argv[], char **minishell_var);
int run_equal_cmd(char *argv[], char **minishell_var);
int run_variable_cmd(char *argv[], char **minishell_var);

#endif
