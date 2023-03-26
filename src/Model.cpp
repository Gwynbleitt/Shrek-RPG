#include "Model.h"

Model::Model()
{
    m_Mtransfrom = glm::mat4(1.0f);
}


void Model::LoadModel(const std::string& path)
{
    
    Assimp::Importer importer;
    
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
        exit(EXIT_FAILURE);
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        m_mesh.push_back(processMesh(mesh, scene));			
    }
  
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
} 

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    bool flags[3] = {false, false, false};

    if(mesh->HasNormals()) flags[0] = true;
    if(mesh->mTextureCoords[0]) flags[1] = true;
    if(mesh->HasBones()) flags[2] = true;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        glm::vec3 TMP;
        glm::vec2 TMP_2;
        Vertex vertex;
    
        TMP.x = mesh->mVertices[i].x/2;
        TMP.y = mesh->mVertices[i].y/2;
        TMP.z = mesh->mVertices[i].z/2;
        vertex.Position = TMP;

        if (flags[0])
        {
            TMP.x = mesh->mNormals[i].x;
            TMP.y = mesh->mNormals[i].y;
            TMP.z = mesh->mNormals[i].z;
            vertex.Normal = TMP;
        }

        if (flags[1])
        {
            TMP_2.x = mesh->mTextureCoords[0][i].x;
            TMP_2.y = mesh->mTextureCoords[0][i].y;
            vertex.Tcord = TMP_2;
        }

        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }
    
    return Mesh(vertices, indices, GL_STATIC_DRAW, flags);
}  