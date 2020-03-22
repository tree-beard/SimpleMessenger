#include <iostream>
#include <thread>
#include "ChatClient.h"

void inputAndSendMessage(ChatClient *chatClient, bool &terminateFlag) {
	std::string userInput = "";

	while (!terminateFlag)
	{
		getline(std::cin, userInput);

		if (userInput == "exit")
		{
			terminateFlag = true;
			break;
		}
		
		if (userInput.size() > 0)
		{
			chatClient -> sendTextMessage(userInput);
		}
	}
}

void recieveMessage(ChatClient* chatClient, bool& terminateFlag)
{
	while (!terminateFlag)
	{
		int bytesRecieved = chatClient->recieveFromServer();
	}
}

int main()
{
	std::cout << "Input port and user name: ";
	int port;
	std::string userName;
	std::cin >> port >> userName;
	if (userName.empty() || port <= 0)
		return -1;
	ChatClient *chatClient = new ChatClient(port, userName);
	const char* serverAddress = "127.0.0.1";
	int serverPort = 8080;
	
	if (chatClient -> init() == 0 && chatClient -> serverConnect(serverAddress, serverPort) == 0)
	{
		std::cout << "Client OK!" << std::endl;
		bool terminateFlag = false;
		std::thread sendThread(inputAndSendMessage, std::ref(chatClient), std::ref(terminateFlag));
		std::thread recvThread(recieveMessage, std::ref(chatClient), std::ref(terminateFlag));
		sendThread.join();
		recvThread.join();
	}
	else
	{
		delete chatClient;
		return -1;
	}

	delete chatClient;
	return 0;
}