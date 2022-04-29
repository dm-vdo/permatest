/*
 * Copyright Red Hat
 *
 * This is the test sysfs node which writes its input using printk.
 *
 * $Id: //eng/main/src/tools/permatest/permatest-1/printk.c#2 $
 */

#include <linux/kobject.h>
#include <linux/module.h>

/**********************************************************************/
static void top_release(struct kobject *kobj)
{
}

/**********************************************************************/
static ssize_t top_show(struct kobject *kobj,
			struct attribute *attr,
			char *buf)
{
	return -EINVAL;
}

/**********************************************************************/
static ssize_t top_store(struct kobject *kobj,
			 struct attribute *attr,
			 const char *buf,
			 size_t length)
{
	printk(KERN_INFO "%*s", (int) length, buf);
	return length;
}

/**********************************************************************/

static struct attribute printk_attr = {
	.name = "printk",
	.mode = 0220,
};

static struct attribute *top_attrs[] = {
	&printk_attr,
	NULL,
};
ATTRIBUTE_GROUPS(top);

static struct sysfs_ops top_ops = {
	.show  = top_show,
	.store = top_store,
};

struct kobj_type top_object_type = {
	.release = top_release,
	.sysfs_ops = &top_ops,
	.default_groups = top_groups,
};

struct kobject top_kobj;

/**********************************************************************/
static int __init printk_init(void)
{
	kobject_init(&top_kobj, &top_object_type);
	return kobject_add(&top_kobj, NULL, THIS_MODULE->name);
}

/**********************************************************************/
static void __exit printk_exit(void)
{
	kobject_put(&top_kobj);
}

module_init(printk_init);
module_exit(printk_exit);

MODULE_DESCRIPTION("VDO testing code");
MODULE_AUTHOR("Red Hat");
MODULE_LICENSE("GPL-2.0");
