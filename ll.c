
//  struct stat {
//              dev_t     st_dev;         /* ID of device containing file */
//               ino_t     st_ino;         /* Inode number */
//               mode_t    st_mode;        /* File type and mode */
//               nlink_t   st_nlink;       /* Number of hard links */
//               uid_t     st_uid;         /* User ID of owner */
//               gid_t     st_gid;         /* Group ID of owner */
//               dev_t     st_rdev;        /* Device ID (if special file) */
//               off_t     st_size;        /* Total size, in bytes */
//               blksize_t st_blksize;     /* Block size for filesystem I/O */
//               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
//
//               /* Since Linux 2.6, the kernel supports nanosecond
//                  precision for the following timestamp fields.
//                  For the details before Linux 2.6, see NOTES. */
//
//               struct timespec st_atim;  /* Time of last access */
//               struct timespec st_mtim;  /* Time of last modification */
//               struct timespec st_ctim;  /* Time of last status change */
//
//           #define st_atime st_atim.tv_sec      /* Backward compatibility */
//           #define st_mtime st_mtim.tv_sec
//           #define st_ctime st_ctim.tv_sec
//           };

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <string.h>


#define S_U_R(m) (((m) & S_IRUSR) == S_IRUSR)
#define S_U_W(m) (((m) & S_IWUSR) == S_IWUSR)
#define S_U_X(m) (((m) & S_IXUSR) == S_IXUSR)

#define S_G_R(m) (((m) & S_IRGRP) == S_IRGRP)
#define S_G_W(m) (((m) & S_IWGRP) == S_IWGRP)
#define S_G_X(m) (((m) & S_IXGRP) == S_IXGRP)

#define S_O_R(m) (((m) & S_IROTH) == S_IROTH)
#define S_O_W(m) (((m) & S_IWOTH) == S_IWOTH)
#define S_O_X(m) (((m) & S_IXOTH) == S_IXOTH)


char* get_username_by_uid(uid_t uid){
	struct passwd *pwd = getpwuid(uid);// read from /etc/passwd
	return pwd->pw_name;
}


char* get_groupname_by_gid(gid_t gid){
	struct group *grp = getgrgid(gid);// read from /etc/group
	return grp->gr_name;
}


char* get_mode_string_from_modenumber(mode_t mode){
	char* output = (char*)malloc(10*sizeof(char));
        strcpy(output, "----------");
	
	if(S_ISDIR(mode)) output[0]='d';
	else if(S_ISCHR(mode)) output[0]='c';
	else if(S_ISBLK(mode)) output[0]='b';
	else if(S_ISLNK(mode)) output[0]='l';
	else if(S_ISFIFO(mode)) output[0]='f';
	else if(S_ISSOCK(mode)) output[0]='s';

	if(S_U_R(mode)) output[1]='r';
	if(S_U_W(mode)) output[2]='w';
	if(S_U_X(mode)) output[3]='x';
	if(S_G_R(mode)) output[4]='r';
	if(S_G_W(mode)) output[5]='w';
	if(S_G_X(mode)) output[6]='x';
	if(S_O_R(mode)) output[7]='r';
	if(S_O_W(mode)) output[8]='w';
	if(S_O_X(mode)) output[9]='x';

	return output;
}


int main(int argc, char** argv){
	struct stat buff;
	int output = stat(argv[1], &buff);
	if(output == -1){
		perror("ERROR:file status wrong");
		return -1;
	}

	char *str = get_mode_string_from_modenumber(buff.st_mode);
	printf("%s ", str);
	free(str);

	printf("%ld ", buff.st_nlink);
	printf("%s ", get_username_by_uid(buff.st_uid));
	printf("%s ", get_groupname_by_gid(buff.st_gid));
	printf("%ld ", buff.st_size);
	printf("%s", ctime(&buff.st_atime));
	return 0;
}
