#include <SDL2/SDL.h>
#include <stdio.h> 
#include <stdbool.h>

int main(int argc, char* argv[]) {
    // 1. SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        //std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. 윈도우 생성 (해상도 800x600)
    SDL_Window* window = SDL_CreateWindow("SDL2 Game", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        //std::cerr << "윈도우 생성 실패: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3. 렌더러 생성 (하드웨어 가속 사용)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 4. 메인 게임 루프
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // 이벤트 처리 (종료 조건 등)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // 화면 렌더링 (배경색 지정: 파란색)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        // TODO: 객체 그리기 로직 추가
        
        // 화면 갱신
        SDL_RenderPresent(renderer);
        
        // 프레임 제한 (약 60FPS)
        SDL_Delay(16);
    }

    // 5. 자원 해제 및 종료
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

