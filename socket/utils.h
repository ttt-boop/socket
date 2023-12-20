#ifndef COMMUNICATION_UTILS_H
#define COMMUNICATION_UTILS_H

#include <cstring>
#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <cmath>
#include <sys/statvfs.h>


using namespace std;

class Utils
{
public:
    struct hardDisk
    {
        double total = 0.;
        double free = 0.;
        double used = 0.;
        double avail = 0.;
    };

    const int KB = 1024;
    const int MB = 1024 * 1024;
    const int GB = 1024 * 1024 * 1024;

    bool getDiskInfo(const char *path, hardDisk &rst)
    {
        struct statvfs stat;
        if (statvfs(path, &stat) < 0)
        {
            printf("read %s error!!!\n", path);
            return false;
        }

        /*获取一个block的大小*/
        fsblkcnt_t block_size = stat.f_bsize;
        /*获取总容量*/
        fsblkcnt_t total_size = stat.f_blocks * block_size;
        /*获取可用容量*/
        fsblkcnt_t free_size = stat.f_bfree * block_size;
        /*获取使用容量*/
        fsblkcnt_t used_size = (stat.f_blocks - stat.f_bavail) * block_size;
        /*获取有效容量*/
        fsblkcnt_t avail_size = stat.f_bavail * block_size;

        rst.total = (double)total_size / (MB);
        rst.free = (double)free_size / (MB);
        rst.used = (double)used_size / (MB);
        rst.avail = (double)avail_size / (MB);

        printf(" path: %s\n", path);
        printf(" total_size = %0.2lf  MB\n", (double)total_size / (MB));
        printf(" free_size = %0.2lf  MB\n", (double)free_size / (MB));
        printf(" used_size = %0.2lf  MB\n", (double)used_size / (MB));
        printf(" avail_size = %0.2lf  MB\n", (double)avail_size / (MB));

        return true;
    }

    bool isFileExist(const std::string &file_path)
    {
        if (access(file_path.c_str(), 0) == -1)
            return false;
        else if (access(file_path.c_str(), 0) == 0)
            return true;
    }
    
    int getFileByteSize(std::string file_path)
    {
        char *cstr = new char[file_path.length() + 1];
        strcpy(cstr, file_path.c_str());
        FILE *pFile = std::fopen(cstr, "rb"); //获取已打开文件的指针
        std::fseek(pFile, 0, SEEK_END);       //先用fseek将文件指针移到文件末尾
        delete[] cstr;
        return std::ftell(pFile); //再用ftell获取文件内指针当前的文件位置。
    }

    long long getTimestamp()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long long timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        return timestamp;
    }
    
};

#endif // COMMUNICATION_UTILS_H