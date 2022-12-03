/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:24:13 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/02 14:57:43 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_file	*fd;
	t_args	*args;

	args = ft_parsing(argc, argv, envp);
	fd = malloc(sizeof(t_file));
	ft_open_file(argc, argv, fd, args);

	int i = 0;
	int j = 0;
	while (args[i].path)
	{
		j = 0;
		ft_printf("path = %s\n", args[i].path);
		while (args[i].command[j])
		{
			ft_printf("command = %s\n", args[i].command[j]);
			j++;
		}
		i++;
	}
	ft_get_exec(args, fd);
	ft_free_struct(args);
	free(fd);
	return (0);
}
