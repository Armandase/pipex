/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:22:14 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/29 18:58:25 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	ft_open_file(int argc, char **argv, t_file *fd, t_args *args)
{
	fd->fd_in = open(argv[1], O_RDONLY | O_CREAT, 0644);
	if (fd->fd_in == -1)
	{
		ft_free_struct(args);
		free(fd);
		exit(1);
	}
	fd->fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd->fd_out == -1)
	{
		ft_free_struct(args);
		free(fd);
		exit(1);
	}
}
