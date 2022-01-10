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

TEST_F(CMyTestMock, gmock_with)
{
    EXPECT_CALL(m, SetXY(testing::_, testing::_))
        .With(testing::Lt()); //第一个参数必须小于第二个参数

    m.SetXY(1,2); //error  
}

TEST_F(CMyTestMock, multi_expect_unorder)
{
    EXPECT_CALL(m, SetX(testing::_));
    EXPECT_CALL(m, SetX(1))
        .Times(2);

    m.SetX(1);
    m.SetX(1);
    m.SetX(2);
}

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

TEST_F(CMyTestMock, multi_expect_retry)
{
    EXPECT_CALL(m, SetX(testing::_));
    EXPECT_CALL(m, SetX(1))
        .Times(2)
        .RetiresOnSaturation();

    m.SetX(1);
    m.SetX(1);
    m.SetX(1);
}

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