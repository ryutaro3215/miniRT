/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/14 18:00:50 by rmatsuba         ###   ########.fr       */
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

t_vec3  *calc_cy_intersections(t_object *obj, t_vec3 dir, t_vec3 cam2cy, t_camera *camera)
{
    double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	*intersections;

	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *obj->axic_vec), 2);
	b = 2 * (vec3_dot(dir, cam2cy) - vec3_dot(dir, *obj->axic_vec)
			* vec3_dot(*obj->axic_vec, cam2cy));
	c = vec3_dot(cam2cy, cam2cy) - pow(vec3_dot(*obj->axic_vec, cam2cy), 2)
		- obj->diameter / 2 * obj->diameter / 2;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (NULL);
	intersections = (t_vec3 *)malloc(sizeof(t_vec3) * 2);
	if (intersections == NULL)
		return (NULL);
	intersections[0] = vec3_add(*camera->view_point, 
			vec3_mul(dir, ((-b - sqrt(d)) / (2 * a))));
	intersections[1] = vec3_add(*camera->view_point,
			vec3_mul(dir, ((-b + sqrt(d)) / (2 * a))));
	return (intersections);
}

bool    calc_cy_height(t_object *object, t_vec3 *intersections, t_camera *camera)
{
    bool	is_intersect_p1;
	bool	is_intersect_p2;
	t_vec3	axic;
	t_vec3	cyl_top;
	t_vec3	cyl_bottom;

	cyl_top = vec3_add(*camera->view_point, 
			vec3_mul(*object->axic_vec, object->height / 2));
	cyl_bottom = vec3_sub(*camera->view_point, 
			vec3_mul(*object->axic_vec, object->height / 2));
	axic = *object->axic_vec;
	is_intersect_p1 = vec3_dot(vec3_sub(intersections[0], cyl_bottom), axic) >= 0 &&
		vec3_dot(vec3_sub(intersections[0], cyl_top), axic) <= 0;
	is_intersect_p2 = vec3_dot(vec3_sub(intersections[1], cyl_bottom), axic) >= 0 &&
		vec3_dot(vec3_sub(intersections[1], cyl_top), axic) <= 0;
	if ( is_intersect_p1|| is_intersect_p2)
		return (true);
	else
		return (false);
}

double calc_cy_distance(t_object *object, t_vec3 screen_vec, t_camera *camera)
{
    t_vec3  dir;
    t_vec3  cam2cy;
    t_vec3  *intersections;
    bool    flag;
    double  distance;

    dir = vec3_norm(vec3_sub(screen_vec, *camera->view_point));
    cam2cy = vec3_sub(*camera->view_point, *object->center);
    intersections = calc_cy_intersections(object, dir, cam2cy, camera);
    if (intersections == NULL)
        return (-1);
    flag = calc_cy_height(object, intersections, camera);
    if (flag == false)
	{
		free(intersections);
        return (-1);
	}
	distance = vec3_mag(vec3_sub(*camera->view_point, intersections[0]));
	if (distance > vec3_mag(vec3_sub(*camera->view_point, intersections[1])))
		distance = vec3_mag(vec3_sub(*camera->view_point, intersections[1]));
    free(intersections);
	return (distance);
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
