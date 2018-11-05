#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "DirectoryListing.h"

using namespace std;

/**
 * Class: TextureManager
 * Extends:  DirectoryListing
 *     Creates a vector of Textures that we can use to help us organize or minesweeper game.
 * 
 */
class TextureManager : public DirectoryListing {
private:
    vector<sf::Texture> Textures;
public:
    /**
     * TextureManager - Expects a path to a folder of images
     * @Param:
     *    image_path {string} : path to texture images
     * @Return:
     *    None
     */
    TextureManager(string image_path = "")
    {
        DirName = image_path;
        
        if (DirName.size() > 0) {
            FileNames = this->scanDir();
        }
        LoadTextures();
    }

    /**
     * LoadTextures - Loops through folder and creates a texture for each image
     * @Param:
     *    None
     * @Return:
     *    None
     */
    void LoadTextures()
    {
        string tempPath = "";
        for (int i = 0; i < FileNames.size(); i++) {
            tempPath = DirName+"/"+FileNames[i];
            //std::cout<<DirName<<"/"<<FileNames[i]<<std::endl;
            Textures.push_back(sf::Texture());
            if (!Textures.back().loadFromFile(tempPath)) {
                std::cout << "Could not load "<<FileNames[i] << std::endl;
            }
        }
    }

    /**
     * getTextureByName - Finds a texture base on filename
     * @Param:
     *    name {string} : name of texture
     * @Return:
     *    sf::Texture if found or and empty sf::Texture if not found
     */
    sf::Texture getTextureByName(string name){
        std::string::size_type n;
        for(int i=0;i<FileNames.size();i++){
            n = FileNames[i].find(name);
            if(n < FileNames[i].size()){
                return sf::Texture(Textures[i]);
            }
        }
        return sf::Texture();
    }
};