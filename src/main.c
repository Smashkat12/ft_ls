/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:10:17 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/09 14:40:44 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			main(int ac, char *av[])
{
	t_flag	flags;

	index_arg = 1; //represent current index of av
	flags = get_flags(ac, av);
	if (index_arg == ac)
	{
		ft_ls(".", &flags);
	}
	else
	{
		while (index_arg < ac)
		{
			ft_ls(av[index_arg], &flags);
			index_arg++;
		}
	}
	return (0);
}