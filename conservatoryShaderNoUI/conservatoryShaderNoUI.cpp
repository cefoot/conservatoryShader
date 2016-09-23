#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include <thread>
#include <wiringPi.h>

using namespace std;
	//wiring pi hat andere pin nummern
const int pinRelais1 = 29;
const int pinRelais2 = 25;
const int pinRelais3 = 28;
const int pinRelais4 = 24;
const int pinRelais5 = 27;
const int pinRelais6 = 23;
const int pinRelais7 = 22;
const int pinRelais8 = 21;
	
std::thread accepter;
	
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
bool accepting = true;


void BtnOpen_1Click()
{
	digitalWrite(pinRelais2, LOW);
	digitalWrite(pinRelais1, HIGH);
}

void BtnClose_1Click()
{
	digitalWrite(pinRelais1, LOW);
	digitalWrite(pinRelais2, HIGH);
}

void BtnEmpty_1Click()
{
	digitalWrite(pinRelais1, HIGH);
	digitalWrite(pinRelais2, HIGH);
}

void BtnOpen_2Click()
{
	digitalWrite(pinRelais4, LOW);
	digitalWrite(pinRelais3, HIGH);
}

void BtnClose_2Click()
{
	digitalWrite(pinRelais3, LOW);
	digitalWrite(pinRelais4, HIGH);
}

void BtnEmpty_2Click()
{
	digitalWrite(pinRelais3, HIGH);
	digitalWrite(pinRelais4, HIGH);
}

void BtnOpen_3Click()
{
	digitalWrite(pinRelais6, LOW);
	digitalWrite(pinRelais5, HIGH);
}

void BtnClose_3Click()
{
	digitalWrite(pinRelais5, LOW);
	digitalWrite(pinRelais6, HIGH);
}

void BtnEmpty_3Click()
{
	digitalWrite(pinRelais5, HIGH);
	digitalWrite(pinRelais6, HIGH);
}

void BtnOpen_4Click()
{
	digitalWrite(pinRelais8, LOW);
	digitalWrite(pinRelais7, HIGH);
}

void BtnClose_4Click()
{
	digitalWrite(pinRelais7, LOW);
	digitalWrite(pinRelais8, HIGH);
}

void BtnEmpty_4Click()
{
	digitalWrite(pinRelais7, HIGH);
	digitalWrite(pinRelais8, HIGH);
}

void BtnAllOpenClick()
{
	digitalWrite(pinRelais1, HIGH);
	digitalWrite(pinRelais2, LOW);
	digitalWrite(pinRelais3, HIGH);
	digitalWrite(pinRelais4, LOW);
	digitalWrite(pinRelais5, HIGH);
	digitalWrite(pinRelais6, LOW);
	digitalWrite(pinRelais7, HIGH);
	digitalWrite(pinRelais8, LOW);
}

void BtnAllCloseClick()
{
	digitalWrite(pinRelais1, LOW);
	digitalWrite(pinRelais2, HIGH);
	digitalWrite(pinRelais3, LOW);
	digitalWrite(pinRelais4, HIGH);
	digitalWrite(pinRelais5, LOW);
	digitalWrite(pinRelais6, HIGH);
	digitalWrite(pinRelais7, LOW);
	digitalWrite(pinRelais8, HIGH);
}

void BtnAllStopClick()
{
	digitalWrite(pinRelais1, HIGH);
	digitalWrite(pinRelais2, HIGH);
	digitalWrite(pinRelais3, HIGH);
	digitalWrite(pinRelais4, HIGH);
	digitalWrite(pinRelais5, HIGH);
	digitalWrite(pinRelais6, HIGH);
	digitalWrite(pinRelais7, HIGH);
	digitalWrite(pinRelais8, HIGH);
}

