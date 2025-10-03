/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:04:01 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:19:18 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	draw_rect(t_game *g, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_pixel(g, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static int	get_tile_color(char tile_char)
{
	if (tile_char == '1')
		return (0x333333); // Wall color
	if (tile_char == ' ')
		return (0x000000); // Empty space color
	return (0x666666);     // Floor color
}

static void	draw_minimap_tiles(t_game *g)
{
	int	tx;
	int	ty;
	int	color;

	ty = 0;
	while (ty < g->config.map_h)
	{
		tx = 0;
		while (tx < (int)ft_strlen(g->config.map[ty]))
		{
			color = get_tile_color(g->config.map[ty][tx]);
			draw_rect(g, MINIMAP_PADDING + tx * MINIMAP_TILE,
				MINIMAP_PADDING + ty * MINIMAP_TILE,
				MINIMAP_TILE, MINIMAP_TILE, color);
			tx++;
		}
		ty++;
	}
}
void	draw_minimap(t_game *g)
{
	int	player_pos_x;
	int	player_pos_y;

	/* First, draw the map grid background */
	draw_minimap_tiles(g);
	/* Then, calculate the player's pixel position on the minimap */
	player_pos_x = MINIMAP_PADDING + (int)(g->player.x / BLOCK * MINIMAP_TILE);
	player_pos_y = MINIMAP_PADDING + (int)(g->player.y / BLOCK * MINIMAP_TILE);
	/* Finally, draw the player on top as a small red square */
	draw_rect(g, player_pos_x - 2, player_pos_y - 2, 5, 5, 0xFF0000);
}
