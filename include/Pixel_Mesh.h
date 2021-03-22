#ifndef PIXEL_MESH_H
#define PIXEL_MESH_H

#include <vector>
#include <string>
#include <fstream>
#include <Pixel_Window.h>
#include <Pixel_Color.h>
#include <Pixel_Vector.h>
#include <Pixel_Matrix.h>
#include <Pixel_Geometry.h>

namespace pixel
{
    enum RenderMode
    {
        WIREFRAME = 0,
        SOLID = 1,
    };

    enum RenderOption
    {
        ENABLE_BACKFACECULLING = 0,
        DISABLE_BACKFACECULLING = 1
    };

    struct Face
    {
        int a, b, c;

        Face() {}
        Face(int a, int b, int c) : a(a), b(b), c(c) {}
    };

    //A class that allows creating or modifying meshes
    class Mesh
    {
    private:
        Vec2 INTERNAL_PrespectiveProjection(Vec3 point)
        {
            //Preform prespective divison
            return Vec2(point.x / point.z, point.y / point.z);
        }

    private:
        std::vector<Vec3> vertices;
        std::vector<Face> edges;
        std::vector<Triangle> faces;

    public:
        Vec3 position;
        Vec3 rotation;
        Vec3 scale;
        Color color;
        RenderMode renderMode;
        RenderOption renderOption;

    public:
        Mesh()
        {
            renderMode = SOLID;
            renderOption = ENABLE_BACKFACECULLING;

            position.x = 0; 
            position.y = 0; 
            position.z = 0;

            rotation.x = 0; 
            rotation.y = 0; 
            rotation.z = 0;

            scale.x = 1; 
            scale.y = 1; 
            scale.z = 1;
        }
    
    public:
        template<typename... Ts>
        void SetVertices(Ts... _vertices)
        {
            Vec3 __vertices[] = {_vertices...};

            for(int i = 0; i < sizeof(__vertices) / sizeof(Vec3); i++)
                vertices.push_back(__vertices[i]);    
        }
        void SetVertices(std::vector<Vec3> _vertices)
        {
            vertices = _vertices;
        }
        std::vector<Vec3> GetVertices()
        {
            return vertices;
        }
        template<typename... Ts>
        void SetFaceData(Ts... _edges)
        {
            Face __edges[] = {_edges...};

            for(int i = 0; i < sizeof(__edges) / sizeof(Face); i++)
                edges.push_back(__edges[i]);
        }
        void SetFaceData(std::vector<Face> _edges)
        {
            edges = _edges;
        }
    
    public:
        void LoadMesh(const char* filepath)
        {
            vertices.clear();
            edges.clear();
            faces.clear();

            std::fstream objFile;
            objFile.open(filepath, std::ios::in);

            std::string data;

            while(!objFile.eof())
            {
                std::getline(objFile, data);

                if(data[0] == 'v' && data[1] == ' ')
                {
                    int c = 0;
                    std::string value;
                    Vec3 vertex;

                    for(int i = 2; i <= data.size(); i++)
                    {
                        if(data[i] != ' ' && data[i] != '\0')
                            value.push_back(data[i]);
                        else
                        {
                            c++;

                            if(c == 1)
                                vertex.x = strtof(value.c_str(), nullptr);
                            else if(c == 2)
                                vertex.y = strtof(value.c_str(), nullptr);
                            else if(c == 3)
                                vertex.z = strtof(value.c_str(), nullptr);
                            
                            value.clear();
                        }
                    }

                    vertices.push_back(vertex);
                }
                else if(data[0] == 'f' && data[1] == ' ')
                {
                    int c = 0;
                    std::string value;
                    Face edge;

                    int size = data.size();

                    for(int i = 2; i > 0 && i <= data.size(); i++)
                    {
                        if(data[i] != ' ' && data[i] != '\0' && data[i] != '/')
                            value.push_back(data[i]);
                        else
                        {
                            c++;

                            if(c == 1)
                                edge.a = strtol(value.c_str(), nullptr, 10);
                            else if(c == 2)
                                edge.b = strtol(value.c_str(), nullptr, 10);
                            else if(c == 3)
                                edge.c = strtol(value.c_str(), nullptr, 10);
                            i = data.find(' ', i);

                            value.clear();
                        }
                    }

                    edges.push_back(edge);
                }
            }

            objFile.close();
        }

