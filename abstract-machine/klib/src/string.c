#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  const char *c=s;
  while(*s!='\0') s++;
  return s-c;
}

char *strcpy(char *dst, const char *src) {
  int i=0;
  assert(dst!=NULL && src!=NULL);
  while(src[i]!='\0') {dst[i]=src[i];i++;}
  dst[i]='\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  int i=0,j=0;
  assert(dst!=NULL && src!=NULL);
  while(dst[i]!='\0') i++;
  while(src[j]!='\0') {dst[i]=src[j];i++;j++;}
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  int i;
  for(i=0;;i++)
  {
    if(s1[i]!='\0'&& s2[i]!='\0')
    {
      if(s1[i]!=s2[i])
      {
        if(s1[i]<s2[i]) return -1;
        else return 1;
      }
    }
    else
    {
      if(s1[i]=='\0' && s2[i]=='\0') return 0;
      else
      {
        if(s1[i]!='\0' && s2[i]=='\0') return 1;
        else return -1;
      }
    }
  }
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  assert(s!=NULL && n>=0);
  char * tmp= (char *)s;
  while(n-->0) *tmp++=c;
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  assert((out!=NULL)&&(in!=NULL));
  assert(out>=in+n||in>out+n);
  unsigned char * pin = (unsigned char *)in;
  unsigned char * pout = (unsigned char *)out;
  while(n-->0)*pout++ = *pin++;
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  assert(s1!=NULL && s2!=NULL);
  int i;
  for(i=0;i<n;i++)
  {
    if(*((char*)s1+i)<*((char*)s2+i)) return -1;
    if(*((char*)s1+i)>*((char*)s2+i)) return 1;
  }
  return 0;
}

#endif
