/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:20:34 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 09:29:59 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_flag			init_flags(void)
{
	t_flag		flags;

	flags.a = 0;
	flags.cap_a = 0;
	flags.l = 0;
	flags.cap_r = 0;
	flags.r = 0;
	flags.f = 0;
	flags.u = 0;
	flags.c = 0;
	flags.t = 0;
	flags.one = 0;
	return (flags);
}

char			get_opts(int ac, char **av, char *flags_str)
{
	static int	nextflag;
	int			i;

	i = 0;
	if (g_indx_arg >= ac || av[g_indx_arg][0] != '-')
		return (-1);
	nextflag++;
	while (i < (int)ft_strlen(flags_str))
	{
		if (av[g_indx_arg][nextflag] == flags_str[i])
		{
			if ((av[g_indx_arg][nextflag + 1]) == '\0')
			{
				g_indx_arg++;
				nextflag = 0;
			}
			return (flags_str[i]);
		}
		i++;
	}
	g_char_not_flag = av[g_indx_arg][nextflag];
	return (0);
}

void			print_flag_error(void)
{
	ft_putstr("ls: illegal option --");
	ft_putendl(&g_char_not_flag);
	ft_putstr("usage: ls [-ARalrtfuc1] [file ...]\n");
	exit(1);
}

t_flag			set_flags(char c, t_flag flags)
{
	if (c == 'a')
		flags.a = 1;
	else if (c == 'A')
		flags.cap_a = 1;
	else if (c == 'l')
		flags.l = 1;
	else if (c == 'R')
		flags.cap_r = 1;
	else if (c == 'r')
		flags.r = 1;
	else if (c == 't')
		flags.t = 1;
	else if (c == '1')
		flags.one = 1;
	else if (c == 'f')
		flags.f = 1;
	else if (c == 'u')
		flags.u = 1;
	else if (c == 'c')
		flags.c = 1;
	return (flags);
}

t_flag			get_flags(int ac, char *av[])
{
	t_flag		flags;
	char		flag_c;

	flags = init_flags();
	while ((flag_c = get_opts(ac, av, "aAlRrfuct1")) != -1)
	{
		if (flag_c == 0)
		{
			print_flag_error();
		}
		flags = set_flags(flag_c, flags);
	}
	return (flags);
}
