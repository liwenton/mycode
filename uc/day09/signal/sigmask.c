#include <stdio.h>
#include <signal.h>

void fa(int signo)
{
    printf("捕获了信号%d\n",signo);
}

int main()
{
    signal(SIGINT, fa);
    signal(SIGQUIT,fa);
    signal(40,fa); //可靠信号
    printf("pid=%d\n", getpid());
    printf("普通代码开始了，信号没有屏蔽");
    sleep(10); //只要来一个信号，休眠就结束了
    printf("执行关键代码，信号被屏蔽\n");
    sigset_t new, old;
    sigemptyset(&new);
    sigaddset(&new, 2);
    sigaddset(&new, 3);
    sigaddset(&new, 40);
    sigprocmask(SIG_SETMASK, &new, &old);
    sleep(20);
    printf("执行关键代码完毕，接触屏蔽\n");
    sigprocmask(SIG_SETMASK, &old, NULL);
}
