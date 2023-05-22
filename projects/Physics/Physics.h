#include "core/math/mat4.h"
#include <vector>

class GameObj;

namespace Physics
{
    struct HitResult
    {
        // hit point
        vec2 p;
        // hit object, or nullptr
        GameObj* object = nullptr;
        // intersection distance
        float t = 99999;
    };

    class Ray
    {
    public:
        Ray(vec2 startpoint, vec2 dir) :
            b(startpoint),
            m(dir)
        {

        }

        ~Ray()
        {

        }

        vec2 PointAt(float t)
        {
            return { b + m * t };
        }

        // beginning of ray
        vec2 b;
        // magnitude and direction of ray
        vec2 m;
    };

    class Collider
    {
    public:
        vec2 position;
        GameObj* parent;

        virtual HitResult RayIntersect(Ray ray, float maxDist) { return HitResult(); }
    };

    class CircleCollider : public Collider
    {
    public:
        float radius;

        CircleCollider();

        CircleCollider(vec2 pos, float rad, GameObj* par);

        HitResult RayIntersect(Ray ray, float maxDist) override;
    };

}