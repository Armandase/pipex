/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:54:19 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/03 19:16:01 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_index_free_struct(t_args *args, int max)
{
	int	i;
	int	j;

	i = 0;
	while (args[i].command && i < max)
	{
		j = 0;
		while (args[i].command[j])
		{
			free(args[i].command[j]);
			j++;
		}
		free(args[i].command);
		i++;
	}
	i = 0;
	while (args[i].path && i < max)
	{
		free(args[i].path);
		i++;
	}
	if (args)
		free(args);
}

void	ft_exit_error(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	exit(1);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	ft_free_struct(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i].command)
	{
		j = 0;
		while (args[i].command[j])
		{
			free(args[i].command[j]);
			j++;
		}
		free(args[i].command);
		i++;
	}
	i = 0;
	while (args[i].path)
	{
		free(args[i].path);
		i++;
	}
	if (args)
		free(args);
}
