#include<iostream>
#include<gtest/gtest.h>
#include"cirqueue.h"

TEST( queue_test, push_test )
{
    CirQueue<int> queue(5);
    queue.push(5);
    
    queue.front();
    //int q = queue.front();

    EXPECT_EQ( queue.front(), 5 ); 
    queue.pop();
    EXPECT_EQ( queue.empty(), false ); 
}

int main(int argc, char **argv )
{
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}