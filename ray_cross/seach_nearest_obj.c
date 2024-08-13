/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/13 20:09:34 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"

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
// TODO　うまく描画されない・・？
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

double calc_cy_distance(t_object *object, t_vec3 screen_vec, t_camera *camera)
{
    	double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	*intersections;
    t_vec3    dir;
    t_vec3    cam2cyl;

    dir = vec3_norm(vec3_sub(screen_vec, *camera->view_point));
    cam2cyl = vec3_sub(*camera->view_point, *object->center);
	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *object->axic_vec), 2);
	b = 2 * (vec3_dot(dir, cam2cyl) - vec3_dot(dir, *object->axic_vec)
			* vec3_dot(*object->axic_vec, cam2cyl));
	c = vec3_dot(cam2cyl, cam2cyl) - pow(vec3_dot(*object->axic_vec, cam2cyl), 2)
		- object->diameter / 2 * object->diameter / 2;
	d = b * b - 4 * a * c;
    double outer = (-b - sqrt(d)) / (2 * a);
    double inner = (-b + sqrt(d)) / (2 * a);
    // TODO まだ未完成・・・
}
double calc_distance(t_object *obj, t_vec3 screen_vec, t_camera *camera)
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
    
    min_distance = DISTANCE_MAX;
    screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
    obj = rt->scene->object;
    nearest_obj = obj;
    // 各オブジェクトについて距離を計算し、最小のものをnearest_objに格納しています
    while(obj)
    {
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

    return (nearest_obj);
}