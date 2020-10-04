#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

struct Material {
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shinyness;
    float refraction;

    Material(
        Color c,
        float ambient,
        float diffuse,
        float specular,
        float shinyness,
        float refraction);
    virtual ~Material();
};



#endif // !MATERIAL_H