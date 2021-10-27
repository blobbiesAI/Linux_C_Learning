#ifndef __VARIABLE_CMD__
#define __VARIABLE__CMD__


typedef struct env{
         char name[10];
         char val[20];
}env;

int is_variable_cmd(char *argv[]);
int run_set_cmd(env wxb_env[]);
int run_unset_cmd(char *argv[], env wxb_env[]);
int run_equal_cmd(char *argv[], env wxb_env[]);
int run_variable_cmd(char *argv[], env wxb_env[]);

#endif
