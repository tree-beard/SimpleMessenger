#pragma once
#include "TcpClient.h"


namespace messageTypes
{
	const std::string REGISTER = "register";
	const std::string TEXT_MSG = "text_msg";
};


class ChatClient : public TcpClient
{
public:

	ChatClient(int port, std::string userName);
	~ChatClient();
	void sendTextMessage(std::string msg);

protected:

	// Handler for connection
	virtual void onConnected();

	// Handler for when a message is received from the server
	virtual void onMessageReceived(const char* msg, int length);

private:
	std::string m_name;
};