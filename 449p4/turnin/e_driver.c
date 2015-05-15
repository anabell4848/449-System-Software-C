/*
Hanyu Xiong
CS449
Project 4

*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h> // For copy_to_user
#include "e.h" // For e function

 /*
 * e_read is the function called when a process calls read() on
 * /dev/e.
 */

static ssize_t e_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{
	unsigned int allocate = *ppos + count;
	char *e_buffer;
	
	// Allocate some space
	e_buffer = (char*)kmalloc(allocate+1, GFP_KERNEL); 
	
	//e function
	e(e_buffer, allocate);
	
	// Copy to the user space
	if (copy_to_user(buf, e_buffer + *ppos, count)) {
		return -EINVAL;
	}
	
	kfree(e_buffer); 	// Free the buffer
	*ppos += count; 	// Increment the position
	return count;
}

/* 
 * The only file operation we care about is read.
 */
static const struct file_operations e_fops = {
	.owner		= THIS_MODULE,
	.read		= e_read,
};

static struct miscdevice e_driver = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/e.
	 */
	"e",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&e_fops
};

static int __init e_init(void)
{
	int ret;
	/*
	 * Create the "hello" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/hello device using
	 * the default rules.
	 */
	ret = misc_register(&e_driver);
	if (ret) 
		printk(KERN_ERR "Unable to register e char device\n");

	return ret;
}

module_init(e_init);

/* Sets up /sys/class/misc/e
 * Must manually create /dev/e
 */
static void __exit e_exit(void)
{
	misc_deregister(&e_driver);
}

module_exit(e_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hanyu Xiong <hax12@pitt.edu>");
MODULE_DESCRIPTION("Module for outputing numbers of e");
MODULE_VERSION("1");
