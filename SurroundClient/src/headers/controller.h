#pragma once
#include <enet/enet.h>

#include "game.h"
#include "menu.h"
#include "waitingRoom.h"

class View;  // Forward declaration of View

class Controller {
 public:
  Controller(View& view, Menu& menu, WaitingRoom& waitingRoom, Game& game);
  void begin();

  // Initializes Enet
  void initEnet();

  // Processes the server's inputs
  void processServer();

  void sendDirection(Direction direciton);
 private:

  // Processes a packet from the server
  void processPacket(const ENetPacket* packet);

  View& m_view;
  ENetHost* m_client;
  ENetPeer* m_server;

  Menu& m_menu;
  WaitingRoom& m_waitingRoom;
  Game& m_game;
};
