#pragma once
#include <enet/enet.h>
#include "model.h"

class View;  // Forward declaration of View

class Controller {
 public:
  Controller(Model& model, View& view);
  void begin();

  // Initializes Enet
  void initEnet();

  // Processes the server's inputs
  void processServer();

  // CLIENT -> SERVER FUNCTIONS START
  void sendDirection(ENetPeer* peer, Direction direciton);
  // CLIENT -> SERVER FUNCTIONS END
 private:
  
  
  // SERVER -> CLIENT FUNCTIONS START
  
  // Processes a packet from the server
  void processPacket(const ENetPacket* packet);
  // Processes the data from the server while waiting for new players
  void processWaitingRoom();
  // Processes the data from the server for updating the players movements in the game
  void processGameUpdates(const char* data);
  // SERVER -> CLIENT FUNCTIONS END

  

  View& m_view;
  Model& m_model;
  ENetHost* m_client;
  ENetPeer* m_server;
  std::string m_waitingMessage;
};
