#pragma once
#include <SDL.h>

#include <vector>

class Grid {
private:
    int                                rows, cols, cellSize;
    std::vector< std::vector< bool > > cells;

    int countNeighbors(int r, int c) {
        int n = 0;
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc)
                if (!(dr == 0 && dc == 0)) {
                    int rr = r + dr, cc = c + dc;
                    if (rr >= 0 && rr < rows && cc >= 0 && cc < cols && cells[rr][cc])
                        n++;
                }
        return n;
    }

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
    }

    void update() {
        std::vector< std::vector< bool > > next = cells;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c) {
                int n = countNeighbors(r, c);
                if (cells[r][c])
                    next[r][c] = (n == 2 || n == 3);
                else
                    next[r][c] = (n == 3);
            }
        cells = next;
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