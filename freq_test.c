#include <stdio.h>
/*
  Code used to test the Channel to Frequency layout
  Dylan Reinhold
  02/03/2017
*/

int is_channel(int cmd) {
    if((cmd >= 0 && cmd <= 0x2F7) || (cmd >= 0x32f && cmd <= 0x33F) ||
          (cmd >= 0x3c1 && cmd <= 0x3FE) ||cmd == 0x3BE ) {
               return 0;
    }
    return -1;
}

double getfreq(int cmd, char band) {
    double freq = 0.0;
    if(cmd < 0 || cmd > 0x3FE) 
        return freq;
    if(cmd <= 0x2CF) {
        if(band == 'R' && cmd >= 0x1B8 && cmd <= 0x22F) { /* Re Banded Site */
          freq = 851.0250 + (0.025 * ((double) (cmd-0x1B8)));
        } else if(band == 'S' && cmd <= 0x257) { /* Splinter Site */
          freq = 851.0 + (0.025 * ((double) cmd));
        } else {
          freq = 851.0125 + (0.025 * ((double) cmd));
        }
    } else if(cmd <= 0x2f7) {
        freq = 866.0000 + (0.025 * ((double) (cmd-0x2D0)));
    } else if(cmd >= 0x32F && cmd <= 0x33F ) {
        freq = 867.0000 + (0.025 * ((double) (cmd-0x32F)));
    } else if( cmd == 0x3BE) {
        freq = 868.9750;
    } else if (cmd >= 0x3C1 && cmd <= 0x3FE) {
        freq = 867.4250 + (0.025 * ((double) (cmd-0x3C1)));
    }

  return freq * 1000000;
}
    

int main(int argc, char *argv[]) {
  int chan_start = 0;
  int chan_end = 1024;
  double b_freq = 0.0;
  double s_freq = 0.0;
  double r_freq = 0.0;
  printf("Testing Motorola Trunk Channel Map\n\n");
  printf("Channel,Standard/Base,Splinter,Reband\n");
  for(;chan_start<=chan_end;chan_start++) {
    if(is_channel(chan_start) == 0) {
      b_freq = getfreq(chan_start,'B');
      s_freq = getfreq(chan_start,'S');
      r_freq = getfreq(chan_start,'R');
      printf("%d,%f,%f,%f\n", chan_start, b_freq/1000000, s_freq/1000000, r_freq/1000000);
    } else {
      printf("%d,ERROR,ERROR,ERROR\n", chan_start);
    }
  }
  return 0;
}
