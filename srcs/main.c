/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 21:32:41 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 23:57:45 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		add_element(t_info *item, STAT tmp, char *fname, int *iter)
{
	item->f_stat = tmp;
	item->name = ft_strdup(fname);
	item->full_path = ft_strdup(fname);
	*iter = *iter + 1;
}

static void		add_single_if_empty(t_localinfo *local)
{
	STAT		tmp;

	lstat(".", &tmp);
	if (local->files)
		free(local->files);
	local->files_size = 1;
	local->files = (t_info*)malloc(sizeof(t_info) * local->files_size);
	local->files[0].f_stat = tmp;
	local->files[0].name = ft_strdup(".");
	local->files[0].full_path = ft_strdup(".");
}

static void		make_args(int c, char **av, t_localinfo *local, int flag)
{
	int			i;
	int			j;
	STAT		tmp;

	i = 0;
	j = 0;
	while (++i < c)
	{
		if (!flag && av[i][0] == '-' && ft_strcmp("--", av[i]))
			continue ;
		if (!flag && !ft_strcmp("--", av[i]) && ((++i) == c))
			break ;
		if (!flag && (flag = 1) && !lstat(av[i], &tmp))
		{
			++(local->files_size);
			add_element(&local->files[j], tmp, av[i], &j);
			continue ;
		}
		if (flag && !lstat(av[i], &tmp) && (++(local->files_size)))
			add_element(&local->files[j], tmp, av[i], &j);
		else if (flag)
			make_error(av[i], local);
	}
	if (c == 1 || (!local->files_size && !ft_strlen(local->errors)))
		add_single_if_empty(local);
}

int				main(int c,char **av)
{
	t_flags		fl;
	t_localinfo		l;

	ft_bzero(&l, sizeof(t_localinfo));
	ft_bzero(&fl, sizeof(t_flags));
	ft_get_lsflags(&fl, c, av);
	l.flags = fl;
	l.errors = ft_strdup("");
	l.loc_path = ft_strdup(".");
	l.files_size = 0;
	l.files = (t_info*)malloc(sizeof(t_info) * c);
	make_args(c, av, &l, 0);
	if (fl.f_list)
		get_width_for_l(&l);
	run_ls(&l);
	return (0);
}
