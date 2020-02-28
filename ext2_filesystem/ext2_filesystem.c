#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#pragma once
#include "ext2_filesystem.h"

int main(){
	printf("Welcome to localhost's simple ext2\n");
	printf("**********************************\n");
	printf("********Author: yangjie***********\n");
	printf("**********************************\n");
	printf("hello*********************world!\n\n");
	
	FILE* pf;
	pf = fopen("file.img", "rb+");
	if(!pf){		
		printf("The File system does not exist!, it will be creating now!\n");
		create_ext2_fileSystem();
	}
	
	pf = fopen("file.img", "rb+");
	last_inode_bit=1;  
	last_block_bit=0; 
	read_ext2_super_block();
	read_ext2_block_group_desc();

	//目录名 
	strcpy(current_path, "[root@localhost ");
	strcpy(path_name, "/");
	strcpy(path_last, "]# ");
	
	current_ext2_dir_entry_2_inode=1; 
	current_ext2_dir_entry_2_length=1;
	
	int flag = 1;
  printf("[root&localhost /]#");
	while(1){
		strcpy(current_path, "[root@localhost ");
		strcat(current_path, path_name);
		strcat(current_path, path_last);

		char command[10]="", temp[9]="";  //存储命令和变量 

		fflush(stdin); //清除stdin，就不会出现两个提示符了 
		printf("%s", current_path);
			//如果是回车，则重显 

		if(flag){
			command[0] = getchar();
			if(command[0] == '\n'){
				continue;
			}
		}
		scanf("%s", command+1);
		
		if(!strcmp(command, "ls")){
			ls();

		}else if(!strcmp(command, "mkdir")){
			scanf("%s", temp);
			mkdir(temp);
			
		}else if(!strcmp(command, "cd")){
			scanf("%s", temp);
			cd(temp);
			
		}else if(!strcmp(command, "format")){
			format();
			
		}else if(!strcmp(command, "rmdir")){
			scanf("%s", temp);
			rmdir(temp);
			
		}else if(!strcmp(command, "help")){
			help();
			
		}else if(!strcmp(command, "logout")){
			logout();
			
		}else if(!strcmp(command, "dumpe2fs")){
			dumpe2fs();
			
		}else if(!strcmp(command, "vi")){
			scanf("%s", temp);
			vi(temp);
			
		}else if(!strcmp(command, "cat")){
			scanf("%s", temp);
			cat(temp);
			
		}else if(!strcmp(command, "rm")){
			scanf("%s", temp);
			rm(temp);

		}else if(!strcmp(command, "rename")){
			char oldname[9];
			char newname[9];
			scanf("%s %s", oldname, newname);
			reName(oldname, newname);

		}else if(!strcmp(command, "data")){
			data();

		}else if(!strcmp(command, "chmod")){
			int mode; 
			scanf("%s", temp);
			scanf("%d", &mode);
			chmod(temp, mode);

		}else{
			printf("Can't find this command！\n");
		}
	}
	return 0;
}

// 创建文件系统
void create_ext2_fileSystem(void){
	// 创建文件系统的存储位置, 虚拟磁盘
	// inode默认从1开始, 而block块默认从0开始
	last_block_bit = 1;
	last_inode_bit = 0;
	int i = 0;
	printf("Please wait...\n");
	while(i < 20){
		printf(".");
		//sleep(3);
		i++;
	}
	
	i = 0;
	// 将file.img作为模拟磁盘
	pf = fopen("file.img", "wb+");
	if(!pf){
		printf("open file failed");
		exit(0);
	}
	
	// 将buffer清空, 有利于对磁盘进行格式化
	for(i = 0; i < BLOCK_SIZE; i++){
		ext2_block_buffer[i] = 0;
		printf("%d", i);
	}
	
	// 格式化磁盘
	fseek(pf, 0, SEEK_SET);	
	for(i=0; i < BLOCKS_COUNT; i++){		
		fwrite(ext2_block_buffer, BLOCK_SIZE, 1, pf);  //向磁盘写入0进行格式化 
	}
	fflush(pf);	 
	fseek(pf, INODE_TABLE_START, SEEK_SET);
	fread(ext2_inode_table_buffer, INODE_TABLE_SIZE, 1, pf); 
	for(i=0; i < INODE_TABLE_SIZE; i++){
		printf("%d", ext2_inode_table_buffer[i]);
	}
	
	//初始化super_block, 并写入磁盘中的block 
	read_ext2_super_block();
	strcpy(ext2_super_block_buffer->s_volume_name, VOLUME_NAME);
	ext2_super_block_buffer->s_inodes_count = INODES_COUNT;
	ext2_super_block_buffer->s_blocks_count = BLOCKS_COUNT;
  ext2_super_block_buffer->s_free_inodes_count = 16373-1; //inode号从1开始，所以空闲的少一个 
	ext2_super_block_buffer->s_free_blocks_count = 62172;
	ext2_super_block_buffer->s_block_size = BLOCK_SIZE;
	ext2_super_block_buffer->s_inode_size = INODE_SIZE;
	current_time();
	strcpy(ext2_super_block_buffer->s_wtime, time_now);
	write_ext2_super_block();
	
	//初始化ext2_block_group_desc, 并写入磁盘 
	read_ext2_block_group_desc();
	ext2_group_desc_buffer->bg_block_bitmap = BLOCK_BITMAP_START;
	ext2_group_desc_buffer->bg_inode_bitmap = INODE_BITMAP_START;
	ext2_group_desc_buffer->bg_inode_table = INODE_TABLE_START;
	ext2_group_desc_buffer->bg_free_inodes_count = 16469;
	ext2_group_desc_buffer->bg_free_blocks_count = 62179;
	ext2_group_desc_buffer->bg_used_dirs_count = 1;
	write_ext2_block_group_desc();
	
	//格式时已初始化block bitmap
	//读入到ext2_block_bitmap_buffer缓冲区 
	read_ext2_block_bitmap();
	//正常 
	for(i=0; i<1024; i++){
		printf("%d", ext2_block_bitmap_buffer[i]);
	}
	//格式时已初始化inode bitmap 
	//读入到inode_bitmap_buffer缓冲区 
	read_ext2_inode_bitmap();
	//正常 
	for(i=0; i<1024; i++){
		printf("%d", ext2_inode_bitmap_buffer[i]);
	}

	//设置根目录
	read_ext2_inode(current_ext2_dir_entry_2_inode);//将第一个inode读入ext2_inode_buffer
	
	ext2_inode_buffer->i_mode = 755; //rwx r-x r-x
	ext2_inode_buffer->i_size = 128; //一个block占1024bytes 
	ext2_inode_buffer->i_atime = 0;
	current_time();
	strcpy(ext2_inode_buffer->i_ctime, time_now);
	ext2_inode_buffer->i_mtime = 0;
	ext2_inode_buffer->i_dtime = 0;
	ext2_inode_buffer->i_blocks = 2;
	ext2_inode_buffer->i_block[0] = get_free_block(); 	//分配一个空闲的block bit 
	
	current_ext2_dir_entry_2_inode = get_free_inode(); 	//分配一个空闲的inode bit 
	current_ext2_dir_entry_2_length = 1; 				//根分区的长度“/” 


	printf("%u\n", current_ext2_dir_entry_2_inode);
	write_ext2_inode(current_ext2_dir_entry_2_inode);
	
	read_ext2_dir_entry_2(0); //写到缓冲区 
	//	初始化子目录“..”和“.” 
	ext2_dir_entry_2[0].inode = ext2_dir_entry_2[1].inode = current_ext2_dir_entry_2_inode;
	ext2_dir_entry_2[0].name_len = 1;
	ext2_dir_entry_2[1].name_len = 1;
	ext2_dir_entry_2[0].file_type = ext2_dir_entry_2[1].file_type = 2;
	strcpy(ext2_dir_entry_2[0].name, ".");
	strcpy(ext2_dir_entry_2[1].name, "..");
	for(i=2; i<64; i++){
		ext2_dir_entry_2[i].inode = 0;
	}
	write_ext2_dir_entry_2(ext2_inode_buffer->i_block[0]);
	printf("\nthe ext2 file system has been installed!\n\n\n");
	fclose(pf);
}

