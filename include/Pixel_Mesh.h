#ifndef PIXEL_MESH_H
#define PIXEL_MESH_H

#include <vector>
#include <string>
#include <fstream>
#include <Pixel_Window.h>
#include <Pixel_Vector.h>
#include <Pixel_Geometry.h>

namespace pixel
{
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
        Vec2 PrespectiveProjection(Vec3 point)
        {
            return Vec2((point.x * scale.x) / point.z, (point.y * scale.y) / point.z);
        }

    private:
        std::vector<Vec3> vertices;
        std::vector<Face> faceData;
        std::vector<Triangle> faces;

    public:
        Vec3 transform;
        Vec3 rotation;
        Vec3 scale;

    public:
        Mesh() {}
    
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
        void SetFaceData(Ts... _faceData)
        {
            Face __faceData[] = {_faceData...};

            for(int i = 0; i < sizeof(__faceData) / sizeof(Face); i++)
                faceData.push_back(__faceData[i]);
        }
        void SetFaceData(std::vector<Face> _faceData)
        {
            faceData = _faceData;
        }
    
    public:
        void LoadMesh(const char* filepath)
        {
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
                    Face face;

                    int size = data.size();

                    for(int i = 2; i > 0 && i <= data.size(); i++)
                    {
                        if(data[i] != ' ' && data[i] != '\0' && data[i] != '/')
                            value.push_back(data[i]);
                        else
                        {
                            c++;

                            if(c == 1)
                                face.a = strtol(value.c_str(), nullptr, 10);
                            else if(c == 2)
                                face.b = strtol(value.c_str(), nullptr, 10);
                            else if(c == 3)
                                face.c = strtol(value.c_str(), nullptr, 10);
                            i = data.find(' ', i);

                            value.clear();
                        }
                    }

                    faceData.push_back(face);
                }
            }

            objFile.close();
        }
    
    public:
        void UpdateMesh()
        {
            faces.clear();

            for(int i = 0; i < faceData.size(); i++)
            {
                Vec3 toProjectVertices[3];
                Vec2 projectedVertices[3];

                Face _faceData = faceData[i];

                toProjectVertices[0] = vertices[_faceData.a - 1];
                toProjectVertices[1] = vertices[_faceData.b - 1];
                toProjectVertices[2] = vertices[_faceData.c - 1];

                for(int j = 0; j < 3; j++)
                {
                    Vec3 toProjectVertix = toProjectVertices[j];

                    //Rotate
                    toProjectVertix = Vec3::RotateX(toProjectVertices[j], rotation.x);
                    toProjectVertix = Vec3::RotateY(toProjectVertix, rotation.y);
                    toProjectVertix = Vec3::RotateZ(toProjectVertix, rotation.z);

                    //Transform
                    toProjectVertix.x += transform.x;
                    toProjectVertix.y += transform.y;
                    toProjectVertix.z += transform.z;

                    //Scale and project
                    projectedVertices[j] = PrespectiveProjection(toProjectVertix);
                }

                    faces.push_back(Triangle(projectedVertices));
                }
        }
        void RenderMesh(Window* window, uint32_t color)
        {
            for(int i = 0; i < faces.size(); i++)
                faces[i].DrawNoFill(window, color);
        }
    }; 
};

#endif