// #ifndef CSC369A3_EXT2_FS_H
// #define CSC369A3_EXT2_FS_H

#define BLOCK_SIZE 1024	
#define INODES_COUNT 16384	
#define BLOCKS_COUNT 65536

#define SUPER_BLOCK_SIZE 1024
#define BLOCK_GROUP_DES_SIZE 32
#define INODE_SIZE 128 
#define INODE_TABLE_SIZE 262124

#define SUPER_BLOCK_START 1024 					//  0x00000400-0x00000800
#define BLOCK_GROUP_DES_START 2048 				//	0x00000800-0x00000900
#define BLOCK_BITMAP_START 264192 				//  0x00040800-0x00040b00
#define INODE_BITMAP_START 265216 				//  0x00040c00-0x00041000
#define INODE_TABLE_START 266240 				//	0x00041000
#define DATA_BLOCK_START 528384 				//  0x00081000

#define VOLUME_NAME "EXT2"

//#pragma comment(lib, "WS2_32.lib")

 

// ext2_super_block结构体
struct ext2_super_block {
    unsigned int   s_inodes_count;      /* Inodes count */
    unsigned int   s_blocks_count;      /* Blocks count */
    unsigned int   s_r_blocks_count;    /* Reserved blocks count */
    unsigned int   s_free_blocks_count; /* Free blocks count */
    unsigned int   s_free_inodes_count; /* Free inodes count */
    unsigned int   s_first_data_block;  /* First Data Block */
    unsigned int   s_log_block_size;    /* Block size */
    unsigned int   s_log_frag_size;     /* Fragment size */
    unsigned int   s_blocks_per_group;  /* # Blocks per group */
    unsigned int   s_frags_per_group;   /* # Fragments per group */
    unsigned int   s_inodes_per_group;  /* # Inodes per group */
    unsigned int   s_mtime;             /* Mount time */
    unsigned int   s_wtime;             /* Write time */
    unsigned short s_mnt_count;         /* Mount count */
    unsigned short s_max_mnt_count;     /* Maximal mount count */
    unsigned short s_magic;             /* Magic signature */
    unsigned short s_state;             /* File system state */
    unsigned short s_errors;            /* Behaviour when detecting errors */
    unsigned short s_minor_rev_level;   /* minor revision level */
    unsigned int   s_lastcheck;         /* time of last check */
    unsigned int   s_checkinterval;     /* max. time between checks */
    unsigned int   s_creator_os;        /* OS */
    unsigned int   s_rev_level;         /* Revision level */
    unsigned short s_def_resuid;        /* Default uid for reserved blocks */
    unsigned short s_def_resgid;        /* Default gid for reserved blocks */
    /*
     * These fields are for EXT2_DYNAMIC_REV superblocks only.
     *
     * Note: the difference between the compatible feature set and
     * the incompatible feature set is that if there is a bit set
     * in the incompatible feature set that the kernel doesn't
     * know about, it should refuse to mount the ext2_fileSystem.
     *
     * e2fsck's requirements are more strict; if it doesn't know
     * about a feature in either the compatible or incompatible
     * feature set, it must abort and not try to meddle with
     * things it doesn't understand...
     */
    unsigned int   s_first_ino;         /* First non-reserved inode */
    unsigned short s_inode_size;        /* size of inode structure */
    unsigned short s_block_size;        /* size of block structure */
    unsigned short s_block_group_nr;    /* block group # of this superblock */
    unsigned int   s_feature_compat;    /* compatible feature set */
    unsigned int   s_feature_incompat;  /* incompatible feature set */
    unsigned int   s_feature_ro_compat; /* readonly-compatible feature set */
    unsigned char  s_uuid[16];          /* 128-bit uuid for volume */
    char           s_volume_name[16];   /* volume name */
    char           s_last_mounted[64];  /* ext2_dir_entry_2ectory where last mounted */
    unsigned int   s_algorithm_usage_bitmap; /* For compression */
    /*
     * Performance hints.  ext2_dir_entry_2ectory preallocation should only
     * happen if the EXT2_COMPAT_PREALLOC flag is on.
     */
    unsigned char  s_prealloc_blocks;     /* Nr of blocks to try to preallocate*/
    unsigned char  s_prealloc_dir_blocks; /* Nr to preallocate for ext2_dir_entry_2s */
    unsigned short s_padding1;
    /*
     * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
     */
    unsigned char  s_journal_uuid[16]; /* uuid of journal superblock */
    unsigned int   s_journal_inum;     /* inode number of journal file */
    unsigned int   s_journal_dev;      /* device number of journal file */
    unsigned int   s_last_orphan;      /* start of list of inodes to delete */
    unsigned int   s_hash_seed[4];     /* HTREE hash seed */
    unsigned char  s_def_hash_version; /* Default hash version to use */
    unsigned char  s_reserved_char_pad;
    unsigned short s_reserved_word_pad;
    unsigned int   s_default_mount_opts;
    unsigned int   s_first_meta_bg;    /* First metablock block group */
    unsigned int   s_reserved[190];    /* Padding to the end of the block */
};


