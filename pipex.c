/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:08:23 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/04/04 20:31:22 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pip(int *pip, int n)
{
	if (n == 0)
		close(pip[0]);
	if (n == 1)
		close(pip[1]);
	perror("Problème de malloc!");
}

static void	child(int *pip ,char **env, char *cmd, int fd1)
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
	execve(path ,command, env);
	free_tab(command);
	free(path);
	perror("Problème lors de l'execution de la première commande");
}

static void	parent(int *pip, char **env, char *cmd, int fd2)
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
	execve(path ,command, env);
	free_tab(command);
	free(path);
	perror("Problème lors de l'execution de la deuxième commande");
}

void	ft_pipex(int fd1, int fd2, char **av, char **env)
{
	pid_t	pid;
	int		pip[2];

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
		waitpid(pid, NULL, 0);
		parent(pip, env, av[3], fd2);
		if (fd1 > 2)
			close(fd1);
		if (fd2 > 2)
			close(fd2);
	}
}