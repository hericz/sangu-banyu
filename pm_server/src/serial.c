/*
	setting awal serial
	banyak dicopy dari pm_server
	
	21 feb 2009
	furkan jadid
	daun biru engineering
	
	*/

//#define BAUDRATE B19200

#include "serial.h"
#include <termios.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


#define BAUDRATE B38400
#define _POSIX_SOURCE 1 /* POSIX compliant source */



void set_awal_serial(int fd)
{
	struct termios oldtio,newtio;
    struct sigaction saio;           /* definition of signal action */
	
	/* install the signal handler before making the device asynchronous */
    saio.sa_handler = signal_handler_IO;
    //saio.sa_mask = 0;
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO,&saio,NULL);
          
    /* allow the process to receive SIGIO */
    fcntl(fd, F_SETOWN, getpid());
    /* Make the file descriptor asynchronous (the manual page says only 
       O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
    fcntl(fd, F_SETFL, FASYNC);
        
    tcgetattr(fd,&oldtio); /* save current port settings */
    /* set new port settings for canonical input processing */
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    
    //newtio.c_iflag = IGNPAR | ICRNL;
    newtio.c_iflag = IGNPAR;
    
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;		// non-canonical
    newtio.c_cc[VMIN]=1;	// wait 1 karakter
    newtio.c_cc[VTIME]=0;
    
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);

}


void signal_handler_IO (int status)
{
	//printf("received SIGIO signal.\n");
    //printf("r");
    wait_flag = FALSE;
}

