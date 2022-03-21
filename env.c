#include "env.h"
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#ifndef SIZE_MAX
#define SIZE_MAX 0xFFFFFFFFFFFFFFFFL
#endif

int setenv(const char *var_name, const char *new_value, int change_flag)
{
	char *putenvValue = NULL;
	size_t var_name_size = 0;
	size_t new_value_size = 0;
	size_t put_env_size = 0;

	if(var_name == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	else
	{
		var_name_size = strlen(var_name);
	}

	if(new_value == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	else
	{
		new_value_size = strlen(new_value);
	}

	if(!change_flag)
	{
#if _MSC_VER >= 1400
		const char * value = NULL;
		getenv_s( &requiredSize, NULL, 0, var_name);
		if (requiredSize != 0)
		{
			value = _alloca(sizeof (char) * (requiredSize + 1));
			if(value == NULL)
			{
				errno = ENOMEM;
				return -1;
			}

			getenv_s(&requiredSize, value, requiredSize, var_name);
		}
#else
		const char * value = getenv(var_name);
#endif
		if(value != NULL)
		{
			return 0;
		}
	}

#if _MSC_VER >= 1400
	return _putenv_s(var_name, new_value);
#else
	if(SIZE_MAX - var_name_size < new_value_size)
	{
		errno = ENOMEM;
		return -1;
	}

	put_env_size = var_name_size + new_value_size;

	if(SIZE_MAX - put_env_size < 2)
	{
		errno = ENOMEM;
		return -1;
	}

	put_env_size += 2;

	putenvValue = alloca(sizeof (char) * put_env_size);

	sprintf(putenvValue, "%s=%s", var_name, new_value);

	return _putenv(putenvValue);
#endif
}

int unsetenv(const char *name)
{
	char *putenvValue = NULL;
	size_t name_size = 0;
	size_t put_env_size = 0;

	if(name == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	else
	{
		name_size = strlen(name);
	}

#if _MSC_VER >= 1400
	return _putenv_s(name, "");
#else
	if(SIZE_MAX - name_size < 1)
	{
		errno = ENOMEM;
		return -1;
	}

	put_env_size = name_size + 1;

	putenvValue = alloca(sizeof (char) * put_env_size);

	sprintf(putenvValue, "%s=", name);

	return _putenv(putenvValue);
#endif
}