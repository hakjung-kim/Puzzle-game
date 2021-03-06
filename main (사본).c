#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "buzzer.h"
#include "led.h"
#include "button.h"
#include "colorLED.h"
#include "fnd.h"
#include "temperature.h"
#include "textlcd.h"
#include "bitmap.h"
int pic_num=0;
int key_home_pressed  = 0;
int key_back_pressed  = 0;
int key_search_pressed = 0;  


int main(void)
{	

	buttonInit();
	buzzerInit();        //buzzer
	ledLibInit();   //led
	pwmLedInit();              //pwmled


	int messageID = msgget(MESSAGE_ID, IPC_CREAT|0666);	//To Receive Message from Library.
	BUTTON_MSG_T rxMsg;



while(1)
{
	pwmSetPercent(0,0);
	pwmSetPercent(0,1);
	pwmSetPercent(100,2);
    show("start_pic.bmp");


     while(1)   //Wait here until key home pressed.
      { 
                msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0,0);
                printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
                         if (rxMsg.pressed == 0) continue;                               
                if (rxMsg.keyInput == KEY_HOME ) 
                 break;                                  
      }
                
 show("puzzle3.bmp");
 pic_num = 3;
   
    



	while (1)
	{
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
		//rxMsg.pressed == 0 -> Really Pressed.

		 if (rxMsg.pressed == 0) continue;
		switch(rxMsg.keyInput)
		{
			case KEY_HOME: 
				key_home_pressed = 1;   
			break;
			case KEY_BACK: 
				key_back_pressed = 1;  
			break;
			case KEY_SEARCH: 
				key_search_pressed = 1;
			break;
			case KEY_MENU: 
				printf("Menu key):"); 
			break;
			case KEY_VOLUMEUP: 
				printf("Volume up key):");  
			break;
			case KEY_VOLUMEDOWN:
				printf("Volume down key):");
			break;
	}
switch(pic_num)
    {
    /*puzzle1??? ????????? ???????????????-> ????????????*/
     case 1:                          //puzzle1??? ????????? ???????????????
          show ("end_pic.bmp");      //?????? ???????????? 
								//while ??? ???????????????(???????????????)
     break;

/*puzzle2??? ????????? ???????????????*/
     case 2:                          
        if(key_home_pressed==1 && key_back_pressed==1)
           { show("puzzle5.bmp");
                pic_num=5;
                key_home_pressed = 0; 
                key_back_pressed = 0;
             }
        else if (key_home_pressed==1 && key_search_pressed==1)
           {  show("puzzle4.bmp");
             pic_num=4;
                key_home_pressed = 0;
                key_search_pressed = 0;
            }
        else if (key_back_pressed==1 && key_search_pressed==1)
              { show("puzzle1.bmp");
               pic_num=1;
                 key_back_pressed = 0;
                 key_search_pressed = 0;
                    sleep(2);
                    show ("end_pic.bmp");
                }
     break;
     
/*puzzle 3??? ??? ????????????*/
     case 3:
         if(key_home_pressed==1 && key_back_pressed==1)
            {show("puzzle1.bmp");
                pic_num=1;
                key_home_pressed = 0;
                key_back_pressed = 0;
                    sleep(2);
                    show ("end_pic.bmp");                    
              }
        else if (key_home_pressed==1 && key_search_pressed==1)
           {  show("puzzle5.bmp");
             pic_num=5;
                key_home_pressed = 0;
                key_search_pressed = 0;
             }
        else if (key_back_pressed==1 && key_search_pressed==1)
               {show("puzzle4.bmp");
               pic_num=4;
                key_back_pressed = 0;
                key_search_pressed = 0;
                  }
     break;

/*puzzle 4??? ??? ????????????*/
     case 4:
         if(key_home_pressed==1 && key_back_pressed==1)
            {show("puzzle6.bmp");
                pic_num=6;
              key_home_pressed = 0;
              key_back_pressed = 0; 
              }
        else if (key_home_pressed==1 && key_search_pressed==1)
            { show("puzzle2.bmp");
             pic_num=2;
                key_home_pressed = 0;
                key_search_pressed = 0;
                }
        else if (key_back_pressed==1 && key_search_pressed==1)
             {  show("puzzle3.bmp");
               pic_num=3; 
                key_back_pressed = 0;
                key_search_pressed = 0;       
   }  
     break;

/*puzzle 5??? ??? ????????????*/
     case 5:
         if(key_home_pressed==1 && key_back_pressed==1)
          {  show("puzzle2.bmp");
                pic_num=2;
                key_home_pressed = 0;
                key_back_pressed = 0;
            }
        else if (key_home_pressed==1 && key_search_pressed==1)
           {  show("puzzle3.bmp");
             pic_num=3;
             key_home_pressed = 0;
             key_search_pressed = 0; 
                }
        else if (key_back_pressed==1 && key_search_pressed==1)
              { show("puzzle6.bmp");
               pic_num=6;
               key_back_pressed = 0;
               key_search_pressed = 0;
                }
     break;

/*puzzle 6??? ??? ????????????*/
     case 6:
         if(key_home_pressed==1 && key_back_pressed==1)
           { show("puzzle4.bmp");
                pic_num=4;
                 key_home_pressed = 0;
                 key_back_pressed = 0;        
            }
        else if (key_home_pressed==1 && key_search_pressed==1)
            { show("puzzle1.bmp");
             pic_num=1;
                key_home_pressed = 0;
                 key_search_pressed = 0;      
                    sleep(2);
                    show ("end_pic.bmp");      
                }
        else if (key_back_pressed==1 && key_search_pressed==1)
             {  show("puzzle5.bmp");
               pic_num=5;
                  key_back_pressed = 0;
                  key_search_pressed = 0;
                }
     break;

    }





if(pic_num==1){
	
	pwmSetPercent(100,0);
	pwmSetPercent(100,1);
	pwmSetPercent(100,2);
	pwmInactiveAll();          //pwmled
		ledLibRaw(0xFF);
	usleep(500000);
	ledLibRaw(0xAA);
	usleep(500000);
	ledLibRaw(0xFF);
	usleep(500000);
	ledLibRaw(0xAA);
	usleep(500000);
	ledLibRaw(0xFF);
	usleep(500000);
	ledLibRaw(0xAA);	
	usleep(500000);	
	ledLibEXT();    //led
        buzzerPlaySong(0);
        usleep(300000);
        buzzerPlaySong(1);
        usleep(300000);        
        buzzerPlaySong(2);
        usleep(300000);
        buzzerPlaySong(3);
        usleep(300000);
        buzzerPlaySong(4);
        usleep(300000);
        buzzerPlaySong(5);
        usleep(300000);
        buzzerPlaySong(6);
        usleep(300000);
        buzzerPlaySong(7);
        usleep(300000);
		 buzzerStopSong();			
        buzzerExit();       //buzzer	

	buttonExit();   //button

                                                   //temperature
        char *buffer; int file;
		file=spi_init("/dev/spidev1.0"); //dev
		buffer=(char *)spi_read_lm74(file);
		close(file);
		int value = 0; //13?????? Big Endian Signed Int??? 16?????? Little Endian Signed Int??? ?????????
		value = (buffer[1] >> 3); //Last 3bit: Trashes ??????????????? ??????: ?????? 5????????? value??? ?????????
		value += (buffer[0]) << 5; //????????? 5?????? ???????????? ?????? 8?????? (= 13??????) ??? ????????? ????????? ??????
		if ( buffer[0]&0x80 ) //?????? buffer[0]??? ????????? 8?????? ????????? 1????????? ????????? ?????? = ?????? ????????? ????????? ??? ???
		{ //?????? value??? 32??? ?????????????????? 14??? ???????????? 1??? ?????? ?????? ??? (2??? ??????, ?????? ??????)
		int i=0;
		for (i=31;i > 12; i--)
		value |= (1<<i); //1??? ????????? ??????
		}
		//??? ??????
		double temp = (double)value*0.0625;
		//1????????? 0.0625???
		printf("Current Temp: %lf \n", temp);
	                                     //temperature  

   writeTextLcd("welcome","",1);
   writeTextLcd("","oo",2);                                               
 

   fndDisp(11111,1);

       /* fndOff(); */





}







	}
   
		
		
	}

	
	                                             




return 0;

}
