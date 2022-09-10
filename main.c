#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define uint8_t __int8
#define uint16_t __int16
#define uint32_t __int32
unsigned char buffer32[4]={0x00,0x00,0x00,0x00};
char buffer32_2[4]={0x0,0x0,0x0,0x0};
uint32_t Decode_buffer(unsigned char buffer[],uint8_t bufferstart,uint8_t bufferend)
{
    uint32_t buffer_num = 0;
    uint8_t i = bufferstart;
    for ( i; i<= bufferend; i++)
    {
        buffer_num =  buffer_num << 8;
        buffer_num +=  buffer[i];
    }
    return buffer_num;
}
char rx_buffer1[19]={0xEA,0x11 ,0x02 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x07 ,0x00 ,0x00 ,0x04 ,0x95 ,0x08 ,0x07 };
char CRSF_FRAMETYPE_HEADER = 0xEA;
char CRSF_FRAMETYPE_GPS = 0x02;
uint32_t crsf_gps_lat=0;//Latitude ( degree / 10`000`000 ) tmp_buffer[3]-[6]
uint32_t crsf_gps_lon=0;//Longitude (degree / 10`000`000 ) tmp_buffer[7]-[10]
uint16_t crsf_groundSpeed=0;//Groundspeed ( km/h / 10 )    tmp_buffer[11]-[12]
uint16_t crsf_gps_heading=0;//GPS heading ( degree / 100 ) tmp_buffer[13]-[14]
uint16_t crsf_altitude=0;//Altitude ( meter -1000m offset )tmp_buffer[15]-[16]
uint8_t crsf_satellites=0;//Satellites in use ( counter )  tmp_buffer[17]-[17]

char rx_buffer2[5]={0xEA,0x11 ,0x07 ,0x0F ,0x60};
char CRSF_FRAMETYPE_VARIO = 0x07;
uint16_t crsf_vertical_speed=0;// Vertical speed ( cm/s )  tmp_buffer[3]-[4]

char rx_buffer3[12]={0xEA ,0x0A ,0x08 ,0x00 ,0x01 ,0x00 ,0x6D ,0x00 ,0x00 ,0x75 ,0x60 ,0xE2 };
char CRSF_FRAMETYPE_BATTERY_SENSOR = 0x08;
uint16_t crsf_voltage=0;// ( mV * 100 )					 tmp_buffer[3]-[4]
uint16_t crsf_current=0;//  ( mA * 100 )					 tmp_buffer[5]-[6]
uint32_t crsf_capacity=0;//  ( mAh )  24位                 tmp_buffer[7]-[9]
uint8_t  crsf_battery_remaining=0;//  ( percent )		     tmp_buffer[10]-[10]

char rx_buffer4[14]={0xEA  ,0x0C  ,0x14  ,0xED  ,0x00  ,0x64  ,0x0C  ,0x00  ,0x02  ,0x00  ,0xF4  ,0x64  ,0x0A  ,0xE1 };
char CRSF_FRAMETYPE_LINK_STATISTICS = 0x14;
uint8_t crsf_rqly=0;//第11字节，[10]              tmp_buffer[10]-[10]

char rx_buffer5[10]={0xEA ,0x08 ,0x1E ,0x13 ,0xD3 ,0x0B ,0x9C ,0xFE ,0xF3 ,0x36 };
char CRSF_FRAMETYPE_ATTITUDE = 0x1E;
uint16_t crsf_pitch_angle;// Pitch angle ( rad / 10000 ) tmp_buffer[3]-[4]
uint16_t crsf_roll_angle;//  Roll angle ( rad / 10000 )  tmp_buffer[5]-[6]
uint16_t crsf_yaw_angle;//	 Yaw angle ( rad / 10000 )   tmp_buffer[7]-[8]

