// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef CONNECT
#define CONNECT

#include "../lib.h"

namespace Connect {

	extern std::atomic<const char*> aRecvData;

	SOCKET connect(bool host, std::string sipaddr = "127.0.0.1", std::string _port = "30980");
	void disconnect(SOCKET& gSocket);

	int RecvData(bool& run, SOCKET& gSocket);

	template<typename DATA>
	int SendData(SOCKET& gSocket, DATA senddata) {

		const char* data = static_cast<const char*>(senddata);

		int iResult = send(gSocket, data, strlen(data), 0);
		if (iResult == SOCKET_ERROR) {

			int LastError = WSAGetLastError();

			if (LastError != WSAENOTSOCK) {

				std::stringstream stream;
				stream << "Error: send() failed with error [" << LastError << "].";
				Utilities::Logger("023c", stream.str());

				if ((LastError == WSAENETRESET) || (LastError == WSAECONNABORTED) || (LastError == WSAECONNRESET) || 
					(LastError == WSAENOTCONN) || (LastError == WSAESHUTDOWN) || (LastError == WSAETIMEDOUT)) {
					disconnect(std::ref(gSocket));
				}
			}
		}

		return 0;
	}
}

#endif // !CONNECT
