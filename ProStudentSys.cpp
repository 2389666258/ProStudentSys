//
// Created by DevourGod on 2021/12/20.
//

#include <iostream>
#include <windows.h>

using namespace std;

/* 主业务函数声明 */
void welcome();         // 欢迎
void menu();            // 主菜单

void addStudent();          // 1.新增
void deleteStudent();       // 2.删除 (软删除)
void queryStudent();        // 3.查询
void updateStudent();       // 4.修改
void printAllin();          // 5.打印所有在档信息
void back_to_the_file();    // 6.回档已删除信息
void printAlldel();         // 7.打印已删除信息
void printAll();            // 8.打印所有信息

int writeData();        // 写入文件
int readData();         // 读取文件

/* 辅助业务函数声明 */
int createNum();                    // 学号 num 生成
void printCurrent(int IndexNow);    // 用下标 Index 打印当前的信息
int findIndex(int num);             // 用学号 num 找到下标
void back_to_menu();                // 返回到主菜单
void sleep();                       // 时停 600ms
void menuSleep();                   // 菜单输出时停间距
void Pause();                       // 按任意键继续

// 学生信息结构体
struct student{
    int num;            // 学号
    char name[20];      // 姓名
    char sex[3];        // 性别
    char Class[10];     // 班级
    int Chinese;        // 语文成绩
    int Maths;          // 数学成绩
    int English;        // 英语成绩
    int total;          // 总成绩
    int state;          // 状态 (1 正常 0 删除)
};
struct student students[1000];   // 声明 结构体组 存储1000个学生信息

int Index = -1;                  // 起始下标为 -1 (初始化)
FILE *fp;                        // 文件指针声明


int main()
{
//    ios::sync_with_stdio(false); // 不能乱用
    welcome();
    Index = readData();         // 在 主菜单 前读取文件 返回应起始的下标值 Index
    menu();
    return 0;
}


// 欢迎函数
void welcome()
{
    string arr1, arr2, arr;
    arr1 = "————————————————————————";
    arr2 = "|-* Welcome to student Administration System *-|";
    arr  = "                                                ";

    int left = 0;
    int si = arr.size();
    int right = si - 1;

    while (left <= right)
    {
        arr[left] = arr2[left];
        arr[right] = arr2[right];
        cout << arr1 << endl << arr << endl << arr1 << endl;
        menuSleep();
        system("cls");
        left++;
        right--;
    }

    for (int i = 0; i < 2; ++i) {
        cout << arr1 << endl << arr << endl << arr1 << endl;
        Sleep(250);
        system("cls");
        Sleep(50);
    }

    cout << "————————————————————————\n"
            "|            欢迎进入学生管理系统!             |\n"
            "————————————————————————\n";

    sleep();
}


// 主菜单函数
void menu()
{
    while (true)
    {
        cout << "——————————————" << endl, menuSleep();
        cout << "|      1 增加学生信息      |" << endl, menuSleep();
        cout << "|      2 删除学生信息      |" << endl, menuSleep();
        cout << "|      3 查找学生信息      |" << endl, menuSleep();
        cout << "|      4 修改学生信息      |" << endl, menuSleep();
        cout << "|      5 打印在档信息      |" << endl, menuSleep();
        cout << "|—————————————|" << endl, menuSleep();
        cout << "|      6 回档已删除信息    |" << endl, menuSleep();
        cout << "|      7 打印已删除信息    |" << endl, menuSleep();
        cout << "|—————————————|" << endl, menuSleep();
        cout << "|      8 打印所有信息      |" << endl, menuSleep();
        cout << "|—————————————|" << endl, menuSleep();
        cout << "|      0 退出系统          |" << endl, menuSleep();
        cout << "——————————————" << endl, menuSleep();
        cout << "请选择业务:" << endl;

        int select;
        cin >> select;

        Sleep(300);

        switch (select) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                queryStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                printAllin();
                Pause();
                break;
            case 6:
                back_to_the_file();
                break;
            case 7:
                printAlldel();
                Pause();
                break;
            case 8:
                printAll();
                Pause();
                break;
            case 0:
                exit(0);
            default:
                cout << "输入有误哦~ 请重试:" << endl;
                break;
        }
        back_to_menu();
    }
}


/* 主业务函数 */

