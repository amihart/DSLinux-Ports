#define __16F873
#include "p16f873.h"

unsigned char failures = 0;
unsigned char dummy = 0;

unsigned char uchar0=0;
unsigned char uchar1=0;
unsigned char uchar2=0;


void done(void)
{
  dummy++;
}
/*
void incptr(unsigned char *ucP)
{
  *ucP = *ucP + 1;
}
*/

void inc(unsigned char k)
{
  uchar0 = uchar0 + k;
}

void f1(void)
{

  uchar2++;
}

void nested_call(unsigned char u)
{

  f1();
  uchar1 = uchar1 + u;
  inc(uchar1);

}
  //  uchar1 = uchar1 + uchar0;
  //  uchar2 = uchar1 + k;

void main(void)
{

  uchar0=1;
  //incptr(&uchar0);
  inc(uchar0);
  if(uchar0 !=2)
    failures++;

  uchar0 = 2;
  uchar1 = 1;
  uchar2 = 1;
  nested_call(uchar2);

  if(uchar0 !=4)
    failures++;

  done();
}
