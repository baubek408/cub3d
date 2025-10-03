/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmynbyae@student.42prague.com <bmynbyae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:02:04 by bmynbyae          #+#    #+#             */
/*   Updated: 2025/09/30 18:18:02 by bmynbyae@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

bool	touch_point(float px, float py, t_game *game, float radius)
{
	const float	ox[4] = {radius, -radius, 0.0f, 0.0f};
	const float	oy[4] = {0.0f, 0.0f, radius, -radius};
	int			i;
	int			mx;
	int			my;

	i = 0;
	while (i < 4)
	{
		mx = (int)((px + ox[i]) / BLOCK);
		my = (int)((py + oy[i]) / BLOCK);
		if (my < 0 || my >= game->config.map_h || mx < 0
			|| mx >= game->config.map_w)
			return (true);
		if (game->config.map[my][mx] == '1')
			return (true);
		i++;
	}
	return (false);
}

static void	handle_rotation(t_player *p)
{
	if (p->left_rotate)
		p->angle -= ROT_SPEED;
	if (p->right_rotate)
		p->angle += ROT_SPEED;
	/* Normalize angle to be between 0 and 2*PI */
	p->angle = fmodf(p->angle, 2.0f * (float)M_PI);
	if (p->angle < 0)
		p->angle += 2.0f * (float)M_PI;
}

static void	apply_movement(t_game *game, float dx, float dy)
{
	t_player	*p;
	float		next_x;
	float		next_y;

	p = &game->player;
	next_x = p->x + dx;
	next_y = p->y + dy;
	/* Check X and Y movement independently to allow sliding along walls */
	if (!touch_point(next_x, p->y, game, PLAYER_RADIUS))
		p->x = next_x;
	if (!touch_point(p->x, next_y, game, PLAYER_RADIUS))
		p->y = next_y;
}

void	move_player(t_game *game)
{
	t_player	*p;
	float		dx;
	float		dy;
	int			forward_move;
	int			strafe_move;

	p = &game->player;
	handle_rotation(p);
	/* Determine movement direction from key states (1, -1, or 0) */
	forward_move = p->key_up - p->key_down;
	strafe_move = p->key_right - p->key_left;
	/* Calculate the movement vector (delta x, delta y) */
	dx = (forward_move * cosf(p->angle) - strafe_move * sinf(p->angle))
		* MOVE_SPEED;
	dy = (forward_move * sinf(p->angle) + strafe_move * cosf(p->angle))
		* MOVE_SPEED;
	/* Only apply movement if there is a change */
	if (dx != 0 || dy != 0)
		apply_movement(game, dx, dy);
}
