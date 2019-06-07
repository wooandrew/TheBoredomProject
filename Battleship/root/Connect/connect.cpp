// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "connect.h"

constexpr auto DEFAULT_BUFLEN = 4098;

namespace Connect {

	SOCKET connect(bool host, std::string sipaddr, PCSTR port) {

		if (host) {

			WSADATA wsaData;
			int iResult;

			SOCKET ListenSocket = INVALID_SOCKET;
			SOCKET ClientSocket = INVALID_SOCKET;

			struct addrinfo* result = NULL;
			struct addrinfo hints;

			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {

				std::stringstream stream;
				stream << "Fatal Error: WSAStartup() failed with error [" << iResult << "].";
				Misc::Logger("000c", stream.str());

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("001c", "Successfully initialized Winsock [WSAStartup() = 0].");
			}

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
			hints.ai_flags = AI_PASSIVE;

			// Resolve the server address and port
			iResult = getaddrinfo(NULL, port, &hints, &result);
			if (iResult != 0) {

				std::stringstream stream;
				stream << "Fatal Error: getaddrinfo() failed with error [" << iResult << "].";
				Misc::Logger("002c", stream.str());

				WSACleanup();

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("003c", "xxxx_success [getaddrinfo() = 0].");
			}

			// Create a SOCKET for connecting to server
			ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			if (ListenSocket == INVALID_SOCKET) {

				std::stringstream stream;
				stream << "Fatal Error: socket() failed with error [" << WSAGetLastError() << "].";
				Misc::Logger("004c", stream.str());

				freeaddrinfo(result);
				WSACleanup();

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("005c", "Successfully created socket [socket() = ListenSocket != INVALID_SOCKET].");
			}

			// Setup the TCP listening socket
			iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
			if (iResult == SOCKET_ERROR) {

				std::stringstream stream;
				stream << "Fatal Error: bind() failed with error [" << WSAGetLastError() << "].";
				Misc::Logger("006c", stream.str());

				freeaddrinfo(result);
				closesocket(ListenSocket);
				WSACleanup();

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("007c", "Successfully set up listening socket [socket() != SOCKET_ERROR].");
			}

			freeaddrinfo(result);

			iResult = listen(ListenSocket, SOMAXCONN);
			if (iResult == SOCKET_ERROR) {

				std::stringstream stream;
				stream << "Fatal Error: listen() failed with error [" << WSAGetLastError() << "].";
				Misc::Logger("008c", stream.str());

				closesocket(ListenSocket);
				WSACleanup();

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("009c", "xxxx_success [listen() != SOCKET_ERROR].");
			}

			Misc::Logger("Connecting...", true);

			unsigned long iMode = 1;
			ioctlsocket(ListenSocket, FIONBIO, &iMode);
			FD_SET readFDS;
			FD_ZERO(&readFDS);
			FD_SET(ListenSocket, &readFDS);
			timeval timeout;

			timeout.tv_sec = 90;
			timeout.tv_usec = 0;

			iResult = select(0, &readFDS, NULL, NULL, &timeout);
			if (iResult == 0) {

				std::stringstream stream;
				stream << "Fatal Error: accept() failed with error [" << WSAGetLastError() << "].";
				Misc::Logger("010c", stream.str());

				closesocket(ListenSocket);
				WSACleanup();

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("012c", "xxxx_success [select() != 0].");
			}

			// Accept a client socket
			ClientSocket = accept(ListenSocket, NULL, NULL);
			if (ClientSocket == INVALID_SOCKET) {


				std::stringstream stream;
				stream << "Fatal Error: accept() failed with error [" << WSAGetLastError() << "].";
				Misc::Logger("012c", stream.str());

				closesocket(ListenSocket);
				WSACleanup();

				return INVALID_SOCKET;
			}
			else {
				Misc::Logger("013c", "Successfully accepted client [accept() = ClientSocket != INVALID_SOCKET].");
			}

			// No longer need server socket
			closesocket(ListenSocket);

			return ClientSocket;
		}
		else {
			// NON HOST CONNECtiONS
			return INVALID_SOCKET;
		}

		return INVALID_SOCKET;
	}

	int __cdecl RecvData(bool& run, SOCKET& gSocket) {

		int iResult = 0;
		bool recvRun = true;

		// Receive until the peer shuts down the connection
		do {
			char recvbuf[DEFAULT_BUFLEN];
			int recvbuflen = DEFAULT_BUFLEN;

			if (!run) {

				recvRun = false;
				disconnect(std::ref(gSocket));

				return 0;
			}

			ZeroMemory(recvbuf, recvbuflen);

			iResult = recv(gSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0) {

				std::string srecvbuf = recvbuf;
				std::cout << srecvbuf << std::endl;

				if (srecvbuf == "exit") {

					recvRun = false;
					disconnect(std::ref(gSocket));

					return 0;
				}
			}
			else if (iResult == 0) {

				recvRun = false;
				disconnect(std::ref(gSocket));

				return 0;
			}
			else {

				int LastError = WSAGetLastError();

				if (LastError != WSAEWOULDBLOCK) {
					std::stringstream stream;
					stream << "Error: recv() failed with error [" << LastError << "].";
					Misc::Logger("014c", stream.str());
				}
				

				return 1;
			}

		} while (iResult > 0 && recvRun);

		return 0;
	}

	void disconnect(SOCKET& gSocket) {

		Misc::Logger("Closing connection...", true);

		// Shutdown the connection
		int iResult = shutdown(gSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {

			std::stringstream stream;
			stream << "Fatal Error: shutdown() failed with error [" << WSAGetLastError() << "].";
			Misc::Logger("015c", stream.str());

			closesocket(gSocket);
			WSACleanup();

			return;
		}
		else {
			Misc::Logger("016c", "Successfully shut down socket [shutdown(ClientSocket) != SOCKET_ERROR].");
		}

		// Cleanup
		closesocket(gSocket);
		WSACleanup();

		gSocket = INVALID_SOCKET;
	}
}