#include "sdl_bmp_parser.h"

#pragma region Methods
void parse_bmp_sdl(SDL_Renderer *renderer, const char *file_name)
{
    SDL_Texture *static_texture;
    if (bmp_to_static_texture(file_name, renderer, &static_texture)) return;

    SDL_Texture *streaming_texture;
    if (bmp_to_streaming_texture(file_name, renderer, &streaming_texture)) return;

    for (;;)
    {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect target_rect = {128, 128, 64, 64};
        SDL_RenderCopy(renderer, static_texture, NULL, &target_rect);

        target_rect.x = 256;
        SDL_RenderCopy(renderer, streaming_texture, NULL, &target_rect);

        SDL_RenderPresent(renderer);
    }
}


#pragma endregion

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("BMP SDL Parsing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, 0);
    if (!window) goto quit;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) goto quit;

    char *file_name = "assets\\block.bmp";

    parse_bmp_sdl(renderer, file_name);

quit:
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}