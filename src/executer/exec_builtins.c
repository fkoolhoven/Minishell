/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exec_builtins.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/18 09:57:46 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/18 14:31:35 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* st_give_cmnd_nopath:
   		-INPUT:		a non-empty command of type t_command
		-OUTPUT:	a string containing the command without its path 
		-WORKINGS:	first the command is split with char '/', because every
					command path contains this character
					if this goes well, the function iterates through the string array 
					to find the last element in the array (because this will be the command)
					the array is freed and a duplicate (which is allocated) of the command is returned 
					if something went wrong, the function returns NULL 

		-PROBLEMS:	1.	Some unforeseen problems may arrise with this function due to using ft_split(...)
						if the command has a special name with '/' in it.
					2. 	... 
*/
static char	*st_give_cmnd_nopath(t_command *command)
{
	char	**no_path_cmnd;
	char	*return_str;
	int		i;

	if (command == NULL)
		return (NULL);
	if (command->command == NULL)
		return (NULL);
	no_path_cmnd = ft_split((command->command)[0], '/');
	if (no_path_cmnd == NULL)
		return ((command->command)[0]);
	i = 0;
	while (no_path_cmnd[i])
	{
		if (no_path_cmnd[i + 1] == NULL)
		{
			return_str = ft_strdup((const char *)no_path_cmnd[i]);
			return (ft_free_str_array(no_path_cmnd), return_str);
		}
		i++;
	}
	ft_free_str_array(no_path_cmnd);
	return (NULL);
}

/* check_if_builtin:
   		-INPUT:		a variable of type t_exec_var and t_command
		-OUTPUT:	an integer, 
					this integer is -2 if something went wrong
					-1 if the command is not a builtin 
					>= 0 if it is a builtin, 
					indicating which builtin in the order defined in this function
		-WORKINGS:	first the command without its path is obtained by calling st_give_cmnd_nopath()
					We use this to iterate through the string array builtins and 
					compare the command to the strings in this array using ft_strncmp()
					If the command is the same as one of the strings in builtins[] then
					the index is returned 
					Otherwise, it goes on to check the rest until the end of builtins[].
*/
int	check_if_builtin(t_exec_var *var, t_command *command)
{
	const char	*builtins[]={"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	const char	*no_path_cmnd;
	int			i;

	if (var == NULL || command == NULL)
		return (-2);
	no_path_cmnd = (const char *)st_give_cmnd_nopath(command);
	if (no_path_cmnd == NULL)
		return (-2);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(builtins[i], no_path_cmnd, ft_strlen(no_path_cmnd)) == 0)
			return (free(no_path_cmnd), i);
		i++;
	}
	return (free(no_path_cmnd), -1);
}

/* execute_builtin:
   		-INPUT:		t_exec_var, t_command and integer
		-OUTPUT:	return value of the correct builtin function
		-WORKINGS:	this function makes a jumptable, which contains 
					pointers to the builtin functions
					The integer bltin is the index which has been calculated before by
					calling check_if_builtin() 
		-PROBLEM:	1. 	This function does not exit, so if it is called in a process
						you should call it as exit(execute_builtin(...)) because then
						it exits with the correct exit value
*/

int	execute_builtin(t_exec_var *var, t_command *cmnd, int bltin)
{
	t_f_bltin 	jmptbl[7];

	jmptbl[0] = &cd;
	jmptbl[1] = &echo;
	jmptbl[2] = &env;
	jmptbl[3] = &exit;
	jmptbl[4] = &export;
	jmptbl[5] = &pwd;
	jmptbl[6] = &unset;

	if (bltin >= 0 && bltin <= 6)
		return (jmptbl[bltin](var, cmnd));
	else
		return (jmptbl[(bltin % 7)](var, cmnd));
}
