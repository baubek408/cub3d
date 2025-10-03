/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:09:03 by bmynbyae@st       #+#    #+#             */
/*   Updated: 2025/09/30 18:11:33 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	get_texture_targets(t_game *game, char *type_id,
								char ***target, bool **flag)
{
	if (ft_strncmp(type_id, "NO", 2) == 0)
	{
		*target = &game->config.north_texture;
		*flag = &game->config.checklist[0];
	}
	else if (ft_strncmp(type_id, "SO", 2) == 0)
	{
		*target = &game->config.south_texture;
		*flag = &game->config.checklist[1];
	}
	else if (ft_strncmp(type_id, "WE", 2) == 0)
	{
		*target = &game->config.west_texture;
		*flag = &game->config.checklist[2];
	}
	else
	{
		*target = &game->config.east_texture;
		*flag = &game->config.checklist[3];
	}
}

int	parse_texture(char *line, t_game *game, char *type_id)
{
	char	**target;
	bool	*checklist_flag;

	get_texture_targets(game, type_id, &target, &checklist_flag);
	if (*checklist_flag)
		exit_error(game, "Duplicate texture identifier found.");
	line += 2;
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0')
		exit_error(game, "Missing texture path after identifier.");
	*target = ft_strdup(line);
	if (!*target)
		exit_error(game, "Memory allocation failed for texture path.");
	*checklist_flag = true;
	return (0);
}
