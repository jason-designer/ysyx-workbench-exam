#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
/**********************************************************/
int _i2a(int num, char buf[32], int radix);
int _itoa(int num, char buf[32]);

int _itoa(int num, char buf[32])
{
    return _i2a(num, buf, 10);
}

int _i2a(int num, char buf[32], int radix)
{
    static const char s[] = "0123456789abcdef";
    int n = num, R = radix;
    char *dst = buf;
    if (n < 0) { *dst++ = '-'; n = -n; }
    if (n < 10)
    {
        *dst++ = s[n]; *dst = 0;
    }else
    {
        char tmp[32], *p = tmp;
        while (n) { *p++ = s[n % R]; n /= R; }
        while (--p != tmp) *dst++ = *p;
        *dst++ = *tmp; *dst = 0;
    }
    return dst-buf;
}

int _ui2a(uint64_t num, char buf[64], int radix)
{
    static const char s[] = "0123456789abcdef";
    uint64_t n = num, R = radix;
    char *dst = buf;
    if (n < 10)
    {
        *dst++ = s[n]; *dst = 0;
    }else
    {
        char tmp[32], *p = tmp;
        while (n) { *p++ = s[n % R]; n /= R; }
        while (--p != tmp) *dst++ = *p;
        *dst++ = *tmp; *dst = 0;
    }
    return dst-buf;
}
/************************************************************/
#define PRINTF_BUF_SIZE 128
char print_buf[PRINTF_BUF_SIZE];
int printf(const char *fmt, ...) {
  va_list ap;
  unsigned int i;

  va_start (ap, fmt);
  i = vsprintf (print_buf, fmt, ap);
  va_end (ap);

  int x;
  for(x=0;x<i;x++) putch(print_buf[x]);

  return i;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *s = out;
  const char *f = fmt;
  while(*f)
  {
    int n=1;
    if(*f!='%') *s=*f;
    else
    {
      ++f;
        switch(*f)
        {
          case 's':
                    {
                      const char *p = va_arg(ap,char*);
                      n = strlen(p);
                      memcpy(s , p, n);
                    }
                    break;
          case 'd':
                    {
                      char buf[32];
                      n = _itoa(va_arg(ap,int),buf);
                      memcpy(s,buf,n);
                    }
                    break;
          case 'p':
                    {
                      char buf[66];
                      buf[0] = '0';
                      buf[1] = 'x';
                      n = _ui2a(va_arg(ap,uint64_t), buf+2, 16);
                      n += 2;
                      memcpy(s,buf,n);
                    }
                    break;
          case 'c':
                    {
                      const char p = va_arg(ap, int);
                      n = 1;
                      *s = p;
                    }
                    break;
          case '0' ... '9':
                    {
                      //???????????????????????????
                      int fchar = ' ', fwidth, ftype;
                      if(*(f+1) >= '0' && *(f+1) <= '9'){
                        fchar = *f;
                        fwidth = *++f - '0';
                        ftype = *++f;
                      }
                      else{
                        fwidth = *f - '0';
                        ftype = *++f;
                      }
                      //
                      switch(ftype){
                        case 'd': 
                                  {
                                    char buf[32];
                                    n = _itoa(va_arg(ap,int),buf);
                                    if(n < fwidth){
                                      char buf2[fwidth];
                                      for(int i = 0; i < fwidth; i++){
                                        if(i < (fwidth - n)) buf2[i] = fchar;
                                        else buf2[i] = buf[i - fwidth + n];
                                      }
                                      n = fwidth;
                                      memcpy(s,buf2,n);
                                    }
                                    else memcpy(s,buf,n);
                                  }
                                  break;
                        case 'x':
                                  {
                                    char buf_final[66];//??????0x
                                    buf_final[0]='0';
                                    buf_final[1]='x';
                                    char buf[64];//16?????????
                                    n = _ui2a(va_arg(ap,uint64_t), buf, 16);
                                    //
                                    if(n < fwidth){
                                      char buf2[fwidth];//???????????????16?????????
                                      for(int i = 0; i < fwidth; i++){
                                        if(i < (fwidth - n)) buf2[i] = fchar;
                                        else buf2[i] = buf[i - fwidth + n];
                                      }
                                      n = fwidth;
                                      strcpy(buf_final+2, buf2);
                                    }
                                    else strcpy(buf_final+2, buf);
                                    n += 2;
                                    memcpy(s,buf_final,n);
                                  }
                                  break;
                        default : 
                                  {
                                    printf("%c\n",ftype);
                                    assert(0);
                                  }
                      }
                    }
                    break;
          default:
                    {
											printf("%c\n",*f);
                      assert(0);
                    }
                    break;
        }
    }
    ++f;
    s+=n;
  }
  *s='\0'; // /0???asic?????????0
  return s-out;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int i=vsprintf(out,fmt,ap);
  va_end(ap);
  return i;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
