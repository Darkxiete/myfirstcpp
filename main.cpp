#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <array>
#include <cctype>
#include <dirent.h>
#include <cmath>

using namespace std;

int f_4_18() {
    double *p3 = new double[3];
    p3[0] = 0.2;
    p3[1] = 0.1;
    p3[2] = 0.8;
    cout << "p3[1] is " << p3[1] << ".\n";
    p3 += 1;
    cout << "Now p3[0] is " << p3[0] << " and "
         << "p3[1] is " << p3[1] << ".\n";
    p3 -= 1;
    delete[] p3;
    return 0;
}

int f_4_19() {
    /*
     * 指针算数，不同数据类型，指针每次偏移的字节数不一样
     */
    double wages[3] = {10000.0, 20000.0, 30000.0};
    short stacks[3] = {3, 2, 1};

    // 是一个意思，都是指向数组的第一个元素
    double *pw = wages;
    short *ps = &stacks[0];
    // 但是如果 `*ps = &stacks` 就不是一个意思了，这表示指向一个数组的指针，虽然两者值相等
    cout << "pw = " << pw << ", *pw = " << *pw << endl;
    pw += 1;
    cout << "add 1 to the pw pointer:\n";
    cout << "pw = " << pw << ", *pw = " << *pw << "\n\n";

    cout << "ps = " << ps << ", *ps = " << *ps << endl;
    ps += 1;
    cout << "add 1 to the ps pointer:\n";
    cout << "ps = " << ps << ", *ps = " << *ps << "\n\n";

    cout << "access tow elements with array notation\n"
         << "stacks[0] = " << stacks[0]
         << ", stacks[1] = " << stacks[1] << endl;
    cout << "access two elementes with pointer notation\n"
         << "*stacks = " << *stacks
         << ", *(stacks + 1) = " << *(stacks + 1) << endl;

    cout << sizeof(wages) << " = size of wages array\n";
    cout << sizeof(pw) << " = size of pw pointer\n";

    /*
     * 前者是一个指向数组第一个元素的指针
     * 后者是一个指向长为3数组的指针
     */
    cout << "array address: " << wages << "\n"
         << "all array address : " << &wages << endl;
    return 0;

}

int f_4_20() {
    char animal[20] = "bear";
    // 可以访问字符串但是无法修改
    const char *bird = "wren";
    char *ps;
    int *pInt = new int;
    int *pInt1 = (int *) animal;

    cout << animal << " and "
         << bird << endl;
    cout << "Enter a kind of animal: ";
    cin >> animal;
    ps = animal;
    cout << ps << "!\n";
    cout << "Before using strcpy():\n";
    cout << animal << " at " << (int *) animal << endl;
    cout << ps << " at " << (int *) ps << endl;

//    ps = new char[strlen(animal) + 1];
    // 还有一个\0字符，所以需要+1
    // TODO 不 +1 也不报错，这是什么原因？
    ps = new char[strlen(animal)];
    strcpy(ps, animal);
    cout << "After using strcpy():\n";
    cout << animal << " at " << (int *) animal << endl;
    cout << ps << " at " << (int *) ps << "\n\n";

    cout << animal << " at " << &animal << endl;
    // 一般来说传入指针会打印地址，但是传入的如果是一个char * 指针，cout会将地址转成字符串
    cout << ps << " at " << ps << endl;
    cout << pInt << " at " << pInt << endl;
    cout << pInt1 << " at " << pInt1 << endl;
    delete[] ps;
    delete pInt;
    /*
     * 不是new出来的东西用delete删除会出现问题
     * delete pInt1;
     * Process finished with exit code -1073740940 (0xC0000374)
     */
    return 0;
}

int f_4_21() {
    /*
     * 动态创建结构体并访问构体成员
     * 即使用指针来创建结构体，结构体的成员取决于运行状态
     */
    struct inflatable {
        char name[20];
        float volume;
        double price;
    };
    // 静态方式
    inflatable choice = {
            "Darjxute",
            0.20,
            14.49
    };

    // 动态方式
    inflatable *ps = new inflatable;
    cout << "Enter name of inflatable item: ";
    cin.get(ps->name, 20);
    cout << "Enter volume in cubic feet: ";
    cin >> (*ps).volume;
    cout << "Enter price: $";
    cin >> ps->price;
    cout << "Name: " << (*ps).name << endl;
    cout << "Volume: " << ps->volume << " cubic feet" << endl;
    cout << "Price: $" << ps->price << endl;
    delete ps;
    return 0;
}

