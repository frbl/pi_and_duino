#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
//gcc pwm.c -I/usr/local/include -L/usr/local/lib -lwiringPi -lpthread -o pwm

enum SIDE            /* Defines an enumeration type    */
{
    right_color = 0x11,       /* Names day and declares a       */
    left_color = 0x12,     /* variable named workday with    */ 
    right_white = 0x14,         /* that type                      */
    left_white = 0x18,
};

struct RGB {
    int side;
    int r;
    int g;
    int b;
};



struct RGB colorConverter(int hexValue)
{
  struct RGB rgbColor;
  rgbColor.side = ((hexValue >> 24) & 0xFF);
  rgbColor.r = ((hexValue >> 16) & 0xFF) * 2.55;  // Extract the RR byte
  rgbColor.g = ((hexValue >> 8) & 0xFF) * 2.55;   // Extract the GG byte
  rgbColor.b = ((hexValue) & 0xFF) * 2.55;        // Extract the BB byte

  return rgbColor; 
}

void control_event(int sig);
void setup_socket();
void set_color(int color);
void test_loop();

int BLUE_PIN=0;
int GREEN_PIN=2;
int RED_PIN=3;

int BLUE_PIN_RIGHT=1;
int GREEN_PIN_RIGHT=4;
int RED_PIN_RIGHT=5;

int PORT = 5000;
int sockfd, newsockfd;
int DELAY_MS=10;


int pins_size = 6;

int main(void)
{
    
    (void)signal(SIGINT,control_event);
    (void)signal (SIGQUIT,control_event);
    (void)signal (SIGPIPE,control_event);
    
    printf("PiLight software based PWM v0.1\n");
    if(getuid()!=0) //wiringPi requires root privileges
    {
        printf("Error:wiringPi must be run as root.\n");
        return 1;
    }
    if(wiringPiSetup()==-1)
    {
        printf("Error:wiringPi setup failed.\n");
        return 1;
    }
    
    softPwmCreate(RED_PIN,0,100); //setup software pwm pin
    softPwmCreate(GREEN_PIN,0,100);
    softPwmCreate(BLUE_PIN,0,100);
    
    softPwmCreate(RED_PIN_RIGHT,0,100); //setup software pwm pin
    softPwmCreate(GREEN_PIN_RIGHT,0,100);
    softPwmCreate(BLUE_PIN_RIGHT,0,100);
    
    test_loop();

    setup_socket();
    
}

void test_loop() {
    
    int pins[] = {GREEN_PIN,GREEN_PIN_RIGHT,BLUE_PIN,BLUE_PIN_RIGHT,RED_PIN,RED_PIN_RIGHT};
    set_color(0x110000ff);
    delay(1000);
    set_color(0x12ff0000);
    delay(1000);
    set_color(0x1100ff00);
        delay(1000);
    set_color(0x1200ff00);
    delay(1000);
    set_color(0x11ff0000);
        delay(1000);
    set_color(0x120000ff);
    delay(1000);
    int i = 0;
    for(i = 0; i < pins_size; i++) {
        softPwmWrite(pins[i],0);        
    }
}


void set_color(int color) {
    //pinMode(HARD_PWM_PIN,PWM_OUTPUT); //setup hardware pwm
    printf("Showing color %x\n", color);
    struct RGB rgbColor = colorConverter(color);
    //pwmWrite(HARD_PWM_PIN,up);
    int red;
    int green;
    int blue;
    printf("Side: %d and %d %d\n", rgbColor.side,right_color,left_color);
    
    if(rgbColor.side == right_color) {
        red = RED_PIN_RIGHT;
        blue = BLUE_PIN_RIGHT;
        green = GREEN_PIN_RIGHT;
    }
    else if(rgbColor.side == left_color) {
        red = RED_PIN;
        blue = BLUE_PIN;
        green = GREEN_PIN;
    }
    
    softPwmWrite(red,rgbColor.r);
    softPwmWrite(blue,rgbColor.g);
    softPwmWrite(green,rgbColor.b);
    //delay(DELAY_MS*10);
}

void control_event(int sig)
{
    int pins[] = {GREEN_PIN,GREEN_PIN_RIGHT,BLUE_PIN,BLUE_PIN_RIGHT,RED_PIN,RED_PIN_RIGHT};
    printf("\b\bExiting...\n");
    int i = 0;
    for(i = 0; i < pins_size; i++) {
        softPwmWrite(pins[i],0);        
    }
    close(newsockfd);
    close(sockfd);
    delay(100); //wait a little for the pwm to finish write
    exit(0);
}

void setup_socket(){
    socklen_t clilen;
         
    char buffer[16];
         
    struct sockaddr_in serv_addr, cli_addr;
         
    int n;
         
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check if the socket can be opened
    if (sockfd < 0) {
        printf("ERROR opening socket");
        control_event(-1);
    }
        
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    // Set some stuff for the socket connection
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    
    // If it is not able to bind to the socket, error 
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR on binding");
        control_event(-1);
    }   
    
    listen(sockfd,5);
         
    clilen = sizeof(cli_addr);
                 
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
    int color;
    
    while(1) {
        
        // If something is wrong with the socket
        if (newsockfd < 0) {
            printf("ERROR on accept");
            control_event(-1);
        }
              
        bzero(buffer,16);
         
        n = read(newsockfd,buffer,15);
        
        if (n <= 0) { 
            break;
        }
             
        
        sscanf(buffer, "%x", &color);

        printf("%x\n", color);
        set_color(color);
    
    }    
    control_event(0);
}