// 读取超级块
void read_ext2_super_block(void){
	fseek(pf, SUPER_BLOCK_START, SEEK_SET); 
	fread(ext2_super_block_buffer, SUPER_BLOCK_SIZE, 1, pf);
}

// 写入超级块
void write_ext2_super_block(void){
	fseek(pf, SUPER_BLOCK_START, SEEK_SET); 
	fwrite(ext2_super_block_buffer, SUPER_BLOCK_SIZE, 1, pf);
	fflush(pf);
}

// 读取块组描述符表
void read_ext2_block_group_desc(void){
	fseek(pf, BLOCK_GROUP_DES_START, SEEK_SET); 
	fread(ext2_group_desc_buffer, BLOCK_GROUP_DES_SIZE, 1, pf);
}

// 写入块组描述符表
void write_ext2_block_group_desc(void){
	fseek(pf, BLOCK_GROUP_DES_START, SEEK_SET); 
	fwrite(ext2_group_desc_buffer, BLOCK_GROUP_DES_SIZE, 1, pf);
	fflush(pf);
}

// 读取块位图
void read_ext2_block_bitmap(void){
	fseek(pf, BLOCK_BITMAP_START, SEEK_SET); 
	fread(ext2_block_bitmap_buffer, BLOCK_SIZE, 1, pf);
}

// 写入块位图
void write_ext2_block_bitmap(void){
	fseek(pf, BLOCK_BITMAP_START, SEEK_SET); 
	fwrite(ext2_block_bitmap_buffer, BLOCK_SIZE, 1, pf);
	fflush(pf);
}

// 读取inode位图
void read_ext2_inode_bitmap(void){
	fseek(pf, INODE_BITMAP_START, SEEK_SET); 
	fread(ext2_inode_bitmap_buffer, BLOCK_SIZE, 1, pf);
}

// 写入inode位图
void write_ext2_inode_bitmap(void){
	fseek(pf, INODE_BITMAP_START, SEEK_SET); 
	fwrite(ext2_inode_bitmap_buffer, BLOCK_SIZE, 1, pf);
	fflush(pf);
}

// 从ext2_inode_table中读写指定位置的inode
void read_ext2_inode(int inode_num){
	fseek(pf, INODE_TABLE_START+(inode_num-1)*INODE_SIZE, SEEK_SET);
	fread(ext2_inode_buffer, INODE_SIZE, 1, pf); 
}

void write_ext2_inode(int inode_num){
	fseek(pf, INODE_TABLE_START+(inode_num-1)*INODE_SIZE, SEEK_SET);
	fwrite(ext2_inode_buffer, INODE_SIZE, 1, pf); 
	fflush(pf);
}

//从block data中读写数据 
void read_ext2_block(int block_num){
	fseek(pf, DATA_BLOCK_START+block_num*BLOCK_SIZE, SEEK_SET);
	fread(ext2_block_buffer, BLOCK_SIZE, 1, pf);
}

void write_ext2_block(int block_num){
	fseek(pf, DATA_BLOCK_START+block_num*BLOCK_SIZE, SEEK_SET);
	fwrite(ext2_block_buffer, BLOCK_SIZE, 1, pf); 
	fflush(pf);
}

//从data block中读写dir信息 
void read_ext2_dir_entry_2(int block_num){
	fseek(pf, DATA_BLOCK_START+block_num*BLOCK_SIZE, SEEK_SET);
	fread(ext2_dir_entry_2, BLOCK_SIZE, 1, pf);
} 

void write_ext2_dir_entry_2(int block_num){
	fseek(pf, DATA_BLOCK_START+block_num*BLOCK_SIZE, SEEK_SET);
	fwrite(ext2_dir_entry_2, BLOCK_SIZE, 1, pf);
	fflush(pf);
} 

//返回当前时间 
void current_time(void){
	time_t t = time(0); //获取当前系统的时间 
	strftime(time_now, sizeof(time_now), "%Y-%m-%d %H:%M:%S", localtime(&t));
}

