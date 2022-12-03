/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:02:48 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/02 17:22:55 by adamiens         ###   ########.fr       */
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

	dup2(pipe_tab[(i % 2) - 1][0], 0);
	dup2(pipe_tab[i % 2][1], 1);
	close(pipe_tab[(i % 2) - 1][1]);
	close(pipe_tab[(i % 2)][0]);
	ret = execve(args[i].path, args[i].command, NULL);
	if (ret == -1)
		perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_get_exec(t_args *args, t_file *fd)
{
	int	i;
	int	*tab_pid;
	int	pipe_tab[2][2];

	i = ft_count_pid(args);
	pipe(pipe_tab[0]);
	tab_pid = malloc(sizeof(int) * i);
	i = 0;
	ft_first_read(pipe_tab, args, fd, tab_pid);
	i++;
	/*while (args[i - 1].command)
	{
		if (i != 1)
			pipe(pipe_tab[0]);
		pipe(pipe_tab[1]);
		tab_pid[i] = fork();
		if (tab_pid[i] == -1)
			ft_error(args, fd);
		else if (tab_pid[i] == 0)
			ft_init_dup(pipe_tab, args, i);
		i++;
	}*/
	ft_end_read(pipe_tab, args, fd, tab_pid, i);
	ft_wait_end_child(args, tab_pid, fd);
}
