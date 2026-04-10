#include "raylib.h"
#include <stdio.h>

int main(void) {
    // 1. 초기화 및 창 생성 (렌더러, 컨텍스트 자동 생성)
    InitWindow(800, 600, "Raylib Image & Mouse");
    SetTargetFPS(60); // 프레임 고정 내장 함수

    // 2. 이미지 텍스처 로드 (PNG 기본 지원)
    Texture2D texture = LoadTexture("../linux_image.png");

    // 3. 메인 루프
    while (!WindowShouldClose()) {
        // 이벤트 큐 방식이 아닌 상태 검사(State Polling) 방식의 입력 처리
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            printf("좌클릭 좌표: X=%d, Y=%d\n", GetMouseX(), GetMouseY());
        }

        // 4. 화면 렌더링
        BeginDrawing();
        ClearBackground(RAYWHITE); // 밝은 회색 배경으로 지우기

        // 텍스처 그리기 (원래 크기대로 0, 0 좌표에 렌더링)
        // 색상 인자(WHITE)는 틴트(Tint) 효과를 주지 않고 원본 색상 그대로 출력함을 의미
        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();
    }

    // 5. 자원 해제
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}