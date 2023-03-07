#include "flist/flist.hpp"
#include <gtest/gtest.h>


TEST(flist, Constructors)
{
    flist<int> empty_lst{};
    flist<int> lst1{1, 2, 3, 4, 5};
    flist<int> lst1_cpy(lst1);
    flist<int> lst1_move(flist<int>{1, 2, 3, 4, 5});


    lst1_cpy.push_front(10);


    EXPECT_TRUE(empty_lst.empty());
    EXPECT_EQ(empty_lst.size(), 0);
    EXPECT_EQ(empty_lst.begin(), empty_lst.end());

    EXPECT_FALSE(lst1.empty());
    EXPECT_EQ(lst1.size(), 5);
    EXPECT_EQ(lst1.front(), 1);

    EXPECT_FALSE(lst1_cpy.empty());
    EXPECT_EQ(lst1_cpy.size(), 6);
    EXPECT_EQ(lst1_cpy.front(), 10);
    EXPECT_EQ(std::distance(lst1_cpy.begin(), lst1_cpy.end()), 6);

    EXPECT_EQ(lst1_move.size(), 5);
    EXPECT_EQ(std::distance(lst1_move.begin(), lst1_move.end()), 5);
}

TEST(flist, AssignmentOperators)
{
    flist<int> lst{1, 2, 3, 4};
    flist<int> lst_cpy = lst;
    flist<int> lst_move = flist<int>{10, 20, 30};

    lst_cpy.push_front(0);

    EXPECT_EQ(lst.size(), 4);
    EXPECT_EQ(lst.front(), 1);

    EXPECT_EQ(lst_cpy.size(), 5);
    EXPECT_EQ(lst_cpy.front(), 0);

    EXPECT_EQ(lst_move.size(), 3);
    EXPECT_EQ(lst_move.front(), 10);
}

TEST(flist, front)
{
    flist<int> empty_lst{};
    flist<int> lst1{1, 2, 3};
    flist<int> lst2{1, 2, 3};


    lst2.push_front(100);
    ++lst2.front();


    EXPECT_THROW(empty_lst.front(), std::length_error);
    EXPECT_NO_THROW(lst1.front());
    EXPECT_EQ(lst2.front(), 101);
}

TEST(flist, size)
{
    flist<int> empty_list{};
    flist<int> lst1{1, 2, 3, 4};
    flist<int> lst2{1};


    lst2.push_front(1);
    lst2.push_front(3);
    lst2.pop_front();


    EXPECT_EQ(empty_list.size(), 0);
    EXPECT_EQ(lst1.size(), 4);
    EXPECT_EQ(lst2.size(), 2);
}

TEST(flist, empty)
{
    flist<int> empty_lst{};
    flist<int> lst1{1, 2, 3};
    flist<int> lst2{1};
    flist<int> lst3{};


    lst2.pop_front();
    lst3.push_front(1);


    EXPECT_TRUE(empty_lst.empty());
    EXPECT_FALSE(lst1.empty());
    EXPECT_TRUE(lst2.empty());
    EXPECT_FALSE(lst3.empty());
}

// also testing push_front
TEST(flist, insert_after)
{
    flist<int> empty_lst{};
    flist<int> lst1{};
    flist<int> lst2{};


    lst1.insert_after(lst1.before_begin(), 100);
    lst2.insert_after(lst2.before_begin(), 1);
    lst2.insert_after(lst2.begin(), 2);
    lst2.insert_after(lst2.before_begin(), 3);


    EXPECT_THROW(empty_lst.insert_after(empty_lst.begin(), 1), std::domain_error);
    EXPECT_NO_THROW(empty_lst.insert_after(empty_lst.before_begin(), 1));

    EXPECT_EQ(lst1.front(), 100);
    EXPECT_EQ(lst2.front(), 3);
    EXPECT_EQ(*++lst2.begin(), 1);
}

TEST(flist, pop_front)
{
    flist<int> empty_list{};
    flist<int> lst{1, 2, 3, 4, 5, 6};


    lst.pop_front();
    lst.pop_front();
    lst.pop_front();


    EXPECT_THROW(empty_list.pop_front(), std::domain_error);
    EXPECT_EQ(lst.size(), 3);
    EXPECT_EQ(lst.front(), 4);
}

TEST(flist, clear)
{
    flist<int> empty_lst{};
    flist<int> lst{1, 2, 3};

    
    lst.clear();


    EXPECT_NO_THROW(empty_lst.clear());
    
    EXPECT_THROW(lst.pop_front(), std::domain_error);
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.size(), 0);
}

// also testing emplace_front
TEST(flist, emplace_after)
{
    flist<int> empty_lst{};
    flist<int> lst{};


    lst.emplace_after(lst.before_begin(), 1);
    lst.emplace_after(lst.begin(), 2);
    lst.emplace_after(++lst.begin(), 3);


    EXPECT_THROW(empty_lst.emplace_after(empty_lst.begin(), 1), std::domain_error);
    
    EXPECT_FALSE(lst.empty());
    EXPECT_EQ(lst.size(), 3);
    EXPECT_EQ(lst.front(), 1);
    EXPECT_EQ(++*lst.begin(), 2);
    EXPECT_EQ(*(++(++lst.begin())), 3);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
