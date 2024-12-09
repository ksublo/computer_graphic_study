#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

#include "ObjectLoader.h"

ObjectLoader::ObjectLoader()
{
}

bool ObjectLoader::load(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate |
        aiProcess_OptimizeMeshes |
        aiProcess_JoinIdenticalVertices |
        aiProcess_CalcTangentSpace;

    const aiScene* scene = importer.ReadFile(filePath, importOptions);

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];

        for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
            Vertex vertex;

            vertex.Position[0] = mesh->mVertices[j].x;
            vertex.Position[1] = mesh->mVertices[j].y;
            vertex.Position[2] = mesh->mVertices[j].z;

            vertex.Normal[0] = mesh->mNormals[j].x;
            vertex.Normal[1] = mesh->mNormals[j].y;
            vertex.Normal[2] = mesh->mNormals[j].z;

            if (mesh->HasTextureCoords(0)) {
                vertex.Texture[0] = mesh->mTextureCoords[0][j].x;
                vertex.Texture[1] = mesh->mTextureCoords[0][j].y;
            }

            if (mesh->HasTangentsAndBitangents()) {
                vertex.Tangent[0] = mesh->mTangents[j].x;
                vertex.Tangent[1] = mesh->mTangents[j].y;
                vertex.Tangent[2] = mesh->mTangents[j].z;
            }

            vertices.push_back(vertex);
        }

        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace& face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(face.mIndices[k]);
            }
        }
    }

    
    return true;
}
