/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/12 23:12:02 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_object seach_nearest_obj(t_rt *rt, double x, double y)
{
    t_object    nearest_obj;
    t_object    *obj;
    t_object    *tmp;
    double      t;
    double      min_t;
    
    min_t = 1000000000;
}