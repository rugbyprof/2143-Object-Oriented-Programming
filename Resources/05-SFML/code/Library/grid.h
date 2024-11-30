#pragma once
#include "dataRectangle.h"
#include "sprixture.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Grid : public sf::Drawable {
   private:
    std::vector<std::vector<DataRectangle>> rectangles;  // 2D vector of rectangles
    sf::Vector2f rectangleSize;
    std::string fontPath;  // Shared font for all rectangles
    sf::Font font;

    unsigned int rows, cols;

    // Custom draw method
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                target.draw(rectangles[i][j], states);  // Delegate to DataRectangle's draw method
            }
        }
    }

   public:
    /**
     * @brief Construct a new Grid object with the specified dimensions.
     * @param rows (int) Number of rows in the grid
     * @param cols (int) Number of columns in the grid
     * @param size (sf::Vector2f) Size of each rectangle in the grid
     * @param initialValue (T) Initial value for each rectangle
     * @param fontPath (std::string)) Font to use  to pass to the rectangles
     * @param fillColor (sf::Color) Fill color for the rectangles
     * @param outlineColor (sf::Color) Outline color for the rectangles
     * @param outlineThickness (float) Thickness of the rectangle outline
     * @return (void)
     * @example:
     * Grid<int> grid(3, 3, sf::Vector2f(100.f, 100.f), 0, font, sf::Color::White, sf::Color::Black, 1.f);
     */

    Grid(unsigned int rows, unsigned int cols, const sf::Vector2f& size, const std::string& initialValue, const std::string fontPath,
         const sf::Color& fillColor = sf::Color::White, const sf::Color& outlineColor = sf::Color::Black, float outlineThickness = 1.f)
        : rows(rows), cols(cols), rectangleSize(size), fontPath(fontPath) {
        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Error loading font\n";
        }

        for (unsigned int i = 0; i < rows; ++i) {
            std::vector<DataRectangle> row;
            for (unsigned int j = 0; j < cols; ++j) {
                // All the definitions below are because of type issues and mismatches with the DataRectangle class
                std::string null    = "null";
                std::string imgPath = "../media/images/0.png";
                Sprixture pennyDie(imgPath);
                sf::Sprite pennySprite = pennyDie.getSprite();
                sf::Vector2f pos(j * size.x, i * size.y);
                DataRectangle rect(pos, rectangleSize, font, pennySprite, 0.5f, null);
                rect.setFillColor(fillColor);  // Default color
                rect.setOutlineColor(outlineColor);
                rect.setOutlineThickness(outlineThickness);
                row.push_back(rect);
            }
            rectangles.push_back(row);
        }
        this->printValues();
    }

    // Set a value for a specific rectangle
    void setRectangleValue(unsigned int row, unsigned int col, const std::string& value) {
        if (row < rows && col < cols) {
            rectangles[row][col].setValue(value);
        }
    }

    // Get a value from a specific rectangle
    std::string getRectangleValue(unsigned int row, unsigned int col) const {
        if (row < rows && col < cols) {
            return rectangles[row][col].getValue();
        }
        throw std::out_of_range("Grid indices out of bounds");
    }

    // Print all rectangle values
    void printValues() const {
        std::cout << std::endl;
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                std::cout << "(" << i << ", " << j << ") : " << rectangles[i][j].getValue() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};