// ext2_group_desc结构体
struct ext2_group_desc
{
    unsigned int   bg_block_bitmap;      /* Blocks bitmap block */
    unsigned int   bg_inode_bitmap;      			/* Inodes bitmap block */
    unsigned int   bg_inode_table;       				/* Inodes table block */
    unsigned short bg_free_blocks_count; 				/* Free blocks count */
    unsigned short bg_free_inodes_count; 				/* Free inodes count */
    unsigned short bg_used_dirs_count;     /* ext2_dir_entry_2ectories count */
    unsigned short bg_pad;                 /* 按字节对齐 */
    unsigned int   bg_reserved[3];         /* 用null填充24个字节*/
};


// ext2_inode_table结构体
struct ext2_inode {
	unsigned short i_mode;        /* File mode */
	unsigned short i_uid;         /* Low 16 bits of Owner Uid */
	unsigned int   i_size;        /* Size in bytes */
	unsigned int   i_atime;       /* Access time */
	unsigned int   i_ctime;       /* Creation time */
	unsigned int   i_mtime;       /* Modification time */
	unsigned int   i_dtime;       /* Deletion Time */
	unsigned short i_gid;         /* Low 16 bits of Group Id */
	unsigned short i_links_count; /* Links count */
	unsigned int   i_blocks;      /* Blocks count IN DISK SECTORS*/
	unsigned int   i_flags;       /* File flags */
	unsigned int   osd1;          /* OS dependent 1 */
	unsigned int   i_block[15];   /* Pointers to blocks */
	unsigned int   i_generation;  /* File version (for NFS) */
	unsigned int   i_file_acl;    /* File ACL */
	unsigned int   i_dir_acl;     /* ext2_dir_entry_2ectory ACL */
	unsigned int   i_faddr;       /* Fragment address */
	unsigned int   extra[3];
};


// 文件模式 file mode
/* #define EXT2_S_IFSOCK 0xC000 */ /* socket */
#define    EXT2_S_IFLNK  0xA000    /* symbolic link */
#define    EXT2_S_IFREG  0x8000    /* regular file */
/* #define EXT2_S_IFBLK  0x6000 */ /* block device */
#define    EXT2_S_IFDIR  0x4000    /* directory */
/* #define EXT2_S_IFCHR  0x2000 */ /* character device */
/* #define EXT2_S_IFIFO  0x1000 */ /* fifo */


// inode号inode numbers
/* #define EXT2_BAD_INO          1 */ /* Bad blocks inode */
#define    EXT2_ROOT_INO         2    /* Root inode */
/* #define EXT4_USR_QUOTA_INO    3 */ /* User quota inode */
/* #define EXT4_GRP_QUOTA_INO    4 */ /* Group quota inode */
/* #define EXT2_BOOT_LOADER_INO  5 */ /* Boot loader inode */
/* #define EXT2_UNDEL_ext2_dir_entry_2_INO    6 */ /* Undelete ext2_dir_entry_2ectory inode */
/* #define EXT2_RESIZE_INO       7 */ /* Reserved group descriptors inode */
/* #define EXT2_JOURNAL_INO      8 */ /* Journal inode */
/* #define EXT2_EXCLUDE_INO      9 */ /* The "exclude" inode, for snapshots */
/* #define EXT4_REPLICA_INO     10 */ /* Used by non-upstream feature */
/* First non-reserved inode for old ext2 ext2_fileSystems */
#define EXT2_GOOD_OLD_FIRST_INO 11



// ext2_dir_entry_2目录s项结构体
#define EXT2_NAME_LEN 255
struct ext2_dir_entry_2 {
    unsigned int   inode;     /* Inode number */
    unsigned short rec_len;   /* ext2_dir_entry_2ectory entry length */
    unsigned char  name_len;  /* Name length */
    unsigned char  file_type;
    char           name[];    /* File name, up to EXT2_NAME_LEN */
};


