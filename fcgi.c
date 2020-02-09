#include "defs.h"

Prototype void HandleConnection(int PassiveSocketFD);

typedef struct {
	unsigned char version;
	unsigned char type;
	unsigned char requestIdB1;
	unsigned char requestIdB0;
	unsigned char contentLengthB1;
	unsigned char contentLengthB0;
	unsigned char paddingLength;
	unsigned char reserved;
	unsigned char contentData[contentLength];
	unsigned char paddingData[paddingLength];
} FCGI_Record;

void
HandleConnection (int PassiveSocketFD) {
	struct sockaddr addr;
	socklen_t addrlen = sizeof(struct sockaddr);
	int ActiveSocketFD = accept4(PassiveSocketFD, &addr, &addrlen, SOCK_CLOEXEC);
	if (-1 == ActiveSocketFD) {
		printlogf(LOG_ERR, "accept: %s\n", strerror(errno));
		return;
	}

	pid_t pid = fork();
	if (-1 == pid) {
		printlogf(LOG_ERR, "fork: %s\n", strerror(errno));
		return;
	} else if (pid > 0) {
		// parent scope
		return;
	}

	// child scope
	close(PassiveSocketFD);
	close(2); // close error stream


}
