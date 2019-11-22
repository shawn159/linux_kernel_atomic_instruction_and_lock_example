#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include "calclock.h"

struct list_head my_list;
struct mutex list_lock;
int finish_count;

unsigned long long time1, count1;
unsigned long long time2, count2;
unsigned long long time3, count3;

struct my_node{
	struct list_head list;
	int data;
};

static int list_insert(void *arg)
{
	struct my_node *new_node;
	int i;
	for(i = 0; i < 25000; i++){
		new_node = (struct my_node*)kmalloc(sizeof(struct my_node), GFP_KERNEL);
		new_node->data = i;
		mutex_lock(&list_lock);
		list_add(&new_node->list, &my_list);
		mutex_unlock(&list_lock);
	}
	__sync_fetch_and_add(&finish_count, 1);
	return 0;
}

static int list_traverse(void *arg)
{
	struct my_node *current_node;
	mutex_lock(&list_lock);
	list_for_each_entry(current_node, &my_list, list){
		if(current_node->data == 10000){
			printk("valuef find, value: 10000\n");
			goto out;
		}
	}
out:
	mutex_unlock(&list_lock);
	__sync_fetch_and_add(&finish_count, 1);
	return 0;
}

static int list_delete(void *arg)
{
	struct my_node *current_node;
delete:
	mutex_lock(&list_lock);
	list_for_each_entry(current_node, &my_list, list){
		list_del(&current_node->list);
		kfree(current_node);
		mutex_unlock(&list_lock);
		goto delete;
	}
	mutex_unlock(&list_lock);
	__sync_fetch_and_add(&finish_count, 1);
	return 0;
}

void thread_create(void)
{
	int i;
	struct timespec local_time[2];
	INIT_LIST_HEAD(&my_list);
	mutex_init(&list_lock);
	finish_count = 0;
	getrawmonotonic(&local_time[0]);
	for(i = 0; i < 4; i++){
		kthread_run(&list_insert, NULL, "test_thread");
	}
	
	while(__sync_fetch_and_add(&finish_count, 0) != 4){
	}
	getrawmonotonic(&local_time[1]);
	calclock(local_time, &time1, &count1);

	finish_count = 0;
	getrawmonotonic(&local_time[0]);
	for(i = 0; i < 4; i++){
		kthread_run(&list_traverse, NULL, "test_thread");
	}
	
	while(__sync_fetch_and_add(&finish_count, 0) != 4){
	}
	getrawmonotonic(&local_time[1]);
	calclock(local_time, &time2, &count2);

	finish_count = 0;
	getrawmonotonic(&local_time[0]);
	for(i = 0; i < 4; i++){
		kthread_run(&list_delete, NULL, "test_thread");
	}
	
	while(__sync_fetch_and_add(&finish_count, 0) != 4){
	}
	getrawmonotonic(&local_time[1]);
	calclock(local_time, &time3, &count3);
	printk("function finished!!!\n");

}

int __init hello_module_init(void)
{
	thread_create();
	printk(KERN_EMERG "Hello Module!\n");
	return 0;
}

void __exit hello_module_cleanup(void)
{
	printk("mutex linked list insert time : %llu ns\n", time1);
	printk("mutex linked list search time : %llu ns\n", time2);
	printk("mutex linked list delete time : %llu ns\n", time3);
	printk("Bye Module!");
}


module_init(hello_module_init);
module_exit(hello_module_cleanup);
MODULE_LICENSE("GPL");