// 获取空闲的block号
unsigned int get_free_block(void){
	unsigned int temp_block_bit = last_block_bit;  //记录上一次分配的block号 
	unsigned int temp = temp_block_bit/8;  //8bit = 1char 
	char flag = 0;
	unsigned char con = 128;
	read_ext2_block_group_desc();
	
	//如果没有剩余block直接跳出 
	if(ext2_group_desc_buffer->bg_free_blocks_count==0){
		printf("there is no free block.\n");
		return -1; 
	}
	
	//将block bitmap读出到  ext2_block_bitmap_buffer[] 
	//查看是否哪个字节有bit位空缺，因为一个文件一共有8个索引块 
	read_ext2_block_bitmap();
	while(ext2_block_bitmap_buffer[temp] == 255){
		if(temp == 1023)
			temp=0;
		else
			temp++;
	}
	
	//用位与的方法，得到空闲的bit位 
	while(ext2_block_bitmap_buffer[temp]&con){
		flag++;
		con /= 2;
	}

	//得到bit位之后，直接修改整个char值 
	ext2_block_bitmap_buffer[temp] = ext2_block_bitmap_buffer[temp]+con; 
	last_block_bit = temp*8+flag;
	write_ext2_block_bitmap(); //更新到block bitmap 
	
	//更新到Super Block 
	read_ext2_super_block(); 
	ext2_super_block_buffer->s_free_blocks_count--;
	write_ext2_super_block();
	
	 //更新到GDT 
	ext2_group_desc_buffer->bg_free_blocks_count--;
	write_ext2_block_group_desc();  
	printf("%u", last_block_bit);  //检验输出 
	return last_block_bit;
}

//返回空闲的inode号 
unsigned int get_free_inode(void){
	unsigned int temp_inode_bit = last_inode_bit; //最开始等于1 
	unsigned int temp = (temp_inode_bit-1)/8;  //8bit = 1char 

	char flag = 0;
	unsigned char con = 128; //1000 0000b
	
	read_ext2_block_group_desc();
	if(ext2_group_desc_buffer->bg_free_inodes_count==0){
		printf("there is no free inode.\n");
		return -1; 
	}

	//将inode bitmap读出到  inode_bitmap_buffer[] 
	read_ext2_inode_bitmap();
	while(ext2_inode_bitmap_buffer[temp] == 255){
		if(temp == 1023)
			temp=0;
		else
			temp++;
	}
	
	printf("temp_inode_bit: %d\n", temp_inode_bit);
	printf("temp: %d\n", temp);
	printf("ext2_inode_bitmap_buffer[temp]: %d\n", ext2_inode_bitmap_buffer[temp]);
	printf("con: %d\n", con);

	while(ext2_inode_bitmap_buffer[temp]&con){
		flag++;
		con /= 2;
		printf("con: %d\n", con);
	}

	ext2_inode_bitmap_buffer[temp] = ext2_inode_bitmap_buffer[temp]+con; 
	printf("ext2_inode_bitmap_buffer[temp]: %d", ext2_inode_bitmap_buffer[temp]);
	last_inode_bit = temp*8+flag+1;
	write_ext2_inode_bitmap(); 							//更新到inode bitmap 
	
	//更新到Super Block 
	read_ext2_super_block(); 
	ext2_super_block_buffer->s_free_inodes_count--;
	write_ext2_super_block();

	ext2_group_desc_buffer->bg_free_inodes_count--;
	write_ext2_block_group_desc(); //更新到块组描述 
	
	printf("%d\n", flag);
	printf("%d\n", con);
	printf("%u\n", last_inode_bit); 
	return last_inode_bit;
} 

// 移除block
void remove_block(int remove_block_bit){
	unsigned temp = remove_block_bit/8;
	
	read_ext2_block_bitmap();
	//找到bit位所属的字节然后和特定的数字相与就可以将它置0 
	switch(remove_block_bit%8){
		case 0: ext2_block_bitmap_buffer[temp]&127;break; //0111 1111
		case 1: ext2_block_bitmap_buffer[temp]&191;break; //1011 1111
		case 2: ext2_block_bitmap_buffer[temp]&223;break; //1101 1111
		case 3: ext2_block_bitmap_buffer[temp]&239;break; //1110 1111
		case 4: ext2_block_bitmap_buffer[temp]&247;break; //1111 0111
		case 5: ext2_block_bitmap_buffer[temp]&251;break; //1111 1011
		case 6: ext2_block_bitmap_buffer[temp]&253;break; //1111 1101
		case 7: ext2_block_bitmap_buffer[temp]&254;break; //1111 1110
	}
	
	//更新Block Bitmap 
	write_ext2_block_bitmap();
	
	//更新GDT 
	read_ext2_block_group_desc();
	ext2_group_desc_buffer->bg_free_blocks_count++;
	write_ext2_block_group_desc();
	
	//更新Super Block 
	read_ext2_super_block(); 
	ext2_super_block_buffer->s_free_blocks_count--;
	write_ext2_super_block();
}

// 移除inode
void remove_inode(int remove_inode_bit){
	unsigned temp = (remove_inode_bit-1)/8;
	
	read_ext2_inode_bitmap();
	switch((remove_inode_bit-1)%8){
		case 0: ext2_inode_bitmap_buffer[temp]&127;break; //0111 1111
		case 1: ext2_inode_bitmap_buffer[temp]&191;break; //1011 1111
		case 2: ext2_inode_bitmap_buffer[temp]&223;break; //1101 1111
		case 3: ext2_inode_bitmap_buffer[temp]&239;break; //1110 1111
		case 4: ext2_inode_bitmap_buffer[temp]&247;break; //1111 0111
		case 5: ext2_inode_bitmap_buffer[temp]&251;break; //1111 1011
		case 6: ext2_inode_bitmap_buffer[temp]&253;break; //1111 1101
		case 7: ext2_inode_bitmap_buffer[temp]&254;break; //1111 1110
	}
	
	//更新Inode Bitmap 
	write_ext2_inode_bitmap();
	
	//更新GDT 
	read_ext2_block_group_desc();
	ext2_group_desc_buffer->bg_free_inodes_count++;
	write_ext2_block_group_desc();
	
	//更新Super Block 
	read_ext2_super_block(); 
	ext2_super_block_buffer->s_free_inodes_count++;
	write_ext2_super_block();
}

