#include "QR_Encode.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc<3) {
    printf("qrencode <input file> <output file> [QR Code level] [QR Code version]\n");
    printf("level and version default to 3 and 0\n");
    return 1;
  }

  int level=3;
  if(argc>3) {
    level = atoi(argv[3]);
  }

  int version=0;
  if(argc>4) {
    version = atoi(argv[4]);
  }

  // Read in the input data from file, terminate with 0.
  FILE *inputfile = fopen(argv[1],"r");
  char inputdata[10000];
  int n;
  for(n=0;(!feof(inputfile)) && (n < 10000);n++) {
    int c = getc(inputfile);
    inputdata[n] = c;
    inputdata[n+1]=0;
  }

  // **** This calls the library and encodes the data
  // *** length is taken from NULL termination, however can also be passed by parameter.


  BYTE QR_m_data[3917]; //max possible bits resolution 177*177/8+1
  CQR_Encode encoder;

  int QR_width=encoder.EncodeData(3,version,inputdata,0,QR_m_data);

  // Write the data to the output file
  FILE *outputfile=fopen(argv[2],"w");
  fwrite(QR_m_data,size,1,outputfile);
  fclose(f);


  // This code dumps the QR code to the screen as ASCII.
  printf("QR Code width: %u\n",QR_width);

  int bit_count=0;
  for(n=0;n<size;n++) {
    int b=0;
    for(b=7;b>=0;b--) {
      if((bit_count%QR_width) == 0) printf("\n");
      if((QR_m_data[n] & (1 << b)) != 0) { printf("1"); }
                                    else { printf("0"); }
      bit_count++;
    }
  }

  return 0;
}
