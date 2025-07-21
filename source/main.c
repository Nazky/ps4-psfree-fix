//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"
#include "PRX.h"
#include "INI.h"

void writePRX(){
  printf_notification("Start adding fix, please wait...");
  size_t len = 0;
  unsigned char* fbuf = base64_decode(PRXStr, sizeof(PRXStr), &len);
  sceKernelSleep(5);
	if (len != 0){
    mkdir("/data/GoldHEN/plugins", 0777);
    int fid = open("/data/GoldHEN/plugins/aio_fix_505.prx", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fid, fbuf, len);
    close(fid);
    sceKernelSleep(5);
    printf_notification("PRX fix install complete");
	}else{
		printf_notification("ERROR:\nNo PRX file found");
	}
}

void writeINI(){
  printf_notification("Start adding ini, please wait...");
  size_t len = 0;
  unsigned char* fbuf = base64_decode(INIStr, sizeof(INIStr), &len);
  sceKernelSleep(5);
	if (len != 0){
    mkdir("/data/GoldHEN", 0777);
    int fid = open("/data/GoldHEN/plugins.ini", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fid, fbuf, len);
    close(fid);
    sceKernelSleep(5);
    printf_notification("INI file install complete");
	}else{
		printf_notification("ERROR:\nNo INI file found");
	}
}

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();

  initSysUtil();

  char fw_version[6] = {0};
  get_firmware_string(fw_version);
  printf_notification("PSFree-Fix\nPS4 Firmware %s", fw_version);
  
  
  writeINI();

  writePRX();
  

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
