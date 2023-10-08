#pragma once
#include <unordered_map>
#include <iostream>

#include "Scene.h"

/*
    AssetManager: 

    responsible for storing resusable assets, preventing duplication 

    this could include

    Animations
    Scenes
    Textures
    etc...

*/
class Core;
class AssetManager {

    public:
        static void Construct(Core*);
        static void Destruct();

        // assuming all shaders are fragment
        static sf::Shader* CreateShader(const char* label, const std::string fragment_file_location);
        static sf::Shader* GetShader(const char* label);
        
        static sf::Texture* CreateTexture(const char* label, const sf::RenderTexture& render_texture, bool repeat = false);
        static sf::Texture* CreateTexture(const char* label, const char* file_location, bool repeat = false);
        static sf::Texture* GetTexture(const char* label);
        /*
            Creates a scene of the specified type T (allowing only classes which inherit Scene)
        */
        template <typename T>
        static Scene* CreateScene(const char* label) {

            Scene* new_scene = new T;
            new_scene->LinkCore(core);
            scenes.insert(std::make_pair(label, new_scene));

            return new_scene;
        }

        /*
            @returns A pointer to a desired scene
            @param label The name the scene is saved as  
        */
        static Scene* GetScene(const char* label); 

    protected:
        static Core* core;

        static std::unordered_map<const char*, sf::Texture> textures; 
        static std::unordered_map<const char*, Scene*> scenes; /*scenes are stored as pointers to allow for inherited scenes*/
        static std::unordered_map<const char*, sf::Shader*> shaders;
};