#include "controller.h"
#include "view.h"
#include <iostream>
#include <sstream>

Controller::Controller(Model& model, View& view)
    : m_view(view),
      m_model(model),
      m_client(nullptr),
      m_server(nullptr),
      m_waitingMessage("") {}

void Controller::sendDirection(ENetPeer* peer, Direction direciton) {
  int directionValue = static_cast<int>(direciton);
  ENetPacket* packet = enet_packet_create(
      &directionValue, sizeof(directionValue), ENET_PACKET_FLAG_RELIABLE);

  if (enet_peer_send(peer, 0, packet) < 0) {
    std::cerr << "Failed to send direction packet." << std::endl;
    enet_packet_destroy(packet);  // Clean up if sending fails
  } else {
    std::cout << "Sent direction " << static_cast<int>(direciton) << std::endl;
  }
}

//TODO fix
void Controller::processWaitingRoom() {

}

void Controller::processGameUpdates(const char* data) {
  std::stringstream ss(data);
  std::string line;

  while (std::getline(ss, line)) {
    std::stringstream lineStream(line);
    enet_uint32 id;
    int x,y;

    if (lineStream >> id >> x >> y) {
      m_model.updatePlayer(id, x, y);
    } else {
      std::cerr << "Error parsing line: " << line << std::endl;
    }
  }
}

// Process a received ENet packet containing a serialized vector
void Controller::processPacket(const ENetPacket* packet) {
  std::string str = std::string((char*)packet->data, packet->dataLength);

  // Waiting Packet:
  if (str.find("Players") != std::string::npos) {
    m_waitingMessage = str;
    std::cout << m_waitingMessage << std::endl;
  } else { // Game Packet
    m_view.changeMode(View::Mode::GAME);
    const char* data = (char*) packet->data;
    size_t dataLength = packet->dataLength;

    processGameUpdates((char*)packet->data);
    std::cout << "Board Updated." << std::endl;
    m_view.displayBoard(m_model.getBoard());
  }
}

ENetHost* initializeClient(int port) {
  if (enet_initialize() != 0) {
    std::cerr << "ENet failed to initialize." << std::endl;
    return nullptr;
  }
  atexit(enet_deinitialize);

  ENetAddress clientAddress;
  clientAddress.host = ENET_HOST_ANY;
  clientAddress.port = 0;

  ENetHost* client = enet_host_create(&clientAddress, 1, 2, 0, 0);
  if (!client) {
    std::cerr << "ENet failed to create a client host." << std::endl;
    return nullptr;
  }
  std::cout << "Client created!" << std::endl;

  return client;
}

ENetPeer* connectToServer(ENetHost* client, const char* serverIp, int port) {
  ENetPeer* server;
  ENetAddress serverAddress;
  enet_address_set_host(&serverAddress, serverIp);
  serverAddress.port = port;
  std::cout << "Trying to connect to " << serverIp << ":" << port << std::endl;

  server = enet_host_connect(client, &serverAddress, 1, 0);
  if (!server) {
    std::cerr << "Client couldn't find host." << std::endl;
    enet_host_destroy(client);
    return nullptr;
  } else {
    std::cout << "Client found the host!" << std::endl;
  }

  ENetEvent event;
  if (enet_host_service(client, &event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT) {
    std::cout << "Successfully connected to the server!" << std::endl;
    return server;
  } else {
    enet_peer_reset(server);
    std::cerr << "Connection to the server failed." << std::endl;
    enet_host_destroy(client);
    return nullptr;
  }
}

void disconnectENet(ENetHost* client, ENetPeer* server) {
  ENetEvent event;
  enet_peer_disconnect(server, 0);  // 0 is data to send
  while (enet_host_service(client, &event, 3000) > 0) {
    if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
      std::cout << "Disconnection successful!" << std::endl;
      break;
    } else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
      enet_packet_destroy(event.packet);  // Clean up any received packet
    }
  }

  enet_host_destroy(client);  // Properly destroy the client host
}

static bool init = false;
void Controller::initEnet() {
  if (init) return;

  m_client = initializeClient(1234);
  m_server = connectToServer(m_client, "192.168.1.23", 7777);

  if (!m_server) {
    std::cout << "Couldn't find server!" << std::endl;
  }

  init = true;
}

void Controller::processServer() {
  ENetEvent event;
  while (enet_host_service(m_client, &event, 0) > 0) {
    if (event.type == ENET_EVENT_TYPE_RECEIVE) {
      processPacket(event.packet);
      enet_packet_destroy(event.packet);
    }
  }
}

void Controller::begin() {
  Direction currentDirection = Direction::DOWN;

  // GAME LOOP START
  int count = 0;

  while (m_view.isOpen()) {  // TODO change later
    m_view.processEvents(*this);
    m_view.display(m_waitingMessage.c_str());
  }
  // GAME LOOP END

  // disconnectENet(client, server);
}