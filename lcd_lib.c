
#include "lcd_lib.h"

void delay(int count){
	int i=0;
	for(i=0;i<=count;i++);
} //
//setup lcd command register
void send_cmd(unsigned char cmd){
	GPIO0DATA=0b000;
	GPIO2DATA=cmd;
	GPIO0DATA=0b100;
	delay(2000);
	GPIO0DATA=0b000;
	delay(1000);
} //
//setup lcd data register
void send_letter(unsigned char letter){
	GPIO0DATA=0b010;
	GPIO2DATA=letter;
	GPIO0DATA=0b110;
	delay(1000);
	GPIO0DATA=0b010;
	delay(50000);
}
void send_string(char* string){
	while(*string != '\0'){
		send_letter(*string);
		string++;
	}
}
void cursor_home(){
	send_cmd(0x2);
	delay(1000);
}
void clear_screen(){
	send_cmd(0x1);
	delay(1000);
}
void setup_lcd(){
	delay(1500);
	send_cmd(0b00110000);
	delay(4100);
	send_cmd(0b00110000);
	delay(100);
	send_cmd(0b00110000);
	send_cmd(0b00111000);
	send_cmd(0b00001111);
	send_cmd(0b00000001);
	delay(1520);
	send_cmd(0b00000110);
}