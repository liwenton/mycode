#include "user.h"
#include "menu.h"

void input(struct User *u1){
  printf("name :");
  fflush(stdout);
  scanf("%s",u1->name);
  printf("passwd:");
  fflush(stdout);
  scanf("%s",u1->passwd);
  printf("email :");
  fflush(stdout);
  scanf("%s",u1->email);
}

void output(struct User *u2){
  printf("name  :%s\n",u2->name);
  printf("passwd:%s\n",u2->passwd);
  printf("email :%s\n",u2->email);
}

int check_user(char *path,char cname[]){
 int i;
 struct User up;
 int fd=open(path,O_RDONLY);
 int len=lseek(fd,0,SEEK_END);
 lseek(fd,0,SEEK_SET);
 for(i=0;i<(len/sizeof(up));i++){
   read(fd,&up,sizeof(up));
  if(!strcmp(cname,up.name)){
   printf("the name alreadyed use,pleace input again\n");
   return -1;
  }
 }
  close(fd);
  return 0;     
}

int regist(char *path){
  struct User ureg;
  printf("welcome to register your information!\n");
  int fd=open(path,O_RDWR|O_CREAT|O_APPEND,0666);
  input(&ureg);
  if(check_user(path,ureg.name))
   return -1;
  int wr=write(fd,&ureg,sizeof(ureg));
  close(fd); 
  if(wr<=0){
    perror("write");
    return -1;
  }
  printf("input user information successful\n");
   return 0;   
}

int login(char *path){
}

int quit(char *path){
  exit(-1);
}

int manager(char *path){
}

int auprintf(char *path){
  int i;
  struct User up;
  int fd=open(path,O_RDONLY);
  if(fd<0){
   perror("allprintf");
   return -1;
  }
  int len=lseek(fd,0,SEEK_END);
  lseek(fd,0,SEEK_SET);
  for(i=0;i<(len/sizeof(up));i++){
  read(fd,&up,sizeof(up));
  printf("[%d]\n",i);
  output(&up);
  }
  close(fd);
  return 0;
}


void printf_menu(char **add){
   int i=1;
  for(;*add!=NULL;add++){
   printf("%s",*add);
  } 
} 
 
struct Cmd clogin[]={
 1,regist,
 2,login,
 3,manager,
 4,quit, 
};

int main(){
 int i;
 struct User u;
 printf_menu(login_menu);
 scanf("%d",&i);
 clogin[i-1].func("./info.bat");
// auprintf("./info.bat");
 return 0;
}