    public:
        void UpdateMesh()
        {
            faces.clear();

            for(int i = 0; i < edges.size(); i++)
            {
                #pragma region Get vertices
                Vec3 normal;                        
                Vec3 untransformedVertices[3];      
                Vec3 transformedVertices[3];        
                Vec2 projectedVertices[3];          

                Face _edge = edges[i];

                untransformedVertices[0] = vertices[_edge.a - 1];
                untransformedVertices[1] = vertices[_edge.b - 1];
                untransformedVertices[2] = vertices[_edge.c - 1];
                #pragma endregion

                #pragma region Transformations
                for(int j = 0; j < 3; j++)
                {
                    transformedVertices[j] = untransformedVertices[j];

                    //Generate world matrix
                    Matrix4 rotateMatrixX = Matrix4::RotateX(this->rotation.x);
                    Matrix4 rotateMatrixY = Matrix4::RotateY(this->rotation.y);
                    Matrix4 rotateMatrixZ = Matrix4::RotateZ(this->rotation.z);
                    Matrix4 scaleMatrix = Matrix4::Scale(this->scale);
                    Matrix4 translateMatrix = Matrix4::Translate(this->position);

                    Matrix4 worldMatrix = Matrix4::Identity();
                    worldMatrix = rotateMatrixZ * worldMatrix;
                    worldMatrix = rotateMatrixY * worldMatrix;
                    worldMatrix = rotateMatrixX * worldMatrix;
                    worldMatrix = scaleMatrix * worldMatrix;
                    worldMatrix = translateMatrix * worldMatrix;

                    transformedVertices[j] = worldMatrix * transformedVertices[j];
                }
                #pragma endregion

                #pragma region Face normal
                Vec3 a = transformedVertices[0];
                Vec3 b = transformedVertices[1];
                Vec3 c = transformedVertices[2];

                Vec3 ab = b - a;
                Vec3 ac = c - a;
                ab = Vec3::Normalize(ab);
                ac = Vec3::Normalize(ac);

                normal = Vec3::Cross(ab, ac);
                normal = Vec3::Normalize(normal);
                #pragma endregion

                #pragma region Back-Face Culling
                if(renderOption == ENABLE_BACKFACECULLING)
                {
                    Vec3 cameraRay = -(a - Vec3(0, 0, 0));

                    float dot = Vec3::Dot(cameraRay, normal);
                    if(dot < 0)
                        continue;
                }
                #pragma endregion

                #pragma region Flat-Shading
                float colorIntensity = -Vec3::Dot(Vec3(0, 0, 1), normal);
                #pragma endregion

                #pragma region Projection
                for(int j = 0; j < 3; j++)
                {
                    projectedVertices[j] = INTERNAL_PrespectiveProjection(transformedVertices[j]);
                    projectedVertices[j].x *= 100;
                    projectedVertices[j].y *= 100;
                }
                #pragma endregion

                #pragma region Create triangle
                faces.push_back(Triangle(projectedVertices, color * colorIntensity));
                #pragma endregion
            }
        }
        void RenderMesh(Window* window)
        {
            for(int i = 0; i < faces.size(); i++)
            {
                switch (renderMode)
                {
                    case WIREFRAME:
                    {
                        faces[i].DrawNoFill(window);
                        break;
                    }
                    case SOLID:
                    {
                        faces[i].DrawFill(window);
                        break;
                    }
                }   
            }
        }
    }; 
};

#endif