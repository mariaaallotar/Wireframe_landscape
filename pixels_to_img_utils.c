/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_to_img_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:17:43 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/13 13:19:11 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_p0_and_p1(t_line *line)
{
	float	temp_x0;
	float	temp_y0;

	temp_x0 = line->x0;
	temp_y0 = line->y0;
	line->x0 = line->x1;
	line->y0 = line->y1;
	line->x1 = temp_x0;
	line->y1 = temp_y0;
}

void	init_line(t_line *line, t_point p0, t_point p1)
{
	line->x0 = p0.x;
	line->y0 = p0.y;
	line->x1 = p1.x;
	line->y1 = p1.y;
	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
	line->xi = 1;
	line->yi = 1;
}
