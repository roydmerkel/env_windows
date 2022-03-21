#ifndef ENV_H
#define ENV_H

int setenv(const char *var_name, const char *new_value, int change_flag);
int unsetenv(const char *name);

#endif // #ifndef ENV_H