int f_4_22() {
    /*
     * 匿名函数
     */
    auto _get_name = []() {
        // 分配了只能存两个char的内存地址，但是如果输入长度 > 2 会覆盖后面的地址，也就是说不带越界检查
        char temp[2];
        cout << "Enter last name: ";
        cin >> temp;
        cout << "Length = " << strlen(temp) << endl;
        // 还要存一个'\0'， 如果不存这个'\0'的话，万一pn[strlen(temp)]后还有数据，会导致数据错误
        char *pn = new char[strlen(temp) + 1];
        strcpy(pn, temp);

        return pn;
    };

    char *name;

    name = _get_name();
    cout << name << " at " << (int *) name << "\n";
    cout << name << " = " << name << "\n";
    delete[] name;

    name = _get_name();
    cout << name << " at " << (int *) name << "\n";
    delete[] name;

    return 0;
}

int f_4_23() {
    struct antarctica_years_end {
        int year;
    };

    antarctica_years_end s01, s02, s03;
    s01.year = 1998;
    antarctica_years_end *pa = &s02;
    pa->year = 1999;
    antarctica_years_end trio[3];
    trio[0].year = 2003;
    cout << trio->year << endl;
    const antarctica_years_end *arp[3] = {&s01, &s02, &s03};
    cout << arp[1]->year << endl;
    const antarctica_years_end **ppa = arp;
    auto ppb = arp;
    cout << (*ppa)->year << endl;
    cout << (*(ppa + 1))->year << endl;
    cout << (**ppa).year << endl;
    return 0;

}

int f_4_24() {
    double a1[4] = {1.2, 2.4, 3.6, 4.8};
    vector<double> a2(4);
    a2 = {1.1, 2.2, 3.3, 4.4};
    array<double, 4> a3 = {2.14, 2.42, 34.5, 5.3};
    array<double, 4> a4 = a3;

    //使用下标访问数组
    cout << "a1[2]: " << a1[2] << " at " << &a1[2] << endl;
    cout << "a2[2]: " << a2[2] << " at " << &a2[2] << endl;
    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;

    // 越界，不报错，但是会影响到a1地址前8个字节的数据
    a1[-2] = 20.2;
    // a2.at(5) = 10.1; 会报错
    cout << "a1[-2]: " << a1[-2] << " at " << &a1[-2] << endl;
    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;

    return 0;
}

