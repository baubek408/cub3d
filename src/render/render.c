/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:04:43 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:38:54 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

t_ray	calculate_ray_properties(t_game *g, int x)
{
	t_ray	ray;

	ray.angle = g->player.angle - FOV_RAD / 2.0f + (float)x / WIDTH * FOV_RAD;
	ray.dist = cast_ray_dda(g, ray.angle, &ray.side, &ray.wall_x);
	/* Correct for fisheye effect */
	ray.dist *= cosf(ray.angle - g->player.angle);
	return (ray);
}

t_wall_slice	calculate_slice_dimensions(t_ray *ray)
{
	t_wall_slice	slice;

	slice.height = (int)(BLOCK / ray->dist * (WIDTH / (2 * tanf(FOV_RAD / 2))));
	slice.y_start = -slice.height / 2 + HEIGHT / 2;
	if (slice.y_start < 0)
		slice.y_start = 0;
	slice.y_end = slice.height / 2 + HEIGHT / 2;
	if (slice.y_end >= HEIGHT)
		slice.y_end = HEIGHT - 1;
	return (slice);
}

t_tex_info	prepare_texture_info(t_game *g, t_ray *ray)
{
	t_tex_info	tex_info;

	tex_info.texture = get_wall_texture(g, ray->side, ray->angle);
	tex_info.tex_x = (int)(ray->wall_x * (float)tex_info.texture->width);
	/* Flip texture if needed */
	if ((ray->side == 0 && cosf(ray->angle) < 0)
		|| (ray->side == 1 && sinf(ray->angle) > 0))
	{
		tex_info.tex_x = tex_info.texture->width - tex_info.tex_x - 1;
	}
	return (tex_info);
}

static void	draw_column(t_game *g, int x, t_wall_slice *slice, t_tex_info *info)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = 0;
	while (y < slice->y_start)
	{
		put_pixel(g, x, y, g->config.ceiling_color);
		y++;
	}
	y = slice->y_start;
	while (y < slice->y_end)
	{
		info->tex_pos = (y - (-slice->height / 2 + HEIGHT / 2))
			/ (float)slice->height;
		tex_y = (int)(info->tex_pos * info->texture->height);
		color = get_pixel_color(info->texture, info->tex_x, tex_y);
		put_pixel(g, x, y, color);
		y++;
	}
	y = slice->y_end;
	while (y < HEIGHT)
	{
		put_pixel(g, x, y, g->config.floor_color);
		y++;
	}
}

void	draw_3d_walls(t_game *g)
{
	int				x;
	t_ray			ray;
	t_wall_slice	slice;
	t_tex_info		tex_info;

	x = 0;
	while (x < WIDTH)
	{
		ray = calculate_ray_properties(g, x);
		slice = calculate_slice_dimensions(&ray);
		tex_info = prepare_texture_info(g, &ray);
		draw_column(g, x, &slice, &tex_info);
		x++;
	}
}
