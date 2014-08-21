#include "NetworkController.h"
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

NetworkController::NetworkController() :
		BaseController("Network"), m_sock(-1) {
	struct sockaddr_in server; // = {AF_INET, INADDR_ANY,30000};

	// open a UDP socket
	m_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sock < 0) {
		printf("Error Opening socket\n");
	}
	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(30000);

	if (bind(m_sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf(" Error Binding\n");
	}

	printf("Opened UDP socket on port %d\n", ntohs(server.sin_port));
}

NetworkController::~NetworkController() {
	close(m_sock);
}

void NetworkController::Update(uint32_t /*seconds*/, bool verbose) {
	int n = 0;
	char buf[128];

	struct foo {
		bool left;
		bool right;
		bool up;
		bool down;
		unsigned char pot0;
		unsigned char pot1;
		unsigned char pot2;
		unsigned char pot3;
	} data;

	// read data from socket and update state 
	n = recv(m_sock, buf, 128, MSG_DONTWAIT);
	if (n > 0) {
		// any traffic enables the network controller
		mEnabled = true;

		// need to fix the case where we have more than one packet pending
		memcpy(&data, buf, n);

		if (verbose) {
			printf("Received %d bytes: %d %d %d %d - %d %d %d %d\n", n,
					data.left, data.right, data.up, data.down,
					data.pot0, data.pot1, data.pot2, data.pot3);
		}

		mDigital[0] = data.left;
		mDigital[1] = data.right;
		mDigital[2] = data.up;
		mDigital[3] = data.down;
		mAnalog[0] = data.pot0 / 100.0;
		mAnalog[1] = data.pot1 / 100.0;
		mAnalog[2] = data.pot2 / 100.0;
		mAnalog[3] = data.pot3 / 100.0;
	}
}
