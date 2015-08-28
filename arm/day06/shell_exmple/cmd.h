#ifndef __CMD_H__
#define __CMD_H__

typedef struct _cmd {
    const char *name;
    void (*cmd)(void);
}cmd_t;


extern cmd_t *cmd_find(const char *srt);

#endif //__CMD_H__

