#include "ChatClient.h"
#include <iostream>


ChatClient::ChatClient(int port, std::string userName) : TcpClient(port), m_name(userName)
{
	
}

ChatClient::~ChatClient()
{

}

// Handler for connection
void ChatClient::onConnected()
{
	std::stringstream datastream;
	std::string sendingMessage;

	datastream << messageTypes::REGISTER << '\n' << m_name;

	sendingMessage = datastream.str();
	sendToServer(sendingMessage.c_str(), sendingMessage.size() + 1);
}

// Handler for when a message is received from the server
void ChatClient::onMessageReceived(const char* msg, int length)
{
	std::string msgType;
	std::stringstream ss(msg);
	getline(ss, msgType);
	std::string data(ss.str().substr(ss.tellg()));

	if (msgType == messageTypes::TEXT_MSG)
	{
		std::stringstream datastream(data);
		std::string senderName;
		getline(datastream, senderName);
		std::string textMsg;
		getline(datastream, textMsg);
		std::cout << senderName << "> " << textMsg << std::endl;
	}
}

void ChatClient::sendTextMessage(std::string msg)
{
	std::stringstream datastream;
	std::string sendingMessage;

	datastream	<< messageTypes::TEXT_MSG << '\n'
				<< m_name << '\n'
				<< msg;

	sendingMessage = datastream.str();

	sendToServer(sendingMessage.c_str(), sendingMessage.size() + 1);
}