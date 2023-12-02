#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TilemapProfile.h"

/*
    allows the range -128 -> 127
*/
typedef signed char signed_byte; 

class TilemapPrimitive : public sf::Drawable, public sf::Transformable
{
    /*
        TilemapPrimitive:

        depends on inherited functionality provided by Tilemap
    */

    public:
        
        bool Load(sf::Texture* texture, TilemapProfile* tilemap_profile, int default_tile = -1);

        /*
            @returns A 2D vector of integer values representing the tilemap
        */
        std::vector<std::vector<signed_byte>>& GetGrid();
        void SetTile(signed_byte tile_index, unsigned int x, unsigned int y);
        /*
            swaps back to the tilemap texture
        */
        void RevertTexture();
        /*
            sets the drawing texture
        */
        void SetTexture(sf::Texture* texture);


        TilemapProfile* tilemap_profile;
        
    private:

        std::vector<std::vector<signed_byte>> grid;

        sf::VertexArray m_vertices;
        
        sf::Texture* texture_reference; // the texture provided in Load()
        sf::Texture* focus_texture;


        /*
            base function for drawing, not same as the Draw() component function
        */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            // apply the transform
            states.transform *= getTransform();

            if(focus_texture == nullptr){
                std::cout << "ERROR : TilemapPrimitive::draw() focus_texture is null\n";
            }

            // apply the tileset texture
            states.texture = focus_texture;
            // draw the vertex array
            target.draw(m_vertices, states);
        }

};