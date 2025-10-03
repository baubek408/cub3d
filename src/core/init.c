/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:56:44 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:00:50 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	init_player(t_player *p, int start_tx, int start_ty, char direction)
{
	p->x = start_tx * BLOCK + BLOCK * 0.5f;
	p->y = start_ty * BLOCK + BLOCK * 0.5f;
	p->key_up = false;
	p->key_down = false;
	p->key_left = false;
	p->key_right = false;
	p->left_rotate = false;
	p->right_rotate = false;
	if (direction == 'N')
		p->angle = 1.5f * (float)M_PI;
	else if (direction == 'S')
		p->angle = 0.5f * (float)M_PI;
	else if (direction == 'W')
		p->angle = 1.0f * (float)M_PI;
	else if (direction == 'E')
		p->angle = 0.0f;
}

void	init_config(t_config *config)
{
	int	i;

	config->north_texture = NULL;
	config->south_texture = NULL;
	config->east_texture = NULL;
	config->west_texture = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->map = NULL;
	config->map_w = 0;
	config->map_h = 0;
	i = 0;
	while (i < 6)
	{
		config->checklist[i] = false;
		i++;
	}
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(*game));
	init_config(&game->config);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(game, "Failed to initialize MLX.");
}
