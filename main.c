/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:45:29 by bmynbyae@st       #+#    #+#             */
/*   Updated: 2025/10/08 20:32:40 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube.h"

static inline void	clear_frame(t_game *g)
{
	ft_memset(g->data, 0, (size_t)g->size_line * HEIGHT);
}

int	draw_loop(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	clear_frame(g);
	move_player(g);
	draw_3d_walls(g);
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map_file.cub>\n", 36);
		return (1);
	}
	init_game(&game);
	parse_file(argv[1], &game);
	load_textures(&game);
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game.win)
		exit_error(&game, "Failed to create MLX window.");
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img)
		exit_error(&game, "Failed to create MLX image.");
	game.data = mlx_get_data_addr(game.img, &game.bpp,
			&game.size_line, &game.endian);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
