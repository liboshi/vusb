/* ########################################################################

   USBIP hardware emulation 

   ########################################################################

   Copyright (c) : 2016  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usbip.h"

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR dev_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    0x01,                   // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x02,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    0x10,                   // Max packet size for EP0, see usb_config.h
    0x2706,                 // Vendor ID
    0x000A,                 // Product ID
    0x0100,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x03,                   // Product string index
    0x00,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

const USB_DEVICE_QUALIFIER_DESCRIPTOR dev_qua = { 
    0x0A,       // bLength
    0x06,       // bDescriptorType
    0x0200,     // bcdUSB 
    0x02,       // bDeviceClass
    0x00,       // bDeviceSubClass
    0x00,       // bDeviceProtocol
    0x10,       // bMaxPacketSize
    0x01,       // iSerialNumber
    0x00        //bNumConfigurations*/
};


/* Configuration 1 Descriptor */
const CONFIG_CDC  configuration_cdc={{
    /* Configuration Descriptor */
    0x09,//sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,                // CONFIGURATION descriptor type
    sizeof(CONFIG_CDC),                 // Total length of data for this cfg
    2,                      // Number of interfaces in this cfg
    1,                      // Index value of this configuration
    0,                      // Configuration string index
    0xC0,      
    50,                     // Max power consumption (2X mA)
    },{ 
    /* Interface Descriptor */
    0x09,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    0,                      // Interface Number
    0,                      // Alternate Setting Number
    1,                      // Number of endpoints in this intf
    0x02,                   // Class code
    0x02,                   // Subclass code
    0x01,                   // Protocol code
    0                       // Interface string index
    },{
    /* CDC Class-Specific Descriptors */
    /* Header Functional Descriptor */    
    0x05,                   // bFNLength
    0x24,                   // bDscType
    0x00,                   // bDscSubType
    0x0110                  // bcdCDC
    },{ 
    /* Call Management Functional Descriptor */   
    0x05,                   // bFNLength
    0x24,                   // bDscType
    0x01,                   // bDscSubType
    0x01,                   // bmCapabilities
    0x01                    // bDataInterface
    },{
    /* Abstract Control Management Functional Descriptor */    
    0x04,                   // bFNLength
    0x24,                   // bDscType
    0x02,                   // bDscSubType 
    0x02                    // bmCapabilities 
    },{
    /* Union Functional Descriptor */    
    0x05,                   // bFNLength
    0x24,                   // bDscType
    0x06,                   // bDscSubType
    0x00,                   // bMasterIntf
    0x01                    // bSaveIntf0
    },{
     /* Endpoint Descriptor */
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x81,                       //EndpointAddress
    0x03,                       //Attributes
    0x0008,                     //size
    0x0A                        //Interval
    },{    
    /* Interface Descriptor */
    0x09,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    1,                      // Interface Number
    0,                      // Alternate Setting Number
    2,                      // Number of endpoints in this intf
    0x0A,                   // Class code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    2,                      // Interface string index
    },{
    /* Endpoint Descriptor */
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x02,                       //EndpointAddress
    0x02,                       //Attributes
    0x0020,                     //size
    0x00                        //Interval
    },{
    /* Endpoint Descriptor */
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x82,                       //EndpointAddress
    0x02,                       //Attributes
    0x0020,                     //size
    0x00                        //Interval
}};


const unsigned char string_0[] = { // available languages  descriptor
		0x04,                  
                USB_DESCRIPTOR_STRING, 
		0x09, 
                0x04 
		};

const unsigned char string_1[] = { //
		0x0A, 
                USB_DESCRIPTOR_STRING, // bLength, bDscType
		'T', 0x00, //
		'e', 0x00, //
		's', 0x00, //
		't', 0x00, //
		};

const unsigned char string_2[] = { //
		0x10, 
                USB_DESCRIPTOR_STRING, //
		'U', 0x00, //
		'S', 0x00, //
		'B', 0x00, //
		' ', 0x00, //
		'C', 0x00, //
		'D', 0x00, //
		'C', 0x00, //
		};

