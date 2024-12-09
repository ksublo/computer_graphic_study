#pragma once
#include <string>
#include <vector>

struct Vertex {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class ObjectLoader {
public:

    ObjectLoader();
    bool load(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};