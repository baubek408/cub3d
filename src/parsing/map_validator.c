/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:57:07 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:03:25 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	if (y < 0 || y >= game->config.map_h || x < 0
		|| x >= (int)ft_strlen(map_copy[y]))
	{
		exit_error(game, "Map is not enclosed by walls.");
		return ;
	}
	if (map_copy[y][x] == ' ' || map_copy[y][x] == 'F'
		|| map_copy[y][x] == '1')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x - 1, y);
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
}

static char	**create_map_copy(t_config *config)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (config->map_h + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < config->map_h)
	{
		copy[i] = ft_strdup(config->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	validate_map_characters(t_game *game)
{
	int	x;
	int	y;
	int	player_found;

	player_found = 0;
	y = 0;
	while (y < game->config.map_h)
	{
		x = 0;
		while (x < (int)ft_strlen(game->config.map[y]))
		{
			if (ft_strchr("NSWE", game->config.map[y][x]))
			{
				if (player_found > 0)
					exit_error(game, "Multiple player start positions found.");
				init_player(&game->player, x, y, game->config.map[y][x]);
				player_found++;
			}
			else if (!ft_strchr("01 ", game->config.map[y][x]))
				exit_error(game, "Invalid character found in map.");
			x++;
		}
		y++;
	}
	return (player_found);
}

static void	validate_map_walls(t_game *game)
{
	char	**map_copy;
	int		y;

	map_copy = create_map_copy(&game->config);
	if (!map_copy)
		exit_error(game, "Memory allocation failed for map validation.");
	flood_fill(game, map_copy, (int)(game->player.x / BLOCK),
		(int)(game->player.y / BLOCK));
	y = 0;
	while (y < game->config.map_h)
	{
		free(map_copy[y]);
		y++;
	}
	free(map_copy);
}

void	validate_map(t_game *game)
{
	int	player_found;

	player_found = validate_map_characters(game);
	if (player_found != 1)
		exit_error(game, "Map must have exactly one player start position.");
	validate_map_walls(game);
}
