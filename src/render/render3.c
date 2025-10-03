/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:23:34 by bmynbyae@st       #+#    #+#             */
/*   Updated: 2025/09/30 18:40:13 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

t_texture	*get_wall_texture(t_game *g, int side, float angle)
{
	if (side == 0)
	{
		if (cosf(angle) > 0)
			return (&g->textures[3]);
		else
			return (&g->textures[2]);
	}
	else
	{
		if (sinf(angle) > 0)
			return (&g->textures[1]);
		else
			return (&g->textures[0]);
	}
}

static void	perform_dda(t_game *g, t_dda *dda)
{
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			*(dda->side) = 0; // Wall is on X-axis (East/West)
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			*(dda->side) = 1; // Wall is on Y-axis (North/South)
		}
		if (dda->map_y < 0 || dda->map_y >= g->config.map_h
			|| dda->map_x < 0
			|| dda->map_x >= (int)ft_strlen(g->config.map[dda->map_y])
			|| g->config.map[dda->map_y][dda->map_x] == '1')
			break ;
	}
}

static void	calculate_step_and_side_dist(t_player *p, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (p->x / BLOCK - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0f - p->x / BLOCK) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (p->y / BLOCK - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0f - p->y / BLOCK) * dda->delta_dist_y;
	}
}

static void	init_dda_vars(t_game *g, t_dda *dda, float angle)
{
	dda->ray_dir_x = cosf(angle);
	dda->ray_dir_y = sinf(angle);
	dda->map_x = (int)(g->player.x / BLOCK);
	dda->map_y = (int)(g->player.y / BLOCK);
	/* Use a small epsilon to avoid division by zero */
	if (fabs(dda->ray_dir_x) < 1e-6)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabsf(1.0f / dda->ray_dir_x);
	if (fabs(dda->ray_dir_y) < 1e-6)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabsf(1.0f / dda->ray_dir_y);
}

float	cast_ray_dda(t_game *g, float angle, int *out_side, float *wall_x)
{
	t_dda	dda;
	float	perp_wall_dist;

	dda.side = out_side;
	dda.wall_x = wall_x;
	init_dda_vars(g, &dda, angle);
	calculate_step_and_side_dist(&g->player, &dda);
	perform_dda(g, &dda);
	if (*(dda.side) == 0)
	{
		perp_wall_dist = (dda.side_dist_x - dda.delta_dist_x) * BLOCK;
		*(dda.wall_x) = g->player.y + perp_wall_dist * dda.ray_dir_y / BLOCK;
	}
	else
	{
		perp_wall_dist = (dda.side_dist_y - dda.delta_dist_y) * BLOCK;
		*(dda.wall_x) = g->player.x + perp_wall_dist * dda.ray_dir_x / BLOCK;
	}
	*(dda.wall_x) -= floorf(*(dda.wall_x));
	return (perp_wall_dist);
}
