#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x87b79d0, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa4575f27, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x7a253321, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x123f82f3, __VMLINUX_SYMBOL_STR(getrawmonotonic64) },
	{ 0x910fae45, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0x6d8f5631, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9db7abd7, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x131b157e, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x99557ed, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xe2562782, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x8b4a6b3e, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3835F565FFC5762EE893D6E");
