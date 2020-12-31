#include "pubsub.h"
#include <iostream>

void onrecieve(string s){
	cout << s << endl;
}

int main(){
	publisher p("team1");
	topic t("team1);
	p.send("hello world");
	
}