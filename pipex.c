/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:23 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/25 18:29:55 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pip(int *pip, int n)
{
	if (n == 0)
		close(pip[0]);
	if (n == 1)
		close(pip[1]);
}

static void	child(int *pip, char **env, char *cmd, int fd1)
{
	char	**command;
	char	*path;

	close(pip[0]);
	command = split_pipex(cmd, ' ');
	if (!command)
		close_pip(pip, 1);
	path = get_path(env, command);
	if (!path)
	{
		free_tab(command);
		close_pip(pip, 1);
	}
	dup2(fd1, STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	execve(path, command, env);
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

static int	parent(int *pip, char **env, char *cmd, int fd2)
{
	char	**command;
	char	*path;

	close(pip[1]);
	command = split_pipex(cmd, ' ');
	if (!command)
		close_pip(pip, 0);
	path = get_path(env, command);
	if (!path)
	{
		free_tab(command);
		close_pip(pip, 0);
	}
	dup2(pip[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(pip[0]);
	execve(path, command, env);
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (1);
}

int	ft_pipex(int fd1, int fd2, char **av, char **env)
{
	int		result;
	pid_t	pid;
	int		pip[2];

	result = 0;
	pipe(pip);
	pid = fork();
	if (pid < 0)
	{
		close(fd1);
		close(fd2);
		error_out(ERROR_FORK);
	}
	if (!pid)
		child(pip, env, av[2], fd1);
	else
	{
		result = parent(pip, env, av[3], fd2);
		if (fd1 > 2)
			close(fd1);
		if (fd2 > 2)
			close(fd2);
	}
	return (result);
}
