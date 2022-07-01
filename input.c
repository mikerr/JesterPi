#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include <termios.h>
#include <linux/input.h>

int inputfd;

int init_input()
{
  //  input
    char inputname[256] = "Unknown";
    char *inputdevice = "/dev/input/event2";

    if ((inputfd = open(inputdevice, O_RDONLY)) >= 0) {
      ioctl (inputfd, EVIOCGNAME (sizeof (inputname)), inputname);
      fprintf(stderr,"Using %s - %s\n", inputdevice, inputname);

      /* Disable auto-repeat (for now...) */
      //int ioctl_params[2] = { 0, 0 };
      //ioctl(inputfd,EVIOCSREP,ioctl_params);
    }

    struct termios new,orig;
    tcgetattr(0, &orig);
    memcpy(&new, &orig, sizeof(struct termios));
    new.c_lflag &= ~(ICANON | ECHO);
    new.c_cc[VTIME] = 0;
    new.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new);
}

int input_getkey ()
{
      int c;
      struct timeval tv = { 0L, 100000L };  /* 100ms */
      fd_set fds;
      int maxfd = 0;
      FD_ZERO(&fds);
      FD_SET(0, &fds);
      if (inputfd >= 0) {
        FD_SET(inputfd,&fds);
        maxfd = inputfd;
      }
      c = -1;
      if (select(maxfd+1, &fds, NULL, NULL, &tv)==0) {
        c = -1;
      } else {
        if (FD_ISSET(0,&fds)) {
          c = getchar();
        }
        if ((inputfd >= 0) && (FD_ISSET(inputfd,&fds))) {
          //c = get_input_key(inputfd);
        }
      }
 return c;
}

