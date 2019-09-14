/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:10:17 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 09:25:34 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			main(int ac, char *av[])
{
	t_flag	flags;

	g_indx_arg = 1;
	flags = get_flags(ac, av);
	if (g_indx_arg == ac)
	{
		ft_ls(".", &flags);
	}
	else
	{
		while (g_indx_arg < ac)
		{
			ft_ls(av[g_indx_arg], &flags);
			g_indx_arg++;
		}
	}
	return (0);
}
