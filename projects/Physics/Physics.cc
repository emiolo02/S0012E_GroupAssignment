#include "Physics.h"

namespace Physics
{
    CircleCollider::CircleCollider()
    {
    }

    CircleCollider::CircleCollider(vec2 pos, float rad, GameObj* par)
    {
        position = pos;
        radius = rad;
        parent = par;
    }

	HitResult
	CircleCollider::RayIntersect(Ray ray, float maxDist)
	{
        HitResult hit;
        vec2 oc = ray.b - this->position;
        vec2 dir = ray.m;
        float b = dot(oc, dir);

        // early out if sphere is "behind" ray
        if (b > 0)
            return HitResult();

        float a = dot(dir, dir);
        float c = dot(oc, oc) - this->radius * this->radius;
        float discriminant = b * b - a * c;

        if (discriminant <= 0)
            return HitResult();

        float div = 1.0f / a;
        float sqrtDisc = sqrt(discriminant);
        float temp = (-b - sqrtDisc) * div;
        float temp2 = (-b + sqrtDisc) * div;

        if (temp < maxDist)
        {
            vec2 p = ray.PointAt(temp);
            hit.p = p;
            hit.t = temp;
            hit.object = this->parent;
            return hit;
        }
        if (temp2 < maxDist)
        {
            vec2 p = ray.PointAt(temp2);
            hit.p = p;
            hit.t = temp2;
            hit.object = this->parent;
            return hit;
        }

        return HitResult();
	}

}