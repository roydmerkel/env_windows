#ifndef ENV_H
#define ENV_H

#if defined(__cplusplus)
extern "C" {
#endif
int setenv(const char *var_name, const char *new_value, int change_flag);
int unsetenv(const char *name);
#if defined(__cplusplus)
}
#endif

#endif // #ifndef ENV_H
