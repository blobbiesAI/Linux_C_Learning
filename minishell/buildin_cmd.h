#ifndef __BUILDIN_CMD__
#define __BUILDIN_CMD__

int buildin_cd_cmd(char *args[]);
int build_exit_cmd(char *args[], char **minishell_var);
int read_analyse_buildin_cmd(char *args[], char **minishell_var);

#endif