//显示当前目录下文件信息 
void ls(){
	printf("%-15s %-10s %-5s %-13s %-22s %-10s %-10s\n", 
      "name", "type", "user", "group", "create_time", "mode", "size");
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前目录的节点信息 
	printf("current_ext2_dir_entry_2_inode: %d\n", current_ext2_dir_entry_2_inode);
	printf("i_size: %u\n", ext2_inode_buffer->i_size);

	unsigned int i=0, k=0, temp=0, j=0, n=0;
	char mode[9]="";
	for(i=0; i< 8; i++){
		printf("%d\n", ext2_inode_buffer->i_block[i]);
	}
	i=0;
	while(i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			if(ext2_dir_entry_2[k].inode){ //判断是否存在 
				printf("%-15s", ext2_dir_entry_2[k].name); 
				if(ext2_dir_entry_2[k].file_type == 1){
					printf("%-12s", "<File>");
				}else if(ext2_dir_entry_2[k].file_type == 2){
					printf("%-12s", "<Dir>");
				}
				printf("%-5s %-10s", "root", "root");
				read_ext2_inode(ext2_dir_entry_2[k].inode);
				printf("%-25s", ext2_inode_buffer->i_ctime);
				temp = ext2_inode_buffer->i_mode;
				printf("%d", temp);
				j=0, n=100;
				//1 2 4 
				while(1){
					switch(temp/n){
						case 0:strcpy(mode+j, "---");break;
						case 1:strcpy(mode+j, "r--");break; 
						case 2:strcpy(mode+j, "-w-");break; 
						case 3:strcpy(mode+j, "rw-");break; 
						case 4:strcpy(mode+j, "--x");break; 
						case 5:strcpy(mode+j, "r-x");break; 
						case 6:strcpy(mode+j, "-wx");break; 
						case 7:strcpy(mode+j, "rwx");break; 
					}
					if(n==1){
						break;
					}
					temp %= n;
					n /= 10;
					j += 3;
				}
				printf("%-15s", mode);
				printf("%d\n", ext2_inode_buffer->i_size);
				
			} 
			k++; 
		}
		i++;
		read_ext2_inode(current_ext2_dir_entry_2_inode);
	}
} 


//新建目录的准备工作 
void ext2_dir_entry_2_prepare(unsigned int ext2_dir_entry_2_inode, int ext2_dir_entry_2_len){
	read_ext2_inode(ext2_dir_entry_2_inode);
	printf("ext2_dir_entry_2_inode: %d\n", ext2_dir_entry_2_inode);
	printf("current_ext2_dir_entry_2_inode: %d\n", current_ext2_dir_entry_2_inode);
	printf("ext2_dir_entry_2_len: %d\n", ext2_dir_entry_2_len);
	printf("current_ext2_dir_entry_2_length: %d\n", current_ext2_dir_entry_2_length);
	ext2_inode_buffer->i_mode=755;  
	ext2_inode_buffer->i_size=128; 
	ext2_inode_buffer->i_blocks=1; //占用的block的数量 
	ext2_inode_buffer->i_block[0] = get_free_block();
	current_time();
	strcpy(ext2_inode_buffer->i_ctime, time_now);
	//printf("ext2_inode_buffer->i_block[0]:%d\n", ext2_inode_buffer->i_block[0]);
	read_ext2_dir_entry_2(ext2_inode_buffer->i_block[0]);
	ext2_dir_entry_2[0].inode = ext2_dir_entry_2_inode;
	ext2_dir_entry_2[1].inode = current_ext2_dir_entry_2_inode; //当前目录的inode 
	ext2_dir_entry_2[0].name_len = ext2_dir_entry_2_len;
	ext2_dir_entry_2[1].name_len = current_ext2_dir_entry_2_length;
	ext2_dir_entry_2[0].file_type = ext2_dir_entry_2[1].file_type = 2;
	//这是很关键的一步，不然一直会显示上次遗留的信息 
	int i=0;
	for(i=2; i<64; i++){
		ext2_dir_entry_2[i].inode=0;
	}
	strcpy(ext2_dir_entry_2[0].name, ".");
	strcpy(ext2_dir_entry_2[1].name, "..");
	write_ext2_dir_entry_2(ext2_inode_buffer->i_block[0]);
	write_ext2_inode(ext2_dir_entry_2_inode);
	//更新GDT
	read_ext2_block_group_desc();
	ext2_group_desc_buffer->bg_used_dirs_count++;
	write_ext2_block_group_desc();
}

//创建新目录 
void mkdir(char temp[9]){
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int i=0, k=0, ext2_dir_entry_2_inode=0, flag=1;
	printf("current_ext2_dir_entry_2_inode: %d\n", current_ext2_dir_entry_2_inode);

	for(i=0; i<9; i++){
		printf("%c", temp[i]); 
	} 
	
	//判断是否有同名，若有则退出 
	while(i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			//如果节点存在并且名字相同 
			//这里是不等于，需要注意一下 
			if(ext2_dir_entry_2[k].inode && !strcmp(ext2_dir_entry_2[k].name, temp)){
				printf("filename has already existed! \n");
				return;
			}
			k++; 
		}
		i++;
	} 
	//k可以用来表示下一个可用的目录点inode， i表示下一个可用的block[i] 
	printf("k: %d\n", k); 
	printf("i: %d\n", i); 
	
	if(ext2_inode_buffer->i_size == 1024*8){
		printf("Directory has no room to be alloced!\n");
		return; 
	} 
	
	flag=1;
	read_ext2_inode(current_ext2_dir_entry_2_inode);
	//判断一个目录项中是否还有空闲 
	if(ext2_inode_buffer->i_size != (ext2_inode_buffer->i_blocks)*1024){
		i=0;
		printf("i: %d\n", i);
		//把空闲block找到 
		while(flag && i < ext2_inode_buffer->i_blocks){
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
			printf("ext2_inode_buffer->i_block[i]: %d\n", ext2_inode_buffer->i_block[i]);
			for(k=0; k<64; k++){
				printf("%d", ext2_dir_entry_2[k].inode);
			}
			k=0;
			while(k < 64){
				if(ext2_dir_entry_2[k].inode == 0){
					flag=0; //如果有空间直接跳出两重循环 
					break;
				}
				printf("\nk: %d\n", k);
				k++; 
			}
			i++;
		} 
		
		printf("k: %d\n", k);
		ext2_dir_entry_2_inode = get_free_inode();
		ext2_dir_entry_2[k].inode = ext2_dir_entry_2_inode;
		ext2_dir_entry_2[k].name_len = strlen(temp);
		ext2_dir_entry_2[k].file_type=2;
		strcpy(ext2_dir_entry_2[k].name, temp);

		printf("inode: %d\n", ext2_dir_entry_2_inode);
		write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i-1]);
		
	}else{
		ext2_inode_buffer->i_block[ext2_inode_buffer->i_blocks] = get_free_block();
		ext2_inode_buffer->i_blocks++;
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[ext2_inode_buffer->i_blocks-1]);
		ext2_dir_entry_2_inode = get_free_inode();
		ext2_dir_entry_2[0].inode = ext2_dir_entry_2_inode;
		ext2_dir_entry_2[0].name_len = strlen(temp);
		ext2_dir_entry_2[0].file_type=2;
		strcpy(ext2_dir_entry_2[0].name, temp);
		for(k=1; k<64; k++){
			ext2_dir_entry_2[k].inode=0;
		}
		
		printf("%d", ext2_dir_entry_2_inode);
		write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i-1]);	
	}
	

	ext2_inode_buffer->i_size += 16;
	write_ext2_inode(current_ext2_dir_entry_2_inode);
	//为每个新加目录添加额外信息 
	printf("ext2_dir_entry_2_inode: %d\n", ext2_dir_entry_2_inode);
	ext2_dir_entry_2_prepare(ext2_dir_entry_2_inode, strlen(temp));
}

