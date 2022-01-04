//
// Created by DevourGod on 2021/12/20.
//

#include <iostream>
#include <windows.h>

using namespace std;

/* ��ҵ�������� */
void welcome();         // ��ӭ
void menu();            // ���˵�

void addStudent();          // 1.����
void deleteStudent();       // 2.ɾ�� (��ɾ��)
void queryStudent();        // 3.��ѯ
void updateStudent();       // 4.�޸�
void printAllin();          // 5.��ӡ�����ڵ���Ϣ
void back_to_the_file();    // 6.�ص���ɾ����Ϣ
void printAlldel();         // 7.��ӡ��ɾ����Ϣ
void printAll();            // 8.��ӡ������Ϣ

int writeData();        // д���ļ�
int readData();         // ��ȡ�ļ�

/* ����ҵ�������� */
int createNum();                    // ѧ�� num ����
void printCurrent(int IndexNow);    // ���±� Index ��ӡ��ǰ����Ϣ
int findIndex(int num);             // ��ѧ�� num �ҵ��±�
void back_to_menu();                // ���ص����˵�
void sleep();                       // ʱͣ 600ms
void menuSleep();                   // �˵����ʱͣ���
void Pause();                       // �����������

// ѧ����Ϣ�ṹ��
struct student{
    int num;            // ѧ��
    char name[20];      // ����
    char sex[3];        // �Ա�
    char Class[10];     // �༶
    int Chinese;        // ���ĳɼ�
    int Maths;          // ��ѧ�ɼ�
    int English;        // Ӣ��ɼ�
    int total;          // �ܳɼ�
    int state;          // ״̬ (1 ���� 0 ɾ��)
};
struct student students[1000];   // ���� �ṹ���� �洢1000��ѧ����Ϣ

int Index = -1;                  // ��ʼ�±�Ϊ -1 (��ʼ��)
FILE *fp;                        // �ļ�ָ������


int main()
{
//    ios::sync_with_stdio(false); // ��������
    welcome();
    Index = readData();         // �� ���˵� ǰ��ȡ�ļ� ����Ӧ��ʼ���±�ֵ Index
    menu();
    return 0;
}


// ��ӭ����
void welcome()
{
    string arr1, arr2, arr;
    arr1 = "������������������������������������������������";
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

    cout << "������������������������������������������������\n"
            "|            ��ӭ����ѧ������ϵͳ!             |\n"
            "������������������������������������������������\n";

    sleep();
}


// ���˵�����
void menu()
{
    while (true)
    {
        cout << "����������������������������" << endl, menuSleep();
        cout << "|      1 ����ѧ����Ϣ      |" << endl, menuSleep();
        cout << "|      2 ɾ��ѧ����Ϣ      |" << endl, menuSleep();
        cout << "|      3 ����ѧ����Ϣ      |" << endl, menuSleep();
        cout << "|      4 �޸�ѧ����Ϣ      |" << endl, menuSleep();
        cout << "|      5 ��ӡ�ڵ���Ϣ      |" << endl, menuSleep();
        cout << "|��������������������������|" << endl, menuSleep();
        cout << "|      6 �ص���ɾ����Ϣ    |" << endl, menuSleep();
        cout << "|      7 ��ӡ��ɾ����Ϣ    |" << endl, menuSleep();
        cout << "|��������������������������|" << endl, menuSleep();
        cout << "|      8 ��ӡ������Ϣ      |" << endl, menuSleep();
        cout << "|��������������������������|" << endl, menuSleep();
        cout << "|      0 �˳�ϵͳ          |" << endl, menuSleep();
        cout << "����������������������������" << endl, menuSleep();
        cout << "��ѡ��ҵ��:" << endl;

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
                cout << "��������Ŷ~ ������:" << endl;
                break;
        }
        back_to_menu();
    }
}


/* ��ҵ���� */

