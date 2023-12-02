#include "SpriteRenderer.h"
#include "../Object.h"
#include "../../Core/Core.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(): offset(0,0), flip_factor(1){}

void SpriteRenderer::Start(){}

void SpriteRenderer::Draw(sf::RenderTarget& surface){

    // convert position to camera relative position "screen position"
    sprite.setPosition(Camera::WorldToScreenPosition(
        object->GetTransform()->position + offset
    ));
    sprite.setScale(sf::Vector2f(object->GetTransform()->scale.x * this->flip_factor, object->GetTransform()->scale.y));
    
    surface.draw(sprite);
}

void SpriteRenderer::SetTexture(const char* label, bool center){
     
    this->texture = AssetManager::GetTexture(label);
    sprite.setTexture(*this->texture);
    // making the origin in the center of the sprite

    if(center){
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
    }
}

sf::Texture* SpriteRenderer::GetTexture(){
    return this->texture;
}

void SpriteRenderer::SetTextureRect(int left, int top, int width, int height){
    sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void SpriteRenderer::SetFlip(bool flip){
    if(flip){
        this->flip_factor = -1;
    }
    else{
        this->flip_factor = 1;
    }
}
bool SpriteRenderer::GetFlip(){ 
    if(flip_factor == 1){ 
        return false; 
    } 
    else{ 
        return true;
    } 
}

void SpriteRenderer::SetOffset(sf::Vector2f offset){
    this->offset = offset;
}
