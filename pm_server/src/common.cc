

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gtkmm.h>

//#include "interface.h"
//#include "support.h"
#include "common.hh"

//======================= INCLUDE SOCKET
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
/*
struct t_serv {
	char stat;
	char IP[18];
	char ourIP[18];
} serv;
//======================================

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>

#define JUMLAH_PM    10
//#define TIPE_PM710
#define TIPE_PM810
#define FONT_LABEL	"Monospace 14"
#define SOKET_NOBLOK


#include "mbcrc.h"
//#include "low_mod.h"

//extern char MODEMDEVICE[];
extern unsigned int jum_PM;

unsigned char addr_PM710;
unsigned char addr_KTA;
unsigned short jum_balik;
unsigned int konting=0;
unsigned int urutan=0;
unsigned int lanjut;
unsigned int trm;
unsigned int pool_wait;
unsigned int loop_kirim=0;
//int iwaktu;
int fd;

#ifdef TIPE_PM710
float satuan_kwh;
float satuan_kw;
float satuan_volt;
float satuan_amp;

#define MAKS_URUT	7

#endif

#ifdef TIPE_PM810
short satuan_t;
float satuan_kwh[JUMLAH_PM];
float satuan_kw[JUMLAH_PM];
float satuan_volt[JUMLAH_PM];
float satuan_volt2[JUMLAH_PM];     // L - N
float satuan_amp[JUMLAH_PM];
float satuan_amp2[JUMLAH_PM];      // L - N

#define MAKS_URUT	8
#endif

unsigned char buf[255];
struct d_pmod pmod;
struct t_kontrol_PM kontrol_PM[JUMLAH_PM];
struct dpm_eth pm_eth;

//#include "serial.c"
#include "low_mod.h"
#include "mbcrc.h"

#ifdef GUNA_THREAD
#include "fungsi_soket.c"
#endif

#ifdef SOKET_NOBLOK
int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
#endif
*/

