#include "PlayerMovement.h"
// #include <windows.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

bool kbhit() {
  fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(STDIN_FILENO, &read_fds);

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  // select() returns the number of file descriptors ready for reading
  return select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &timeout) > 0;
}

void PlayerMovement::tick(double deltaTime) {
  if (!m_bCanMove) {
    return;
  }

  Vector vectorMove;

  // if (GetAsyncKeyState('D')) {
  // 	vectorMove += Vector(1, 0);
  // }
  // if (GetAsyncKeyState('A')) {
  // 	vectorMove += Vector(-1, 0);
  // }
  // if (GetAsyncKeyState('W')) {
  // 	vectorMove += Vector(0, -1);
  // }
  // if (GetAsyncKeyState('S')) {
  // 	vectorMove += Vector(0, 1);
  // }

  termios old_termios;
  tcgetattr(STDIN_FILENO, &old_termios);

  termios new_termios = old_termios;
  new_termios.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  if (kbhit()) {
    char c = getchar();

    if (c == 'd') {
      vectorMove += Vector(1, 0);
    }
    if (c == 'a') {
      vectorMove += Vector(-1, 0);
    }
    if (c == 'w') {
      vectorMove += Vector(0, -1);
    }
    if (c == 's') {
      vectorMove += Vector(0, 1);
    }
  }
  // std::cout << deltaTime << "; " << std::endl;

  vectorMove.normal();

  vectorMove *= 0.5f * deltaTime;

  m_pGameObject->m_vecPosition.m_dX += vectorMove.m_dX;
  m_pGameObject->m_vecPosition.m_dY += vectorMove.m_dY;

  // m_pGameObject->getComponent<Collider>()->updateCollider();
  // // if (m_pGameObject->getComponent<Collider>()->isCollidingWith(COL_ID_STOP)
  // // && !GetAsyncKeyState('Q')) { 	m_pGameObject->m_vecPosition.m_dX -=
  // // vectorMove.m_dX * 1;
  // // }
  //
  // m_pGameObject->m_vecPosition.m_dY += vectorMove.m_dY;
  //
  // m_pGameObject->getComponent<Collider>()->updateCollider();
  // // if (m_pGameObject->getComponent<Collider>()->isCollidingWith(COL_ID_STOP)
  // // && !GetAsyncKeyState('Q')) { 	m_pGameObject->m_vecPosition.m_dY -=
  // // vectorMove.m_dY * 1;
  // // }

  if (vectorMove.magnitude() < 0.1) {
    m_pGameObject->getComponent<Animator>()->setBool("Walking", false);
    return;
  }

  m_pGameObject->getComponent<Animator>()->setBool("LookUp", false);
  m_pGameObject->getComponent<Animator>()->setBool("LookDown", false);
  m_pGameObject->getComponent<Animator>()->setBool("LookLeft", false);
  m_pGameObject->getComponent<Animator>()->setBool("LookRight", false);

  m_pGameObject->getComponent<Animator>()->setBool("Walking", true);
  if (abs(vectorMove.m_dX) > abs(vectorMove.m_dY)) {
    if (vectorMove.m_dX > 0) {
      m_pGameObject->getComponent<Animator>()->setBool("LookRight", true);
    } else {
      m_pGameObject->getComponent<Animator>()->setBool("LookLeft", true);
    }
  } else {
    if (vectorMove.m_dY > 0) {
      m_pGameObject->getComponent<Animator>()->setBool("LookDown", true);
    } else {
      m_pGameObject->getComponent<Animator>()->setBool("LookUp", true);
    }
  }
}
