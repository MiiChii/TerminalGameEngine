// #include <windows.h>

#include "Game.h"
#include "Engine/engine.h"

// void setConsoleSize(int iNewSize) {
//     CONSOLE_FONT_INFOEX cfi;
//     cfi.cbSize = sizeof(cfi);
//     cfi.nFont = 0;
//     cfi.dwFontSize.X = iNewSize * PIXEL_WIDTH;                   // Width of each character in the font
//     cfi.dwFontSize.Y = iNewSize * PIXEL_HEIGHT;            // Height
//     cfi.FontFamily = FF_DONTCARE;
//     cfi.FontWeight = FW_NORMAL;
//     std::wcscpy(cfi.FaceName, L"Arial"); // Choose your font
//     SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
// }






int main()
{
    // setConsoleSize(9);
    getchar();

    Screen::init();
    Game game;

    Scene::sm_vScenes[0].loadScene();


    float lastUpdateTime = clock();

    while (!game.finiCondition()) {

        game.tick((clock() - lastUpdateTime)/1000);

        for (GameObject* gO : GameObject::sm_vGameObjects) {

            if (!gO->m_bActive) {
                continue;
            }


            for (Component* c : gO->m_vComponents) {
                if (!c->m_bActive)
                    continue;

                // std::cout << gO << std::endl;
                c->tick((clock() - lastUpdateTime)/1000);
            }
        }

        if (Scene::sm_bReload) {
            Scene::sm_bReload = false;
            continue;
        }

        lastUpdateTime = clock();

        Screen::updateScreen();
    }

    GameObject deathscreen(Vector(150, 80), { new ImageRenderer(new ImageFile("Assets//Death.bmp"), 1000)});
    deathscreen.getComponent<ImageRenderer>()->printToScreen();

    Screen::updateScreen();

    getchar();


}




