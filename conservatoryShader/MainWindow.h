#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void BtnOpen_1Click();
	void BtnClose_1Click();
	void BtnEmpty_1Click();
	
	void BtnOpen_2Click();
	void BtnClose_2Click();
	void BtnEmpty_2Click();
	
	void BtnOpen_3Click();
	void BtnClose_3Click();
	void BtnEmpty_3Click();
	
	void BtnOpen_4Click();
	void BtnClose_4Click();
	void BtnEmpty_4Click();
	
	void BtnAllOpenClick();
	void BtnAllStopClick();
	void BtnAllCloseClick();
	void SocketAccept();
	
private:
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
	
    Ui::MainWindow *ui;
	
	void error(const char *msg)
	{
		perror(msg);
		exit(1);
	}
};



#endif // MAINWINDOW_H
