#pragma once

#include "ResourceManager.h"
#include <algorithm>

class GameObj; //Forward declare
class Camera;

namespace Physics
{
class Collider;

}

class Player;
class EnemyAI;

enum GameState
{
    Active,
    GameOver
};

//Singleton
class Scene
{
public:
	
	static Scene* Instance() 
	{ 
		static Scene instance;
		return &instance; 
	}

	void AddObj(GameObj* gm) 
	{ 
		gameObjects.push_back(gm); 
	}

    void DestroyObj(GameObj* gm)
    {
        auto it = std::find(gameObjects.begin(), gameObjects.end(), gm);
        if (it != gameObjects.end())
        gameObjects.erase(it);
    }

	void AddEnemies(EnemyAI* agent)
	{
		enemies.push_back(agent);
	}

    void DestroyEnemy(EnemyAI* e)
    {
        auto it = std::find(enemies.begin(),enemies.end(), e);
        if (it != enemies.end())
            enemies.erase(it);
    }

	std::vector<GameObj*> GetGameObjVec()
	{
		return gameObjects;
	}

    void AddCollider(Physics::Collider* col)
    {
        colliders.push_back(col);
    }

    void DestroyCollider(Physics::Collider* col)
    {
        auto it = std::find(colliders.begin(), colliders.end(), col);
        if (it != colliders.end())
            colliders.erase(it);
    }

    std::vector<Physics::Collider*> GetColliders()
    {
        return colliders;
    }

    void SetMainCamera(Camera* cam)
    {
        mainCamera = cam;
    }

    Camera* GetMainCamera()
    {
        return mainCamera;
    }

	std::vector<EnemyAI*> GetEnemyVec()
	{
	    return enemies;
	}

    std::vector<bool>& GetMapColliders()
    {
        return mapColliders;
    }

    void SetMapDimensions(unsigned int w, unsigned int h)
    {
        mapDim = vec2i(w, h);
    }

    vec2i GetMapDimensions()
    {
        return mapDim;
    }

    //Testing wave count
    int GetWaveCount()
    {
        return waveCount;
    }

    void incrementWave()
    {
        waveCount++;
    }

    void ResetWave()
    {
        waveCount = 1;
    }

    GameState* GetGameState()
    {
        return &gameState;
    }

    void SetGameState(GameState gs)
    {
        gameState = gs;
    }

private:
	static Scene* instance; //declare 
	std::vector<GameObj*> gameObjects; //GameOBJ Placeholder //Keep track of all the object in the game
    std::vector<Physics::Collider*> colliders;
    
    std::vector<bool> mapColliders;
    vec2i mapDim;

    int waveCount = 1; //enemy wave nr

    GameState gameState;

    Camera* mainCamera;
	std::vector<EnemyAI*> enemies;
	~Scene() {}
};

//only store all the gameobject in the world (list)
// 1- constructor (take in a setup scene coordinates)

namespace Debug
{

    class Line {
        int shaderProgram;
        unsigned int VBO, VAO;
        std::vector<float> vertices;
        vec3 startPoint;
        vec3 endPoint;
        mat4 MVP;
        vec3 lineColor;
    public:
        Line()
        {
        }

        Line(vec3 start, vec3 end) {

            startPoint = start;
            endPoint = end;
            lineColor = vec3(1, 1, 1);
            MVP = mat4(1.0f);

            const char* vertexShaderSource = "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "uniform mat4 MVP;\n"
                "void main()\n"
                "{\n"
                "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                "}\0";
            const char* fragmentShaderSource = "#version 330 core\n"
                "out vec4 FragColor;\n"
                "uniform vec3 color;\n"
                "void main()\n"
                "{\n"
                "   FragColor = vec4(color, 1.0f);\n"
                "}\n\0";

            // vertex shader
            int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            // check for shader compile errors

            // fragment shader
            int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            // check for shader compile errors

            // link shaders
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            // check for linking errors

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            vertices = {
                 start.x, start.y, start.z,
                 end.x, end.y, end.z
            };

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

        }

        int setMVP(mat4 mvp) {
            MVP = mvp;
            return 1;
        }

        int setColor(vec3 color) {
            lineColor = color;
            return 1;
        }

        int setLine(vec3 s, vec3 e)
        {
            vertices = {
                 s.x, s.y, s.z,
                 e.x, e.y, e.z
            };
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

            glBindVertexArray(0);
            return 1;
        }

        int draw() {
            glUseProgram(shaderProgram);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
            glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);

            glBindVertexArray(VAO);
            glDrawArrays(GL_LINES, 0, 2);
            return 1;
        }
    };

    inline
    void DrawCircle(Line& line, vec3 pos, float rad, unsigned int segments)
    {
        mat4 view = Scene::Instance()->GetMainCamera()->view;
        mat4 proj = Scene::Instance()->GetMainCamera()->projection;
        line.setMVP(proj * view);

        for (int i = 0; i < segments; i++)
        {
            float denominator = float(segments) / 2.0f;
            vec2 v0 = normalize(vec2(sin(i * PI / denominator), cos(i * PI / denominator)));
            vec2 v1 = normalize(vec2(sin((i + 1) * PI / denominator), cos((i + 1) * PI / denominator)));

            v0 *= rad;
            v1 *= rad;

            line.setLine(pos + vec3(v0.x, 0.5f, v0.y), pos + vec3(v1.x, 0.5f, v1.y));
            line.draw();
        }
    }
}