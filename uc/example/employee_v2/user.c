#include "user.h"
#include "menu.h"

char *path="info.bat";

void input_user(struct User *u1){
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

void output_user(const struct User *u2){
  printf("name  :%s\n",u2->name);
  printf("passwd:%s\n",u2->passwd);
  printf("email :%s\n",u2->email);
}

int write_user(char *filename, const struct User *user,int size){
  int i;
  int fd=open(filename,O_RDWR|O_CREAT|O_APPEND,0666);
  if(fd==-1)return -1;
  int res;
  for(i=0;i<size;i++){
  res=write(fd,&user[i],sizeof(struct User));
  }
  close(fd);
  return res==-1?res:0;
}

int get_usersize(char *filename){
  struct stat s;
  int res=stat(filename,&s);
  return (s.st_size/sizeof(struct User));
}

int read_user(char *filename,struct User *user,int size){
  int i;
  int fd=open(filename,O_RDONLY);
  if(fd==-1)return -1;
  int res;
  for(i=0;i<size;i++){
  res=read(fd,&user[i],sizeof(struct User));
  }
  close(fd);
  return res==-1?res:0;
}
int register_user(char *filename,  struct User *user){
   int i=0;
   int res; 
   printf("请输入用户的注册信息\n");
   input_user(user);
   res=access(path,F_OK);
   if(res==-1)return -1;

   int size=get_usersize(path);  
   struct User buf[size];
   read_user(path,buf,size);
   for(i=0;i<size;i++){
    if(!strcmp(buf[i].name,user->name)){
      return -2;
    }
  }

   res=write_user(path,user,1);
   if(res==-1)return -1;
   return 0;
}
int login_user(char *filename,struct User *us){
   printf("请输入用户的注册信息\n");
}
int modify_user(char *filename,struct User *user){
  printf("\n");
  
}

int remove_user(char *filename,struct User *user){
   int size=get_usersize(path);
   struct User buf[size];
   read_user(path,buf,size);
   for(i=0;i<size;i++){
    if(!strcmp(buf[i].name,user->name)){
    }
  }

   res=write_user(path,user,1);
   if(res==-1)return -1;
   return 0;
}

}
void printf_menu(char **men){
 for(;*men!=NULL;men++)
  printf("%s",*men);
}
int main(){
   struct User u;
   printf_menu(main_menu);
   int sw;
   scanf("%d",&sw);
   switch(sw){
   case 1:{
   int res=register_user(path,&u);
   if(res==-1)perror("register"),exit(-1);
   else if(res==-2){printf("这个名字用户已经注册，请重新输入\n");return -1;}
   else printf("注册成功\n");
   }
   case 2:{
   }
   case 3:{
   }
   case 4:{
   }
 }
/*
*/
}
