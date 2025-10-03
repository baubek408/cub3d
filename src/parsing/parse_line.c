/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:13:12 by bmynbyae@st       #+#    #+#             */
/*   Updated: 2025/09/30 18:16:11 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	add_line_to_map(char *line, t_list **map_list)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	/* You should add error checking for ft_lstnew and ft_strdup */
	ft_lstadd_back(map_list, ft_lstnew(ft_strdup(line)));
}
static bool	parse_config_line(char *trimmed_line, t_game *game)
{
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
		parse_texture(trimmed_line, game, "NO");
	else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
		parse_texture(trimmed_line, game, "SO");
	else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
		parse_texture(trimmed_line, game, "WE");
	else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
		parse_texture(trimmed_line, game, "EA");
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		parse_color(trimmed_line, game, 'F');
	else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		parse_color(trimmed_line, game, 'C');
	else
		return (false); // Not a config line
	return (true); // It was a config line
}

static void	handle_map_transition(char *line, t_game *game,
									t_list **map_list, bool *is_parsing_map)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!game->config.checklist[i])
			exit_error(game, "Config incomplete before map definition.");
		i++;
	}
	*is_parsing_map = true;
	add_line_to_map(line, map_list);
}

void	process_line(char *line, t_game *game,
						t_list **map_list, bool *is_parsing_map)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line || *trimmed_line == '\0' || *trimmed_line == '#')
	{
		free(trimmed_line);
		return ;
	}
	if (*is_parsing_map)
		add_line_to_map(line, map_list);
	else
	{
		if (!parse_config_line(trimmed_line, game))
			handle_map_transition(line, game, map_list, is_parsing_map);
	}
	free(trimmed_line);
}

void	parse_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	t_list	*map_list;
	bool	is_parsing_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error(game, "Could not open map file.");
	map_list = NULL;
	is_parsing_map = false;
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, game, &map_list, &is_parsing_map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map_list)
		exit_error(game, "Map content is missing or file is empty.");
	parse_map(map_list, game);
	validate_map(game);
}
