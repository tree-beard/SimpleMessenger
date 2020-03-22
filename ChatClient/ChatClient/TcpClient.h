#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE 1024

class TcpClient
{

public:

	TcpClient(int port): m_port(port) { }

	~TcpClient();

	// Initialize client's network interface
	int init();

	// Connect to a server
	int serverConnect(const char* ipAddress, int port);

	// Send to a server
	void sendToServer(const char* msg, int length);

	// Recieve from server
	int recieveFromServer();

	// Check for incoming data
	int dataAvailable(long sec, long usec);

	void cleanup();

protected:

	// Handler for connection
	virtual void onConnected();

	// Handler for when a message is received from the server
	virtual void onMessageReceived(const char* msg, int length);

private:
	
	int				m_port;
	int				m_socket;		// Client's socket
	char			m_messageBuffer[MAX_BUFFER_SIZE];
};