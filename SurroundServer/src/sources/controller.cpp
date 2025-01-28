#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "controller.h"

#include <enet/enet.h>

#include <SFML/Graphics.hpp>
#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

Controller::Controller(Model& model) : m_model(model) {}

// Serialize a 2D vector to a flat byte array
std::vector<uint8_t> serializeVector(
    const std::vector<std::vector<enet_uint32>>& vec) {
  std::vector<uint8_t> buffer;

  // Write the number of rows
  size_t numRows = vec.size();
  buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&numRows),
                reinterpret_cast<const uint8_t*>(&numRows) + sizeof(numRows));

  for (const auto& row : vec) {
    // Write the number of elements in each row
    size_t numCols = row.size();
    buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&numCols),
                  reinterpret_cast<const uint8_t*>(&numCols) + sizeof(numCols));

    // Write the elements of the row
    buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(row.data()),
                  reinterpret_cast<const uint8_t*>(row.data() + numCols));
  }

  return buffer;
}

// Send a serialized vector over ENet
void sendVector(ENetPeer* peer,
                const std::vector<std::vector<enet_uint32>>& vec) {
  // Serialize the vector
  std::vector<uint8_t> buffer = serializeVector(vec);

  // Create and send the ENet packet
  ENetPacket* packet = enet_packet_create(buffer.data(), buffer.size(),
                                          ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer, 0, packet);
}

void sendBoard(std::vector<ENetPeer*> clients,
               const std::vector<std::vector<enet_uint32>>& board) {
  for (ENetPeer* client : clients) {
    sendVector(client, board);
  }
}

void sendWaitingMessage(std::vector<ENetPeer*> clients, int players) {
  // Construct the message
  std::stringstream str;
  str << "Players: " << clients.size() << "/" << players;
  std::string s = str.str();
  std::cout << s << std::endl;

  // Create the packet
  ENetPacket* packet =
      enet_packet_create(s.c_str(), s.size() + 1, ENET_PACKET_FLAG_RELIABLE);

  // Send the packet to each client
  for (ENetPeer* client : clients) {
    if (client != nullptr) {  // Ensure the client pointer is valid
      enet_peer_send(client, 0, packet);
    }     
  }
}

void sendUpdates(std::vector<ENetPeer*> clients, std::string message) {
  // Create the packet
  ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1,
                                          ENET_PACKET_FLAG_RELIABLE);

  // Send the packet to each client
  for (ENetPeer* client : clients) {
    if (client != nullptr) {  // Ensure the client pointer is valid
      enet_peer_send(client, 0, packet);
    }
  }
}

ENetHost* initializeServer(const char* serverAddresss, int port,
                           int numberOfPlayers) {
  // Initialize ENet
  if (enet_initialize() != 0) {
    std::cerr << "ENet failed to initialize." << std::endl;
    return nullptr;
  }
  atexit(enet_deinitialize);

  // Add server to ip address
  ENetAddress serverAddress;
  enet_address_set_host(&serverAddress, serverAddresss);
  serverAddress.port = port;
  ENetHost* server = enet_host_create(&serverAddress, numberOfPlayers, 1, 0, 0);
  if (server == nullptr) {
    std::cerr << "Failed to create ENet server." << std::endl;
  } else {
    std::cout << "Server Initialized!" << std::endl;
  }

  return server;
}

// TODO do something with adding more player information?
void newPlayerEvent(Model& model, ENetEvent& event,
                    std::vector<ENetPeer*>& clients) {
  // Add the client to the list of clients
  clients.push_back(event.peer);

  // Add the players to the model
  model.addPlayer(Player("...", 0), event.peer->connectID);
}

void updatePlayerEvent(Model& model, ENetEvent& event,
                       std::vector<ENetPeer*>& clients) {
  if (event.packet->dataLength == sizeof(int)) {
    // Convert packet into int
    int directionValue;
    std::memcpy(&directionValue, event.packet->data, sizeof(directionValue));
    // Convert int into Direction
    Direction direction = static_cast<Direction>(directionValue);

    // Change the players direction!
    model.changePlayerDirection(event.peer->connectID, direction);
  } else {
    std::cerr << "Unexpected packet size: " << event.packet->dataLength
              << std::endl;
  }
}

// TODO def doesn't work
void leavePlayerEvent(Model& model, ENetEvent& event,
                      std::vector<ENetPeer*>& clients) {
  auto it = std::remove(clients.begin(), clients.end(), event.peer);
  if (it != clients.end()) {
    clients.erase(it, clients.end());
  }
}

void handleServerEvents(Model& model, ENetHost* server,
                        std::vector<ENetPeer*>& clients) {
  ENetEvent event;
  while (enet_host_service(server, &event, 0) > 0) {
    switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT:
        std::cout << "Client " << event.peer->connectID
                  << " connected to the server!" << std::endl;
        newPlayerEvent(model, event, clients);
        break;
      case ENET_EVENT_TYPE_RECEIVE:
        std::cout << "Client " << event.peer->connectID
                  << " updated it's direction." << std::endl;
        updatePlayerEvent(model, event, clients);
        break;
      case ENET_EVENT_TYPE_DISCONNECT:
        std::cout << "Client " << event.peer->connectID
                  << " disconnected from the server." << std::endl;
        leavePlayerEvent(model, event, clients);
        break;
    }
  }
}

void Controller::begin() {
  int players = 1;

  ENetHost* server = initializeServer("192.168.1.23", 7777, players);

  // From each event from the clients
  std::vector<ENetPeer*> clients;

  while (true) {
    handleServerEvents(m_model, server, clients);

    if (clients.size() == players) {
      sf::sleep(sf::milliseconds(500));
      std::string updates = m_model.updatePlayers();

      // send the model again to all the clients.
      sendUpdates(clients, updates);
    } else {
      sf::sleep(sf::milliseconds(1000));
      sendWaitingMessage(clients, players);
    }
  }

  // Clean up server resources
  enet_host_destroy(server);
}