// 1.增加学生信息
void addStudent(){
    // 定义判断是否继续的变量
    char answer;

    // 定义判断写入文件是否成功的变量
    int flag;

    cout << endl << "|——————新增学生信息——————|" << endl;
    while(true){      // 可以重复添加
        Index ++;    // 下标值自增
        cout << "请输入学生信息: 姓名 性别 班级 语文成绩 数学成绩 英语成绩  (班级 和 各成绩 要为数字哦~)" << endl;
        students[Index].num = createNum();          // 学号自增

        //其他信息输入
        cin >> students[Index].name
            >> students[Index].sex
            >> students[Index].Class
            >> students[Index].Chinese
            >> students[Index].Maths
            >> students[Index].English;

        // 计算总成绩
        students[Index].total = students[Index].Chinese + students[Index].Maths + students[Index].English;

        // 设置当前信息状态为 1 新增的数据状态必须为 1 删除则为 0
        students[Index].state = 1;

        // 显示添加的学生信息
        printCurrent(Index);

        // 将数组中的数据写入到文件内
        flag = writeData();     // 成功为 1 失败为 0

        //对表示符进行判断
        if(flag == 1) cout << "添加成功!" << endl;
        else cout << "添加失败!" << endl;

        sleep();

        //是否要继续进行添加
        flag = 1;
        while (true)
        {
            cout << "是否继续添加?  (y是 \\ n否)" << endl;
            cin >> answer;
            if (answer == 'y')
            {
                flag = 0;
                break;
            }
            else if (answer == 'n') break;
            else cout << "输入有误哦~ 请重试:" << endl;
        }
        if (!flag) continue;
        else break;
    }

}


// 2.删除学生信息
void deleteStudent()
{
    // 定义一个学号 是我们要输入的
    int num;

    // 定义一个下标
    int IndexNow;

    // 定义判断是否继续的变量
    char answer;

    printAllin();
    cout << endl << "|——————删除学生信息——————|" << endl;
    cout << "请 根据上表 输入您要删除的学生的学号:  (注意输入的是 学号 哦~)" << endl;
    cin >> num;

    // 用学号 num 查询下标 Index
    IndexNow = findIndex(num);
    if(IndexNow == -1 || students[IndexNow].state == 0){         // 如果找不到
        cout << "未找到该学生学号信息哦~" << endl;
        return;
    }

    while (true)
    {
        // 打印学生信息 根据查询的下标 Index 查询出该学生信息
        printCurrent(IndexNow);
        cout << "您确定要删除吗?  (y是 \\ n否)" << endl;
        cin >> answer;
        if(answer == 'y'){
            // 删除后数据信息还存在 软删除 修改其状态 state
            students[IndexNow].state = 0;

            // 写入文件
            writeData();
            cout << "删除成功!" << endl;
            break;
        } else if (answer == 'n')
        {
            cout << "已取消删除!" << endl;
            break;
        }
        else cout << "输入有误哦~ 请重试:" << endl;
    }

}


// 3.查找学生信息
void queryStudent()
{
    // 定义判断写入文件是否成功的变量
    int flag = 0;

    cout << endl << "|——————查找学生信息——————|" << endl;
    cout << "请输入您要查找的学生姓名:  (注意输入的是 姓名 哦~)" << endl;

    // 清空缓冲区
    fflush(stdin);

    // 获取学生姓名 获取结构体数组当中的 name
    string name;
    cin >> name;

    for(int i = 0; i <= Index; i++){
        string studentName = students[i].name;
        // 如果输入的 name 含于 students[i].name 就打印
        if (studentName.find(name) != studentName.npos && students[i].state == 1)
        {
            printCurrent(i);
            cout << endl;
            flag = 1;
        }
    }
    if(!flag) cout << "没找到任何相关信息!" << endl;

    Pause();
}


