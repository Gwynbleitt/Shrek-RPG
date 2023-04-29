#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Animation.h"

#pragma once

class Model
{

protected:
    
    std::string m_dir;
    
public:

    glm::mat4 m_Mtransfrom;

    std::vector<Mesh> m_mesh;
    
    //loades model from give file path. extracts meshes in m_mesh vector
    void LoadModel(const std::string& path);

    
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    void PlayAnim(Animation Anim, bool Loop);

    Model();
};