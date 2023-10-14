#include "AnimationRenderer.h"
#include "../../Core/AssetManager.h"

AnimationRenderer::AnimationRenderer() : index(0), timer(0), set(nullptr), current_animation(nullptr){}

void AnimationRenderer::Start(){
}

void AnimationRenderer::Update(){

    if(set == nullptr){
        std::cout << "ERROR : No AnimationSet assigned, assign with AnimationRenderer::SetAnimationSet()\n";
        return;
    }

    if(timer < current_animation->GetDurations()->at(index)){

        timer += Time::Dt();
    }
    else{
        index++;
        index %= current_animation->GetEnd() - current_animation->GetStart();
        timer = 0;
    }

}

void AnimationRenderer::Draw(sf::RenderTarget& surface){
    
    if(current_animation == nullptr){
        std::cout << "ERROR : current_animation property on AnimationRenderer is null, AnimationRenderer::Draw()\n";
        return;
    }

    sprite.setTextureRect(sf::IntRect(current_animation->GetCellsize() * (index + current_animation->GetStart()), 0, current_animation->GetCellsize(), sprite.getTexture()->getSize().y));

    sprite.setPosition(Camera::WorldToScreenPosition(object->GetTransform()->position));

    surface.draw(sprite);
}

void AnimationRenderer::SetAnimationSet(const char* label){
    set = AssetManager::GetAnimationSet(label);
    current_animation = set->GetDefaultState();
    sprite.setTexture(*current_animation->GetTexture());

    index = 0;
    timer = 0;
}   

void AnimationRenderer::SetState(const char* label){
    current_animation = set->GetState(label);
    sprite.setTexture(*current_animation->GetTexture());

    index = 0;
    timer = 0;
}