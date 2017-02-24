#include "diffusearealight.h"

Color3f DiffuseAreaLight::L(const Intersection &isect, const Vector3f &w) const
{
    //TODO
    Vector3f invW = -w;

    if(twoSided)
    {
        return emittedLight;
    }
    else
    {
        Normal3f intersectionNormal = isect.normalGeometric;
        if(glm::dot(intersectionNormal, invW)>0)
        {
            return glm::vec3(0.0);
        }
        else
        {
            return emittedLight;
        }
    }

}