char rx_buffer6[10]={0xEA ,0x07 ,0x21 ,0x52 ,0x54 ,0x4C ,0x20 ,0x00 ,0xF0 };
char CRSF_FRAMETYPE_FLIGHT_MODE = 0x21; //EA ID 21 CHAR CHAR CHAR 00 crcbit
uint32_t crsf_flightmode;
char crsf_flightmode_str[20];
#define MANUAL_MODE "MANUAL"
#define CIRCLE_MODE "CIRCLE"
#define STABILIZE_MODE "STABILIZE"
#define TRAINING_MODE "TRAINING"
#define ACRO_MODE "ACRO"
#define FLY_BY_WIRE_A_MODE "FLY_BY_WIRE_A"
#define FLY_BY_WIRE_B_MODE "FLY_BY_WIRE_B"
#define CRUISE_MODE "CRUISE"
#define AUTOTUNE_MODE "AUTOTUNE"
#define AUTO_MODE "AUTO"
#define RTL_MODE "RTL"
#define LOITER_MODE "LOITER"
#define TAKEOFF_MODE "TAKEOFF"
#define AVOID_ADSB_MODE "AVOID_ADSB"
#define GUIDED_MODE "GUIDED"
#define INITIALISING_MODE "INITIALISING"
#define QSTABILIZE_MODE "QSTABILIZE"
#define QHOVER_MODE "QHOVER"
#define QLOITER_MODE "QLOITER"
#define QLAND_MODE "QLAND"
#define QRTL_MODE "QRTL"
#define QAUTOTUNE_MODE "QAUTOTUNE"
#define QACRO_MODE "QACRO"
#define THERMAL_MODE "THERMAL"
#define LOITER_ALT_QLAND_MODE "LOITER_ALT_QLAND"
int main(void)
{
	if((rx_buffer[0]==CRSF_FRAMETYPE_HEADER)&&(rx_buffer[2]==CRSF_FRAMETYPE_GPS))
	{
			crsf_gps_lat=Decode_buffer(rx_buffer,3,6);
			printf("crsf_gps_lat:%d\r\n",crsf_gps_lat);
			crsf_gps_lon=Decode_buffer(rx_buffer,7,10);
			printf("crsf_gps_lon:%d\r\n",crsf_gps_lon);
			crsf_groundSpeed=Decode_buffer(rx_buffer,11,12);
			printf("crsf_groundSpeed:%d\r\n",crsf_groundSpeed);
			crsf_gps_heading=Decode_buffer(rx_buffer,13,14);
			printf("crsf_gps_heading:%d\r\n",crsf_gps_heading);
			crsf_altitude=Decode_buffer(rx_buffer,15,16);
			printf("crsf_altitude:%d\r\n",crsf_altitude);
			crsf_satellites=Decode_buffer(rx_buffer,17,17);
			printf("crsf_satellites:%d\r\n",crsf_satellites);
			
	}
	else if((rx_buffer[0]==CRSF_FRAMETYPE_HEADER)&&(rx_buffer[2]==CRSF_FRAMETYPE_VARIO))
	{
			crsf_vertical_speed=Decode_buffer(rx_buffer,3,4);
			printf("crsf_vertical_speed:%d\r\n",crsf_vertical_speed);
			
	}
	else if((rx_buffer[0]==CRSF_FRAMETYPE_HEADER)&&(rx_buffer[2]==CRSF_FRAMETYPE_BATTERY_SENSOR))
	{
			crsf_voltage=Decode_buffer(rx_buffer,3,4);
			printf("crsf_voltage:%d\r\n",crsf_voltage);
			crsf_current=Decode_buffer(rx_buffer,5,6);
			printf("crsf_current:%d\r\n",crsf_current);
			crsf_capacity=Decode_buffer(rx_buffer,7,9);
			printf("crsf_capacity:%d\r\n",crsf_capacity);
			crsf_battery_remaining=Decode_buffer(rx_buffer,10,10);
			printf("crsf_battery_remaining:%d\r\n",crsf_battery_remaining);
	}
	else if((rx_buffer[0]==CRSF_FRAMETYPE_HEADER)&&(rx_buffer[2]==CRSF_FRAMETYPE_LINK_STATISTICS))
	{
			crsf_rqly=Decode_buffer(rx_buffer,11,11)*-1;
			printf("crsf_rqly:%d\r\n",crsf_rqly);
	}
	else if((rx_buffer[0]==CRSF_FRAMETYPE_HEADER)&&(rx_buffer[2]==CRSF_FRAMETYPE_ATTITUDE))
	{
			crsf_pitch_angle=Decode_buffer(rx_buffer,3,4);
			printf("crsf_pitch_angle:%d\r\n",crsf_pitch_angle);
			crsf_roll_angle=Decode_buffer(rx_buffer,5,6);
			printf("crsf_roll_angle:%d\r\n",crsf_roll_angle);
			crsf_yaw_angle=Decode_buffer(rx_buffer,7,8);
			printf("crsf_yaw_angle:%d\r\n",crsf_yaw_angle);
	}
	else if((rx_buffer[0]==CRSF_FRAMETYPE_HEADER)&&(rx_buffer[2]==CRSF_FRAMETYPE_FLIGHT_MODE))
	{
			uint8_t i=0;
			for(i;i<20;i++)
			{
				crsf_flightmode_str[i]=Decode_buffer(rx_buffer,3+i,3+i);
			}
			printf("crsf_flightmode_str:%s\r\n",crsf_flightmode_str);
			
			if(!strncmp(crsf_flightmode_str,MANUAL_MODE,strlen(MANUAL_MODE)))
			{
				printf("mode:%s\r\n","MANUAL");
				crsf_flightmode=0;
			}
			if(!strncmp(crsf_flightmode_str,CIRCLE_MODE,strlen(CIRCLE_MODE)))
			{
				printf("mode:%s\r\n","CIRCLE");
				crsf_flightmode=1;
			}
			if(!strncmp(crsf_flightmode_str,STABILIZE_MODE,strlen(STABILIZE_MODE)))
			{
				printf("mode:%s\r\n","STABILIZE");
				crsf_flightmode=2;
			}
			if(!strncmp(crsf_flightmode_str,TRAINING_MODE,strlen(TRAINING_MODE)))
			{
				printf("mode:%s\r\n","TRAINING");
				crsf_flightmode=3;
			}
						if(!strncmp(crsf_flightmode_str,ACRO_MODE,strlen(ACRO_MODE)))
			{
				printf("mode:%s\r\n","ACRO");
				crsf_flightmode=4;
			}
			if(!strncmp(crsf_flightmode_str,FLY_BY_WIRE_A_MODE,strlen(FLY_BY_WIRE_A_MODE)))
			{
				printf("mode:%s\r\n","FLY_BY_WIRE_A");
				crsf_flightmode=5;
			}
			if(!strncmp(crsf_flightmode_str,FLY_BY_WIRE_B_MODE,strlen(FLY_BY_WIRE_B_MODE)))
			{
				printf("mode:%s\r\n","FLY_BY_WIRE_B");
				crsf_flightmode=6;
			}
			if(!strncmp(crsf_flightmode_str,CRUISE_MODE,strlen(CRUISE_MODE)))
			{
				printf("mode:%s\r\n","CRUISE");
				crsf_flightmode=7;
			}
			if(!strncmp(crsf_flightmode_str,AUTOTUNE_MODE,strlen(AUTOTUNE_MODE)))
			{
				printf("mode:%s\r\n","AUTOTUNE");
				crsf_flightmode=8;
			}
			if(!strncmp(crsf_flightmode_str,AUTO_MODE,strlen(AUTO_MODE)))
			{
				printf("mode:%s\r\n","RTL");
				crsf_flightmode=10;
			}
			if(!strncmp(crsf_flightmode_str,RTL_MODE,strlen(RTL_MODE)))
			{
				printf("mode:%s\r\n","RTL");
				crsf_flightmode=11;
			}
			if(!strncmp(crsf_flightmode_str,LOITER_MODE,strlen(LOITER_MODE)))
			{
				printf("mode:%s\r\n","LOITER");
				crsf_flightmode=12;
			}
			if(!strncmp(crsf_flightmode_str,TAKEOFF_MODE,strlen(TAKEOFF_MODE)))
			{
				printf("mode:%s\r\n","TAKEOFF");
				crsf_flightmode=13;
			}
			if(!strncmp(crsf_flightmode_str,AVOID_ADSB_MODE,strlen(AVOID_ADSB_MODE)))
			{
				printf("mode:%s\r\n","AVOID_ADSB");
				crsf_flightmode=14;
			}
			if(!strncmp(crsf_flightmode_str,GUIDED_MODE,strlen(GUIDED_MODE)))
			{
				printf("mode:%s\r\n","GUIDED");
				crsf_flightmode=15;
			}
			if(!strncmp(crsf_flightmode_str,INITIALISING_MODE,strlen(INITIALISING_MODE)))
			{
				printf("mode:%s\r\n","INITIALISING");
				crsf_flightmode=16;
			}
			if(!strncmp(crsf_flightmode_str,QSTABILIZE_MODE,strlen(QSTABILIZE_MODE)))
			{
				printf("mode:%s\r\n","QSTABILIZE");
				crsf_flightmode=17;
			}
			if(!strncmp(crsf_flightmode_str,QHOVER_MODE,strlen(QHOVER_MODE)))
			{
				printf("mode:%s\r\n","QHOVER");
				crsf_flightmode=18;
			}
			if(!strncmp(crsf_flightmode_str,QLOITER_MODE,strlen(QLOITER_MODE)))
			{
				printf("mode:%s\r\n","QLOITER");
				crsf_flightmode=19;
			}
			if(!strncmp(crsf_flightmode_str,QLAND_MODE,strlen(QLAND_MODE)))
			{
				printf("mode:%s\r\n","QLAND");
				crsf_flightmode=20;
			}
			if(!strncmp(crsf_flightmode_str,QRTL_MODE,strlen(QRTL_MODE)))
			{
				printf("mode:%s\r\n","QRTL");
				crsf_flightmode=21;
			}
			if(!strncmp(crsf_flightmode_str,QAUTOTUNE_MODE,strlen(QAUTOTUNE_MODE)))
			{
				printf("mode:%s\r\n","QAUTOTUNE");
				crsf_flightmode=22;
			}
			if(!strncmp(crsf_flightmode_str,QACRO_MODE,strlen(QACRO_MODE)))
			{
				printf("mode:%s\r\n","QACRO");
				crsf_flightmode=23;
			}
			if(!strncmp(crsf_flightmode_str,THERMAL_MODE,strlen(THERMAL_MODE)))
			{
				printf("mode:%s\r\n","THERMAL");
				crsf_flightmode=24;
			}
			if(!strncmp(crsf_flightmode_str,LOITER_ALT_QLAND_MODE,strlen(LOITER_ALT_QLAND_MODE)))
			{
				printf("mode:%s\r\n","LOITER_ALT_QLAND");
				crsf_flightmode=25;
			}
			
	}
}