const unsigned char string_3[] = { //
		0x18, 
                USB_DESCRIPTOR_STRING, //
		'V', 0x00, //
		'i', 0x00, //
		'r', 0x00, //
		't', 0x00, //
		'u', 0x00, //
		'a', 0x00, //
		'l', 0x00, //
		' ', 0x00, //
                'U', 0x00, //
                'S', 0x00, //
                'B', 0x00, //
		};


const char *configuration = (const char *)&configuration_cdc; 

const USB_INTERFACE_DESCRIPTOR *interfaces[]={ &configuration_cdc.dev_int0, &configuration_cdc.dev_int1};

const unsigned char *strings[]={string_0, string_1, string_2, string_3};


#define BSIZE 1 
char buffer[BSIZE+1];
int  bsize=0;


void handle_data(int sockfd, USBIP_RET_SUBMIT *usb_req)
{   
    
  if(usb_req->ep == 0x01)
  {  
    send_usb_req(sockfd, usb_req, "", 0, 0);
    printf("EP1 received \n"); 
    //usleep(50000);
  }
  
  if((usb_req->ep == 0x02))
  {
    if(usb_req->direction == 0) //input
    { 
      bsize=recv (sockfd, (char *) buffer , BSIZE, 0);
      send_usb_req(sockfd, usb_req,"", 0, 0);
      buffer[bsize+1]=0; //string terminator
      printf("received (%s)\n",buffer);    
    }
    else //output
    {
      if(bsize != 0)
      {   
        int i;
        for(i=0;i<bsize;i++)//increment received char
           buffer[i]+=1;

        send_usb_req(sockfd, usb_req, buffer, bsize, 0);    
        printf("sending (%s)\n",buffer);
        bsize=0;
      }
      else
        send_usb_req(sockfd, usb_req,"", 0, 0);    
        printf("no data \n");
      //usleep(50000);
    }
  }
  
};


typedef struct _LINE_CODING
{
    word dwDTERate;  //in bits per second
    byte bCharFormat;//0-1 stop; 1-1.5 stop; 2-2 stop bits
    byte ParityType; //0 none; 1- odd; 2 -even; 3-mark; 4 -space
    byte bDataBits;  //5,6,7,8 or 16
}LINE_CODING;



LINE_CODING linec;

unsigned short linecs=0;

void handle_unknown_control(int sockfd, StandardDeviceRequest * control_req, USBIP_RET_SUBMIT *usb_req)
{
        if(control_req->bmRequestType == 0x21)//Abstract Control Model Requests
        { 
          if(control_req->bRequest == 0x20)  //SET_LINE_CODING
          {
            printf("SET_LINE_CODING\n");   
            if ((recv (sockfd, (char *) &linec , control_req->wLength, 0)) != control_req->wLength)
            {
              printf ("receive error : %s \n", strerror (errno));
              exit(-1);
            };
            send_usb_req(sockfd,usb_req,"",0,0);
          } 
          if(control_req->bRequest == 0x21)  //GET_LINE_CODING
          {
            printf("GET_LINE_CODING\n");  
            send_usb_req(sockfd,usb_req,(char *)&linec,7,0);
          }
          if(control_req->bRequest == 0x22)  //SET_LINE_CONTROL_STATE
          {
            linecs=control_req->wValue0;
            printf("SET_LINE_CONTROL_STATE 0x%02X\n", linecs);   
            send_usb_req(sockfd,usb_req,"",0,0);
          }
          if(control_req->bRequest == 0x23)  //SEND_BREAK
          {
            printf("SEND_BREAK\n");   
            send_usb_req(sockfd,usb_req,"",0,0);
          }
        } 

};

int main()
{
   printf("cdc started....\n");
   usbip_run(&dev_dsc);
}

