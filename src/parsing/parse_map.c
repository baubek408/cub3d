/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:10:49 by bmynbyae@st       #+#    #+#             */
/*   Updated: 2025/09/30 18:13:05 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static int	populate_map_from_list(char **map, t_list *list)
{
	int		i;
	int		max_w;
	int		current_len;
	t_list	*current;

	i = 0;
	max_w = 0;
	current = list;
	while (current)
	{
		map[i] = (char *)current->content;
		current->content = NULL;
		current_len = ft_strlen(map[i]);
		if (current_len > max_w)
			max_w = current_len;
		current = current->next;
		i++;
	}
	return (max_w);
}

void	parse_map(t_list *map_list, t_game *game)
{
	int	max_w;

	game->config.map_h = ft_lstsize(map_list);
	game->config.map = malloc(sizeof(char *) * (game->config.map_h + 1));
	if (!game->config.map)
	{
		ft_lstclear(&map_list, free);
		exit_error(game, "Failed to allocate memory for map.");
	}
	max_w = populate_map_from_list(game->config.map, map_list);
	game->config.map[game->config.map_h] = NULL;
	game->config.map_w = max_w;
	ft_lstclear(&map_list, free);
}


