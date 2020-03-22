#include "TcpClient.h"

TcpClient::~TcpClient()
{
	cleanup();
}

// Initialize client's network interface
int TcpClient::init()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		return wsOk;
	}

	// Create a socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(m_port);

	if (bind(m_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	return 0;
}

// Connect to a server
int TcpClient::serverConnect(const char* ipAddress, int port)
{
	//Fill a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress, &hint.sin_addr);

	//Connect to the server
	int connResult = connect(m_socket, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	
	onConnected();

	return connResult;
}

void TcpClient::cleanup()
{
	closesocket(m_socket);
	WSACleanup();
}

// Send to a server
void TcpClient::sendToServer(const char* msg, int length)
{
	send(m_socket, msg, length, 0);
}

// Recieve from server
int TcpClient::recieveFromServer()
{
	if (dataAvailable(1, 0) > 0)
	{
		ZeroMemory(m_messageBuffer, MAX_BUFFER_SIZE);
		int bytesRecieved = recv(m_socket, m_messageBuffer, MAX_BUFFER_SIZE, 0);

		if (bytesRecieved > 0)
		{
			onMessageReceived(m_messageBuffer, bytesRecieved);
		}

		return bytesRecieved;
	}
	else
	{
		return -1;
	}
}

// Check for incoming data
int TcpClient::dataAvailable(long sec, long usec)
{
	struct timeval timeout;
	struct fd_set fds;

	// assign the second and microsecond variables
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	// Setup fd_set structure
	FD_ZERO(&fds);
	FD_SET(m_socket, &fds);

	// Possible return values:
	// -1: error occurred
	// 0: timed out
	// > 0: data ready to be read
	int dataStatus = select(0, &fds, 0, 0, &timeout);
	FD_ZERO(&fds);

	return dataStatus;
}

// Handler for connection
void TcpClient::onConnected()
{

}

// Handler for when a message is received from the server
void TcpClient::onMessageReceived(const char* msg, int length)
{

}

