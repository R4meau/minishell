/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:16:55 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/20 01:15:45 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_env(void)
{
	int     i;

	i = -1;
	while (g_envv[++i])
		ft_putendl(g_envv[i]);
}

int    find_env_var(char *var)
{
	int     i;
	char	*tmp;

	i = -1;
	while (g_envv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(g_envv[i], tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (i);
}

/*
*
* Returns the environment value of the variable name to find
*
* @param	var		The variable name to find
* @return	NULL if var wasn't found, or a pointer to
*			the value of var in the environment
*/
char	*get_env_var(char *var)
{
	int     i;

	i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], ft_strjoinch(var, '='))) // free this mem
			return (ft_strchr(g_envv[i], '=') + 1);
	}
	return (NULL);
}

char	**realloc_envv(int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (g_envv[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_envv[i]);
		free(g_envv[i]);
	}
	free(g_envv);
	return (new);
}

void	set_env_var(char *key, char *value)
{
	int		pos;
	char	*tmp;

	pos = find_env_var(key);
	tmp = ft_strjoin("=", value);
	if (g_envv[pos])
	{
		free(g_envv[pos]);
		if (value)
			g_envv[pos] = ft_strjoin(key, tmp);
		else
			g_envv[pos] = ft_strjoin(key, "=");
	}
	else
	{
		g_envv = realloc_envv(pos + 1);
		if (value)
			g_envv[pos] = ft_strjoin(key, tmp);
		else
			g_envv[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}

/*
** Executes the setenv builtin command, takes the format 'VAR_NAME VAR_VALUE',
** not 'VAR_NAME=VAR_VALUE', when called with no arguments, it prints all the
** environment variables, just like env, otherwise, it parses the arguments and
** prints accordingly
**
** @param		args	The arguments to pass to setenv
** @returns		1 on completion
*/
int    setenv_builtin(char **args)
{
	if (!args[0])
	{
		print_env();
		return (1);
	}
	if (args[2])
	{
		ft_putendl("setenv: Too many arguments.");
		return (1);
	}
	set_env_var(args[0], args[1]);
	return (1);
}
