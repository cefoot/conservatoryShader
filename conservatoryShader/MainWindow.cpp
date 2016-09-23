#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <wiringPi.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 13059;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd,
		(struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) {
			error("ERROR binding");
	}
	listen(sockfd, 5);
	accepter = std::thread([this]() {
		SocketAccept();
	});
}

MainWindow::~MainWindow()
{
	::close(newsockfd);
	::close(sockfd);
	accepting = false;
	accepter.join();
	digitalWrite(pinRelais1, HIGH);
	digitalWrite(pinRelais2, HIGH);
	digitalWrite(pinRelais3, HIGH);
	digitalWrite(pinRelais4, HIGH);
	digitalWrite(pinRelais5, HIGH);
	digitalWrite(pinRelais6, HIGH);
	digitalWrite(pinRelais7, HIGH);
	digitalWrite(pinRelais8, HIGH);
    delete ui;
}

void MainWindow::SocketAccept()
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
		if (n < 0) error("ERROR reading from socket");
		printf("Here is the message: %s\n", buffer);
		/*if (strncmp(buffer, "All"))
		{
			BtnAllOpenClick();
		}*/
		::close(newsockfd);
	}
}

void MainWindow::BtnOpen_1Click()
{
	digitalWrite(pinRelais2, LOW);
	digitalWrite(pinRelais1, HIGH);
}

void MainWindow::BtnClose_1Click()
{
	digitalWrite(pinRelais1, LOW);
	digitalWrite(pinRelais2, HIGH);
}

void MainWindow::BtnEmpty_1Click()
{
	digitalWrite(pinRelais1, HIGH);
	digitalWrite(pinRelais2, HIGH);
}

void MainWindow::BtnOpen_2Click()
{
	digitalWrite(pinRelais4, LOW);
	digitalWrite(pinRelais3, HIGH);
}

void MainWindow::BtnClose_2Click()
{
	digitalWrite(pinRelais3, LOW);
	digitalWrite(pinRelais4, HIGH);
}

void MainWindow::BtnEmpty_2Click()
{
	digitalWrite(pinRelais3, HIGH);
	digitalWrite(pinRelais4, HIGH);
}

void MainWindow::BtnOpen_3Click()
{
	digitalWrite(pinRelais6, LOW);
	digitalWrite(pinRelais5, HIGH);
}

void MainWindow::BtnClose_3Click()
{
	digitalWrite(pinRelais5, LOW);
	digitalWrite(pinRelais6, HIGH);
}

void MainWindow::BtnEmpty_3Click()
{
	digitalWrite(pinRelais5, HIGH);
	digitalWrite(pinRelais6, HIGH);
}

void MainWindow::BtnOpen_4Click()
{
	digitalWrite(pinRelais8, LOW);
	digitalWrite(pinRelais7, HIGH);
}

void MainWindow::BtnClose_4Click()
{
	digitalWrite(pinRelais7, LOW);
	digitalWrite(pinRelais8, HIGH);
}

void MainWindow::BtnEmpty_4Click()
{
	digitalWrite(pinRelais7, HIGH);
	digitalWrite(pinRelais8, HIGH);
}

void MainWindow::BtnAllOpenClick()
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

void MainWindow::BtnAllCloseClick()
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

void MainWindow::BtnAllStopClick()
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
