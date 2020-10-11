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

#include <vector>
#include <windows.h>
#include <tchar.h>
#include <algorithm>

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


void Raytrace(Image& image, Scene* scene, Camera* c) {

    int width = image.getWidth();
    int height = image.getHeight();

    std::cout << "Timer: " << std::endl;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            float X = 2.0f * x / width - 1;
            float Y = -2.0f * y / height + 1;

            Ray r = c->getRay(X, Y);
            Intersection i(r);

            if (scene->S.intersect(i)) {

                Color localColor = i.pShape->getColor(i, &scene->S, &scene->L, 3);
                // apply interpolation
                image.changePixel(localColor, y, x);
            }

        }

        if (x % (int)(width / 20) == 0)
            std::cout << "#";
    }

    std::cout << std::endl;
}

void read_directory(const std::string& folder, std::vector<std::string>& files)
{
    //std::vector<std::string> files;
    WIN32_FIND_DATA data;
    HANDLE hFind;

    std::string buffer;

    std::string prefix = folder;
    prefix.append("\\");
    std::string pattern = prefix;
    pattern.append("*.txt");

    std::wstring patternw(pattern.begin(), pattern.end());
    const wchar_t* c = patternw.c_str();

    if ((hFind = FindFirstFile(c, &data)) != INVALID_HANDLE_VALUE) {

        std::wstring first = data.cFileName;
        std::string str1(first.begin(), first.end());
        buffer.append(prefix);
        buffer.append(str1);
        files.emplace_back(buffer);
        buffer.clear();

        while (FindNextFile(hFind, &data) != 0) {

            std::wstring temp = data.cFileName;
            std::string str(temp.begin(), temp.end());
            buffer.append(prefix);
            buffer.append(str);
            files.emplace_back(buffer);
            buffer.clear();
        }
        FindClose(hFind);
    }
}

int main()
{

    int height = 600;
    int width = 800;

    std::vector<std::string> files;
    read_directory("Scene", files);

    int counter = 10000;

    for (const auto& file : files) {

        Scene s;
        if (s.fromFile(file)) {
            std::cout << "Reading Scene: " << file << std::endl;
        }

        Camera c(
            Point(-200.f, 0.0f, 0.f),
            Vector3(1.0f, 0.0f, 0.0f),
            Vector3(0.0f, 0.0f, 1.0f),
            30.0f * PI / 180.0f,
            (float)width / (float)height
        );

        Image img(width, height);

        Raytrace(img, &s, &c);

        std::string exportf = "imgs\\";
        exportf.append(std::to_string(counter));

        exportf.append(".png");

        if (img.saveImage(exportf))
            std::cout << exportf << " saved!" << std::endl;

        counter++;

        break;


    }

    

    return 0;
}