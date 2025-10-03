/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:56:20 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:00:09 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	free_config(t_config *config)
{
	int	i;

	if (!config)
		return ;
	if (config->north_texture)
		free(config->north_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->east_texture)
		free(config->east_texture);
	if (config->west_texture)
		free(config->west_texture);
	if (config->map)
	{
		i = 0;
		while (i < config->map_h)
		{
			if (config->map[i])
				free(config->map[i]);
			i++;
		}
		free(config->map);
	}
}

/* Frees all game resources and exits */
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_config(&game->config);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/* Prints an error message, frees resources, and exits */
void	exit_error(t_game *game, char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	free_game(game);
	exit(1);
}
