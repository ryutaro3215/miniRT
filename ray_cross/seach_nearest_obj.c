/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/31 14:26:20 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"

double calc_sp_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
    
    t_vec3	sph2source;
    double	a;
    double	b;
    double	c;
	double	t1;
	double	t2;
    sph2source = vec3_sub(*source_point, *object->center);
    a = vec3_dot(dir, dir);
    b = 2 * vec3_dot(sph2source, dir);
    c = vec3_dot(sph2source, sph2source) - (object->diameter * object->diameter);
    if(b * b - 4 * a * c < 0)
        return -1;
	t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	if (t1 < t2)
		return (t1);
	return (t2);
}
// TODO　うまく描画されない・・？
double calc_pl_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
    
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	cam2pl = vec3_sub(*source_point, *object->p_in_the_plane);
	denominator = (vec3_dot(vec3_mul(dir,-1), *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}





bool    calc_cy_height(t_object *object, t_vec3 *intersections, t_vec3 *source_point)
{
    bool	is_intersect_p1;
	bool	is_intersect_p2;
	t_vec3	axic;
	t_vec3	cyl_top;
	t_vec3	cyl_bottom;

	cyl_top = vec3_add(*source_point, 
			vec3_mul(*object->axic_vec, object->height / 2));
	cyl_bottom = vec3_sub(*source_point,
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

double  calc_cy_t2(t_object *obj, t_vec3 dir, t_vec3 cam2cy, int flag,t_vec3 *source_point)
{
    double	a;
	double	b;
	double	c;
	double	d;
    a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
    a*=a;
     b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec), vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));

     c = vec3_mag(vec3_cross(vec3_sub(*source_point, *obj->center),  *obj->axic_vec));
	c = c * c - (obj->diameter/2) *(obj->diameter/2);
     if(cam2cy.x == 0 && cam2cy.y == 0 && cam2cy.z == 0)
        ;
	d = b * b - 4 * a * c;

    if(flag == 1)
        return (-b + sqrt(d)) / (2 * a);
    
    return (-b - sqrt(d)) / (2 * a);
}
t_vec3  *calc_cy_intersections(t_object *obj, t_vec3 dir, t_vec3 cam2cy, t_vec3 *source_point)
{
    double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	*intersections;

	// a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *obj->axic_vec), 2);
	// b = 2 * (vec3_dot(dir, cam2cy) - vec3_dot(dir, *obj->axic_vec)
	// 		* vec3_dot(*obj->axic_vec, cam2cy));

	// c = vec3_dot(cam2cy, cam2cy) - pow(vec3_dot(*obj->axic_vec, cam2cy), 2)
	// 	- obj->diameter / 2 * obj->diameter / 2;
    a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
    a*=a;
     b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec), vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));
     c = vec3_mag(vec3_cross(vec3_sub(*source_point, *obj->center),  *obj->axic_vec));
	c = c * c - (obj->diameter/2) *(obj->diameter/2);
    if(cam2cy.x == 0 && cam2cy.y == 0 && cam2cy.z == 0)
        ;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (NULL);
	intersections = (t_vec3 *)malloc(sizeof(t_vec3) * 2);
	if (intersections == NULL)
		return (NULL);
	intersections[0] = vec3_add(*source_point, 
			vec3_mul(dir, ((-b - sqrt(d)) / (2 * a))));
	intersections[1] = vec3_add(*source_point,
			vec3_mul(dir, ((-b + sqrt(d)) / (2 * a))));
	return (intersections);
}
double calc_cy_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{

    t_vec3  cam2cy;
    t_vec3  *intersections;
    // bool    flag;
    double  distance;

    cam2cy = vec3_sub(*source_point, *object->center);
    intersections = calc_cy_intersections(object, dir, cam2cy, source_point);
    if (intersections == NULL)
        return (-1);
    // flag = calc_cy_height(object, intersections, source_point);
    // if (flag == false)
	// {
	// 	free(intersections);
    //     return (-1);
	// }
    t_vec3 center2inner = vec3_sub(intersections[1],*object->center);
    t_vec3 center2outer = vec3_sub(intersections[0],*object->center);

    double h_outer = vec3_dot(center2outer, *object->axic_vec);
    double h_inner = vec3_dot(center2inner, *object->axic_vec);
    printf("h_outer:%f, h_inner:%f\n", h_outer, h_inner);
	// distance = vec3_mag(vec3_sub(*source_point, intersections[0]));
	if (h_outer >= 0 && h_outer <= object->height)
        distance = calc_cy_t2(object, dir, vec3_sub(*source_point, *object->center), 0,source_point);
        	// distance = vec3_mag(vec3_sub(*source_point, intersections[0]));
    else if(h_inner>= 0 && h_inner <= object->height)
		distance = calc_cy_t2(object, dir, vec3_sub(*source_point, *object->center), 1,source_point);
        	// distance = vec3_mag(vec3_sub(*source_point, intersections[1]));
    else
        distance = -1;
    free(intersections);
	return (distance);
}

double calc_distance(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
    if(obj->type == SPHERE)
        return (calc_sp_distance(obj, dir, source_point));
    else if(obj->type == PLANE)
        return(calc_pl_distance(obj, dir, source_point));
    else if(obj->type == CYLINDER)
        return(calc_cy_distance(obj, dir, source_point));
    return 0;
}

t_object *seach_nearest_obj(t_rt *rt, double x, double y)
{
    t_object    *nearest_obj;
    t_object    *obj;
    t_vec3     screen_vec;
    double      distance;
    double      min_distance;
    t_vec3      dir;
    min_distance = DISTANCE_MAX;
    screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
    obj = rt->scene->object;
    nearest_obj = obj;
    dir = vec3_norm(vec3_sub(screen_vec, *rt->scene->camera->view_point));
    // 各オブジェクトについて距離を計算し、最小のものをnearest_objに格納しています
    while(obj)
    {
        distance = calc_distance(obj, dir, rt->scene->camera->view_point);   
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
