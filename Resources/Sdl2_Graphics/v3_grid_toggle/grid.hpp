#pragma once
#include <SDL.h>

#include <vector>

class Grid {
private:
    int                                rows, cols, cellSize;
    std::vector< std::vector< bool > > cells;

public:
    Grid(int width, int height, int cell)
        : cellSize(cell) {
        cols = width / cell;
        rows = height / cell;
        cells.assign(rows, std::vector< bool >(cols, false));
    }

    void toggleCell(int x, int y) {
        int col = x / cellSize, row = y / cellSize;
        if (row >= 0 && row < rows && col >= 0 && col < cols)
            cells[row][col] = !cells[row][col];
        std::cout << "toggled " << row << "," << col << std::endl;
    }

    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 200, 80, 255);
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (cells[r][c])
                    SDL_RenderFillRect(renderer, new SDL_Rect{c * cellSize, r * cellSize, cellSize, cellSize});
        SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
        for (int x = 0; x <= cols * cellSize; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, rows * cellSize);
        for (int y = 0; y <= rows * cellSize; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, cols * cellSize, y);
    }
};