int t_4_12() {
    // 1
    cout << "Test 1" << endl;
    char actor[30];
    short betsie[100];
    float chuck[13];
    long double dipsea[64];
    // 2
    cout << "Test 2" << endl;
    array<char, 30> actor2;
    array<short, 100> betsie2;
    array<float, 13> chuck2;
    array<long double, 64> dipsea2;
    // 3
    cout << "Test 3" << endl;
    array<int, 5> arr3 = {1, 3, 5, 7, 9};
    // 4
    cout << "Test 4" << endl;
    auto even = arr3[1] + arr3[sizeof(arr3)];
    cout << "even = " << even << endl;
    // 5
    cout << "Test 5" << endl;
    array<float, 5> ideas = {1.0, 2.0, 3.0, 4.0, 5.0};
    cout << "ideas[2] = " << ideas[2] << endl;
    // 6
    cout << "Test 6" << endl;
    char d6[13] = {'c', 'h', 'e', 'e', 's', 'e', 'b', 'u', 'r', 'g', 'e', 'r'};
    cout << "d6 = " << d6 << endl;
    // 7
    cout << "Test 7" << endl;
    string d7 = "Waldorf Salad";
    cout << "d7 = " << d7 << endl;
    // 8
    cout << "Test 8" << endl;
    struct fish {
        float weight;
        string type;
        float length;
    };
    // 9
    cout << "Test 9" << endl;
    fish duobao = {
            1.0,
            "duobao",
            1.1
    };
    // 10
    cout << "Test 10" << endl;
    enum Response {
        No, Yes, Maybe
    };
    Response res = No;
    // 11
    cout << "Test 11" << endl;
    double ted = 1.1;
    double *p11;
    p11 = &ted;
    cout << "ted = " << *p11 << endl;
    // 12
    cout << "Test 12" << endl;
    float treacle[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float *p12 = treacle;
    cout << "treacle[0] = " << *p12 << endl;
    cout << "treacle[10] = " << p12[10] << endl;
    // 13
    cout << "Test 13" << endl;
    int length;
    cout << "Enter a positive number." << endl;
    cin >> length;
    int *p13 = new int[length];
    *p13 = 1;
    cout << "arr13[0] = " << *p13 << endl;
    delete[] p13;
    vector<int> arr13(length);
    arr13[0] = 1;
    cout << "arr13[0] = " << arr13[0] << endl;
    // 14
    cout << "Test 14" << endl;
    cout << (int *) "Hello" << endl;
    // 15
    cout << "Test 15" << endl;
    fish *p15 = new fish;
    p15->length = 1.1;
    p15->type = "basha";
    p15->weight = 1.2;
    cout << p15->type << "'s weight = " << p15->weight << endl;
    // 16
    cout << "Test 16" << endl;
    // 17
    const int length17 = 10;
    vector<string> a17[length17];
    array<string, length17> b17;
    return 0;

}

int t_4_13() {
    auto t1 = []() {
        string first_name;
        string last_name;
        char grade;
        int age;
        cout << "What is your first name?";
        getline(cin, first_name);
        cout << "What is your last name?";
        getline(cin, last_name);
        cout << "What letter grade do you deserve?";
        cin >> grade;
        cout << "What is your age?";
        cin >> age;
        cout << "Name: " << last_name + "," + first_name << endl;
        cout << "Grade: " << grade << endl;
        cout << "Age: " << age;
    };
    auto t3 = []() {
        // <cstring>
        char first_name[10];
        char last_name[10];
        char name[20];
        cout << "What is your first name?";
        cin.getline(first_name, 10);
        cout << "What is your last name?";
        cin.getline(last_name, 10);
        strcat(name, last_name);
        strcat(name, ", ");
        strcat(name, first_name);
        cout << "Name: " << name << endl;
    };
    auto t4 = []() {
        // // <string>
        string first_name;
        string last_name;
        cout << "What is your first name?";
        getline(cin, first_name);
        cout << "What is your last name?";
        getline(cin, last_name);
        cout << "Name: " << last_name + "," + first_name << endl;
    };
    auto t5 = []() {
        struct CandyBar {
            string band;
            float weight;
            float calorie;
        };
        CandyBar snack = {
                "Mocha Munch",
                2.3,
                350
        };
        cout << "snack's band is " << snack.band << endl;
        cout << "snack's weight is " << snack.weight << endl;
        cout << "snack's calorie is " << snack.calorie << endl;
    };
    auto t6 = []() {
        const int length = 3;
//        vector<int> nums = {0, 1, 2};
        array<int, 3> nums = {0, 1, 2};
        struct CandyBar {
            string band;
            float weight;
            float calorie;
        };
        CandyBar candies[length] = {
                {"A", 1, 2},
                {"B", 3, 4},
                {"C", 5, 6}
        };
        for (int x: nums) {
            cout << candies[x].band << endl;
        }
    };
    auto t7 = []() {
        struct Pizza {
            string name;
            float size;
            float weight;
        };
        Pizza *p = new Pizza;
        cout << "Enter the name.";
        cin >> p->name;
        cout << "Enter the size.";
        cin >> p->size;
        cout << "Enter the weight";
        cin >> p->weight;
        cout << "Name: " << (*p).name << endl;

    };
    auto t10 = []() {
        vector<int> nums = {0, 1, 2};
        array<float, 3> times;
        float sum = 0.0;
        // TODO 为什么除了第一行所有的输出都带空格
        for (int x: nums) {
            cout << "Enter your time: ";
            cin >> times[x];
            sum += times[x];
        }
        float avg_time = sum / 3;
        cout << "Average time: " << avg_time << endl;
    };
    t10();
    return 0;
}

int f_5_9() {
    string word;
    char tmp;
    int i, j;

    cout << "Enter a word." << endl;
    cin >> word;
    for (i = 0, j = word.size() - 1; i < j; i++, j--) {
        tmp = word[i];
        word[i] = word[j];
        word[j] = tmp;
    }
    cout << word << endl;
    return 0;
}

int f_5_19() {
    char ch;
    int count = 0;

//    while ((ch = cin.get())) {
    while ((cin.get(ch))) {
        cout << ch;
        ++count;
    }
    // 有的系统无法支持键盘模拟EOF，按理来说可以使用CTRL+Z(in Windows) 或者是CTRL+D(in Linux)，
    // 但是我的Windows似乎不行
    cout << endl << count << " characters read\n";
    return 0;
}

int f_5_20() {
    /*
     * 初始化二维数组的两种方法
     * 1. 指针数组
     * 2. 二维数组
     */
    const int Cities = 5;
    const int Years = 4;
    // cities共有5个元素，每个元素都是其对应字符串的地址
    const char *cities[Cities] = {
            "Gribble City",
            "Gribbletown",
            "New Gribble",
            "San Gribble",
            "Gribble vista"
    };
    const string years[Years] = {
            "2008", "2009", "2010", "2011"

    };
    int maxtemps[Years][Cities] = {
            {1, 2, 3, 4, 5},
            {2, 3, 4, 5, 6},
            {3, 4, 5, 6, 7},
            {2, 3, 4, 5, 6},
    };

    cout << "Maximum temperatures for 2008 - 2011\n\n";
    for (int city = 0; city < Cities; ++city) {
        cout << cities[city] << ":\t";
//      for (auto maxtemp : maxtemps) {
//      这里加 & 与不加有什么区别吗？
//      如果加上 & 代表循环的参数是一个reference变量，即引用变量，意味着我们可以修改数组的值
        for (auto &maxtemp: maxtemps) {
            // maxtemp 就是一个city数组
            maxtemp[city] = 99;
            cout << maxtemp[city] << "\t";
        }
        cout << endl;
    }
    auto f = [](int &r) {
        r = 2 * r;
    };
    int x = 1;
    f(x);
    cout << x << endl;
    return 0;
}

int t_5_8() {
    auto t4 = []() {
        int j = 5;
        while (++j < 9)
            cout << j++ << endl;
    };
    auto t5 = []() {
        int k = 8;
        do
            cout << k << endl;
        while (k++ < 5);
    };
    auto t6 = []() {
        int i, j;
        for (i = 1, j = 0; j < 7; i *= 2, j += 1)
            cout << i << endl;
    };
    // cin >> ch; cin.get(ch); ch=cin.get()的区别
    auto t9_1 = []() {
        /*
         * 1. 按照ch的类型来解析读取的数据
         * 2. 使用cin >> ch 会替换掉输入中的空格和换行符
         * 3. 存在输入缓冲。意味着输入的字符可能比预想的多
         */
        char ch;
        cout << "Enter a char" << endl;
        cin >> ch;
        while (ch != '#') {
            cout << ch;
            cin >> ch;
        }
    };
    auto t9_2 = []() {
        /*
         * 1. 读取一个char
         * 2. 存在输入缓冲。意味着输入的字符可能比预想的多
         */
        char ch;
        cout << "Enter a char" << endl;
        cin.get(ch);
        while (ch != '#') {
            cout << ch;
            cin.get(ch);
        }
    };
    auto t9_3 = []() {
        /*
         * 1. 读取一个char，返回可以是char也可以是int
         * 2. 需要键盘支持模拟EOF才能正常结束
         */
        char ch;
        cout << "Enter a char" << endl;
        while ((ch = cin.get())) {
            cout << ch;
        }
    };
    t9_1();
    return 0;
}

int t_5_9() {
    auto t1 = []() {
        vector<int> nums(2);
//        cout << "Enter a Number" << endl;
        /*
         * nums[0] = cin.get();
         * cin.get();
         * 如果使用以上代码会出错，此时cin.get()返回的是一个char，如果输入1的话，nums[0]=49
         * TODO 如果输入浮点数会发生什么？为什么？ 等效于问如果输入的数据类型不符合之前的定义会如何
         */
//        cin >> nums[0];
//        cout << "Enter a Number" << endl;
//        cin >> nums[1];
        for (auto &x: nums) {
            cout << "Enter a Number" << endl;
            while (!(cin >> x)) {
                cin.clear();
                while (cin.get() != '\n')
                    continue;
                cout << "Please enter an int: ";
            }
        }

        int i, j, sum;
        cout << "nums[0] = " << nums[0] << "\n"
             << "nums[1] = " << nums[1] << "\n";
        for (i = nums[0], j = nums[1], sum = 0; i <= j; ++i) {
            sum += i;
        }
        cout << "Sum = " << sum << endl;
    };

    auto t3 = []() {
        int tmp, sum;
        cout << "Enter a number." << endl;
        cin >> tmp;
        for (sum = tmp; tmp != 0; sum += tmp) {
            cout << "Enter a number." << endl;
            cin >> tmp;
        }
        cout << "Sum = " << sum << endl;
    };

    auto t4 = []() {
        double sum1 = 100;
        double sum2 = 100;
        int year = 2;
        sum1 += 0.1 * 100;
        sum2 = 1.05 * sum2;
        for (; sum1 > sum2; ++year) {
            sum1 += 0.1 * 100;
            sum2 = 1.05 * sum2;
        }
        cout << "Year = " << year << endl;
        cout << "sum1 = " << sum1 << "\n"
             << "sum2 = " << sum2 << endl;
    };

    auto t5 = []() {
        const int Month = 4;
        int tmp;
        int sum = 0;
        const char *months[Month] = {
                "1", "2", "3", "4"
        };
        vector<int> sales(Month);
        for (auto x: {0, 1, 2, 3}) {
            cin >> tmp;
            sales[x] = tmp;
        }
        for (int month = 0; month < Month; ++month) {
            cout << months[month] << ":\t";
            cout << sales[month] << endl;
            sum += sales[month];
        }
        cout << "Total sales = " << sum << endl;
    };

    auto t6 = []() {
        const int Years = 3;
        const int Month = 4;
        float tmp;
        float sales[Years][Month];
//        for (auto year: {0, 1, 2}) {
//            for (auto month: {0, 1, 2, 3}) {
//                cin >> tmp;
//                cout << "tmp: " << tmp << endl;
//                sales[year][month] = tmp;
//            }
//        }
        for (auto &sale : sales) {
            for (auto &x: sale) {
                cin >> tmp;
                x = tmp;
            }
        }
        for (auto &sale : sales) {
            for (auto x: sale) {
                cout << x << "\t";
            }
            cout << endl;
        }

    };
    t1();
    return 0;
}

int f_6_2() {
    char ch;
    cout << "Type, and i shall repeat.\n";
    cin.get(ch);
    while (ch != '.') {
        if (ch == '\n')
            cout << ch;
        else
            // 下面语句是将每个char都往后移
//            cout << ++ch;
            // 以下语句会打印出int值，因为ch会被强制转换成int和1相加，然后给cout
            cout << ch + 1;
        cin.get(ch);
    }
    cout << "\nPlease excuse the slight confusion.\n";
    return 0;
}

int f_6_3() {
    const int Fave = 29;
    int n;

    cout << "Enter a number in the range 1-100 to find ";
    cout << "my favorite number: ";
    do {
        cin >> n;
        if (n < Fave)
            cout << "Too low  -- guess again: ";
        else if (n > Fave)
            cout << "Too high -- guess again: ";
        else
            cout << Fave << " is right!\n";
    } while (n != Fave);
    return 0;
}

int f_6_4() {
    cout << "This program may reformat your hard disk\n"
            "and destroy all your data.\n"
            "Do you wish to continue? <y/n> ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        cout << "You were warned!\a\a\n";
    else if (ch == 'n' || ch == 'N')
        cout << "A wise choice ... bye\n";
    else
        cout << "That wasn't a y or n! Apparently you "
                "can't follow\ninstructions, so"
                "I'll trash your disk anyway.\a\a\a\n";
    return 0;
}

int f_6_9() {
    int a, b;
    cout << "Enter two integers: ";
    // 以空格进行分割
    cin >> a >> b;
    cout << "The larger of " << a << " and " << b;
    int c = a > b ? a : b;
    cout << " is " << c << endl;
    return 0;
}

int f_6_14() {
    const int MAX = 5;

    int golf[MAX];
    cout << "Please enter your golf scores.\n";
    cout << "You must enter " << MAX << " rounds.\n";
    int i;
    for (i = 0; i < MAX; ++i) {
        cout << "round #" << i + 1 << ": ";
        // TODO cin是有返回值的，输入成功返回1，输出失败返回0
        while (!(cin >> golf[i])) {
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Please enter a number: ";
        }
    }
    double total = 0.0;
    for (auto x: golf) {
        total += x;
    }
    cout << total / MAX << " = average score " << MAX << " rounds\n";
    return 0;
}

int f_6_15() {
    string automobile;
    int year;
    double a_price;
    double b_price;

    ofstream outFile;
    // 如果打开已有文件会截断原来的内容
    outFile.open("carinfo.txt");

    cout << "Enter the make and model of automobile: ";
    getline(cin, automobile);
    cout << "Enter the model year: ";
    cin >> year;
    cout << "Enter the original asking price: ";
    cin >> a_price;
    b_price = a_price * 0.913;

    cout << fixed; // write floating-point values in fixed-point notation.
    cout.precision(2);
    cout.setf(ios_base::showpoint); // For standard streams, the showpoint flag is not set on initialization.
    cout << "Make and model: " << automobile << endl;
    cout << "Year: " << year << endl;
    cout << "Was asking $" << a_price << endl;
    cout << "Now asking $" << b_price << endl;

    outFile << fixed;
    outFile.precision(2);
    outFile.setf(ios_base::showpoint);
    outFile << "Make and model: " << automobile << endl;
    outFile << "Year: " << year << endl;
    outFile << "Was asking $" << a_price << endl;
    outFile << "Now asking $" << b_price << endl;

    outFile.close();
    return 0;
}

int f_6_16() {
    string filename = "scores";
    ifstream inFile;
    int value;
    // TODO 无法打开，为什么？
    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "Can't open this file: " << filename << endl;
    }
    while (inFile >> value) {
        cout << "value: " << value << endl;
    }
    inFile.close();
    if (inFile.eof())
        cout << "EOF" << endl;
    else if (inFile.fail())
        cout << "FAILED" << endl;
    else
        cout << "UNKNOWN" << endl;
    return 0;
}

