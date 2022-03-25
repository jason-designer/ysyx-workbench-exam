#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
	//int i;
  //int w = 400;  // TODO: get the correct width
  //int h = 300;  // TODO: get the correct height
  //uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  //for (i = 0; i < w * h; i ++) fb[i] = i;
  //outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 0, .height = 0,
    .vmemsz = 0
  };
	uint32_t ctl=inl(VGACTL_ADDR);
	cfg->width=ctl>>16;
	cfg->height=ctl&0x0000ffff;
	cfg->vmemsz=(cfg->width)*(cfg->height)*(sizeof(uint32_t));
}

void cp(int x,int y,uint32_t v)
{
	outl(FB_ADDR+4*(y*400+x),v);
}
//void cp_line(int x,int y,int w,uint32_t *v)
//{
//	uint32_t *p=(volatile uint32_t *)(FB_ADDR);
//	memcpy(v,p+400*y+x,w);
//}
//int min(a,b)
//{
//	return a<b?a:b;
//}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
	int x,y,w,h;
	int i,j;
	uint32_t* p=ctl->pixels;
	uint32_t W,H;
	W=inl(VGACTL_ADDR)>>16;
	H=inl(VGACTL_ADDR)&0x0000ffff;
	x=ctl->x;
	y=ctl->y;
	w=ctl->w;
	h=ctl->h;
	for(j=y;j<(y+h) && j<H;j++)
	{
		for(i=x;i<(x+w) && i<W;i++) cp(i,j,p[w*(j-y)+(i-x)]);
	}
	//outl(SYNC_ADDR, 1);//不要立即刷新时注释掉
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
