//voorbeeld2.cpp
//voorbeeld van een subscriper
//builden met g++ -o <naam van executable> voorbeeld2.cpp PracticalSocket.cpp -pthread

#include "pubsub.h"
#include <iostream>

//maak een functie die aangeeft wat er dient te gebeuren indien een message binnenkomt
void onrecieve(string s){
	cout << s << endl;
}

int main(){
	
	//maak een subscription met twee parameters 1. de naam van de topic 2. de naam van de functie
	//optioneel 3. ipadres en 4. poortnummer van de server
	subscription s("mytopic", onrecieve);
	
	cout << "waiting for messages" << endl;
	cout << "type \'s\' to stop"  << endl;
	cin.get();
	
	
	return 0;
}