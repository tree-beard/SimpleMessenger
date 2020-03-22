#pragma once

#include <string>
#include <vector>
#include "TcpServer.h"

namespace messageTypes
{
	const std::string REGISTER = "register";
	const std::string TEXT_MSG = "text_msg";
};

struct Client
{
	int sock;
	std::string name;
};

class ChatServer : public TcpServer
{
public:

	ChatServer(const char* ipAddress, int port) :
		TcpServer(ipAddress, port) { }

protected:
	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// Handler for when a message is received from the client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);

private:
	std::vector<Client> m_clients;
	void registerClient(int clientSocket, std::string data);
	void sendTextMessage(int senderSocket, std::string data);
};