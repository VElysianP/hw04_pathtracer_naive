#include "naiveintegrator.h"

Color3f NaiveIntegrator::Li(const Ray &ray, const Scene &scene, std::shared_ptr<Sampler> sampler, int depth) const
{
    //TODO
    //omega 0 should be treated as the inverse of the ray

    Color3f liColor = glm::vec3(0.0);
    Color3f totalColor = glm::vec3(0.0);
    if(depth<recursionLimit)
    {
        Intersection isec = Intersection();
        scene.Intersect(ray,isec);
        Vector3f wo = -ray.direction;

        Color3f leColor = isec.Le(wo);

        Ray newRay = isec.SpawnRay(wo);
        Color3f wi = newRay.direction;
        liColor = liColor + Li(newRay,scene,sampler,depth+1);

        if(isec.objectHit->name!="Light Source")
        {
            BSDF* bsdfPointer = isec.bsdf;
            Color3f fColor = bsdfPointer->f(BSDF::tangentToWorld(wo),BSDF::tangentToWorld(wi));
            totalColor = totalColor + fColor*liColor*AbsCosTheta(wi);
        }

    }

    return totalColor+leColor;
}
