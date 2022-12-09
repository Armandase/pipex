/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:22:14 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/09 10:31:33 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>

void	ft_open_file(int argc, char **argv, t_file *fd)
{
	fd->fd_in = open(argv[1], O_RDONLY);
	if (fd->fd_in == -1)
		perror("Error");
	fd->fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd->fd_out == -1)
		perror("Error");
}
