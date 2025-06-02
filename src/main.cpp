#include "engine/render_engine.h"
#include "engine/asset_manager.h"
#include "engine/scene_manager.h"
#include "common/command_parser.h"
#include "common/stat_counter.h"

#include <ctime>
#include <iostream>

int main()
{
    Engine::Initialize();

    std::vector<std::string> meshIDs = {
        "loaded_1", "loaded_2", "loaded_3", "loaded_4", "loaded_5", "loaded_6", "loaded_7",
        "loaded_8", "loaded_9", "loaded_10", "loaded_11", "loaded_12", "loaded_13", "loaded_14"
    };

    AM::IO::LoadObjAsync("res/objs/suzanne_smooth.obj", meshIDs[0]);
    AM::IO::LoadObjAsync("res/objs/suzanne.obj",        meshIDs[1]);
    AM::IO::LoadObjAsync("res/objs/sphere.obj",         meshIDs[2]);
    AM::IO::LoadObjAsync("res/objs/cube.obj",           meshIDs[3]);
    AM::IO::LoadObjAsync("res/objs/teapot.obj",         meshIDs[4]);
    AM::IO::LoadObjAsync("res/objs/sphere.obj",         meshIDs[5]);
    AM::IO::LoadObjAsync("res/objs/cube.obj",           meshIDs[6]);
    AM::IO::LoadObjAsync("res/objs/teapot.obj",         meshIDs[7]);
    AM::IO::LoadObjAsync("res/objs/suzanne.obj",        meshIDs[8]);
    AM::IO::LoadObjAsync("res/objs/sphere.obj",         meshIDs[9]);
    AM::IO::LoadObjAsync("res/objs/cube.obj",           meshIDs[10]);
    AM::IO::LoadObjAsync("res/objs/teapot.obj",         meshIDs[11]);
    AM::IO::LoadObjAsync("res/objs/sphere.obj",         meshIDs[12]);
    AM::IO::LoadObjAsync("res/objs/cube.obj",           meshIDs[13]);

    int num = 7;
    int spacing = 4;

    std::vector<SM::Object*> createdObjects;

    std::srand(static_cast<unsigned>(69));
    for (int i = 0; i < num * num * num; i++)
    {
        int xdir = i % num;
        int ydir = i / (num * num);
        int zdir = (i / num) % num;

        std::string mesh = meshIDs[rand() % meshIDs.size()];

        SM::Object* myobj = new SM::Object("obj_" + std::to_string(i), mesh);
        myobj->SetPosition(glm::vec3(
            xdir * spacing - ((num - 1) * spacing) / 2.0f,
            ydir * spacing,
            zdir * spacing - ((num - 1) * spacing) / 2.0f
        ));

        float rx = static_cast<float>(rand() % 360);
        float ry = static_cast<float>(rand() % 360);
        float rz = static_cast<float>(rand() % 360);
        myobj->Rotate(glm::vec3(rx, ry, rz));

        SM::AddNode(myobj);
        createdObjects.push_back(myobj);  // Track for cleanup
    }

    Engine::Run();

    // Clean up allocated memory (if not managed by SM internally)
    for (auto obj : createdObjects)
    {
        delete obj;
    }

    Engine::Shutdown(); // Optional: add this if you have such a function

    return 0;
}
