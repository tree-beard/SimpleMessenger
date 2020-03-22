#include "ChatServer.h"
#include <iostream>

int main()
{
	ChatServer chatServer("0.0.0.0", 8080);
	if (chatServer.init() == 0)
	{
		std::cout << "Running chat server OK!" << std::endl;
		chatServer.run();
	}
	else
	{
		return -1;
	}

	return 0;
}