// 1.����ѧ����Ϣ
void addStudent(){
    // �����ж��Ƿ�����ı���
    char answer;

    // �����ж�д���ļ��Ƿ�ɹ��ı���
    int flag;

    cout << endl << "|����������������ѧ����Ϣ������������|" << endl;
    while(true){      // �����ظ����
        Index ++;    // �±�ֵ����
        cout << "������ѧ����Ϣ: ���� �Ա� �༶ ���ĳɼ� ��ѧ�ɼ� Ӣ��ɼ�  (�༶ �� ���ɼ� ҪΪ����Ŷ~)" << endl;
        students[Index].num = createNum();          // ѧ������

        //������Ϣ����
        cin >> students[Index].name
            >> students[Index].sex
            >> students[Index].Class
            >> students[Index].Chinese
            >> students[Index].Maths
            >> students[Index].English;

        // �����ܳɼ�
        students[Index].total = students[Index].Chinese + students[Index].Maths + students[Index].English;

        // ���õ�ǰ��Ϣ״̬Ϊ 1 ����������״̬����Ϊ 1 ɾ����Ϊ 0
        students[Index].state = 1;

        // ��ʾ��ӵ�ѧ����Ϣ
        printCurrent(Index);

        // �������е�����д�뵽�ļ���
        flag = writeData();     // �ɹ�Ϊ 1 ʧ��Ϊ 0

        //�Ա�ʾ�������ж�
        if(flag == 1) cout << "��ӳɹ�!" << endl;
        else cout << "���ʧ��!" << endl;

        sleep();

        //�Ƿ�Ҫ�����������
        flag = 1;
        while (true)
        {
            cout << "�Ƿ�������?  (y�� \\ n��)" << endl;
            cin >> answer;
            if (answer == 'y')
            {
                flag = 0;
                break;
            }
            else if (answer == 'n') break;
            else cout << "��������Ŷ~ ������:" << endl;
        }
        if (!flag) continue;
        else break;
    }

}


// 2.ɾ��ѧ����Ϣ
void deleteStudent()
{
    // ����һ��ѧ�� ������Ҫ�����
    int num;

    // ����һ���±�
    int IndexNow;

    // �����ж��Ƿ�����ı���
    char answer;

    printAllin();
    cout << endl << "|������������ɾ��ѧ����Ϣ������������|" << endl;
    cout << "�� �����ϱ� ������Ҫɾ����ѧ����ѧ��:  (ע��������� ѧ�� Ŷ~)" << endl;
    cin >> num;

    // ��ѧ�� num ��ѯ�±� Index
    IndexNow = findIndex(num);
    if(IndexNow == -1 || students[IndexNow].state == 0){         // ����Ҳ���
        cout << "δ�ҵ���ѧ��ѧ����ϢŶ~" << endl;
        return;
    }

    while (true)
    {
        // ��ӡѧ����Ϣ ���ݲ�ѯ���±� Index ��ѯ����ѧ����Ϣ
        printCurrent(IndexNow);
        cout << "��ȷ��Ҫɾ����?  (y�� \\ n��)" << endl;
        cin >> answer;
        if(answer == 'y'){
            // ɾ����������Ϣ������ ��ɾ�� �޸���״̬ state
            students[IndexNow].state = 0;

            // д���ļ�
            writeData();
            cout << "ɾ���ɹ�!" << endl;
            break;
        } else if (answer == 'n')
        {
            cout << "��ȡ��ɾ��!" << endl;
            break;
        }
        else cout << "��������Ŷ~ ������:" << endl;
    }

}


// 3.����ѧ����Ϣ
void queryStudent()
{
    // �����ж�д���ļ��Ƿ�ɹ��ı���
    int flag = 0;

    cout << endl << "|����������������ѧ����Ϣ������������|" << endl;
    cout << "��������Ҫ���ҵ�ѧ������:  (ע��������� ���� Ŷ~)" << endl;

    // ��ջ�����
    fflush(stdin);

    // ��ȡѧ������ ��ȡ�ṹ�����鵱�е� name
    string name;
    cin >> name;

    for(int i = 0; i <= Index; i++){
        string studentName = students[i].name;
        // �������� name ���� students[i].name �ʹ�ӡ
        if (studentName.find(name) != studentName.npos && students[i].state == 1)
        {
            printCurrent(i);
            cout << endl;
            flag = 1;
        }
    }
    if(!flag) cout << "û�ҵ��κ������Ϣ!" << endl;

    Pause();
}