void SocketAccept()
{
	clilen = sizeof(cli_addr);
	while (accepting)
	{
		newsockfd = accept(sockfd,
			(struct sockaddr *) &cli_addr,
			&clilen);
		if (newsockfd < 0)
			continue;
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		if (n < 0) {
			printf("ERROR reading from socket\n");
			::close(newsockfd);
			continue;
		}
		printf("Here is the message: %s\n", buffer);
		n = strcmp(buffer, "Wartenberg\r\n");
		if (n != 0)
		{
			::close(newsockfd);
			continue;
		}
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		if (n < 0) {
			printf("ERROR reading from socket\n");
			::close(newsockfd);
			continue;
		}
		if (strcmp(buffer, "All Open\r\n") == 0) {
			BtnAllOpenClick();
		}
		else if (strcmp(buffer, "All Close\r\n") == 0) {
			BtnAllCloseClick();
		}
		else if (strcmp(buffer, "All Stop\r\n") == 0) {
			BtnAllStopClick();
		}
		else if (strcmp(buffer, "Close 1\r\n") == 0) {
			BtnClose_1Click();
		}
		else if (strcmp(buffer, "Close 2\r\n") == 0) {
			BtnClose_2Click();
		}
		else if (strcmp(buffer, "Close 3\r\n") == 0) {
			BtnClose_3Click();
		}
		else if (strcmp(buffer, "Close 4\r\n") == 0) {
			BtnClose_4Click();
		}
		else if (strcmp(buffer, "Open 1\r\n") == 0) {
			BtnOpen_1Click();
		}
		else if (strcmp(buffer, "Open 2\r\n") == 0) {
			BtnOpen_2Click();
		}
		else if (strcmp(buffer, "Open 3\r\n") == 0) {
			BtnOpen_3Click();
		}
		else if (strcmp(buffer, "Open 4\r\n") == 0) {
			BtnOpen_4Click();
		}
		else if (strcmp(buffer, "Stop 1\r\n") == 0) {
			BtnEmpty_1Click();
		}
		else if (strcmp(buffer, "Stop 2\r\n") == 0) {
			BtnEmpty_2Click();
		}
		else if (strcmp(buffer, "Stop 3\r\n") == 0) {
			BtnEmpty_3Click();
		}
		else if (strcmp(buffer, "Stop 4\r\n") == 0) {
			BtnEmpty_4Click();
		}
		else if (strcmp(buffer, "Stop Server\r\n") == 0) {
			::close(newsockfd);
			::close(newsockfd);
			::close(sockfd);
			exit(1); 
			accepting = false;
		}
		::close(newsockfd);
	}
}

void StartSocket()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = 13059;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	struct timeval tv;

	tv.tv_sec = 30;  /* 30 Secs Timeout */
	tv.tv_usec = 0;  // Not init'ing this can cause strange errors

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));
	if (bind(sockfd,
		(struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) {
		printf("ERROR binding\n");
	}
	listen(sockfd, 5);
	accepter = std::thread([]() {
		SocketAccept();
	});
}


void my_handler(int s) {
	::close(newsockfd);
	::close(sockfd);
	exit(1); 

}

int main(int argc, char *argv[])
{
	char sz[] = "Hello, World!";	//Hover mouse over "sz" while debugging to see its contents
	cout << sz << endl;	//<================= Put a breakpoint here
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);
	
	wiringPiSetup();

	pinMode(pinRelais1, OUTPUT);
	digitalWrite(pinRelais1, HIGH);
	pinMode(pinRelais2, OUTPUT);
	digitalWrite(pinRelais2, HIGH);
	pinMode(pinRelais3, OUTPUT);
	digitalWrite(pinRelais3, HIGH);
	pinMode(pinRelais4, OUTPUT);
	digitalWrite(pinRelais4, HIGH);
	pinMode(pinRelais5, OUTPUT);
	digitalWrite(pinRelais5, HIGH);
	pinMode(pinRelais6, OUTPUT);
	digitalWrite(pinRelais6, HIGH);
	pinMode(pinRelais7, OUTPUT);
	digitalWrite(pinRelais7, HIGH);
	pinMode(pinRelais8, OUTPUT);
	digitalWrite(pinRelais8, HIGH);
	BtnAllStopClick();
	StartSocket();
	sleep(300);//wait 5 min
	accepter.join();
	BtnAllStopClick();
	::close(newsockfd);
	::close(sockfd);
	return 0;
}