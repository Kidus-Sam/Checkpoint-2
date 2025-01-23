#include "Model.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

Model::Model()
{
    triangles = vector<Triangle3D>();
}

int Model::numTriangles()
{
    return triangles.size();
}

Triangle3D Model::operator[](int i)
{
    return triangles[i];
}

void Model::transform(Matrix4 m)
{
    for (int i = 0; i < numTriangles(); i++)
    {
        if (triangles[i].shouldDraw)
        {
            Triangle3D t = triangles[i];
            cout << "Before v1 = " << t.v1.x << ", " << t.v1.y << ", " << t.v1.z << ", " << t.v1.w << endl;
            t.transform(m);
            cout << "After v1 = " << t.v1.x << ", " << t.v1.y << ", " << t.v1.z << ", " << t.v1.w << endl;
            triangles[i] = t;
        }
    }
}

void Model::readFromOBJFile(string filepath, Color pFillColor)
{
    vector<Vector4> vertices;
    int count = 1;
    int count2 = 1;
    ifstream myFile(filepath);
    if (myFile.is_open())
    {
        string line;
        float vx;
        float vy;
        float vz;
        while (getline(myFile, line))
        {
            if (line[0] == '#')
            {
            }
            else if (line[0] == 'v')
            {
                istringstream s(line);
                string myWord;
                while (getline(s, myWord, ' '))
                {
                    if (count % 4 == 1)
                    {
                    }
                    else if (count % 4 == 2)
                    {
                        vx = atof(myWord.c_str());
                    }
                    else if (count % 4 == 3)
                    {
                        vy = atof(myWord.c_str());
                    }
                    else
                    {
                        vz = atof(myWord.c_str());
                    }
                    count++;
                }
                vertices.push_back(Vector4(vx, vy, vz, 1));
            }
            else if (line[0] == 'f')
            {
                istringstream s(line);
                string myWord;
                while (getline(s, myWord, ' '))
                {
                    if (count2 % 4 == 1)
                    {
                    }
                    else if (count2 % 4 == 2)
                    {
                        vx = atof(myWord.c_str());
                    }
                    else if (count2 % 4 == 3)
                    {
                        vy = atof(myWord.c_str());
                    }
                    else
                    {
                        vz = atof(myWord.c_str());
                    }
                    count2++;
                }
                triangles.push_back(Triangle3D(vertices[vx - 1], vertices[vy - 1], vertices[vz - 1], pFillColor, pFillColor, pFillColor));
            }
        }
    }
}

void Model::homogenize()
{
    for (int i = 0; i < numTriangles(); i++)
    {
        Triangle3D t = triangles[i];
        //     cout << "Before Divide v1 = " << t.v1.x << ", "<< t.v1.y <<", " << t.v1.z << ", " << t.v1.w <<  endl;
        t.v1 = t.v1 * (1.0f / t.v1.w);
        t.v2 = t.v2 * (1.0f / t.v2.w);
        t.v3 = t.v3 * (1.0f / t.v3.w);
        triangles[i] = t;
        //    cout << "After Divide v1 = " << t.v1.x << ", "<< t.v1.y <<", " << t.v1.z << ", "<< t.v1.w << endl;
    }
}

void Model::performBackfaceCulling(Vector4 eye, Vector4 spot)
{
    Vector4 look = spot - eye;

    for (int i = 0; i < numTriangles(); i++)
    {
        Vector4 a = triangles[i].v1 - triangles[i].v2;
        Vector4 b = triangles[i].v3 - triangles[i].v2;
        Vector4 normal = a.cross(b);
        if (look.dot(normal) > 0.0)
        {
             triangles[i].shouldDraw = false;
            // triangles[i].c1 = Blue;
            // triangles[i].c2 = Blue;
            // triangles[i].c3 = Blue;
        }
    }
}