                                            **gtest测试总结**

# 一、gtest开源项目下载和编译

下载路径：[GitHub - google/googletest: GoogleTest - Google Testing and Mocking Framework](https://github.com/google/googletest)

下载最新版的gtest. 当前下载的1.11.0版本

![](.\assets\2022-01-06-13-37-10-image.png)

解压后，进入目录

执行如下命令：

```shell
mkdir build

cd build

cmake ..
```

完成后即可在build目录下生成lib目录：

![](.\assets\2022-01-06-13-41-20-image.png)

到此libgtest.a库就准备好了。

其头文件目录为：

![](.\assets\2022-01-06-13-45-31-image.png)

# 二、进行简单的gtest测试

1、创建测试目录mydemo

2、在里面新建include目录、lib目录

![](.\assets\2022-01-06-13-48-41-image.png)

3、将gtest头文件拷贝到include目录下、将libgtest.a相关库文件拷贝到lib目录下

4、编写执行功能函数，即待测试的功能模块。

![](.\assets\2022-01-06-13-50-56-image.png)

```cpp
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

int add(int a,int b);
int myMinus(int a,int b);
int multiply(int a,int b);
int divide(int a,int b);

#endif
```

```cpp
#include"functions.h"
    int add(int a,int b){
        return a+b;
    }
    int myMinus(int a,int b){
        return a-b;
    }
    int multiply(int a,int b){
        return a*b;
    }
    int divide(int a,int b){
        return a/b;
    }
```

5、编写gtest测试函数

![](.\assets\2022-01-06-13-53-28-image.png)

```cpp
#include "gtest/gtest.h"
#include "functions.h"

TEST(AddTest,AddTestCase){
    ASSERT_EQ(2,add(1,1));
}
TEST(MinusTest,MinusTestCase){
    ASSERT_EQ(10,myMinus(25,15));
}
TEST(MultiplyTest,MutilpTestCase){
    ASSERT_EQ(10,multiply(3,4));
}
TEST(DivideTest,DivideTestCase){
    ASSERT_EQ(2,divide(7,3));
}
```

6、编写gtest 测试总入口main函数

![](.\assets\2022-01-06-13-58-22-image.png)

```cpp
#include "gtest/gtest.h"
#include<iostream>
using namespace std;

int main(int argc,char* argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
```

当然这个main函数是可以直接写在前面的测试模块文件里面的，这样就减少一个文件嘛。

7、编写makefile文件

```makefile
EXEC = GtestDemo

XX = gcc
CPPXX = g++


C_SRCS = \


CPP_SRCS = \
        TestAll.cpp \
        functions.cpp \
        functionsTest.cpp

CFLAGS = \
        -I./include \
        -I./

LDFLAGS = \
          -L./lib -lgtest -lpthread \
          -Wl,-rpath="./"


OBJS = $(C_SRCS:.c=.o) $(CPP_SRCS:.cpp=.o) 

#链接用g++编译器
start:$(OBJS)
    $(CPPXX) -o $(EXEC) $(OBJS) $(LDFLAGS)


.c.o:
    $(XX) $(CFLAGS) -o $@ -c $<    

.cpp.o:
    $(CPPXX) $(CFLAGS) -o $@ -c $<

clean:
    rm -rf $(OBJS)
    rm -rf $(EXEC)
```

![](.\assets\2022-01-06-14-03-12-image.png)

执行make命令，一切正常的话，会生成目标程序。

![](.\assets\2022-01-06-14-05-26-image.png)

8、运行目标程序，验证测试结果。

![](.\assets\2022-01-06-14-06-14-image.png)

根据错误提示排除错误原因，修改测试用例后重新编译即可。

![](.\assets\2022-01-06-14-08-30-image.png)

9、指定输出测试结果文件

![](.\assets\2022-01-06-14-16-55-image.png)

这里指定输出xml结果文件，不知能否生成xlsx文件呢？

正常时：

![](.\assets\2022-01-06-14-18-13-image.png)

错误时：

![](.\assets\2022-01-06-14-23-31-image.png)

一个简单的gtest使用测试的示例就搞定了。

# 三、涉及到的问题

1、将pthread的位置写在前面就会报错

如：pthread应该采用的系统默认的库吧，按照以往经验，系统库不需要指定路径嘛，写在前面就行，只有gtest库指定路径就行嘛，但结果却不是。

![](.\assets\2022-01-06-14-31-15-image.png)

但为啥这样写就正确呢？

![](.\assets\2022-01-06-14-35-57-image.png)

![](.\assets\2022-01-06-14-43-46-image.png)

这种顺序就能正确。明明测试目录下面的lib目录只有gtest的相关库。

2、vscode终端显示颜色

刚开始vscode终端没有颜色显示，且也没有完整路径显示，点击终端上的+符号选择bash后就有颜色了，且也有完整的目录显示了。

说是默认的ssh终端没有颜色的。

3、gmock的作用是啥？

4、这里只用了gtest.a这个库，但还有gtest_main.a这个库，是否也需要呢？

经测试将gtest改成gtest_main这个库编译报错的。

gtest_main.a的作用：我们看到这里的main()函数完全是固定格式：故可以不要这个main函数，直接由库提供的main函数。这时就需要添加gtest_main.a这个库了。

未添加该库现象：

![](.\assets\2022-01-07-09-18-10-image.png)

添加该库后：

![](.\assets\2022-01-07-09-20-34-image.png)

5、能否输出xls格式的文档？

# 四、TEXT_F的测试

使用的场景：

场景：  

1. 准备数据A，TEST测试a  
2. 准备数据A，TEST测试b  
   ....  
3. 准备数据A，TEST测试n  

问题：  
准备数据A太多次，，，可以使用TEST_F，就是为了解决这种情况。

即多个测试都需要进行同样的初始配置时：

示例：

```cpp
//using TEST_F
class CMyTest : public ::testing::Test
{
    void SetUp()
    {
        m_pIntArr = new int [5];
        cout << "auto call SetUp()!" << endl;

        for(int i=0;i<5;i++)
        {
            m_pIntArr[i] = i+1;
        }
    }

    void TearDown()
    {
        if(m_pIntArr)
        {
            delete [] m_pIntArr;
            m_pIntArr = nullptr;
        }

        cout << "auto call TearDown()!" << endl;
    }

protected:
    int *m_pIntArr;
};


TEST_F(CMyTest, CMyTestCase1)
{
    EXPECT_EQ(m_pIntArr[2], 3);
}

TEST_F(CMyTest, CMyTestCase2)
{
    EXPECT_NE(m_pIntArr[3], 4);
}

TEST_F(CMyTest, CMyTestCase3)
{
    EXPECT_LT(m_pIntArr[1], 1);
}
```

运行结果：

![](.\assets\2022-01-10-14-05-38-image.png)

从中可以看出：每个用例都会调用SetUp()和TearDown(),并不是自己理解的只会掉一次这两个函数。

    这里的作用就是每次自动调用初始化函数，避免我们手动的每次手写初始化过程。

# 五、TEXT_P的测试

有多个参数来跑一个测试用例的使用就可以用TEXT_P这个宏，即实现参数的自动迭代。

示例：

```cpp
//using TEXT_P
class CMyTest : public ::testing::TestWithParam<int>
{
public:
    void SetUp()
    {
        m_iVal = GetParam();
        cout << "auto call SetUp()! cnt:" << m_iCnt++ << endl;
    }

    void TearDown()
    {
        cout << "auto call TearDown()!" << endl;
    }

protected:
    int m_iVal;
    static int m_iCnt;
};

int CMyTest::m_iCnt = 1;

INSTANTIATE_TEST_SUITE_P(my_test_p, CMyTest, ::testing::Values(1,2,3,4,5));


TEST_P(CMyTest, CMyTestCase)
{
    EXPECT_LT(m_iVal, 3);
}
```

运行结果：

![](.\assets\2022-01-10-14-48-26-image.png)

同样会每次都调用SetUp()和TearDown()，调用的此时就是由值的个数决定的，通过GetParam()迭代获取每次参数的值。

    针对测试用例相同，但参数不同的情况。

    当然也可以根据参数来控制不同的判定条件嘛。

示例：

```cpp
TEST_P(CMyTest, CMyTestCase)
{
    // EXPECT_LT(m_iVal, 3);
    if(m_iCnt <= 3)
    {
        EXPECT_LT(m_iVal, 3);
    }
    else
    {
        EXPECT_GT(m_iVal, 3);
    }
}
```

运行结果：

![](.\assets\2022-01-10-15-02-18-image.png)

# 六、gmock的测试

即通过设定**虚拟输出**的方式来实现接口的模拟。

将需要模拟的接口函数，通过MOCK_METHOD()函数实现声明。

示例：

```cpp
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

using namespace std;

class MockTarget 
{
public:
    MOCK_METHOD(int, GetX, ());

};

class CMyTestMock : public testing::Test
{
public:
    MockTarget m;

};


TEST_F(CMyTestMock, gmock_basic)
{
    EXPECT_CALL(m, GetX())
        .Times(2)
        .WillOnce(testing::Return(1))
        .WillOnce(testing::Return(2));

    EXPECT_EQ(1, m.GetX());
    EXPECT_EQ(2, m.GetX());
}
```

运行结果：

![](.\assets\2022-01-10-15-46-10-image.png)

这里只是一个示例，但里面需要2次的判定，只要有一个判定失败了，这个case也就测试失败了哦。

这里指定了2次，故后续就必须调用2次，否则运行也会失败的。

```cpp
TEST_F(CMyTestMock, gmock_basic)
{
    EXPECT_CALL(m, GetX())
        .Times(2)
        .WillOnce(testing::Return(1))
        .WillOnce(testing::Return(2));

    EXPECT_EQ(1, m.GetX());
    // EXPECT_EQ(2, m.GetX());
}
```

运行结果：

![](.\assets\2022-01-10-15-51-09-image.png)

2、对一个class的所有接口进行模拟：

```cpp
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

using namespace std;

class Base
{
public:
    virtual ~Base() {}
    virtual int GetX()
    {
        return 10;
    }
    virtual void SetX(int v)
    {
    }
    virtual void SetXY(int x, int y)
    {
    }
};

class MockTarget : public Base
{
public:
    MOCK_METHOD(int, GetX, (), (override));
    MOCK_METHOD(void, SetX, (int), (override));
    MOCK_METHOD(void, SetXY, (int, int), (override));
};

class CMyTestMock : public testing::Test
{
public:
    MockTarget m;
    CMyTestMock()
    {

    }

    virtual ~CMyTestMock()
    {

    }
};


TEST_F(CMyTestMock, gmock_basic)
{
    EXPECT_CALL(m, GetX())
        .Times(2)
        .WillOnce(testing::Return(1))
        .WillOnce(testing::Return(2));

    EXPECT_EQ(1, m.GetX());
    EXPECT_EQ(2, m.GetX());
}
```

```cpp
TEST_F(CMyTestMock, gmock_with)
{
    EXPECT_CALL(m, SetXY(testing::_, testing::_))
        .With(testing::Lt()); //第一个参数必须小于第二个参数

    m.SetXY(2,2); //error  
}
```

```cpp
using ::testing::_;
using ::testing::AllOf;
using ::testing::AtLeast;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::Return;
using ::testing::Test;
//通知声明命名空间，后续就不用命名空间就能访问了。
```

```cpp
TEST_F(CMyTestMock, multi_expect_unorder)
{
    EXPECT_CALL(m, SetX(testing::_));
    EXPECT_CALL(m, SetX(1))
        .Times(2);

    m.SetX(1);
    m.SetX(1);
    m.SetX(1); //more times
}
```

![](.\assets\2022-01-10-16-25-52-image.png)



```cpp
TEST_F(CMyTestMock, multi_expect_order)
{
    testing::InSequence dummy;
    EXPECT_CALL(m, SetX(testing::_));
    EXPECT_CALL(m, SetX(1))
        .Times(2);

    m.SetX(2); // error, 必须严格按照期望的顺序调用
    m.SetX(1);

    m.SetX(1);
}
```

```cpp
TEST_F(CMyTestMock, multi_expect_retry)
{
    EXPECT_CALL(m, SetX(testing::_));
    EXPECT_CALL(m, SetX(1))
        .Times(2)
        .RetiresOnSaturation();

    m.SetX(1);
    m.SetX(1);
    m.SetX(1); //这样就是正确的
}
```



```cpp
TEST_F(CMyTestMock, gmock_after)
{
    testing::Expectation one = EXPECT_CALL(m, SetX(1));
    testing::Expectation two = EXPECT_CALL(m, SetX(2));
    EXPECT_CALL(m, SetX(3))
        .After(two); // 该期望必须在two后面

    m.SetX(1);
    m.SetX(2);
    m.SetX(3); // 3必须在2后面，不影响其他的顺序
}
```



一些简单的gmock测试就算验证完成了。



注意一个重要问题：就是图片没有附在文档里面，只是一个链接到图片保存的路径下面，故最好不要采用图片，或每个文件的图片都与文件保持在一个目录下才行。
