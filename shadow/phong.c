/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/31 14:28:38 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"

double  calc_cy_t(t_object *obj, t_vec3 dir, t_vec3 cam2cy, int flag)
{
    double	a;
	double	b;
	double	c;
	double	d;
    a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *obj->axic_vec), 2);
    // a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
    // a*=a;
	b = 2 * (vec3_dot(dir, cam2cy) - vec3_dot(dir, *obj->axic_vec)
			* vec3_dot(*obj->axic_vec, cam2cy));
    //  b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec), vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));

	c = vec3_dot(cam2cy, cam2cy) - pow(vec3_dot(*obj->axic_vec, cam2cy), 2)
		- obj->diameter / 2 * obj->diameter / 2;
    //  c = vec3_mag(vec3_cross(vec3_sub(*source_point, *obj->center),  *obj->axic_vec));
	// c = c * c - (obj->diameter/2) *(obj->diameter/2);
    //  if(cam2cy.x == 0 && cam2cy.y == 0 && cam2cy.z == 0)
        // ;
	d = b * b - 4 * a * c;

    if(flag == 1)
        return (-b + sqrt(d)) / (2 * a);
    
    return (-b - sqrt(d)) / (2 * a);
}
// TODO　centerを使わないやり方にリファクタする
int phong_calc(t_scene *scene, t_vec3 screen_vec, t_object *nearest_obj, t_rt *rt)
{
    //ここの係数関係どうすれば、、？
    double ka=0.8;
    double kd=0.8;
    double ks=0.8;
    int shininess = 10;
    t_vec3 dir_vec = vec3_norm(vec3_sub(screen_vec, *scene->camera->view_point));
    double t = calc_distance(nearest_obj, dir_vec, scene->camera->view_point);
    t_vec3 intersection = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, t));
    t_vec3 normal;
    if(rt)
    ;
    //正規化による方向ベクトルの算出
    if(nearest_obj->type == SPHERE){
            normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
    }
    if(nearest_obj->type == PLANE)
        normal = *nearest_obj->normal_vec;
    if(nearest_obj->type == CYLINDER)
    {
        //         t_vec3  *intersections = calc_cy_intersections(nearest_obj, dir_vec, vec3_sub(*scene->camera->view_point, *nearest_obj->center), scene->camera->view_point);
        // t_vec3  intersection = intersections[0];
        // t_vec3  center2intersection = vec3_sub(intersection,*nearest_obj->center);
        // double  intersection_height = vec3_dot(center2intersection, *nearest_obj->axic_vec);
        // printf("height:%f\n", intersection_height);
        // if (intersection_height > rt->height)
        //     return (0xffffff);
        // t_vec3  vertical_vec = vec3_add(*nearest_obj->center,
        //         vec3_mul(*nearest_obj->axic_vec, intersection_height));
        // normal = vec3_norm(vec3_sub(intersection, vertical_vec));
    double	a;
	double	b;
	double	c;
	double	d;
    a = vec3_dot(dir_vec, dir_vec) - pow(vec3_dot(dir_vec, *nearest_obj->axic_vec), 2);
    	b = 2 * (vec3_dot(dir_vec, vec3_sub(*scene->camera->view_point, *nearest_obj->center)) - vec3_dot(dir_vec, *nearest_obj->axic_vec)
			* vec3_dot(*nearest_obj->axic_vec, vec3_sub(*scene->camera->view_point, *nearest_obj->center)));
            c = vec3_dot(vec3_sub(*scene->camera->view_point, *nearest_obj->center), vec3_sub(*scene->camera->view_point, *nearest_obj->center)) - pow(vec3_dot(*nearest_obj->axic_vec, vec3_sub(*scene->camera->view_point, *nearest_obj->center)), 2)
		- nearest_obj->diameter / 2 * nearest_obj->diameter / 2;
        d = b * b - 4 * a * c;
        if( d < 0 )
            printf("d is negative\n");
            // normal = *nearest_obj->normal_vec;
        double inner_t = (-b + sqrt(d)) / (2 * a);
        double outer_t = (-b - sqrt(d)) / (2 * a);
        // printf("inner_t:%f, outer_t:%f\n", inner_t, outer_t);
        // t_vec3  *intersections = calc_cy_intersections(nearest_obj, dir_vec, vec3_sub(*scene->camera->view_point, *nearest_obj->center), scene->camera->view_point);
        t_vec3 intersection_inner = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, inner_t));
        t_vec3 intersection_outer = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, outer_t));
        t_vec3  center2intersection_inner = vec3_sub(intersection_inner,*nearest_obj->center);
        t_vec3  center2intersection_outer = vec3_sub(intersection_outer,*nearest_obj->center);
        // t_vec3  center2intersection_inner = vec3_sub(*nearest_obj->center,intersection_inner);
        // t_vec3  center2intersection_outer = vec3_sub(*nearest_obj->center,intersection_outer);
        // t_vec3 vertical_vec ;
        double  intersection_height_inner = vec3_dot(center2intersection_inner, *nearest_obj->axic_vec);
        double  intersection_height_outer = vec3_dot(center2intersection_outer, *nearest_obj->axic_vec);

        // if (intersection_height > rt->height)
        // printf("height:%f\n", nearest_obj->height);
        // printf("inner:%f, outer:%f\n", intersection_height_inner, intersection_height_outer);
        if( intersection_height_outer>=0&& intersection_height_outer <= nearest_obj->height)
        {
            //   vertical_vec = vec3_add(*nearest_obj->center,
            // vec3_mul(*nearest_obj->axic_vec, intersection_height_inner));
            normal = vec3_norm(vec3_sub(center2intersection_outer, vec3_mul(*nearest_obj->axic_vec, intersection_height_outer)));
            // printf("inner\n");
            intersection = intersection_inner;
            // t = inner_t;
            t = vec3_mag(vec3_sub(*scene->camera->view_point, intersection_inner));
        }
        else if( intersection_height_inner>=0 && intersection_height_inner <= nearest_obj->height)
        {
        //   vertical_vec = vec3_add(*nearest_obj->center,
        //         vec3_mul(*nearest_obj->axic_vec, intersection_height_outer));
            // printf("outer\n");
            normal = vec3_norm(vec3_sub(vec3_mul(*nearest_obj->axic_vec,intersection_height_inner), center2intersection_inner));
            intersection = intersection_outer;
            // t = outer_t;
            t = vec3_mag(vec3_sub(*scene->camera->view_point, intersection_outer));
        }
        else 
            printf("error\n");
        // t=calc_cy_t(nearest_obj, dir_vec, vec3_sub(*scene->camera->view_point, *nearest_obj->center));
        // t=calc_cy_distance(nearest_obj, dir_vec, scene->camera->view_point);
        // printf("normal:%f,%f,%f\n", normal.x, normal.y, normal.z);
        // normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
        // t_vec3 cylinder_axis = vec3_norm(*nearest_obj->axic_vec); // 円柱の軸（通常は単位ベクトルとして定義）
        // t_vec3 intersection_to_center = vec3_sub(intersection, *nearest_obj->center);
        // t_vec3 projection_on_axis = vec3_mul(cylinder_axis, vec3_dot(intersection_to_center, cylinder_axis));
        // normal = vec3_norm(vec3_sub(intersection_to_center, projection_on_axis));
    }
        // printf("intersection:%f,%f,%f\n", intersection.x, intersection.y, intersection.z);
    t_vec3 light_vec = vec3_norm(vec3_sub(*scene->light->light_point,intersection));
    t_vec3 view_vec = vec3_norm(vec3_sub(intersection, *scene->camera->view_point));
    t_vec3 reflect_vec = vec3_reflect(vec3_mul(light_vec, -1), normal);
    // normal = vec3_mul(normal, -1);
    // reflect_vec = vec3_mul(reflect_vec, -1);
    double amb = scene->ambi_light->ratio * ka ;

    double diff = vec3_dot(normal, light_vec) * scene->light->bright_ratio * kd;
    if(vec3_dot(normal, light_vec) <= 0)
        diff = 0;

    // double spec = pow(fmax(vec3_dot(view_vec, reflect_vec), 0.0), shininess) * scene->light->bright_ratio * ks;
    // printf("reflect_vec:%f,%f,%f\n", reflect_vec.x, reflect_vec.y, reflect_vec.z);
    // printf("light_vec:%f,%f,%f\n", light_vec.x, light_vec.y, light_vec.z);
    // printf("view_vec:%f,%f,%f\n", view_vec.x, view_vec.y, view_vec.z);
    double spec = pow(vec3_dot(view_vec, reflect_vec), shininess) * scene->light->bright_ratio * ks;
    
    if(vec3_dot(view_vec, reflect_vec) < 0)
        spec = 0;
    if(is_shadow(scene, t, dir_vec))
    {
        diff = 0;
        spec = 0;
    }
    // if(nearest_obj->type == CYLINDER)
        // printf("amb:%f, diff:%f, spec:%f\n", amb, diff, spec);
    double brightness = amb + diff + spec; 
    /* (void)spec; */
    /* double brightness = amb + diff; */
    int color_r = (int)(fmin(nearest_obj->rgb->r * brightness , 1.0) * 255);
    int color_g = (int)(fmin(nearest_obj->rgb->g * brightness , 1.0) * 255);
    int color_b = (int)(fmin(nearest_obj->rgb->b * brightness , 1.0) * 255);

    int color = (color_r << 16) | (color_g << 8) | color_b;
    return color;
}
