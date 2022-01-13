/*
 * Copyright (c) 2016 Permabit Technology Corporation.
 *
 * This is the test sysfs node which writes its input using printk.
 *
 * $Id: //eng/main/src/tools/permatest/permatest-1/printk.c#1 $
 */

#include <linux/kobject.h>
#include <linux/module.h>

/**********************************************************************/
static void topRelease(struct kobject *kobj)
{
}

/**********************************************************************/
static ssize_t topShow(struct kobject   *kobj,
                       struct attribute *attr,
                       char             *buf)
{
  return -EINVAL;
}

/**********************************************************************/
static ssize_t topStore(struct kobject   *kobj,
                        struct attribute *attr,
                        const char       *buf,
                        size_t            length)
{
  printk(KERN_INFO "%*s", (int) length, buf);
  return length;
}

/**********************************************************************/

static struct attribute printkAttr = {
  .name = "printk",
  .mode = 0222,
};

static struct attribute *topAttrs[] = {
  &printkAttr,
  NULL,
};

static struct sysfs_ops topOps = {
  .show  = topShow,
  .store = topStore,
};

struct kobj_type topObjectType = {
  .release       = topRelease,
  .sysfs_ops     = &topOps,
  .default_attrs = topAttrs,
};

struct kobject topKobj;

/**********************************************************************/
static int __init printkInit(void)
{
  kobject_init(&topKobj, &topObjectType);
  return kobject_add(&topKobj, NULL, THIS_MODULE->name);
}

/**********************************************************************/
static void __exit printkExit(void)
{
  kobject_put(&topKobj);
}

module_init(printkInit);
module_exit(printkExit);

MODULE_DESCRIPTION("Permabit printk module for testing code");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");
