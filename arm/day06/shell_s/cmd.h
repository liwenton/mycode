#ifndef __CMD_H_
#define __CMD_H_

void cmd_led_on(void);
void cmd_led_off(void);
void cmd_nand_readid(void);
void cmd_nand_page_read(void);
void cmd_nandbad(void);
void cmd_boot(void);
void cmd_reboot_shell(void);
void cmd_erase(void);
void cmd_help(void);
#endif
