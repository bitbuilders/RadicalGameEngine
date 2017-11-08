#include "stdafx.h"
#include "myMeshLoader.h"
#include <fstream>


namespace MyMeshLoader
{
	bool LoadMesh(const std::string & filename, std::vector<glm::vec3>& positions, 
		std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs)
	{
		std::vector<glm::vec3> verticesTemp;
		std::vector<glm::vec3> normalsTemp;
		std::vector<glm::vec2> uvsTemp;

		std::fstream fileStream(filename, std::fstream::in);

		std::string line;
		while (std::getline(fileStream, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				std::istringstream s(line.substr(2));
				glm::vec3 v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				verticesTemp.push_back(v);
			}
			else if (line.substr(0, 3) == "vt ")
			{
				std::istringstream s(line.substr(3));
				glm::vec2 v2;
				s >> v2.x;
				s >> v2.y;
				uvsTemp.push_back(v2);
			}
			else if (line.substr(0, 3) == "vn ")
			{
				std::istringstream s(line.substr(3));
				glm::vec3 v3;
				s >> v3.x;
				s >> v3.y;
				s >> v3.z;
				normalsTemp.push_back(v3);
			}
			else if (line.substr(0, 2) == "f ")
			{
				GLuint indices[3];
				size_t i = 0;
				std::istringstream s(line.substr(2));

				std::string pointString;
				while (std::getline(s, pointString, ' '))
				{
					std::istringstream pointStream(pointString);

					std::string valueString;
					while (std::getline(pointStream, valueString, '/'))
					{
						std::istringstream valueStream(valueString);
						valueStream >> indices[i++];
					}
					i = 0;

					glm::vec3 vertex = verticesTemp[indices[0] - 1];
					positions.push_back(vertex);
					if (uvsTemp.size() > 0)
					{
						glm::vec2 uv = uvsTemp[indices[1] - 1];
						uvs.push_back(uv);
					}
					if (normalsTemp.size() > 0)
					{
						glm::vec3 norm = normalsTemp[indices[2] - 1];
						normals.push_back(norm);
					}
				}
			}
		}
		if (fileStream.eof()) {
			fileStream.close();
			return true;
		}
		fileStream.close();

		return false;
	}
}