int f_7_5() {
    const int ArSize = 5;

    auto sum_arr = [](int arr[], int n) {
        int total = 0;
        for (int i = 0; i < n; ++i)
            total += arr[i];
        return total;
    };
    int cookies[ArSize] = {1, 2, 3, 4, 5};
    int sum = sum_arr(cookies, ArSize);
    cout << "Total cookies eaten: " << sum << "\n";
    return 0;
}

int f_7_8() {
    const int ArSize = 5;

    auto sum_arr = [](const int *begin, const int *end) {
        int total = 0;
        // 使用const申明指针表明无法*使用该指针*修改数据
        for (const int *pt = begin; pt != end; ++pt)
            total += *pt;
        return total;
    };
    int cookies[ArSize] = {1, 2, 3, 4, 5};
    int sum = sum_arr(cookies, cookies + ArSize);
    cout << "Total cookies eaten: " << sum << endl;
    return 0;
}

int f_7_8_1() {
    const int months[5] = {1, 2, 3, 4, 5};
    auto sum = [](int arr[], int n) {
        int total = 0;
        for (int i = 0; i < n; ++i) {
            total += arr[i];
        }
        return total;
    };
    // 报错，不能将 const int* 变成 int*
//    int j = sum(months, 5);
    return 0;
}

int f_7_8_2() {
    /*
     * 0xC0000005 错误，声明指针的时候一定要初始化指针
     */
    int **pp2 = nullptr;
    int n = 13;
    int m = 1;
//    int *p1 = &n; // 不可以
    int *p1 = &m;
    pp2 = &p1;
//    *pp2 = p1; // pp2可能是空指针




//    pp2 = &p1; //不行的
//    *pp2 = &n;
    *p1 = n;
//    *p1 += 1;
    cout << "pp2 value: " << pp2 << " " << "p1 address: " << &p1 << endl;
    return 0;
}

