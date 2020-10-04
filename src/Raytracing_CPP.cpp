// Raytracing_CPP.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include "Vector.h"
#include "filereader.h"
#include "Ray.h"
#include "Color.h"
#include "Material.h"
#include "Camera.h"
#include "Image.h"

// Color Blueprints
static Color white(1.0f, 1.0f, 1.0f);
static Color black(0.0f, 0.0f, 0.0f);
static Color gray(0.48f, 0.48f, 0.48f);
static Color blue(0.0f, 0.403f, 0.498f);
static Color red(0.447f, 0.08f, 0.048f);
static Color green(0.431f, 0.627f, 0.274f);
static Color light_green(0.862f, 0.929f, 0.756f);
static Color light_pink(0.99f, 0.756f, 0.666f);
static Color orange(0.901f, 0.568f, 0.137f);

// material blueprints
static Material MatGray(gray, 0.7f, 0.9f, 0.9f, 80.0f, 0.8f);
static Material MatBlue(blue, 0.7f, 0.9f, 0.9f, 80.0f, 0.8f);
static Material MatRed(white, 0.7f, 0.9f, 0.9f, 80.0f, 0.8f);
static Material MatOrange(orange, 0.7f, 0.9f, 0.9f, 80.0f, 0.0f);
static Material MatGreen(green, 0.7f, 0.9f, 0.9f, 80.0f, 0.0f);

void Raytrace(Image& image, Scene* scene, Camera* c) {

    int width = image.getWidth();
    int height = image.getHeight();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            float X = 2.0f * x / width - 1;
            float Y = -2.0f * y / height + 1;

            Ray r = c->getRay(X, Y);
            //r.print();

            Intersection i(r);

            Color pixel = black;

            if (scene->S.intersect(i)) {
                std::cout << "Intersection" << std::endl;
                pixel = i.color;
            }
        }
    }
}

int main()
{

    int height = 60;
    int width = 80;


    // loading scene from file 
    Scene s;
    if (s.fromFile("params.txt")){
        std::cout << "Scene successfully loaded!" << std::endl;
    }
    
    Camera c(
        Point(-200.f, 0.0f, 70.f),
        Vector3(1.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 1.0f),
        15.0f * PI / 180.0f,
        (float)width / (float)height
    );

    Image img(width, height);

    //Raytrace(img, &s, &c);

    Ray r(Point(0.0, 0.0, 0.0), Vector3(1., 0., 0.));
    Sphere test(Point(2.0, 0.0, 0.0), 1, MatGray);
    Intersection i(r);

    if (test.intersect(i))
        std::cout << "Yes" << std::endl;

    
    return 0;
}