// 4.�޸�ѧ����Ϣ
void updateStudent()
{
    // �����ж��Ƿ�����ı���
    char answer;

    // �����ж�д���ļ��Ƿ�ɹ��ı���
    int flag;

    printAllin();
    cout << endl << "|�������������޸�ѧ����Ϣ������������|" << endl;
    cout << "�� �����ϱ� ������Ҫ�޸ĵ�ѧ����ѧ��:  (ע��������� ѧ�� Ŷ~)" << endl;
    int num;
    cin >> num;
    int IndexNow = findIndex(num);
    if(IndexNow == -1 || students[IndexNow].state == 0){             // ����Ҳ���
        cout << "û�и�ѧ��ѧ����ϢŶ~" << endl;
        return;
    }

    // ��ӡ����ѧ����Ϣ
    while (true)
    {
        printCurrent(Index);
        cout << "��ȷ��Ҫ�޸���?  (y�� \\ n��)" << endl;
        cin >> answer;
        if(answer == 'y')
        {
            cout << "���������޸ĵ�ǰѧ����Ϣ: ���� �Ա� �༶ ���ĳɼ� ��ѧ�ɼ� Ӣ��ɼ�  ( �༶ �� ���ɼ� ҪΪ����Ŷ~)" << endl;
            cin >> students[Index].name
                >> students[Index].sex
                >> students[Index].Class
                >> students[Index].Chinese
                >> students[Index].Maths
                >> students[Index].English;

            // �����ܳɼ�
            students[Index].total = students[Index].Chinese + students[Index].Maths + students[Index].English;

            // ��ʾ����ǰѧ������Ϣ
            printCurrent(Index);

            // ������д���ļ�
            flag = writeData();
            if(flag) cout << "�޸ĳɹ�!" << endl;
            else cout << "�޸�ʧ��!" << endl;
            break;
        } else if (answer == 'n')
        {
            cout << "����ȡ���޸�!" << endl;
            break;
        }
        else cout << "��������Ŷ~ ������:" << endl;
    }

}


