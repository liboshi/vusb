/*-----------------------------------------------------------------------------
  USBIP hardware emulation

  -----------------------------------------------------------------------------
  Copyright (c) : 2016  Boush Li

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

Email: boush.li@outlook.com
---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usbip.h"

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR dev_dsc=
{
        0x12,                   // Size of this descriptor in bytes
        0x01,                   // DEVICE descriptor type
        0x0111,                 // USB Spec Release Number in BCD format
        0x00,                   // Class Code
        0x00,                   // Subclass code
        0x00,                   // Protocol code
        0x08,                   // Max packet size for EP0, see usb_config.h
        0x9527,                 // Vendor ID
        0x0000,                 // Product ID: Mouse in a circle fw demo
        0x0000,                 // Device release number in BCD format
        0x00,                   // Manufacturer string index
        0x00,                   // Product string index
        0x00,                   // Device serial number string index
        0x01                    // Number of possible configurations
};


/* Configuration 1 Descriptor */
const CONFIG_MASS configuration_mass={
        {
                /* Configuration Descriptor */
                0x09,                         // Size of this descriptor in bytes
                0x02,                         // CONFIGURATION descriptor type
                sizeof(CONFIG_MASS),          // Total length of data for this cfg
                0x01,                         // Number of interfaces in this cfg
                0x01,                         // Value to use as an agrument
                0x01,                         // Index of string descriptor
                0x80,                         // Configuration characteristics
                0x50                          // Max power consumption (2X mA)
        },{
                /* Interface Descriptor */
                0x09,                         // Size of this descriptor in bytes
                0x04,                         // INTERFACE descriptor type
                0x00,                         // Interface Number
                0x00,                         // Alternate Setting Number
                0x02,                         // Number of endpoints in this intf
                0x08,                         // Class code
                0x02,                         // Subclass code
                0x50,                         // Protocol code
                0x00                          // Interface string index
        },{
                /* Bulk-In Endpoint Descriptor */
                0x07,                         // Size of this descriptor in bytes
                0x05,                         // Endpoint Descriptor
                0x81,                         // EndpointAddress
                0x02,                         // Attributes
                0x0008,                       // size
                0x00                          // Interval
        },{
                /* Bulk-Out Endpoint Descriptor */
                0x07,                         // Size of this descriptor in bytes
                0x05,                         // Endpoint Descriptor
                0x00,                         // EndpointAddress
                0x02,                         // Attributes
                0x0008,                       // size
                0x00                          // Interval
        }
};

const char *configuration = (const char *) &configuration_mass;
const USB_INTERFACE_DESCRIPTOR *interfaces[]={ &configuration_mass.dev_int };
const unsigned char *strings[]={};
const USB_DEVICE_QUALIFIER_DESCRIPTOR  dev_qua={};

void handle_data(int sockfd, USBIP_RET_SUBMIT *usb_req)
{
};

void handle_unknown_control(int sockfd, StandardDeviceRequest * control_req, USBIP_RET_SUBMIT *usb_req)
{
        if(control_req->bmRequestType == 0x81)
        {
                if(control_req->bRequest == 0x6)  //# Get Descriptor
                {
                        if(control_req->wValue1 == 0x22)  // send initial report
                        {
                                printf("send initial report\n");
                        }
                }
        }
        if(control_req->bmRequestType == 0x21)  // Host Request
        {
                if(control_req->bRequest == 0x0a)  // set idle
                {
                        printf("Idle\n");
                        // Idle
                        send_usb_req(sockfd,usb_req,"",0,0);
                }
        }
};

int main()
{
        printf("mass-storage started....\n");
        usbip_run(&dev_dsc);
}

