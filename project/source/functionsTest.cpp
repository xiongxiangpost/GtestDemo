#include <iostream>

#include "gtest/gtest.h"
#include "functions.h"

using namespace std;

/*
TEST(TestDemo,AddTestCase){
    ASSERT_EQ(2,add(1,1));
}
TEST(TestDemo,MinusTestCase){
    ASSERT_EQ(10,myMinus(25,15));
}
TEST(TestDemo,MutilpTestCase){
    ASSERT_EQ(12,multiply(3,4));
}
TEST(TestDemo,DivideTestCase){
    ASSERT_EQ(2,divide(7,3));
}

*/

/*
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

*/

/*
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

*/