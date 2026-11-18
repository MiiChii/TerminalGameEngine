#include "Game.h"
#include "Engine/engine.h"

void Game::initAssets()
{
    m_pSheetSwordDown  = new SpriteSheet("Assets//Character//Sword Down.bmp",  24, 24);
    m_pSheetSwordUp    = new SpriteSheet("Assets//Character//Sword Up.bmp",    24, 24);
    m_pSheetSwordRight = new SpriteSheet("Assets//Character//Sword Right.bmp", 24, 24);
    m_pSheetSwordLeft  = new SpriteSheet("Assets//Character//Sword Left.bmp",  24, 24);

    m_pImgOverworld    = new ImageFile("Assets//Overworld.bmp");
    // m_pImgOverworld->initHeightMap("Assets//Starting-Screen-TLOZ_h.bmp");
    m_pImgCow          = new ImageFile("Assets//Character//Breiner Down.bmp");
    m_pImgCave         = new ImageFile("Assets//Cave.bmp");

    m_pAnimSwordDown   = new Animation({"SlashDown"},   m_pSheetSwordDown);
    m_pAnimSwordUp     = new Animation({"SlashUp"},     m_pSheetSwordUp);
    m_pAnimSwordRight  = new Animation({"SlashRight"},  m_pSheetSwordRight);
    m_pAnimSwordLeft   = new Animation({ "SlashLeft" }, m_pSheetSwordLeft);

    LightSource* l = new LightSource(Vector(80, 80, 10), 0.5, 100);
    l = new LightSource(Vector(180, 60, 10), 0.5, 100);

}

void Game::initScenes() {

#pragma region globalInit
    m_pPlayer = new Player(Vector(150, 80, 12));
#pragma endregion

#pragma region Scene 0 - Start
    Scene::sm_vScenes.push_back(Scene({
        new GameObject(Vector(150, 80, 0), {
            new ImageRenderer(m_pImgOverworld, LAYER_BACKGROUND),
            // new Collider("Assets//Starting-Screen-TLOZCol.bmp", 1, new int{ COL_ID_STOP }),
            // new Component(),
            // new Component(),
            // new Component(),
            // new Component(),
            // new Component(),
            // new Component(),
            // new Component(),
            // new Component(),
            // new Component(),
            }),
        // new GameObject(Vector(95, 5), {
        //     new Collider("Assets//Cow.bmp", 1, new int{ COL_ID_LOADINGZONE }),
        //     new LoadingZone(1, Vector(150, 130)),
        //     }),
        new GameObject(Vector(95, 60, 12), {
            new ImageRenderer(m_pImgCow, LAYER_MIDDLEGROUND),
            // new Collider("Assets//Cow.bmp", 1, new int{ COL_ID_ENEMYDAMAGE }),
            new Enemy(3),
            }),

        }));
#pragma endregion

#pragma region Scene 1 - Cave
    Scene::sm_vScenes.push_back(Scene({
        new GameObject(Vector(150, 80), {
            new ImageRenderer(m_pImgCave, LAYER_BACKGROUND),
            // new Collider("Assets//CaveCol.bmp", 1, new int{ COL_ID_STOP }),
            }),
        new GameObject(Vector(150, 150), {
            // new Collider("Assets//Player.bmp", 1, new int{ COL_ID_LOADINGZONE }),
            new LoadingZone(0, Vector(94, 22)),
            }),
        }));
#pragma endregion

}

Game::Game()
{
    initAssets();
    initScenes();
}

void Game::tick(double deltaTime)
{
    
}

bool Game::finiCondition()
{
    if (m_pPlayer->getComponent<PlayerStats>()->m_iHp <= 0) {
        return true;
    }
    return false;
}

void Game::fini()
{

}
