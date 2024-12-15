#include "Game.h"

int main(){
    InitWindow(512,512,"11_Enemy_Algorithm");
    SetTargetFPS(60);
    Game game;

    while(WindowShouldClose()==false){
        // 1. event handling
        game.handleInput();

        //2. updating game loop
        game.update();

        //3. draw loop
        BeginDrawing();
            ClearBackground({29,29,27,255});
            game.draw();
        EndDrawing();
    }
    CloseWindow();
}