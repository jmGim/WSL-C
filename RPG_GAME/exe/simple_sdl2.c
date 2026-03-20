#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    // 1. 초기화
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG); // PNG 디코더 초기화

    SDL_Window* window = SDL_CreateWindow("SDL2 Image & Mouse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 2. 이미지 텍스처 로드 (실행 파일과 같은 폴더에 image.png 필요)
    SDL_Texture* texture = IMG_LoadTexture(renderer, "image.png");
    if (!texture) {
        printf("이미지 로드 실패: %s\n", IMG_GetError());
    }

    bool isRunning = true;
    SDL_Event event;

    // 3. 메인 루프
    while (isRunning) {
        // 이벤트 처리 (입력 가로채기)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            // 마우스 버튼이 눌렸을 때의 이벤트 처리
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    printf("좌클릭 좌표: X=%d, Y=%d\n", event.button.x, event.button.y);
                }
            }
        }

        // 4. 화면 렌더링
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); // 밝은 회색 배경
        SDL_RenderClear(renderer);

        if (texture) {
            // 이미지를 화면 전체 크기에 맞춰 렌더링
            // 특정 위치/크기를 지정하려면 SDL_Rect 구조체를 3번째, 4번째 인자에 전달함
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 프레임 제한 (약 60FPS)
    }

    // 5. 자원 해제 (순서 중요)
    if (texture) SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
