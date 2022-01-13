# Copyright (c) 2022 Red Hat.

EXTRA_CFLAGS =	-std=gnu99				\
		-fno-builtin-memset			\
		-fno-stack-protector			\
		-Werror					\
		-Wno-declaration-after-statement

obj-m += permatest.o
permatest-objs = printk.o
