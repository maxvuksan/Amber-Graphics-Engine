#include "World.h"

class TileBehaviourManager {

    public:

        static void LinkWorld(World* world);
        static void PerformTileUpdatePass();
        /*
            updating a tile to simulate the effect of time,

            vines spread, crops grow etc
        */
        static void UpdateTile(int x, int y);
        
        /*
            updating a tile because surrounding tiles have changed,

            a block with grass was removed, grass should also be destroyed
        */
        static void PropogateTile(int x, int y, signed_byte new_block, signed_byte previous_block, SetLocation set_location);

    private:

        // traverses down a position 
        static void RemoveVine(int x, int y, signed_byte vine_code);

    private:
        static int tickrate;
        static World* world;
};