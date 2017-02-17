#include "naiveintegrator.h"

Color3f NaiveIntegrator::Li(const Ray &ray, const Scene &scene, std::shared_ptr<Sampler> sampler, int depth) const
{
    //TODO
    //omega 0 should be treated as the inverse of the ray

    Color3f liColor = glm::vec3(0.0);
    Color3f totalColor = glm::vec3(0.0);

    Intersection isec = Intersection();
    if(scene.Intersect(ray,&isec))
    {
        Vector3f wo = -ray.direction;
        Color3f leColor = isec.Le(wo);

        if(depth>0)
        {
            if(isec.bsdf!=nullptr)
            {
                Color3f woW = wo;
                Color3f wiW;
                float currentPdf;
                Color3f fColor = isec.bsdf->Sample_f(woW,&wiW,sampler->Get2D(),&currentPdf);
                Ray newRay = isec.SpawnRay(wiW);
                liColor = Li(newRay, scene,sampler, depth--);
                totalColor = leColor + fColor*liColor*AbsDot(wiW,isec.normalGeometric)/currentPdf;
            }
            else
            {
                totalColor = leColor;
            }

        }
        else
        {
            totalColor = leColor;
        }
    }
    return totalColor;
}
