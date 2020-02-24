/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 23:09:13 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/24 18:37:59 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ordinate(t_lst *t, int l, int k)
{
	mnoj(t, &(t->x0), &(t->y0), &(t->z0));
	mnoj(t, &(t->x1), &(t->y1), &(t->z1));
	if (l > 0)
	{
		t->z2 = t->matz[l - 1][k];
		if ((t->color_file)[l - 1][k] != -1)
			t->color2 = (t->color_file)[l - 1][k];
		t->z2_begin = t->z2;
		mnoj(t, &(t->x2), &(t->y2), &(t->z2));
		t->check_xy = 2;
		if ((t->z2 < t->zp && t->z0 < t->zp) || t->perspective == 0)
			draw_line(*t);
	}
}

void	home_0(t_lst *t, int l, int k)
{
	while (++k < t->len[l])
	{
		t->color0 = -1;
		t->color1 = -1;
		t->color2 = -1;
		t->x0 = t->a * k + t->a - (t->len[l] / 2) * t->a;
		t->x2 = t->x0;
		t->y1 = t->a * l + t->a - (t->len[l] / 2) * t->a;
		t->y0 = t->y1;
		t->z0 = t->matz[l][k];
		if ((t->color_file)[l][k] != -1)
			t->color0 = (t->color_file)[l][k];
		t->z0_begin = t->z0;
		t->x1 = t->a * (k + 1) + t->a - (t->len[l] / 2) * t->a;
		t->y2 = t->a * (l - 1) + t->a - (t->len[l] / 2) * t->a;
		t->z1 = t->matz[l][k + 1];
		if (k < t->len[l] - 1 && (t->color_file)[l][k + 1] != -1)
			t->color1 = (t->color_file)[l][k + 1];
		t->z1_begin = t->z1;
		ordinate(t, l, k);
		t->check_xy = 1;
		if (((t->z1 < t->zp && t->z0 < t->zp)
			|| t->perspective == 0) && k < t->len[l] - 1)
			draw_line(*t);
	}
}

void	home(t_lst *lst)
{
	int l;

	lst->matriy[0][0] = 1;
	lst->matriy[1][1] = cos(lst->be_x);
	lst->matriy[1][2] = -sin(lst->be_x);
	lst->matriy[2][1] = sin(lst->be_x);
	lst->matriy[2][2] = cos(lst->be_x);
	lst->matrix[0][0] = cos(lst->be_y);
	lst->matrix[0][2] = sin(lst->be_y);
	lst->matrix[1][1] = 1;
	lst->matrix[2][0] = -sin(lst->be_y);
	lst->matrix[2][2] = cos(lst->be_y);
	lst->matriz[0][0] = cos(lst->be_z);
	lst->matriz[0][1] = -sin(lst->be_z);
	lst->matriz[1][0] = sin(lst->be_z);
	lst->matriz[1][1] = cos(lst->be_z);
	lst->matriz[2][2] = 1;
	l = -1;
	while (++l < lst->i)
		if (lst->color_file[l][0] == 0)
			lst->color_file[l][0] = -1;
	l = -1;
	while (++l < lst->i)
		home_0(lst, l, -1);
}

void	new_0(t_lst *l, int t, int k)
{
	int ct;

	l->min_z = 2147483647;
	l->max_z = -2147483648;
	while ((l->line)[++t])
	{
		k = 0;
		ct = 0;
		while ((l->line)[t][k])
		{
			record(l, t, k, &ct);
			while ((l->line)[t][k] && (l->line)[t][k] == ' ')
				k++;
			if ((l->line)[t][k] && (l->line)[t][k] == '-')
				k++;
			while ((l->line)[t][k] && (l->line)[t][k] >= '0'
				&& (l->line)[t][k] <= '9')
				k++;
			if ((l->line)[t][k] == ',')
			{
				check_color(l->line[t], &k);
				(l->color_file)[t][ct - 1] = ft_atoi_16((l->line)[t], &k, 0, 0);
			}
		}
	}
}

int		new(t_lst *lst)
{
	fon(lst->data, FON);
	lst->be_x = 27 * 0.04;
	lst->be_y = 0;
	lst->be_z = -27 * 0.04;
	lst->per = 0;
	lst->color_b0 = BLUE;
	lst->color_e0 = RED;
	lst->color_fon = FON;
	lst->point = 0;
	if (!(lst->len = (int *)malloc(sizeof(int) * lst->i)) ||
		!(lst->matz = (int **)malloc(sizeof(int *) * lst->i)) ||
		!(lst->color_file = (int **)malloc(sizeof(int *) * lst->i)))
		return (error());
	cycle(lst, lst->line, -1, 0);
	lst->perspective = 0;
	lst->zp = 800;
	new_0(lst, -1, 0);
	nul_matrix(lst);
	home(lst);
	return (1);
}