int f_7_10() {
    auto return_str = [](char ch, int n) {
        char *pstr = new char[n + 1];
        pstr[n] = '\0';
        while (n-- > 0) {
            pstr[n] = ch;
        }
        return pstr;
    };
    string s = return_str('A', 10);
    cout << s << endl;
    return 0;
}

int f_7_11() {
    struct travel_time {
        int hours;
        int mins;
    };
    const int Mins_per_hr = 60;

    auto sum = [](travel_time t1, travel_time t2) {
        travel_time total;

        total.mins = t1.mins + t2.mins + (t1.mins + t2.mins) % Mins_per_hr;
        total.hours = t1.hours + t2.hours + (t1.hours + t2.hours) / Mins_per_hr;
        return total;
    };
    auto show_time = [](travel_time t) {
        cout << t.hours << " hours, "
             << t.mins << " mins." << endl;
    };
    travel_time t1 = {5, 45};
    travel_time t2 = {4, 24};

    travel_time trip = sum(t1, t2);
    show_time(trip);
    cout << "t1.hour address: " << &t1.hours << endl;
    cout << "t1.mins address: " << &t1.mins << endl;
    return 0;
}

int f_7_12() {

    struct rect {
        double x;
        double y;
    };
    struct polar {
        double distance;
        double angle;
    };
    auto rect_to_polar = [](rect xypos) {
        polar answer;
        answer.distance = sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
        answer.angle = atan2(xypos.y, xypos.x);
        return answer;
    };
    auto show_polar = [](polar dapos) {
        const double Rad_to_deg = 57.295775951;
        cout << "distance = " << dapos.distance << ", "
             << "angle = " << dapos.angle << dapos.angle * Rad_to_deg
             << " degree" << endl;
    };

    rect rpalce;
    polar pplace;

    cout << "Enter the x and y:";
    while (cin >> rpalce.x >> rpalce.y) {
        pplace = rect_to_polar(rpalce);
        show_polar(pplace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Done" << endl;
    return 0;
}

int f_7_13() {

    struct rect {
        double x;
        double y;
    };
    struct polar {
        double distance;
        double angle;
    };
    auto rect_to_polar = [](rect *pxy, polar *pda) {
        pda->distance = sqrt(pxy->x * pxy->x + pxy->y * pxy->y);
        pda->angle = atan2(pxy->y, pxy->x);
    };
    auto show_polar = [](polar *pda) {
        const double Rad_to_deg = 57.295775951;
        cout << "distance = " << pda->distance << ", "
             << "angle = " << pda->angle << pda->angle * Rad_to_deg
             << " degree" << endl;
    };

    rect rpalce;
    polar pplace;

    cout << "Enter the x and y:";
    while (cin >> rpalce.x >> rpalce.y) {
        rect_to_polar(&rpalce, &pplace);
        show_polar(&pplace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Done" << endl;
    return 0;
}

int f_7_15() {
    const int Seasons = 4;
    // lambda 函数里似乎是无法读取到这个const array
    // 如果想让lambda函数获取（capture）到外部变量，需要放在[]里
    const array<string, Seasons> Snames = {
            "Spring", "Summer", "Fall", "Winter"
    };
    auto fill = [Snames](array<double, Seasons> *pa) {
        for (int i = 0; i < Seasons; ++i) {
            cout << "Enter " << Snames[i] << " expenses: ";
            cin >> (*pa)[i];
        }
    };
    auto show = [Snames](array<double, Seasons> *pa) {
        for (int i = 0; i < Seasons; ++i) {
            cout << Snames[i] << ": " << (*pa)[i] << endl;
        }
    };

    array<double, Seasons> expenses;
    fill(&expenses);
    show(&expenses);
    return 0;

}

int f_7_18() {
    auto estimate = [](int lines, double (*pf)(int)) {
        cout << lines << " lines will tale ";
        cout << (*pf)(lines) << " hour(s)\n";
    };
    auto betsy = [](int lines) {
        return 0.05 * lines;
    };
    auto pam = [](int lines) {
        return 0.03 *lines + 0.0004 * lines * lines;
    };

    int code;
    cout << "How many lines of code do you need? ";
    cin >> code;
    cout << "Here's Betsy's estimate: " << endl;
    estimate(code, betsy);
    cout << "Here's Pam's estimate: " << endl;
    estimate(code, pam);
    return 0;
}

int t_7_13() {
    // 1
    auto f_1 = [](){
        float x, y, ret;
        while (true){
            cout << "Enter two number: ";
            cin >> x >> y;
            if (x == 0 or y == 0){
                cout << "Quit!" << endl;
                break;
            }
            ret = 2.0 * x * y / (x + y);
            cout << "Result: " << ret << endl;
        }
    };
    // 2
    auto f_2 = []() {
        const int size = 10;
        auto f_2_1 = [](float ar[], int lens) {
            for (int i = 0; i < 10; ++i){
                cout << "Enter your scores " << i + 1 << " (q to quit).";
                if (!(cin >> ar[i]))
                    break;
            }
        };
        auto f_2_2 = [](float ar[], int lens) {
            for (int i = 0; i < lens; ++i)
                cout << ar[i] << " ";
            cout << endl;
        };
        auto f_2_3 = [](float ar[], int lens) {
            float sum = 0;
            for (int i = 0; i < lens; ++i)
                sum += ar[i];
            cout << "Sum: " << sum << endl;
        };

        float arr[size] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        f_2_1(arr, size);
        f_2_2(arr, size);
        f_2_3(arr, size);


    };
    // 3
    struct box {
        char maker[40];
        float height;
        float width;
        float length;
        float volume;
    };
    auto f_3 = []() {
        auto f_3_a = [](box b) {
            cout << "maker: " << b.maker << '\n';
            cout << "width: " << b.width << '\n';
            cout << "length: " << b.length << '\n';
            cout << "volume: " << b.volume << '\n';
        };
        auto f_3_b = [](box *b) {
            float volume = b->width * b->height * b->length;
            b->volume = volume;
            cout << "volume: " << b->volume << endl;
        };

        box b = {
                "Hello", 1.0, 2.0 , 3.0 , 4.0
        };
        f_3_a(b);
        f_3_b(&b);
    };
    // 4
    auto f_4 = []() {
        auto probability = [](unsigned numbers, unsigned picks) {
            long double result = 1.0;
            unsigned int n, p;
            for (n = numbers, p = picks; p > 0; --p, --n)
                result *= n / p;
            return result;
        };

        unsigned total, choices, special;
        cout << "Enter three number:\n";
        while (cin >> total >> choices >> special && total >=choices && special > 0){
            long double p1 = probability(total, choices);
            long double p2 = probability(special, 1);
            long double result = 1 / (p1 * p2);
            cout << "Result: " << result << endl;
            cout << "Enter three number(q to quit):\n ";
        }
    };
    auto f_5 = []() {
        unsigned  n;
        cout << "Enter a number: \n";
        cin >> n;
        // TODO 在递归中使用lambda函数
        function<unsigned(unsigned)> rec_1;
        rec_1 = [&](unsigned number) -> unsigned {
            if (number == 0)
                return 1;
            return number * rec_1(number - 1);
        };

        auto rec_2 = [&](unsigned number) -> unsigned {
            if (number == 0)
                return 1;
            return number * rec_2(number - 1); // 错误
        };
        cout << rec_2(n) << endl;
    };
    f_5();
}

int main() {
    t_7_13();
}