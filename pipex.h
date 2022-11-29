/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:24:21 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/29 10:40:32 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"

typedef struct s_args
{
	char	*command;
	char	*param;
}	t_args;

void	ft_parsing(char **argv, char **envp);

#endif
