#include "Material.h"

Material::Material() :
    color(Color()),
    ambient(0.4f),
    diffuse(0.5f),
    specular(0.6f),
    shinyness(80),
    refraction(0.0f)
{}

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