// 4.修改学生信息
void updateStudent()
{
    // 定义判断是否继续的变量
    char answer;

    // 定义判断写入文件是否成功的变量
    int flag;

    printAllin();
    cout << endl << "|——————修改学生信息——————|" << endl;
    cout << "请 根据上表 输入您要修改的学生的学号:  (注意输入的是 学号 哦~)" << endl;
    int num;
    cin >> num;
    int IndexNow = findIndex(num);
    if(IndexNow == -1 || students[IndexNow].state == 0){             // 如果找不到
        cout << "没有该学生学号信息哦~" << endl;
        return;
    }

    // 打印出该学生信息
    while (true)
    {
        printCurrent(Index);
        cout << "您确定要修改吗?  (y是 \\ n否)" << endl;
        cin >> answer;
        if(answer == 'y')
        {
            cout << "请输入以修改当前学生信息: 姓名 性别 班级 语文成绩 数学成绩 英语成绩  ( 班级 和 各成绩 要为数字哦~)" << endl;
            cin >> students[Index].name
                >> students[Index].sex
                >> students[Index].Class
                >> students[Index].Chinese
                >> students[Index].Maths
                >> students[Index].English;

            // 计算总成绩
            students[Index].total = students[Index].Chinese + students[Index].Maths + students[Index].English;

            // 显示出当前学生的信息
            printCurrent(Index);

            // 将数据写入文件
            flag = writeData();
            if(flag) cout << "修改成功!" << endl;
            else cout << "修改失败!" << endl;
            break;
        } else if (answer == 'n')
        {
            cout << "您以取消修改!" << endl;
            break;
        }
        else cout << "输入有误哦~ 请重试:" << endl;
    }

}


// 5.打印全部学生信息
void printAllin()
{
    // 只打印状态为1的学生信息
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|学号      |姓名    |性别    |班级    |语文    |数学    |英语    |总成绩  |" << endl, menuSleep();
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();

    // 对应的数组中的数据
    for(int i = 0; i <= Index; i++){
        if(students[i].state == 1){
            printf("|%-10d|%-8s|%-8s|%-8s|%-8d|%-8d|%-8d|%-8d|\n",
                   students[i].num,
                   students[i].name,
                   students[i].sex,
                   students[i].Class,
                   students[i].Chinese,
                   students[i].Maths,
                   students[i].English,
                   students[i].total = students[i].Chinese+students[i].Maths + students[i].English);
             cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
        }
    }

}


// 6.回档已删除信息
void back_to_the_file()
{
    // 定义一个学号 是我们要输入的
    int num;

    // 定义一个下标
    int IndexNow;

    // 定义判断是否继续的变量
    char answer;

    printAlldel();
    cout << endl << "|——————回档已删除学生信息——————|" << endl;
    cout << "请 根据上表 输入您要回档的学生的学号:  (注意输入的是 学号 哦~)" << endl;
    cin >> num;

    // 用学号 num 查询下标 Index
    IndexNow = findIndex(num);
    if(IndexNow == -1 || students[IndexNow].state == 1){         // 如果找不到
        cout << "未找到该学生学号信息哦~" << endl;
        return;
    }

    while (true)
    {
        // 打印学生信息 根据查询的下标 Index 查询出该学生信息
        printCurrent(IndexNow);
        cout << "您确定要回档吗?  (y是 \\ n否)" << endl;
        cin >> answer;
        if(answer == 'y'){
            // 删除后数据信息还存在 软删除 修改其状态 state
            students[IndexNow].state = 1;

            // 写入文件
            writeData();
            cout << "回档成功!" << endl;
            break;
        } else if (answer == 'n')
        {
            cout << "已取消回档!" << endl;
            break;
        }
        else cout << "输入有误哦~ 请重试:" << endl;
    }

}


// 7.打印已删除信息
void printAlldel()
{
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|学号      |姓名    |性别    |班级    |语文    |数学    |英语    |总成绩  |" << endl, menuSleep();
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();

    // 对应的数组中的数据
    for(int i = 0; i <= Index; i++){
        if(students[i].state == 0){
            printf("|%-10d|%-8s|%-8s|%-8s|%-8d|%-8d|%-8d|%-8d|\n",
                   students[i].num,
                   students[i].name,
                   students[i].sex,
                   students[i].Class,
                   students[i].Chinese,
                   students[i].Maths,
                   students[i].English,
                   students[i].total = students[i].Chinese+students[i].Maths + students[i].English);
            cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
        }
    }

}


// 8.打印所有信息
void printAll()
{
    cout << "|----------------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|学号      |姓名    |性别    |班级    |语文    |数学    |英语    |总成绩  |是否在档|" << endl, menuSleep();
    cout << "|----------------------------------------------------------------------------------|" << endl, menuSleep();

    Sleep(100);
    // 对应的数组中的数据
    for(int i = 0; i <= Index; i++){
        printf("|%-10d|%-8s|%-8s|%-8s|%-8d|%-8d|%-8d|%-8d|%-8d|\n",
                students[i].num,
                students[i].name,
                students[i].sex,
                students[i].Class,
                students[i].Chinese,
                students[i].Maths,
                students[i].English,
                students[i].total = students[i].Chinese+students[i].Maths + students[i].English,
                students[i].state);
        cout << "|----------------------------------------------------------------------------------|" << endl, menuSleep();
    }

}


