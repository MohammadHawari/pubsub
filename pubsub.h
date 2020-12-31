#include "PracticalSocket.h"
#include <iostream>
#include <thread>
#include <string>
using namespace std;


class publisher{
private:
	SocketAddress remote_addr;
	string topic;
	UDPSocket sock;
	
	
public:
	publisher(string topic, string ipadr = "127.0.0.1", int port = 8080):topic(topic), remote_addr(ipadr, port, SocketAddress::UDP_SOCKET) noexcept(false) {

	}
	
	void send(string message){
		string message = "publish " + topic + " " + message;
		try{
			sock.sendTo(message.data(), message.size(), remote_addr );
		}
		catch(SocketException& e) {
			cerr << "ERROR sending " << message << " --> " << e.what() << endl;
		}
	}
};



void onrecieve(string message);

class topic{
	
private:
	
	string topic_string;
	UDPSocket sock;
	
	void wait_for_messages(){
		while(true){
			try{
				SocketAddress from_adr;
				int n = sock.recvFrom(buffer, 1024, from_adr);
				buffer[n] = '\0';
				onrecieve(buffer);
				
			}
			catch(SocketException& e) {
				cerr << "ERROR recieving messages from " << topic  << " --> " << e.what() << endl;
			}
			
		}
	}
	
public:
	
	topic(string s, string ipadr = "127.0.0.1", int port = 8080):topic_string (s), remote_addr(ipadr, port, SocketAddress::UDP_SOCKET) noexcept(false) {
		thread t(wait_for_messages, this).detach();
	}
	
	void subscribe(){
		string message = "subscribe " + topic_string + "  ";
		try{
			sock.sendTo(message.data(), message.size(), remote_addr );
		}
		catch(SocketException& e) {
			cerr << "ERROR subscribing to " << topic  << " --> " << e.what() << endl;
		}
	}
	
	void unsubscribe(){
		string message = "unsubscribe " + topic_string + "  ";
		try{
			sock.sendTo(message.data(), message.size(), remote_addr );
		}
		catch(SocketException& e) {
			cerr << "ERROR unsubscribing from " << topic  << " --> " << e.what() << endl;
		}
	}
	
	
};
		