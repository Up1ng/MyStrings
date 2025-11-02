#include <gtest/gtest.h>
#include "MyString.hpp"

TEST(MyStringTest, Print) {
    Mystring s1("Hello");
    Mystring s2("World");
    Mystring s3(s1);
    
    EXPECT_STREQ("Hello", s1.c_str());
    EXPECT_STREQ("World", s2.c_str());
    EXPECT_STREQ("Hello", s3.c_str());
}

TEST(MyStringTest, equalop) {
    Mystring s1("Hello");
    Mystring s2("World");
    Mystring s3(s1);
    
    s3 = s2;
    EXPECT_STREQ("World", s3.c_str());
}

TEST(MyStringTest, PlusOperator) {
    Mystring s1("Hello");
    Mystring s2("World");
    
    Mystring s4 = s1 + s2;
    EXPECT_STREQ("HelloWorld", s4.c_str());
}

TEST(MyStringTest, PlusEqualOperator) {
    Mystring s1("Hello");
    Mystring s2("World");
    
    s1 += s2;
    EXPECT_STREQ("HelloWorld", s1.c_str());
}

TEST(MyStringTest, ComparisonOperators) {
    Mystring s1("abc");
    Mystring s2("abc");
    Mystring s3("abd");
    Mystring s4("ab");
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 != s3);
    EXPECT_TRUE(s1 < s3);
    EXPECT_TRUE(s3 > s1);
    EXPECT_TRUE(s4 <= s1);
    EXPECT_TRUE(s1 >= s4);
}

TEST(MyStringTest, IndexOperatorAndCOW) {
    Mystring s1("World");
    Mystring s2 = s1;
    
    EXPECT_EQ('W', s1[0]);
    EXPECT_EQ('W', s2[0]);
    
    s2[0] = 'w';
    
    EXPECT_STREQ("World", s1.c_str());
    EXPECT_STREQ("world", s2.c_str());
    
    EXPECT_LE(1, s1.CountRef());
    EXPECT_LE(1, s2.CountRef());
}

TEST(MyStringTest, ClearMethod) {
    Mystring s1("Hello");
    s1.Clear();
    
    EXPECT_STREQ("", s1.c_str());
    EXPECT_EQ(0, s1.Length());
}

TEST(MyStringTest, ReferenceCounting) {
    Mystring s1("Test");
    EXPECT_EQ(1, s1.CountRef());
    
    {
        Mystring s2 = s1;
        EXPECT_EQ(2, s1.CountRef());
        EXPECT_EQ(2, s2.CountRef());
        
        {
            Mystring s3;
            s3 = s1;
            EXPECT_EQ(3, s1.CountRef());
            EXPECT_EQ(3, s2.CountRef());
            EXPECT_EQ(3, s3.CountRef());
        }
        
        EXPECT_EQ(2, s1.CountRef());
        EXPECT_EQ(2, s2.CountRef());
    }
    
    EXPECT_EQ(1, s1.CountRef());
}

TEST(MyStringTest, SelfAssignment) {
    Mystring s1("Test");
    s1 = s1;
    
    EXPECT_STREQ("Test", s1.c_str());
    EXPECT_EQ(1, s1.CountRef());
}

TEST(MyStringTest, EmptyString) {
    Mystring s1;
    Mystring s2("");
    
    EXPECT_STREQ("", s1.c_str());
    EXPECT_STREQ("", s2.c_str());
    EXPECT_EQ(0, s1.Length());
    EXPECT_EQ(0, s2.Length());
}

TEST(MyStringTest, ReferenceBehavior) {
    Mystring s1("Original");
    EXPECT_EQ(1, s1.CountRef());
    
    Mystring s2 = s1;
    EXPECT_EQ(2, s1.CountRef());
    EXPECT_EQ(2, s2.CountRef());
    EXPECT_EQ(s1.c_str(), s2.c_str());
    
    s2[0] = 'X';
    EXPECT_STREQ("Original", s1.c_str());
    EXPECT_STREQ("Xriginal", s2.c_str());
    EXPECT_EQ(1, s1.CountRef());
    EXPECT_EQ(1, s2.CountRef());
    EXPECT_NE(s1.c_str(), s2.c_str());
}

TEST(MyStringTest, FindChar) {
    Mystring s("Hello");
    Mystring u("privet kak dela vse good love you goodbai poka omg9");
    EXPECT_EQ(50, u.Find('9'));
    
    EXPECT_EQ(0, s.Find('H'));
    EXPECT_EQ(2, s.Find('l'));
    EXPECT_EQ(-1, s.Find('x'));
}

TEST(MyStringTest, FindSubstring) {
    Mystring s("Hello World");

    Mystring m("privet kak dela vse good love you goodbai poka omg cheezecake");
    EXPECT_EQ(51, m.Find("cheezecake"));
    
    
    EXPECT_EQ(0, s.Find("Hello"));
    EXPECT_EQ(6, s.Find("World"));
    EXPECT_EQ(-1, s.Find("Test"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
