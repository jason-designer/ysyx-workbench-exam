#include "sdb.h"

#define NR_WP 32

int pool_num;

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
	char* expr;
	uint64_t old_res;
	uint64_t new_res;
  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
		wp_pool[i].expr=NULL;
		wp_pool[i].old_res=0;
		wp_pool[i].new_res=0;
  }

  head = NULL;
  free_ = wp_pool;
	pool_num=0;
}

/* TODO: Implement the functionality of watchpoint */

void new_wp(char* exp)
{
	bool success;
	if(pool_num>=NR_WP) {printf("watchpoint pool is full\n");return;}
	WP* wp;
	wp=head;

	if(wp==NULL) {head=free_;wp=head;}
	else 	
	{
		while(wp->next!=NULL) wp=wp->next;
		wp->next=free_;
	}
	wp=free_;
	free_=free_->next;
	pool_num++;

	wp->next=NULL;
	wp->expr=malloc(50*sizeof(char));
	strcpy(wp->expr,exp);
	wp->new_res=expr(exp,&success);
	printf("new pool NO:%d ,expr:%s ,now pool num:%d\n",wp->NO,wp->expr,pool_num);
}

void free_wp(int NO)
{
	if(pool_num==0) {printf("can't find this watchpoint\n");return;}
	WP* wp;
	WP* wp_p;
	if(head->NO==NO) {wp=head;head=head->next;}
	else
	{
		wp_p=head;
		wp=head->next;
		while(wp!=NULL && wp->NO!=NO) {wp=wp->next;wp_p=wp_p->next;}
		if(wp==NULL) {printf("can't find this watchpoint\n");return;}
		wp_p->next=wp->next;	
	}
	
	free(wp->expr);
	wp->expr=NULL;
	wp->old_res=0;
	wp->new_res=0;

	wp->next=free_;
	free_=wp;
	pool_num--;
}

void show_watchpoint()
{
	WP* wp;
	wp=head;
	printf("used pool num:%d\n",pool_num);
	printf("used pool\n");
	while(wp!=NULL) 
	{
		printf("new pool NO:%d,expr:%s,old_res:%ld,new_res:%ld\n",wp->NO,wp->expr,wp->old_res,wp->new_res);	
		wp=wp->next;
	}

	wp=free_;
	printf("free pool\n");
	while(wp!=NULL)
  {
 		printf("new pool NO:%d,expr:%s,old_res:%ld,new_res:%ld\n",wp->NO,wp->expr,wp->old_res,wp->new_res);
    wp=wp->next;
  }
}

bool check_watchpoint()
{
	WP *wp;
	bool success;
	bool change=false;
	wp=head;
	while(wp!=NULL)
	{
		wp->old_res=wp->new_res;
		wp->new_res=expr(wp->expr,&success);
		if(wp->old_res!=wp->new_res) 
		{
			printf("watchpoint change! NO:%d,expr:%s,old_res:%ld,new_res:%ld\n",wp->NO,wp->expr,wp->old_res,wp->new_res);
			change=true;
		}
		wp=wp->next;
	}
	return change;
}


