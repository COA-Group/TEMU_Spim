#include "../TEMU/temu/include/monitor/watchpoint.h"
#include "../TEMU/temu/include/monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

//addadd
WP *new_wp(){
    if(free_){
        WP *tmp = head, *nwp = free_;
        free_ = free_->next;
        nwp->next = head;
        head = nwp;
        int no = 0;
        while(tmp != NULL){
            no++;
            tmp = tmp->next;
        }
        nwp->NO = no;
        return nwp;
    }
    else{
        assert(0);
    }
}


void free_wp(WP *wp){
    WP *tmp = head;
    if(tmp == wp){
        head = head->next;
        tmp->next = free_;
        free_ = tmp;
        return;
    }
    while(tmp->next != wp && tmp->next != NULL){
        tmp = tmp->next;
    }
    if(tmp->next == NULL){
        return;
    }
    else{
        tmp->next = wp->next;
        wp->next = free_;
        free_ = wp;
    }
}
//addadd
