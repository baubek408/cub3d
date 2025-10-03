/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:57:17 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:44:17 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	validate_rgb_format(char **rgb_parts, t_game *game)
{
	int	i;

	i = 0;
	while (rgb_parts && rgb_parts[i])
		i++;
	if (i != 3)
	{
		free_str_array(rgb_parts);
		exit_error(game, "Invalid RGB format. Must be exactly R,G,B.");
	}
}

static int	convert_rgb_to_int(char **rgb_parts, t_game *game)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_str_array(rgb_parts);
		exit_error(game, "RGB color values must be between 0 and 255.");
	}
	return ((r << 16) | (g << 8) | b);
}

static void	assign_color_to_game(t_game *game, int color, char type_id)
{
	if (type_id == 'F')
	{
		if (game->config.checklist[4])
			exit_error(game, "Duplicate floor color identifier found.");
		game->config.floor_color = color;
		game->config.checklist[4] = true;
	}
	else
	{
		if (game->config.checklist[5])
			exit_error(game, "Duplicate ceiling color identifier found.");
		game->config.ceiling_color = color;
		game->config.checklist[5] = true;
	}
}

int	parse_color(char *line, t_game *game, char type_id)
{
	char	**rgb_parts;
	int		color;

	line++;
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0')
		exit_error(game, "Missing color value after identifier.");
	rgb_parts = ft_split(line, ',');
	validate_rgb_format(rgb_parts, game);
	color = convert_rgb_to_int(rgb_parts, game);
	assign_color_to_game(game, color, type_id);
	free_str_array(rgb_parts);
	return (0);
}



