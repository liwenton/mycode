#ifndef __file_trans_H__
	#define __file_trans_H__
	#include <stdio.h>
	#include <pthread.h>
	#include <errno.h>
	#include "socket.h"
	#include "client.h"
	#include "Queue.h"
	
	#define DOWNLOAD_PATH "./DP2PCSDownload/"
	#define SIZE_INFO_HEAD "size is "
	#define SIZE_INFO_TAIL " bytes"
	
	struct file_trans{
		int file_trans_fd;//set by file trans control
		int connect_launcher;//set when init ---- TRUE is launcher;FALSE is the accpeter
		char *file_name;//set when init
		char *file_location;//Launcher -- set when init; Recevier -- set by itself
		FILE *file_ptr;//get by itself# Recevier write binary; Launcher read binary
		long total_size;//Recevier --set when init; Launcher -- get by itself
		long fin_size;//set when trans happen
	};
	
	extern int client_shutdown;
	
	Queue *file_trans_control;
	
	Queue *init_file_trans_control();
	int file_trans_control_length(Queue *file_trans_control);
	void destroy_file_trans_control(Queue *file_trans_control);
	

	int init_file_trans(Queue *file_trans_control, int connect_launcher, char *file_name, char *file_location, long total_size);
	struct file_trans *find_file_trans_task(Queue *file_trans_control, int file_trans_fd);
	void destroy_file_trans(Queue *file_trans_control, int file_trans_fd);
	
	int read_file_trans_block(Queue *file_trans_control, int file_trans_fd, unsigned char *file_block);
	void append_file_trans_block(Queue *file_trans_control, int file_trans_fd, unsigned char *block, int write_size);
	int send_file_trans_block(Queue *file_trans_control, int file_trans_fd, socket_fd connect_socket_fd, unsigned char *file_block);
	int recv_file_trans_block(Queue *file_trans_control, int file_trans_fd, socket_fd connect_socket_fd, unsigned char *file_block);
	
#endif /* __file_trans_H__ */ 
