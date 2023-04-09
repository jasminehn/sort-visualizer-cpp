// using namespace std;
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
// #include <vector>

void draw_state(std::vector<int> &v, SDL_Renderer *renderer, unsigned int red, unsigned int blue)
{
    int index = 0;
    for (int i : v)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index += 1;
    }
}

int main(int argc, char *argv[])
{
    std::random_device rd;
    std::uniform_int_distribution d(1, 99);
    /*std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d(1, 99);*/

    std::vector<int> v;

    // fill vector with numbers
    for (int i = 0; i < 100; i++)
    {
        v.push_back(d(rd));
    }

    // create renderer
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(100 * 10, 100 * 10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // sort algo
    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                std::swap(v[j], v[i]);
            }
            // clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // draw state of the sort
            draw_state(v, renderer, i, j);

            // show to window
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
    // print
    for (int i : v)
    {
        std::cout << i << " ";
    }

    // check
    if (std::ranges::is_sorted(v)) // this has an error now but just use -std=c++20
    {
        std::cout << "\nsorted!\n";
    }

    // return 0; //TODO do i need this?
}