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
    enum RenderMode
    {
        WIREFRAME = 0,
        SOLID = 1,
        WIREFRAME_AND_SOLID = 2
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
        Vec2 PrespectiveProjection(Vec3 point)
        {
            //Preform prespective divison
            return Vec2((point.x * scale.x) / point.z, (point.y * scale.y) / point.z);
        }
        float BackFaceCull(Vec3 faceVertices[])
        {
            Vec3 a = faceVertices[0];
            Vec3 b = faceVertices[1];
            Vec3 c = faceVertices[2];

            Vec3 ab = a - b;
            Vec3 ac = a - c;

            Vec3 normal = Vec3::Cross(ab, ac);
            normal = Vec3::Normalize(normal);

            Vec3 cameraRay = Vec3(0, 0, 0) - a;

            return Vec3::Dot(cameraRay, normal);
        }

    private:
        std::vector<Vec3> vertices;
        std::vector<Face> faceData;
        std::vector<Triangle> faces;

    public:
        Vec3 transform;
        Vec3 rotation;
        Vec3 scale;
        RenderMode renderMode;
        RenderOption renderOption;

    public:
        Mesh()
        {
            renderMode = WIREFRAME_AND_SOLID;
            renderOption = ENABLE_BACKFACECULLING;
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
            vertices.clear();
            faceData.clear();
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
                Vec3 untransformedVertices[3];      //Array to hold vertices that haven't been tranformed yet
                Vec3 transformedVertices[3];        //Array to hold vertices that hes been transformed
                Vec2 projectedVertices[3];          //Array to hold vertices that has been projected and ready to render

                Face _faceData = faceData[i];

                //Get correct vertices using face data and store them
                untransformedVertices[0] = vertices[_faceData.a - 1];
                untransformedVertices[1] = vertices[_faceData.b - 1];
                untransformedVertices[2] = vertices[_faceData.c - 1];

                //Loop through all vertices of a triangle and apply transformations
                for(int j = 0; j < 3; j++)
                {
                    transformedVertices[j] = untransformedVertices[j];

                    //Rotate
                    transformedVertices[j] = Vec3::RotateX(transformedVertices[j], rotation.x);
                    transformedVertices[j] = Vec3::RotateY(transformedVertices[j], rotation.y);
                    transformedVertices[j] = Vec3::RotateZ(transformedVertices[j], rotation.z);

                    //Transform z-axis
                    transformedVertices[j].z += transform.z;
                }

                //Preform back-face culling
                if(renderOption == ENABLE_BACKFACECULLING)
                    if(BackFaceCull(transformedVertices) < 0)
                        continue;

                //Apply projection for all vertices of a triangle for rendering
                for(int j = 0; j < 3; j++)
                {
                    //Scale and project
                    projectedVertices[j] = PrespectiveProjection(transformedVertices[j]);

                    //Transform x-axis and y-axis
                    projectedVertices[j].x += transform.x;
                    projectedVertices[j].y += transform.y;
                }

                //Create a new triangle and add it to the faces array
                faces.push_back(Triangle(projectedVertices));
            }
        }
        void RenderMesh(Window* window, uint32_t color)
        {
            for(int i = 0; i < faces.size(); i++)
            {
                switch (renderMode)
                {
                    case WIREFRAME:
                    {
                        faces[i].DrawNoFill(window, color);
                        break;
                    }
                    case SOLID:
                    {
                        faces[i].DrawFill(window, color);
                        break;
                    }
                    case WIREFRAME_AND_SOLID:
                    {
                        faces[i].DrawFill(window, color);
                        faces[i].DrawNoFill(window, 0xFF000000);
                        break;
                    }
                }   
            }
        }
    }; 
};

#endif