//切换目录
void cd(char temp[9]){
	int i=0, k=0;
	printf("%u", current_ext2_dir_entry_2_inode); 
	fseek(pf, INODE_TABLE_START, SEEK_SET);
	fread(ext2_inode_table_buffer, INODE_TABLE_SIZE, 1, pf); 
	for(i=0; i < INODE_TABLE_SIZE; i++){
		printf("%d", ext2_inode_table_buffer[i]);
	} 
	temp[strlen(temp)] = '\0';
	printf("%d", strlen(temp));
	int strcmp(const char *s1, const char *s2);
	int strncmp(const char *s1, const char *s2, size_t n);

	if(!strcmp(temp, ".")){
		//printf("test");//啥都不做 
		return;
	}else if(!strcmp(temp, "..")){
		read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前目录的节点信息 
		
		while(i < ext2_inode_buffer->i_blocks){
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]); //读取每一个block指针所对应的dir 
			k=0;
			while(k < 64){
				if(!strcmp(ext2_dir_entry_2[k].name, "..")){
					current_ext2_dir_entry_2_inode = ext2_dir_entry_2[k].inode;
					path_name[strlen(path_name)-ext2_dir_entry_2[k-1].name_len-1] = '\0';
					current_ext2_dir_entry_2_length = ext2_dir_entry_2[k].name_len;
					printf("%d", current_ext2_dir_entry_2_inode);
					//  / localhost/123/123/ 
					return;
				}
				k++;				
			}
			i++;
		}
	}

	
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前目录的节点信息 
	while(i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]); //读取每一个block指针所对应的dir 
		k=0;
		while(k < 64){
			if(!strcmp(ext2_dir_entry_2[k].name, temp) && ext2_dir_entry_2[k].inode && ext2_dir_entry_2[k].file_type==2){
				current_ext2_dir_entry_2_inode = ext2_dir_entry_2[k].inode;
				current_ext2_dir_entry_2_length = ext2_dir_entry_2[k].name_len;
				printf("%d", current_ext2_dir_entry_2_inode); 
				
				strcat(path_name, temp);
				strcat(path_name, "/");
				return;
			}
			k++;	
		}
		i++;
	}
	printf("Can't find this Directory! \n");
}

//格式化磁盘 
void format(){
	char answer = 'Y';
	while(1){
		scanf("%c", &answer);
		if(toupper(answer) == 'Y'){
			printf("Ready to format......\n"); 
			create_ext2_fileSystem();
			pf = fopen("file.img", "rb+");
			last_inode_bit=1;  
			last_block_bit=0; 
			read_ext2_super_block();
			read_ext2_block_group_desc();
		
			//目录名 
			strcpy(current_path, "[root@localhost ");
			strcpy(path_name, "/");
			strcpy(path_last, "]# ");
			
			current_ext2_dir_entry_2_inode=1; 
			current_ext2_dir_entry_2_length=1;
			return;
		}else if(toupper(answer) == 'N'){
			return;
		}else{
			fflush(stdin);
		}
		printf("Are you sure you want to format the disk ?[y / n]: ");
	}
}

//删除空目录 
void rmdir(char temp[9]){
	int i=0, k=0, flag=0;
	
	if(!strcmp(temp, "..") || !strcmp(temp, ".")) {
		printf("This directory is not allowed to be deleted!\n");
		return;
	}
	
	read_ext2_inode(current_ext2_dir_entry_2_inode);

	while(!flag && i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			if(ext2_dir_entry_2[k].inode && !strcmp(ext2_dir_entry_2[k].name, temp) &&
				ext2_dir_entry_2[k].file_type==2){
				flag = 1; //找到此目录了 
				break;
			}
			k++; 
		}
		i++;
	} 
	
	if(!flag){
		printf("Please enter the correct directory name!\n");
		return;
	}else{
		//加载需要删除的节点信息 
		read_ext2_inode(ext2_dir_entry_2[k].inode);
		//判断是否为空目录 
		//只有 .. 和 . 目录 
//			unsigned int i_mode;  //文件类型和权限 
//			unsigned int i_size;  //文件或者目录大小 
//			unsigned int i_blocks; //占用的block的数量 
//			unsigned short i_block[8];  //内容指向, 存放block号 
		if(ext2_inode_buffer->i_size == 128){
			ext2_inode_buffer->i_mode = 0;
			ext2_inode_buffer->i_size = 0;
			ext2_inode_buffer->i_blocks = 0;
			ext2_inode_buffer->i_size = 0;
			//将子目录下的两个文件删除 
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[0]);
			ext2_dir_entry_2[0].inode=0;
			ext2_dir_entry_2[1].inode=0;
			write_ext2_dir_entry_2(ext2_inode_buffer->i_block[0]);
			//删除block号 
			remove_block(ext2_inode_buffer->i_block[0]);
			//删除本目录下的这个目录 
			read_ext2_inode(current_ext2_dir_entry_2_inode); 
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i-1]);
			ext2_dir_entry_2[k].inode=0;
			write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i-1]);
			ext2_inode_buffer->i_size -= 16;
			
			//把哪些整个block都是空的这种块去掉
			 i=1;
			 flag=0;
			 while(flag<64 && i<ext2_inode_buffer->i_blocks){
			 	k=0;
			 	read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
			 	while(k<64){
			 		if(!ext2_dir_entry_2[k].inode){
			 			flag++;
			 		}
			 		k++;
			 	}
			 	if(flag==64){
			 		remove_block(ext2_inode_buffer->i_block[i]);
			 		ext2_inode_buffer->i_blocks--;
			 		while(i<ext2_inode_buffer->i_blocks){
			 			ext2_inode_buffer->i_block[i] = ext2_inode_buffer->i_block[i+1];
						i++;
			 		}
			 	}
			 	
			 }
			 write_ext2_inode(current_ext2_dir_entry_2_inode);	
		}else{
			printf("Can't delete, directory is not null! ");
			return;
		}
	}

}


