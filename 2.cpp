// 编译 g++ 2.cpp -o 2，管理员运行 2.exe
// 使用说明：曲谱写在“song2.txt”这个文件中，输入字母即对应按键。空格或换行表示间隔时间（无输入时间）
#include <Windows.h>
#include <iostream>
#include <cstdio>
using namespace std;

int main() 
{
    int i = 0, j = 0;
    int ret = 0, size = 0;
    int interval_time = 500;
    char buf[10240] = {0};

    // 修改编码
    system("chcp 65001");

    cout << "请输入单位间隔时间（毫秒）：";
    cin >> interval_time;

    FILE *fp = fopen("song2.txt", "r");
    ret = fread(buf, 10240, 1, fp);
    fclose(fp);
    size = strlen(buf);
    cout << "谱子长(字节):" << size << endl;
    cout << "谱子内容为：" << buf << endl;

    cout << "5秒后程序开始运行" << endl;

	// 睡眠5s，准备时间
	Sleep(5000);

	// 循环
	for(i = 0; i < size; i++)
	{
        for(j = i; j < size; j++)
        {
            // 判断数字 只能为0-9，超过9就不能一起识别
            if(48 <= buf[j] && buf[j] <= 57)
            {
                i = j;
                break;
            }

            // 跳过空格和回车
            if(buf[j] == ' ' || buf[j] == '\n')
            {
                continue;
            }

            // 小写转大写字母
            if(97 <= buf[j] && buf[j] <= 122)
                buf[j] -= 32;

            // 按键
            keybd_event((BYTE)buf[j], 0, 0, 0);
            keybd_event((BYTE)buf[j], 0, KEYEVENTF_KEYUP, 0);
        }

        // char转int
        int num = 0;
        num = (int)(buf[i] - '0');
        // 睡眠 数字 * 间隔时间 毫秒
        Sleep(num * interval_time);
	}
	
    cout << "程序运行完毕" << endl;

	system("pause");
	return 0;
}
