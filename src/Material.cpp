#include "Material.h"


Material::Material( Color c, float ambient, float diffuse, float specular, float shinyness, float refraction) :
    color(c),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    shinyness(shinyness),
    refraction(refraction)
{}

Material::~Material()
{}

