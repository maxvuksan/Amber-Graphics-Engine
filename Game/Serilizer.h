#pragma once
#include "../Amber/Framework.h"
#include "Items/ItemDictionary.h"
#include "Settings.h"
#include <filesystem>


class World;
class GameClient;

class Serilizer {

    public:

        struct DataPair{
            std::string name;
            std::string filepath;
        };

        /*
            @param target_name the ideal name for the file, is incremented with each collision (e.g. john, john(1), john(2))
            @param extension the extension of the new file (e.g. .txt, .png, .something)
            @returns a filename which will not colliding with any exisiting filenames in a directory

        */
        static std::string GetCollisionFreeFilename(std::string target_name, std::string extension, std::string directory);

        // @returns a string extracted from a directory entry
        static std::string FilepathFromDirectoryEntry(std::filesystem::__cxx11::directory_entry entry);
        static std::string ExtractExtension(std::string filename);

        static void LoadPlayer(std::string filepath, GameClient* client);
        static void CreateNewPlayer(std::string name);
        static void CreateNewWorld(std::string name, World* world_to_write);

        static void SaveWorld(DataPair world_datapair, World* world);
        static void LoadWorldIntoMemory(std::string filename, World* world);

        // @returns a vector of DataPairs for each player in the Players/ directory
        static std::vector<DataPair> LoadPlayerList();
        // @returns a vector of DataPairs for each world in the Worlds/ directory
        static std::vector<DataPair> LoadWorldList();


};