// 5.��ӡȫ��ѧ����Ϣ
void printAllin()
{
    // ֻ��ӡ״̬Ϊ1��ѧ����Ϣ
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|ѧ��      |����    |�Ա�    |�༶    |����    |��ѧ    |Ӣ��    |�ܳɼ�  |" << endl, menuSleep();
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();

    // ��Ӧ�������е�����
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


// 6.�ص���ɾ����Ϣ
void back_to_the_file()
{
    // ����һ��ѧ�� ������Ҫ�����
    int num;

    // ����һ���±�
    int IndexNow;

    // �����ж��Ƿ�����ı���
    char answer;

    printAlldel();
    cout << endl << "|�������������ص���ɾ��ѧ����Ϣ������������|" << endl;
    cout << "�� �����ϱ� ������Ҫ�ص���ѧ����ѧ��:  (ע��������� ѧ�� Ŷ~)" << endl;
    cin >> num;

    // ��ѧ�� num ��ѯ�±� Index
    IndexNow = findIndex(num);
    if(IndexNow == -1 || students[IndexNow].state == 1){         // ����Ҳ���
        cout << "δ�ҵ���ѧ��ѧ����ϢŶ~" << endl;
        return;
    }

    while (true)
    {
        // ��ӡѧ����Ϣ ���ݲ�ѯ���±� Index ��ѯ����ѧ����Ϣ
        printCurrent(IndexNow);
        cout << "��ȷ��Ҫ�ص���?  (y�� \\ n��)" << endl;
        cin >> answer;
        if(answer == 'y'){
            // ɾ����������Ϣ������ ��ɾ�� �޸���״̬ state
            students[IndexNow].state = 1;

            // д���ļ�
            writeData();
            cout << "�ص��ɹ�!" << endl;
            break;
        } else if (answer == 'n')
        {
            cout << "��ȡ���ص�!" << endl;
            break;
        }
        else cout << "��������Ŷ~ ������:" << endl;
    }

}


// 7.��ӡ��ɾ����Ϣ
void printAlldel()
{
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|ѧ��      |����    |�Ա�    |�༶    |����    |��ѧ    |Ӣ��    |�ܳɼ�  |" << endl, menuSleep();
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();

    // ��Ӧ�������е�����
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


// 8.��ӡ������Ϣ
void printAll()
{
    cout << "|----------------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|ѧ��      |����    |�Ա�    |�༶    |����    |��ѧ    |Ӣ��    |�ܳɼ�  |�Ƿ��ڵ�|" << endl, menuSleep();
    cout << "|----------------------------------------------------------------------------------|" << endl, menuSleep();

    Sleep(100);
    // ��Ӧ�������е�����
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


/* ����ҵ���� */

// �����±� index ��ӡ����ǰ�±������
void printCurrent(int IndexNow){
    cout << "|-------------------------------------------------------------------------|" << endl, menuSleep();
    cout << "|ѧ��      |����    |�Ա�    |�༶    |����    |��ѧ    |Ӣ��    |�ܳɼ�  |" << endl, menuSleep();
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


// ѧ�� num ����
int createNum(){
    // ����һ���±�ֵ ���±�ֵΪ 0 ʱ��ʾ��һ�����
    if(Index == 0) return 2021001;

    // ���±겻Ϊ 0 ʱ ����ѧ�ż� 1
    else return students[Index - 1].num + 1;
}


// ��ȡ�ļ�
int readData()
{
    // Ϊ�� д�ļ�
    if((fp = fopen("studentinfo.txt", "r")) == nullptr)
    {
        // ����ļ�Ϊ�� ����д�ķ�ʽ���ļ�
        fopen("studentinfo.txt", "w");
        return -1;          // �����±� Index �ĳ�ֵ ��ʼд����Ϣ
    }

    // ��Ϊ�� ���ļ� ��ȷ���ļ��ж�����Ϣ ʹ��ѭ��
    int i = 0;  // �� 0 ��ʼ��
    while(true)
    {
        // �ж��ļ��Ƿ������� ����������
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
        i++;    // ����һ�����ݺ��±��� 1 ������
    }

    // �ر��ļ�
    fclose(fp);
    return i - 2;   // ��� 1 �� �±��ֱ�ʵ�������� 1 ���� -2
}


// д���ļ�
int writeData()
{
    // ���ļ�
    if((fp = fopen("studentinfo.txt", "w")) == nullptr)
    {
        //��ʾ����
        printf("�ļ���ʧ��!");
        return 0;
    }

    // д�ļ�
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

    //�ر��ļ�
    fclose(fp);
    return 1;
}


// ��ѧ�� num �ҵ����±� index
int findIndex(int num)
{
    int IndexNow = -1;
    for(int i = 0; i <= Index; i++){
        if(students[i].num == num){
            IndexNow = i;   // ���ҵ���ͬ��ѧ��
            break;
        }
    }
    return IndexNow;    // ��δ�ҵ���ͬ��ѧ�� �ͷ��� -1
}


void sleep()
{
    Sleep(600);
}


// ���ص����˵�
void back_to_menu()
{
    cout << endl, menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << endl, menuSleep();
    cout << endl, menuSleep();
    sleep();
}


// �˵����ʱͣ���
void menuSleep()
{
    Sleep(18);
}


// ����������� ��ͣ
void Pause()
{
    cout << endl, menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "Ϣ", menuSleep();
    cout << "��", menuSleep();
    cout << "~", menuSleep();
    cout << " ", menuSleep();
    sleep();
    cout << endl, menuSleep();
    cout << endl, menuSleep();
    cout << endl, menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << "��", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << " ", menuSleep();
    cout << ".", menuSleep();
    cout << endl, menuSleep();
    system("pause > nul");
}