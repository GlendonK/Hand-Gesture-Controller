#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include "sensors.h"



void delay(int);

int led(int data)
{
   
    int fbfd;
    uint16_t *map;
    uint16_t *p;
    struct fb_fix_screeninfo fix_info;

    /* open the led frame buffer device */
    fbfd = open(FILEPATH, O_RDWR);
    if (fbfd == -1) {
	perror("Error (call to 'open')");
	exit(EXIT_FAILURE);
    }

    /* read fixed screen info for the open device */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
	perror("Error (call to 'ioctl')");
	close(fbfd);
	exit(EXIT_FAILURE);
    }

    /* now check the correct device has been found */
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
	printf("%s\n", "Error: RPi-Sense FB not found");
	close(fbfd);
	exit(EXIT_FAILURE);
    }

    /* map the led frame buffer device into memory */
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (map == MAP_FAILED) {
	close(fbfd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }

    /* set a pointer to the start of the memory area */
    p = map;
    memset(map, 0, FILESIZE);

    /* clear the led matrix */
    if(data == 3){

    //Punch
    *(p + 17) = GREEN;
    *(p + 18) = GREEN;
    *(p + 19) = GREEN;
    *(p + 20) = GREEN;
    *(p + 21) = GREEN;
    *(p + 22) = GREEN;
    *(p + 30) = GREEN;
    *(p + 38) = GREEN;
    *(p + 46) = GREEN;
    *(p + 45) = GREEN;
    *(p + 44) = GREEN;
    *(p + 36) = GREEN;
    *(p + 28) = GREEN;
    *(p + 20) = GREEN;
    *(p + 27) = GREEN;
    *(p + 34) = GREEN;
    *(p + 41) = GREEN;

    delay(0);

   // memset(map, 0, FILESIZE);
    }

//down
    /* light it down! */
    if(data == 0){

    *(p + 25) = RGB565_RED;
    *(p + 26) = RGB565_RED;
    *(p + 27) = RGB565_RED;
    *(p + 28) = RGB565_RED;
    *(p + 29) = RGB565_RED;
    *(p + 30) = RGB565_RED;
    *(p + 33) = RGB565_RED;
    *(p + 34) = RGB565_RED;
    *(p + 35) = RGB565_RED;
    *(p + 36) = RGB565_RED;
    *(p + 37) = RGB565_RED;
    *(p + 38) = RGB565_RED;
    *(p + 21) = RGB565_RED;
    *(p + 12) = RGB565_RED;
    *(p + 52) = RGB565_RED;
    *(p + 45) = RGB565_RED;
    delay(0);

   // memset(map, 0, FILESIZE);
    }
 //up
    if(data == 4){
    *(p + 25) = RGB565_RED;
    *(p + 26) = RGB565_RED;
    *(p + 27) = RGB565_RED;
    *(p + 28) = RGB565_RED;
    *(p + 29) = RGB565_RED;
    *(p + 30) = RGB565_RED;
    *(p + 33) = RGB565_RED;
    *(p + 34) = RGB565_RED;
    *(p + 35) = RGB565_RED;
    *(p + 36) = RGB565_RED;
    *(p + 37) = RGB565_RED;
    *(p + 38) = RGB565_RED;
    *(p + 18) = RGB565_RED;
    *(p + 11) = RGB565_RED;
    *(p + 51) = RGB565_RED;
    *(p + 42) = RGB565_RED;
    delay(0);

    //memset(map, 0, FILESIZE);
    }
//left
    if(data == 2){
    *(p + 11) = RGB565_RED;
    *(p + 19) = RGB565_RED;
    *(p + 27) = RGB565_RED;
    *(p + 35) = RGB565_RED;
    *(p + 43) = RGB565_RED;
    *(p + 52) = RGB565_RED;
    *(p + 12) = RGB565_RED;
    *(p + 20) = RGB565_RED;
    *(p + 28) = RGB565_RED;
    *(p + 36) = RGB565_RED;
    *(p + 44) = RGB565_RED;
    *(p + 51) = RGB565_RED;
    *(p + 45) = RGB565_RED;
    *(p + 38) = RGB565_RED;
    *(p + 42) = RGB565_RED;
    *(p + 33) = RGB565_RED;
    delay(0);

    //memset(map, 0, FILESIZE);
    }

//right
    if(data == 1){
    *(p + 11) = RGB565_RED;
    *(p + 19) = RGB565_RED;
    *(p + 27) = RGB565_RED;
    *(p + 35) = RGB565_RED;
    *(p + 43) = RGB565_RED;
    *(p + 52) = RGB565_RED;
    *(p + 12) = RGB565_RED;
    *(p + 20) = RGB565_RED;
    *(p + 28) = RGB565_RED;
    *(p + 36) = RGB565_RED;
    *(p + 44) = RGB565_RED;
    *(p + 51) = RGB565_RED;
    *(p + 18) = RGB565_RED;
    *(p + 25) = RGB565_RED;
    *(p + 21) = RGB565_RED;
    *(p + 30) = RGB565_RED;
    delay(0);

    //memset(map, 0, FILESIZE);
    }


    /* un-map and close */
    if (munmap(map, FILESIZE) == -1) {
	perror("Error un-mmapping the file");
    }
    close(fbfd);

    return 0;
}

void delay(int t)
{
    usleep(t * 1000);
}