//退出登录 
void logout(void){
	char answer = 'Y';
	while(1){
		scanf("%c", &answer);
		if(toupper(answer) == 'Y'){
			printf("\nbye bye ~~\n");
			exit(0);
		}else if(toupper(answer) == 'N'){
			return;
		}else{
			fflush(stdin);
		}
		printf("Are you sure you want to quit ?[y / n]: ");
	}
}

//显示帮助命令 
void help(){
    printf("      *****************************************************************************************\n");
    printf("      *                                    command help                                       *\n");
    printf("      *                                                                                       *\n");
    printf("      * 01.command help  : help                  09.format disk       : format                *\n");
    printf("      * 02.create dir    : mkdir + dir_name      10.delete empty dir  : rmdir + dir_name      *\n");
    printf("      * 03.list dir      : ls                    11.chang dir         : cd + dir_name         *\n");
    printf("      * 04.edit file     : vi + file_name        12.read file         : cat + file_name       *\n");
    printf("      * 05.remove file   : rm + file_name        13.ping IP/Address   : ping + ip/host        *\n");
    printf("      * 06.list local IP : ifconfig              14.traceroute        : traceroute + ip/host  *\n");   
    printf("      * 07.show data now : data                  15.modify mode       : chmod + mode          *\n");
    printf("      * 08.logout        : logout                16.display disk info : dumpe2fs              *\n");
    printf("      *                                                                                       *\n");
    printf("      *****************************************************************************************\n\n");
} 

//显示磁盘信息 
void dumpe2fs(){
	read_ext2_super_block();
	printf("volume name            : %s\n", ext2_super_block_buffer->s_volume_name);
	printf("inodes counts          : %d\n", ext2_super_block_buffer->s_inodes_count);
	printf("blocks counts          : %d\n", ext2_super_block_buffer->s_blocks_count);
	printf("free inodes counts     : %d\n", ext2_super_block_buffer->s_free_inodes_count);
	printf("free blocks counts     : %d\n", ext2_super_block_buffer->s_free_blocks_count);
	printf("inode size             : %d(kb)\n", ext2_super_block_buffer->s_inode_size);
	printf("block size             : %d(kb)\n", BLOCK_SIZE);
	printf("create time            : %s\n\n", ext2_super_block_buffer->s_wtime);

}

