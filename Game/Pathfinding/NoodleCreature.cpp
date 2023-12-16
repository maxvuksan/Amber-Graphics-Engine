#include "NoodleCreature.h"
#include "PathfindingGraph.h"
#include "../LightSource.h"
#include "InverseKinematicLimb.h"
void NoodleCreature::Start(){

    auto light_source = AddComponent<LightSource>();
    light_source->colour = sf::Color(200, 143, 255);
    light_source->decay = 0.04f;

    auto sr = AddComponent<SpriteRenderer>();
    sr->SetRenderLayer(4);
    sr->SetTexture("noodle_head", true);

    search_again_delay_tracked = search_again_delay;

    GetTransform()->position = sf::Vector2f(100,100);

    for(int i = 0; i < 4; i++){
        auto limb = AddComponent<InverseKinematicLimb>();
        limb->Init(1 + rand() % 2, 22, 5);
        limb->AddSubLimb(6, 12, 0, 14, 3);
        limb->AddSubLimb(15, 23, 0, 12, 3);
        limb->AddSubLimb(0, 8, 0, 16, 2);
        
        limbs.push_back(limb);
    }
    ideal_grab_angle.push_back(-20);
    ideal_grab_angle.push_back(20);
    ideal_grab_angle.push_back(-80);
    ideal_grab_angle.push_back(80);
}

void NoodleCreature::Update(){

    if(Calc::Distance(GetTransform()->position, Camera::ScreenToWorldPosition(Mouse::DisplayPosition())) < 3.0f){
        return;
    }

    float direction_of_travel = Calc::Radians(Calc::AngleBetween(GetTransform()->position, Camera::ScreenToWorldPosition(Mouse::DisplayPosition())));

    GetTransform()->position += Calc::RadiansToVector(direction_of_travel) * Time::Dt() * 0.04f;

    for(int i = 0; i < 4; i++){

        sf::Vector2f target_position = Calc::RadiansToVector(Calc::Radians(ideal_grab_angle[i]) + direction_of_travel);
        target_position.x *= 120;
        target_position.y *= 120;
        target_position += GetTransform()->position;

        InverseKinematicLimb* limb = limbs[i];

        limb->SetOrigin(GetTransform()->position);

        if(Calc::Distance(GetTransform()->position, limb->GetTarget()) > 150){
            limb->SetTargetOverTime(target_position, 400);
        }
    }
    /*
    return;

    if(current_node < path_to_target.size()){

        physics->velocity = Calc::Normalize(sf::Vector2f(path_to_target.at(current_node).x * 8, path_to_target.at(current_node).y * 8) - GetTransform()->position) * 0.07f;

        if(Calc::Distance(sf::Vector2f(path_to_target[current_node].x * 8, path_to_target[current_node].y * 8), GetTransform()->position) < 3){
            current_node++;
        }
    }
    
    if(search_again_delay_tracked >= search_again_delay){

        path_to_target = PathfindingGraph::RequestPathWorld(GetTransform()->position, Camera::ScreenToWorldPosition(Mouse::DisplayPosition()), 2000);
        search_again_delay_tracked = 0;
        current_node = 0;
    }
    
    search_again_delay_tracked += Time::Dt();
    */
}