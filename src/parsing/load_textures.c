/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by bmynbyae@st       #+#    #+#             */
/*   Updated: 2025/10/08 20:41:46 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	load_single_texture(t_game *game, char *path, int index)
{
	t_texture	*texture;

	texture = &game->textures[index];
	if (!path)
		exit_error(game, "Texture path is NULL");
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		exit_error(game, "Failed to load texture");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		exit_error(game, "Failed to get texture data address");
}

void	load_textures(t_game *game)
{
	load_single_texture(game, game->config.north_texture, 0);  // North
	load_single_texture(game, game->config.south_texture, 1);  // South
	load_single_texture(game, game->config.west_texture, 2);   // West
	load_single_texture(game, game->config.east_texture, 3);   // East
}