void vi(char temp[9]){ 
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int i=0, k=0, flag=1, m=0, file_inode=0;
	int local=0, file_length=0, file_block_count=0;
	
	//寻找文件是否存在，如果是目录，则不能进行编辑
	//如果是文件，则存在进行编辑，不存在进行创建 
	while(flag && i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			if(ext2_dir_entry_2[k].inode && !strcmp(ext2_dir_entry_2[k].name, temp)){
				if(ext2_dir_entry_2[k].file_type == 2){
					printf("Directory can't be edit! \n");
					return;
				}else{
					flag = 0; //存在文件 
					break;
				}
			}
			k++; 
		}
		i++;
	} 
	
	//如果文件不存在, 将创建新文件 
	if(flag){
		printf("Can't find the file name, will create a new file!\n");
		printf("Please input '\\q' to quit! \n\n");
		read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
		i=0, k=0, file_inode=0, flag=1;
		
		//是否还有block 
		if(ext2_inode_buffer->i_size == 1024*8){
			printf("Directory has no room to be alloced!\n");
			return; 
		} 

		m=1; //用来终止循环 
		//判断一个目录项中是否还有空闲 
		if(ext2_inode_buffer->i_size != (ext2_inode_buffer->i_blocks)*1024){
			i=0;
			while(m && i < ext2_inode_buffer->i_blocks){
				read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
				k=0;
				while(k < 64){
					if(ext2_dir_entry_2[k].inode == 0){
						m=0; //如果有空间直接跳出两重循环 
						break;
					}
					printf("\nk: %d\n", k);
					k++; 
				}
				i++;
			} 
			
			printf("k: %d\n", k);
			file_inode = get_free_inode();
			ext2_dir_entry_2[k].inode = file_inode;
			ext2_dir_entry_2[k].name_len = strlen(temp);
			ext2_dir_entry_2[k].file_type=1;
			strcpy(ext2_dir_entry_2[k].name, temp);
	
			printf("inode: %d\n", file_inode);
			write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i-1]);
			
		}else{
			ext2_inode_buffer->i_block[ext2_inode_buffer->i_blocks] = get_free_block();
			ext2_inode_buffer->i_blocks++;
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[ext2_inode_buffer->i_blocks-1]);
			file_inode = get_free_inode();
			ext2_dir_entry_2[0].inode = file_inode;
			ext2_dir_entry_2[0].name_len = strlen(temp);
			ext2_dir_entry_2[0].file_type=1;
			strcpy(ext2_dir_entry_2[0].name, temp);
			for(k=1; k<64; k++){
				ext2_dir_entry_2[k].inode=0;
			}
		
			printf("%d", file_inode);
			write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i-1]);	
		}
		
		ext2_inode_buffer->i_size += 16;
		write_ext2_inode(current_ext2_dir_entry_2_inode);//写入当前目录 
		
		//写入文件初始化信息 
		read_ext2_inode(file_inode);
		ext2_inode_buffer->i_mode = 777;
		ext2_inode_buffer->i_size = 0;
		ext2_inode_buffer->i_blocks = 0;
		current_time();
		strcpy(ext2_inode_buffer->i_ctime, time_now);

		
		//开始写入文件缓存ext2_filebuffer；
		while(1){
			ext2_filebuffer[local] = getchar();
			if(ext2_filebuffer[local] == 'q' && ext2_filebuffer[local-1]=='\\'){
				ext2_filebuffer[local-1] = '\0';
				break;
			}

			if(local>=8191){
				printf("Sorry,the max size of a file is 4KB!\n"); 
				break;
			}
			
			local++;
		}
		
		for(i=0; i<local-1; i++){
			printf("%c", ext2_filebuffer[i]);
		}
		printf("\n");

		file_length = strlen(ext2_filebuffer); //文件内容的长度
		file_block_count = file_length/1024;
		if(file_length%1024){
			file_block_count++;
		} 
		printf("file_block_count: %d\n", file_block_count);
		//直接覆盖写入
		for(i=0; i<file_block_count; i++){
			ext2_inode_buffer->i_blocks++;
			ext2_inode_buffer->i_block[i] = get_free_block();
			read_ext2_block(ext2_inode_buffer->i_block[i]); //将数据读入缓冲区
			if(i==file_block_count-1)
				memcpy(ext2_block_buffer, ext2_filebuffer+i*BLOCK_SIZE, file_length-i*BLOCK_SIZE);
			else
				memcpy(ext2_block_buffer, ext2_filebuffer+i*BLOCK_SIZE, BLOCK_SIZE);
			write_ext2_block(ext2_inode_buffer->i_block[i]);
		}
		
		ext2_inode_buffer->i_size=file_length;
		printf("file_inode: %d", file_inode);
		printf("ext2_inode_buffer->i_blocks: %d\n", ext2_inode_buffer->i_blocks);
		write_ext2_inode(file_inode);
		printf("\nSave as ");
		for(i=0; i<strlen(temp); i++){
			printf("%c", temp[i]);
		} 
		printf("!\n");
	//文件存在时 
	}else{
		fflush(stdin);
		printf("The file is exist!!\n");
		printf("Please input '\\q' to quit! \n\n");
		read_ext2_inode(ext2_dir_entry_2[k].inode); //读取当前节点信息,存入ext2_inode_buffer
		printf("dir[k].inode: %d\n", ext2_dir_entry_2[k].inode);
		printf("ext2_inode_buffer->i_blocks: %d\n", ext2_inode_buffer->i_blocks);

		for(i=0; i<ext2_inode_buffer->i_blocks; i++){
			read_ext2_block(ext2_inode_buffer->i_block[i]); //存入ext2_block_buffer
			if(i == ext2_inode_buffer->i_blocks-1){
				memcpy(ext2_filebuffer+i*BLOCK_SIZE, ext2_block_buffer, ext2_inode_buffer->i_size-i*BLOCK_SIZE);	
			}else{
				memcpy(ext2_filebuffer+i*BLOCK_SIZE, ext2_block_buffer, i*BLOCK_SIZE);	
			}
			remove_block(ext2_inode_buffer->i_block[i]);	
		} 
		
		for(i=0; i<ext2_inode_buffer->i_size; i++){
			printf("%c", ext2_filebuffer[i]);
		}
		
		ext2_inode_buffer->i_blocks=0;
		local = ext2_inode_buffer->i_size;
		while(1){
			if(local>=8191){
				printf("Sorry,the max size of a file is 4KB!\n"); 
				break;
			}
			
			ext2_filebuffer[local] = getchar();
			if(ext2_filebuffer[local] == 'q' && ext2_filebuffer[local-1]=='\\'){
				ext2_filebuffer[local-1] = '\0';
				break;
			}
			
			local++;
		}
		

		file_length = strlen(ext2_filebuffer); //文件内容的长度
		file_block_count = file_length/1024;
		if(file_length%1024){
			file_block_count++;
		}

		for(i=0; i<file_block_count; i++){
			ext2_inode_buffer->i_blocks++;
			ext2_inode_buffer->i_block[i] = get_free_block();
			read_ext2_block(ext2_inode_buffer->i_block[i]); //将数据读入缓冲区
			if(i==file_block_count-1)
				memcpy(ext2_block_buffer, ext2_filebuffer+i*BLOCK_SIZE, file_length-i*BLOCK_SIZE);
			else
				memcpy(ext2_block_buffer, ext2_filebuffer+i*BLOCK_SIZE, BLOCK_SIZE);
			write_ext2_block(ext2_inode_buffer->i_block[i]);
		}
		
		ext2_inode_buffer->i_size=file_length;
		//更新时间 
		current_time();
		strcpy(ext2_inode_buffer->i_ctime, time_now);
		printf("file_inode: %d", file_inode);
		printf("ext2_inode_buffer->i_blocks: %d\n", ext2_inode_buffer->i_blocks);
		write_ext2_inode(ext2_dir_entry_2[k].inode);
		
		printf("\nSave!\n");
	} 

} 

void cat(char temp[9]){
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int i=0, k=0, flag=1;
	
	//寻找文件是否存在，如果是目录，则不能进行查看 
	while(flag && i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			if(ext2_dir_entry_2[k].inode && !strcmp(ext2_dir_entry_2[k].name, temp)){
				if(ext2_dir_entry_2[k].file_type == 2){
					printf("That is a directory! \n");
					return;
				}else{
					flag = 0; //存在文件 
					break;
				}
			}
			k++; 
		}
		i++;
	} 
	if(!flag){
		read_ext2_inode(ext2_dir_entry_2[k].inode); //读取当前节点信息,存入ext2_inode_buffer
		for(i=0; i<ext2_inode_buffer->i_blocks; i++){
			read_ext2_block(ext2_inode_buffer->i_block[i]); //存入ext2_block_buffer
			if(i == ext2_inode_buffer->i_blocks-1){
				memcpy(ext2_filebuffer+i*BLOCK_SIZE, ext2_block_buffer, ext2_inode_buffer->i_size-i*BLOCK_SIZE);	
			}else{
				memcpy(ext2_filebuffer+i*BLOCK_SIZE, ext2_block_buffer, i*BLOCK_SIZE);	
			}
			remove_block(ext2_inode_buffer->i_block[i]);	
		} 
		
		for(i=0; i<ext2_inode_buffer->i_size; i++){
			printf("%c", ext2_filebuffer[i]);
		}
		printf("\n");
	}else{
		printf("Can't find the filename!\n");
		return;
	}

} 

