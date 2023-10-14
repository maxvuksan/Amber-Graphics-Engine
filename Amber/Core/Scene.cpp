#include "Scene.h"
#include "../Utility/Time.h"
#include "../Object/Rendering/PointLight.h"
#include "../Object/Physics/BoxCollider.h"
#include <iostream>

Camera* Scene::active_camera = nullptr;

Core* Scene::GetCore(){
    return this->core;
}
void Scene::LinkCore(Core* core){
    this->core = core;
}


void Scene::Restart(){
    this->ClearAll();
    this->Start();
}

Camera* Scene::GetActiveCamera(){
    if(active_camera == nullptr){
        std::cout << "ERROR : Something is trying to access the active camera before it has been assigned Scene::GetActiveCamera\n";
    }
    return active_camera;
}

void Scene::SetActiveCamera(Camera* camera){
    active_camera = camera;
}


void Scene::InternalUpdate(){
    
    if(active_camera == nullptr){
        std::cout << "ERROR : No camera is selected, set using Scene::SetActiveCamera(), Scene::InternalUpdate()\n";
        return;
    }

    this->Update();

    // iterate over each render layer
    for (auto layer = objects.begin(); layer != objects.end(); layer++) {

        // iterate over each object in said layer
        for(auto obj : layer->second){

            // skip disabled objects
            if(!obj->IsActive()){
                continue;
            }

            for(auto comp : *obj->GetComponents()){
                comp->Update();
                comp->UpdateSecondary();
            }
            obj->Update();
        }
    }

    // do the same for each ui element
    for (auto layer = ui.begin(); layer != ui.end(); layer++) {

        // iterate over each object in said layer
        for(auto obj : layer->second){

            // skip disabled objects
            if(!obj->IsActive()){
                continue;
            }

            for(auto comp : *obj->GetComponents()){
                comp->Update();
                comp->UpdateSecondary();
            }
            obj->Update();
        }
    }
}

void Scene::InternalCatchEvent(sf::Event event){

    this->CatchEvent(event);
    
    // iterate over each render layer
    for (auto layer = objects.begin(); layer != objects.end(); layer++) {

        // iterate over each object

        for(auto obj : layer->second){
            // skip disabled objects
            if(!obj->IsActive()){
                continue;
            }

            obj->CatchEvent(event);
        }
    }

    // do the same for each ui element
    for (auto layer = ui.begin(); layer != ui.end(); layer++) {

        // iterate over each object

        for(auto obj : layer->second){
            // skip disabled objects
            if(!obj->IsActive()){
                continue;
            }

            obj->CatchEvent(event);
        }
    }
}


void Scene::AddBoxCollider(BoxCollider* collider){
    this->box_colliders.push_back(collider);
}

void Scene::RemoveBoxCollider(BoxCollider* collider){
    for(int i = 0; i < box_colliders.size(); i++){

        if(collider == box_colliders[i]){
            box_colliders.erase(box_colliders.begin() + i);
            break;
        }
    }
}

void Scene::AddPointLight(PointLight* point_light){
    this->point_lights.push_back(point_light);
}

void Scene::RemovePointLight(PointLight* point_light){
    for(int i = 0; i < point_lights.size(); i++){

        if(point_light == point_lights[i]){
            point_lights.erase(point_lights.begin() + i);
            break;
        }
    }
}

void Scene::AddTilemap(Tilemap* tilemap){
    this->tilemaps.push_back(tilemap);
}

void Scene::RemoveTilemap(Tilemap* tilemap){
    for(int i = 0; i < tilemaps.size(); i++){

        if(tilemap == tilemaps[i]){
            tilemaps.erase(tilemaps.begin() + i);
            break;
        }
    }
}

void Scene::ClearAll(){
    
    active_camera = nullptr;

    for (auto layer = objects.begin(); layer != objects.end(); layer++) {

        for(auto obj : layer->second){

            delete obj;
        }
    }
    objects.clear();

    for (auto layer = ui.begin(); layer != ui.end(); layer++) {

        for(auto obj : layer->second){

            delete obj;
        }
    }
    ui.clear();
}


Scene::~Scene(){
    this->ClearAll();
}