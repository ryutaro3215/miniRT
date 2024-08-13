/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/13 12:01:53 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double calc_sp_distance(t_object *object, t_vec3 screen_vec, t_camera *camera)
{
    t_vec3	dir;
    t_vec3	cam2sph;
    double	a;
    double	b;
    double	c;
    dir = vec3_norm(vec3_sub(screen_vec, *camera->view_point));
    cam2sph = vec3_sub(*camera->view_point, *object->center);
    a = vec3_dot(dir, dir);
    b = 2 * vec3_dot(cam2sph, dir);
    c = vec3_dot(cam2sph, cam2sph) - (object->diameter * object->diameter);
    if(b * b - 4 * a * c < 0)
        return -1;
    return ((-b+sqrt(b * b - 4 * a * c))/(2.0 * a));
}

double calc_pl_distance(t_object *object, t_vec3 screen_vec, t_camera *camera)
{
    t_vec3	dir;
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	dir = vec3_norm(vec3_sub(screen_vec, *camera->view_point)); 
	cam2pl = vec3_sub(*camera->view_point, *object->p_in_the_plane);
	denominator = -(vec3_dot(dir, *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}

static double calc_distance(t_object *obj, t_vec3 screen_vec, t_camera *camera)
{
    if(obj->type == SPHERE)
        return (calc_sp_distance(obj, screen_vec, camera));
    else if(obj->type == PLANE)
        return(calc_pl_distance(obj, screen_vec, camera));
    // else if(obj->type == CYLINDER)
    //     return(calc_cy_distance(obj, screen_vec, camera));
    return 0;
}

t_object *seach_nearest_obj(t_rt *rt, double x, double y)
{
    t_object    *nearest_obj;
    t_object    *obj;
    t_vec3     screen_vec;
    double      distance;
    double      min_distance;
    
    // TODO defineで定義するようにする
    min_distance = 1000000000;
    screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
    obj = rt->scene->object;
    nearest_obj = obj;
    while(obj)
    {
        distance = 0;
        distance = calc_distance(obj, screen_vec, rt->scene->camera);   
        if(distance < 0)
        {
            obj = obj->next;
            continue;
        }
        if(distance < min_distance)
        {
            min_distance = distance;
            nearest_obj = obj;
        }
        obj = obj->next;
    }
    // printf("obj type %d\n", nearest_obj->type);

    return (nearest_obj);
}