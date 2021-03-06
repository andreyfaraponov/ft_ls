/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 00:01:13 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 23:59:32 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_get_one_flag(t_flags *fl, char sign)
{
	if (sign == 'R')
		fl->f_recur = 1;
	else if (sign == 'l')
		fl->f_list = 1;
	else if (sign == 'a')
		fl->f_all = 1;
	else if (sign == 'r')
		fl->f_rever = 1;
	else if (sign == 't')
		fl->f_by_time = 1;
	else if (sign == 'G')
		fl->f_colors = 1;
	else if (sign == 'f')
		fl->f_dis_lsg = 1;
	else if (sign == 'g')
		fl->f_list_not_owner = 1;
	else if (sign == 'd')
		fl->f_just_dir = 1;
	else
		make_flag_error(sign);
}

static void		ft_after_flags_control(t_flags *fl)
{
	if (fl->f_dis_lsg)
		fl->f_all = 1;
}

static void		ft_parse_flags(t_flags *fl, char *str)
{
	str++;
	while (*str)
	{
		ft_get_one_flag(fl, *str);
		str++;
	}
}

void			ft_get_lsflags(t_flags *fl, int c, char **v)
{
	int		i;

	i = 1;
	while (i < c)
	{
		if (v[i][0] == '-' && ft_strcmp("--", v[i]))
			ft_parse_flags(fl, v[i]);
		else
			break ;
		i++;
	}
	ft_after_flags_control(fl);
}