void rm(char temp[9]){
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int i=0, k=0, flag=1;
	int m=0, n=0;
	
	//判断文件是否存在，若文件存在才可删除 
	while(flag && i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			if(ext2_dir_entry_2[k].inode && !strcmp(ext2_dir_entry_2[k].name, temp)){
				if(ext2_dir_entry_2[k].file_type == 2){
					printf("'rm' only delete file! \n");
					return;
				}else{
					flag = 0; //存在文件 
					break;
				}
			}
			k++; 
		}
		i++;
	} 
	
	//flag = 1 文件不存在 
	if(flag){
		printf("Can't find this filename!\n"); 
		return;
	}else{
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		read_ext2_inode(ext2_dir_entry_2[k].inode); //加载inode
		//把当前文件的inode信息删除 
		for(i=0; i<ext2_inode_buffer->i_blocks; i++){
			remove_block(ext2_inode_buffer->i_block[i]);
		}
		ext2_inode_buffer->i_mode = 0;
		ext2_inode_buffer->i_size = 0;
		ext2_inode_buffer->i_blocks=0;
		
		//删除本目录下此文件的信息
		read_ext2_inode(current_ext2_dir_entry_2_inode);
		ext2_inode_buffer->i_size -= 16;
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		ext2_dir_entry_2[k].inode = 0;
		write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		
		m=1;
		while(m < ext2_inode_buffer->i_blocks){
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[m]);
			flag=n=0;
			while(n<64){
				if(!ext2_dir_entry_2[n].inode){
					flag++;
				}
				n++;
			}
			
			if(flag == 64){
				remove_block(ext2_inode_buffer->i_block[m]);
				ext2_inode_buffer->i_blocks--;
				while(m < ext2_inode_buffer->i_blocks){
					ext2_inode_buffer->i_block[m] = ext2_inode_buffer->i_block[m+1];
					m++;
				}
			}
			m++;
			
		}
		write_ext2_inode(current_ext2_dir_entry_2_inode);
		printf("The file has been deleted!\n");
		
	}
} 

/*
void ifconfig(){
     char host_name[256]; 
     int WSA_return, i;
     WSADATA WSAData;
     HOSTENT *host_entry; 
     WORD wVersionRequested;

     wVersionRequested = MAKEWORD(2, 0);
     WSA_return = WSAStartup(wVersionRequested, &WSAData); 

     if (WSA_return == 0){
         gethostname(host_name, sizeof(host_name));
         host_entry = gethostbyname(host_name);
		 printf("\t%-15s\t  %s\n", "IP", "hostname");
         for(i = 0; host_entry != NULL && host_entry->h_addr_list[i] != NULL; ++i){
             const char *pszAddr = inet_ntoa (*(struct in_addr *)host_entry->h_addr_list[i]);
             printf("   %-24s%s\n", pszAddr, host_name);
         }
     }
     else{
         printf("Please check network!\n");
     }
     WSACleanup();
}

void ping(char ip[INODE_SIZE]){
	char address[150];
	strcpy(address, "ping -n 4 ");
	strcat(address, ip);
	char buffer[INODE_SIZE];
	
//	for(int i=0; i<INODE_SIZE; i++){
//		printf("%c", ip[i]);
//	}
	FILE *pipe = _popen(address, "r");
	if(!pipe){
		printf("cmd failed\n");
	}
	
	while(!feof(pipe)){
		fgets(buffer, INODE_SIZE, pipe);
		printf("%s", buffer);
	} 
	_pclose(pipe);
	printf("\n");
} 
*/

//对文件重命名 
void reName(char oldname[INODE_SIZE], char newname[INODE_SIZE]){ 
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int i=0, k=0, flag=1;
	int m=0, n=0;
	//判断文件是否存在，若文件存在才可修改 
	while(flag && i < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		k=0;
		while(k < 64){
			if(ext2_dir_entry_2[k].inode && !strcmp(ext2_dir_entry_2[k].name, oldname)){
				if(ext2_dir_entry_2[k].file_type == 2){
					printf("The directory name can't be modified!\n");
					return;
				}else{
					flag = 0; //存在
					break;
				}
			}
			k++; 
		}
		i++;
	}
	
	//文件不存在flag=1 
	if(flag){
		printf("Can't find the filename!\n");
		return; 
	}else{
		flag=1;
		//判断newname是否重名 
		while(flag && m < ext2_inode_buffer->i_blocks){
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[m]);
			n=0;
			while(n < 64){
				if(ext2_dir_entry_2[n].inode && !strcmp(ext2_dir_entry_2[n].name, newname)){
						flag = 0; //存在
						break;
				}
				n++; 
			}
			m++;
		}
		if(!flag){
			printf("The filename \"%s\" is existed\n", newname);
			return;
		}else{
			read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
			read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
			strcpy(ext2_dir_entry_2[k].name, newname);
			ext2_dir_entry_2[k].name_len=strlen(newname);
			write_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		}
	}
} 
//显示时间 
void data(){
	char data_time[INODE_SIZE];
	time_t t = time(0); //获取当前系统的时间 
	strftime(data_time, sizeof(data_time), "%Y-%m-%d %H:%M:%S %A", localtime(&t));
	printf("%s\n", data_time);
}

//修改权限 
void chmod(char temp[9], int mode){
	if(mode>777 || mode < 0){
		printf("mode <000-777>!\n");
		return;
	}
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int i=0, k=0, flag=1;

	//判断文件是否存在，若文件存在才可修改 
	flag = search_file(temp, &i, &k);
	
	//flag = 1 文件不存在 
	if(flag){
		printf("Can't find this filename!\n"); 
		return;
	}else{
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i]);
		read_ext2_inode(ext2_dir_entry_2[k].inode);
		ext2_inode_buffer->i_mode = mode;
		current_time();
		strcpy(ext2_inode_buffer->i_ctime, time_now);
		write_ext2_inode(ext2_dir_entry_2[k].inode);
		printf("The file's mode has been modify!\n");
		
	}
}

// 文件查找
int search_file(char temp[9], int *i, int *k){
	read_ext2_inode(current_ext2_dir_entry_2_inode); //读取当前节点信息
	int flag=1, i_temp=0, k_temp=0; //设置临时变量 
	
	while(flag && i_temp < ext2_inode_buffer->i_blocks){
		read_ext2_dir_entry_2(ext2_inode_buffer->i_block[i_temp]);
		k_temp=0;
		while(k_temp < 64){
			if(ext2_dir_entry_2[k_temp].inode && !strcmp(ext2_dir_entry_2[k_temp].name, temp)){
					flag = 0; //存在
					*i=i_temp;
					*k=k_temp;
					return 0;
			}
			k_temp++; 
		}
		i_temp++;
	}
	return 1;
} 