// ext2_dir_entry_2_directory file types
#define    EXT2_FT_UNKNOWN  0    /* Unknown File Type */
#define    EXT2_FT_REG_FILE 1    /* Regular File */
#define    EXT2_FT_DIR   	2	 /* Directory File */
/* #define EXT2_FT_CHRDEV   3 */ /* Character Device */
/* #define EXT2_FT_BLKDEV   4 */ /* Block Device */
/* #define EXT2_FT_FIFO     5 */ /* Buffer File */
/* #define EXT2_FT_SOCK     6 */ /* Socket File */
#define    EXT2_FT_SYMLINK  7    /* Symbolic Link */
#define    EXT2_FT_MAX      8
#define    BLOCK_N      15

FILE* pf;
static char ext2_block_buffer[1024];  
char ext2_test[8708*1024];  //测试用 
char ext2_inode_table_buffer[522240]; //测试用 
char ext2_filebuffer[8192]=""; 										//文件内容缓存
  
struct ext2_super_block ext2_super_block_buffer[1024];	        //超级块缓冲区 
struct ext2_group_desc ext2_group_desc_buffer[1024];			/* 组描述符缓冲区 */
struct ext2_inode ext2_inode_buffer[1024];  					/* 节点缓冲区 */
struct ext2_dir_entry_2 ext2_dir_entry_2[1024]; 					//64*16 = 1024 = 1block
 
unsigned char ext2_block_bitmap_buffer[1024]=""; //block bitmap缓冲区 
unsigned char ext2_inode_bitmap_buffer[1024]=""; //inode bitmap缓冲区 


unsigned int last_inode_bit=1;  	//记录最后一次的inode bit 
unsigned int last_block_bit=0;  	//记录最后一次的block bit 
unsigned int current_ext2_dir_entry_2_inode; 	//当前目录的inode 
unsigned int current_ext2_dir_entry_2_length; 	//当前目录的长度 
char current_path[256]="";    		//当前路径名  [root@localhost ~]#   16bytes  将13位替换
//char path_first[13]=""; 
char path_last[4]="";
char path_name[241]=""; 
char time_now[32] = "";  //存储当前时间 


//系统函数声明
void read_ext2_super_block(void); 					//从磁盘中读出super_block 到缓冲区
void write_super_block(void);				 		//将缓冲区的super_block 写入磁盘 

void read_ext2_block_group_desc(void); 				// 从磁盘中读出block_group_des 到缓冲区 
void write_ext2_block_group_desc(void); 		    //将缓冲区的ext2_block_group_desc 写入磁盘 

void read_ext2_block_bitmap(void); 					//将bit map 读到缓冲区block_buffer
void write_ext2_block_bitmap(void); 				//将缓冲区block_buffer写入磁盘 

void read_ext2_inode_bitmap(void); 					//将bit map 读到缓冲区inode_buffer
void write_ext2_inode_bitmap(void); 				//将缓冲区inode_buffer写入磁盘 

void read_inode(int);  								//读取一个inode信息 
void write_inode(int); 								//写入一个inode信息 

void read_block(int);  								//读取一个block信息 
void write_block(int); 								//写入一个block信息 

void read_ext2_dir_entry_2(int); 					//读取一个ext2_dir_entry_2信息 
void write_ext2_dir_entry_2(int); 					//写入一个ext2_dir_entry_2信息 

unsigned int get_free_block(void); 					//返回一个空闲的block
unsigned int get_free_inode(void); 					//返回一个空闲的inode 

void remove_block(int); 							//移除一个block bit
void remove_inode(int); 							//移除一个inode bit

void current_time(void); 							//设置当前时间 
void create_ext2_fileSystem(); 						//新建文件系统 


//功能函数声明 
void ls(void); 										//显示目录下的文件
void mkdir(char temp[9]); 						//新建一个目录 
void dir_prepare(unsigned int, int); 				//对新建的目录进行初始化
void cd(char temp[9]); 							//切换目录
void format(void); 									//格式化磁盘 
void rmdir(char temp[9]); 			//删除空目录
void logout(void); 									//退出登录
void help(void); 									//显示帮助命令
void dumpe2fs(void); 								//显示磁盘信息
void vi(char temp[9]); 							//创建新文件 
void cat(char temp[9]); 							//查看文件内容 
void rm(char temp[9]); 							//删除文件 
// void ifconfig(void); 								//显示IP 
// void ping(char ip[128]); 							//ping主机 
void reName(char oldname[255], char newname[255]); 	//文件重命名 
void data(void); 									//显示当前时间 
void chmod(char temp[9], int mode); 				//修改权限 
int search_file(char temp[9], int *i, int *k); 	//寻找该目录是否有此文件，若有返回1，没有返回0 


