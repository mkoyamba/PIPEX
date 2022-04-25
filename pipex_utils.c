/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:31:29 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/25 18:28:37 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n])
		n++;
	return (n);
}

static int	ft_find_str(char *s1, int n)
{
	static char	s2[6] = "PATH=";
	int			i;

	i = 0;
	while (n > 0 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		n--;
		i++;
	}
	if (n == 0)
		return (1);
	else
		return (0);
}

static char	*ft_strjoin(char *str, char *cmd)
{
	size_t	a;
	size_t	b;
	char	*line;

	if (!str)
	{
		str = (char *)malloc(sizeof(char) * 1);
		if (!str || !cmd)
			return (NULL);
		str[0] = '\0';
	}
	line = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(cmd)) + 1));
	if (line == NULL)
		return (NULL);
	a = -1;
	b = 0;
	if (str)
		while (str[++a] != '\0')
			line[a] = str[a];
	while (cmd[b] != '\0')
		line[a++] = cmd[b++];
	line[ft_strlen(str) + ft_strlen(cmd)] = '\0';
	return (line);
}

static char	*path_finding(char **all_path, char **command)
{
	size_t	n;
	char	*temp;
	char	*temp2;

	n = 0;
	temp2 = NULL;
	if (!command || !command[0])
		return (NULL);
	while (all_path[n])
	{
		if (temp2)
			free(temp2);
		temp = ft_strjoin(all_path[n], "/");
		if (!temp)
			break ;
		temp2 = ft_strjoin(temp, command[0]);
		free(temp);
		if (access(temp2, F_OK) == 0)
		{
			free_tab(all_path);
			return (temp2);
		}
		n++;
	}
	if (temp2)
		return (temp2);
	free_tab(all_path);
	return (NULL);
}

char	*get_path(char **env, char **command)
{
	char		*path;
	char		**all_path;
	size_t		n;

	n = 0;
	while (env[n] && !ft_find_str(env[n], 5))
		n++;
	if (!env[n])
		return (NULL);
	path = env[n] + 5;
	all_path = split_pipex(path, ':');
	if (!all_path)
		return (NULL);
	path = path_finding(all_path, command);
	return (path);
}
