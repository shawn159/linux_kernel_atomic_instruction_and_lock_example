#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/delay.h>

int cnt;

int test_thread_1(void *_arg)
{
	int *arg = (int*)_arg;
	__sync_lock_test_and_set(&cnt, 10);
	printk("set cnt 10\n");
	kfree(arg);
	return 0;
}

int test_thread_2(void *_arg)
{
	int *arg = (int*)_arg;
	bool stop = false;
	while(!stop){
		if(__sync_val_compare_and_swap(&cnt, 10, 7) == 10)
			stop = true;
	}
	printk("swap cnt 7\n");
	kfree(arg);
	return 0;
}

int test_thread_3(void *_arg)
{
	int *arg = (int*)_arg;
	bool stop = false;
	while(!stop){
		if(__sync_val_compare_and_swap(&cnt, 7, 4) == 7)
			stop = true;
	}
	printk("swap cnt 4\n");
	kfree(arg);
	return 0;
}

int test_thread_4(void *_arg)
{
	int *arg = (int*)_arg;
	bool stop = false;
	while(!stop){
		if(__sync_val_compare_and_swap(&cnt, 4, 1) == 4)
			stop = true;
	}
	printk("swap cnt 1\n");
	kfree(arg);
	return 0;
}

void thread_create(void)
{
	int *arg;
	arg = (int*)kmalloc(sizeof(int), GFP_KERNEL);
	*arg = 1;
	kthread_run(&test_thread_1, (void*)arg, "test_thread");
	arg = (int*)kmalloc(sizeof(int), GFP_KERNEL);
	*arg = 1;
	kthread_run(&test_thread_2, (void*)arg, "test_thread");
	arg = (int*)kmalloc(sizeof(int), GFP_KERNEL);
	*arg = 1;
	kthread_run(&test_thread_3, (void*)arg, "test_thread");
	arg = (int*)kmalloc(sizeof(int), GFP_KERNEL);
	*arg = 1;
	kthread_run(&test_thread_4, (void*)arg, "test_thread");
}

int __init hello_module_init(void)
{
	thread_create();
	printk(KERN_EMERG "Hello Module!\n");
	return 0;
}

void __exit hello_module_cleanup(void)
{
	printk("Bye Module!");
}


module_init(hello_module_init);
module_exit(hello_module_cleanup);
MODULE_LICENSE("GPL");
