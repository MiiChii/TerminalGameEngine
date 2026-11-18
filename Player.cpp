#include "Player.h"

Player::Player() : Player(Vector::zero()) {}
Player::Player(Vector vectorPos) : GameObject(vectorPos) 
{
    m_sheetWalkDown   = new SpriteSheet("Assets//Character//Walk Down.bmp",   24, 24);
    m_sheetWalkUp     = new SpriteSheet("Assets//Character//Walk Up.bmp",     24, 24);
    m_sheetWalkRight  = new SpriteSheet("Assets//Character//Walk Right.bmp",  24, 24);
    m_sheetWalkLeft   = new SpriteSheet("Assets//Character//Walk Left.bmp",   24, 24);

    m_sheetSlashDown  = new SpriteSheet("Assets//Character//Slash Down.bmp",  24, 24);
    m_sheetSlashUp    = new SpriteSheet("Assets//Character//Slash Up.bmp",    24, 24);
    m_sheetSlashRight = new SpriteSheet("Assets//Character//Slash Right.bmp", 24, 24);
    m_sheetSlashLeft  = new SpriteSheet("Assets//Character//Slash Left.bmp",  24, 24);

    m_animWalkDown    = new Animation({ "Walking", "LookDown" },     m_sheetWalkDown);
    m_animWalkUp      = new Animation({ "Walking", "LookUp" },       m_sheetWalkUp);
    m_animWalkRight   = new Animation({ "Walking", "LookRight" },    m_sheetWalkRight);
    m_animWalkLeft    = new Animation({ "Walking", "LookLeft" },     m_sheetWalkLeft);

    m_animIdleDown    = new Animation({ "!Slashing", "!Walking", "LookDown" },     { m_sheetWalkDown->m_vImages[0] });
    m_animIdleUp      = new Animation({ "!Slashing", "!Walking", "LookUp" },       { m_sheetWalkUp->m_vImages[0] });
    m_animIdleRight   = new Animation({ "!Slashing", "!Walking", "LookRight" },    { m_sheetWalkRight->m_vImages[0] });
    m_animIdleLeft    = new Animation({ "!Slashing", "!Walking", "LookLeft" },     { m_sheetWalkLeft->m_vImages[0] });

    m_animSlashDown   = new Animation({ "Slashing", "LookDown" },    m_sheetSlashDown);
    m_animSlashUp     = new Animation({ "Slashing", "LookUp" },      m_sheetSlashUp);
    m_animSlashRight  = new Animation({ "Slashing", "LookRight" },   m_sheetSlashRight);
    m_animSlashLeft   = new Animation({ "Slashing", "LookLeft" },    m_sheetSlashLeft);

    addComponent(new PlayerStats);
    addComponent(new PlayerAttack);
    addComponent(new PlayerMovement);

    addComponent(new ImageRenderer(m_sheetWalkDown->m_vImages[0], LAYER_MIDDLEGROUND + 5));
    // addComponent(new Collider("Assets//Player.bmp", 1, new int{ COL_ID_PLAYER })); TODO: Fix
    addComponent(new Animator(m_sheetWalkDown->m_vImages[0], {
            m_animWalkDown,
            m_animWalkUp,
            m_animWalkLeft,
            m_animWalkRight,
            m_animIdleDown,
            m_animIdleUp,
            m_animIdleLeft,
            m_animIdleRight,
            m_animSlashDown,
            m_animSlashUp,
            m_animSlashLeft,
            m_animSlashRight,
        },
        {
            "Walking",
            "Slashing",
            "LookUp",
            "LookDown",
            "LookLeft",
            "LookRight",
        }
        ));
    getComponent<Animator>()->setActive(false);
    m_bGlobal = true;
}
