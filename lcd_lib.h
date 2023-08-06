#define GPIO0DIR (*((volatile unsigned long *)0x50008000))
#define GPIO0DATA (*((volatile unsigned long *)0x50003FFC))
#define GPIO1DIR (*((volatile unsigned long *)0x50018000))
#define GPIO1DATA (*((volatile unsigned long *)0x50013FFC))
#define GPIO2DIR (*((volatile unsigned long *)0x50028000))
#define GPIO2DATA (*((volatile unsigned long *)0x50023FFC))

void delay(int count);
void send_cmd(unsigned char cmd);
void send_letter(unsigned char letter);
void send_string(char* string);
void cursor_home();
void clear_screen();
void setup_lcd();