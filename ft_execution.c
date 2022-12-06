/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:02:48 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/05 17:09:07 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_count_pid(t_args *args)
{
	int	i;

	i = 0;
	while (args[i].path != NULL)
		i++;
	return (i);
}

void	ft_error(t_args *args, t_file *fd)
{
	perror("Error");
	ft_free_struct(args);
	free(fd);
	exit(1);
}

void	ft_init_dup(int pipe_tab[2][2], t_args *args, int i)
{
	int	ret;

	dup2(pipe_tab[(i - 1) % 2][0], 0);
	dup2(pipe_tab[i % 2][1], 1);
	ft_close_pipe(pipe_tab);
	ret = execve(args[i].path, args[i].command, NULL);
	if (ret == -1)
		perror("Execve error");
	exit(EXIT_FAILURE);
}

void	ft_open_pipe(int pipe_tab[2][2], int i)
{
	close(pipe_tab[i % 2][1]);
	close(pipe_tab[i % 2][0]);
	pipe(pipe_tab[i % 2]);
}

void	ft_get_exec(t_args *args, t_file *fd)
{
	int	i;
	int	*tab_pid;
	int	pipe_tab[2][2];

	i = ft_count_pid(args);
	tab_pid = malloc(sizeof(int) * i);
	i = 0;
	pipe(pipe_tab[0]);
	pipe(pipe_tab[1]);
	ft_first_read(pipe_tab, args, fd, &tab_pid[i]);
	i++;
	while (args[i + 1].command)
	{
		ft_open_pipe(pipe_tab, i);
		tab_pid[i] = fork();
		if (tab_pid[i] == -1)
			ft_error(args, fd);
		else if (tab_pid[i] == 0)
			ft_init_dup(pipe_tab, args, i);
		dup2(pipe_tab[i % 2][0], 0);
		i++;
	}
	ft_open_pipe(pipe_tab, i);
	ft_end_read(pipe_tab, args, fd, tab_pid, i);
	while (i >= 0)
	{
		ft_wait_end_child(args, tab_pid[i], fd);
		i--;
	}
	free(tab_pid);
}
