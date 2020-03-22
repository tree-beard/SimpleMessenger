#include "ChatServer.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>

void ChatServer::onClientConnected(int clientSocket)
{
	// Send a welcome message to the connected client
	Client newClient;
	newClient.sock = clientSocket;
	m_clients.push_back(newClient);
	
	/*std::string welcomeMsg = "Wellcome to Secure chat!\n";
	sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);*/
}

void ChatServer::onClientDisconnected(int clientSocket)
{
	std::string clientName;
	for (int i = 0; i < m_clients.size(); ++i)
	{
		if (m_clients[i].sock == clientSocket)
		{
			clientName = m_clients[i].name;
			m_clients.erase(m_clients.begin() + i);
		}
	}
	std::string serverMsg = "Server\n" + clientName + " left this chat";
	sendTextMessage(clientSocket, serverMsg);
}

void ChatServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	std::string msgType;
	std::stringstream ss(msg);
	getline(ss, msgType);
	std::string data(ss.str().substr(ss.tellg()));

	std::cout << "Message type: " << msgType << std::endl;
	std::cout << "data: " << data << std::endl;

	if (msgType == messageTypes::REGISTER)
	{
		registerClient(clientSocket, data);
	}
	else if (msgType == messageTypes::TEXT_MSG)
	{
		sendTextMessage(clientSocket, data);
	}
}

void ChatServer::registerClient(int clientSocket, std::string data)
{
	std::stringstream ss(data);
	std::string clientName;
	for (int i = 0; i < m_clients.size(); ++i)
	{
		if (m_clients[i].sock == clientSocket)
		{
			getline(ss, clientName);
			m_clients[i].name = clientName;
		}
	}
	std::string serverMsg = "Server\n" + clientName + " joined this chat";
	sendTextMessage(clientSocket, serverMsg);
}

void ChatServer::sendTextMessage(int senderSocket, std::string data)
{
	std::stringstream msgss;
	msgss << messageTypes::TEXT_MSG << '\n' << data;
	std::string msg = msgss.str();
	broadcastToClients(senderSocket, msg.c_str(), msg.size() + 1);
}