/* 辅助业务函数 */

// 根据下标 index 打印出当前下标的数据
void printCurrent(int IndexNow){
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|学号      |姓名    |性别    |班级    |语文    |数学    |英语    |总成绩  |" << endl, menuSleep();
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    printf("|%-10d|%-8s|%-8s|%-8s|%-8d|%-8d|%-8d|%-8d|\n",
           students[IndexNow].num,
           students[IndexNow].name,
           students[IndexNow].sex,
           students[IndexNow].Class,
           students[IndexNow].Chinese,
           students[IndexNow].Maths,
           students[IndexNow].English,
           students[IndexNow].total = students[IndexNow].Chinese + students[IndexNow].Maths + students[IndexNow].English);
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
}


// 学号 num 生成
int createNum(){
    // 定义一个下标值 当下标值为 0 时表示第一次添加
    if(Index == 0) return 2021001;

    // 当下标不为 0 时 就让学号加 1
    else return students[Index - 1].num + 1;
}


// 读取文件
int readData()
{
    // 为空 写文件
    if((fp = fopen("studentinfo.txt", "r")) == nullptr)
    {
        // 如果文件为空 就以写的方式打开文件
        fopen("studentinfo.txt", "w");
        return -1;          // 返回下标 Index 的初值 开始写入信息
    }

    // 不为空 读文件 不确定文件有多少信息 使用循环
    int i = 0;  // 从 0 开始读
    while(true)
    {
        // 判断文件是否读完结束 结束就跳出
        if(feof(fp)) break;

        fscanf(fp,"%d %s %s %s %d %d %d %d %d",
               &students[i].num,
                students[i].name,
                students[i].sex,
                students[i].Class,
               &students[i].Chinese,
               &students[i].Maths,
               &students[i].English,
               &students[i].total,
               &students[i].state);
        i++;    // 读完一条数据后下标增 1 继续读
    }

    // 关闭文件
    fclose(fp);
    return i - 2;   // 多读 1 行 下标又比实际行数少 1 所以 -2
}


// 写入文件
int writeData()
{
    // 打开文件
    if((fp = fopen("studentinfo.txt", "w")) == nullptr)
    {
        //提示错误
        printf("文件打开失败!");
        return 0;
    }

    // 写文件
    for(int i = 0; i <= Index; i++)
    {
        fprintf(fp,"%d %s %s %s %d %d %d %d %d\n",
                students[i].num,
                students[i].name,
                students[i].sex,
                students[i].Class,
                students[i].Chinese,
                students[i].Maths,
                students[i].English,
                students[i].total,
                students[i].state);
    }

    //关闭文件
    fclose(fp);
    return 1;
}


// 用学号 num 找到其下标 index
int findIndex(int num)
{
    int IndexNow = -1;
    for(int i = 0; i <= Index; i++){
        if(students[i].num == num){
            IndexNow = i;   // 查找到相同的学号
            break;
        }
    }
    return IndexNow;    // 若未找到相同的学号 就返回 -1
}


void sleep()
{
    Sleep(600);
}


// 返回到主菜单
void back_to_menu()
{
    cout << endl, menuSleep();
    cout << "正", menuSleep();
    cout << "在", menuSleep();
    cout << "返", menuSleep();
    cout << "回", menuSleep();
    cout << "主", menuSleep();
    cout << "菜", menuSleep();
    cout << "单", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << endl, menuSleep();
    cout << endl, menuSleep();
    sleep();
}


// 菜单输出时停间距
void menuSleep()
{
    Sleep(18);
}


// 按任意键继续 暂停
void Pause()
{
    cout << endl, menuSleep();
    cout << "查", menuSleep();
    cout << "看", menuSleep();
    cout << "信", menuSleep();
    cout << "息", menuSleep();
    cout << "中", menuSleep();
    cout << "~", menuSleep();
    cout << " ", menuSleep();
    sleep();
    cout << endl, menuSleep();
    cout << endl, menuSleep();
    cout << endl, menuSleep();
    cout << "按", menuSleep();
    cout << "任", menuSleep();
    cout << "意", menuSleep();
    cout << "键", menuSleep();
    cout << "继", menuSleep();
    cout << "续", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << endl, menuSleep();
    system("pause > nul");
}