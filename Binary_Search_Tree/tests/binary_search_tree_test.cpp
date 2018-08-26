/**
Copyright (c) <2018> <Mohab Meshref>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the Software), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"binary_search_tree.h"
#include <vector>
class InsertOneInt : public ::testing::Test
{
    public:
    BinarySearchTree<int> tree;
    int input;
    InsertOneInt()
    {
    }

    void SetUp()
    {
        input = 5;
    }

    void TearDown()
    {
    }

    ~InsertOneInt()
    {
    }
};

TEST_F (InsertOneInt, SizeIsZeroBeforeInserionAndOneAfter)
{
    ASSERT_EQ(tree.size(), 0);
    tree.Insert(input);
    ASSERT_EQ(tree.size(), 1);
}

TEST_F (InsertOneInt, CheckIfInsertedNumberSetTheNodeValueCorrectly)
{
    tree.Insert(input);
    auto inorder = tree.ReturnInOrder();
    ASSERT_EQ(input,inorder[0]);
}

class InsertTwoInts : public ::testing::Test
{
    public:
    BinarySearchTree<int> tree;
    int root;
    int left;
    int right;
    InsertTwoInts()
    {
    }

    void SetUp()
    {
        root = 5;
        left = 2;
        right = 7;
    }

    void TearDown()
    {
    }

    ~InsertTwoInts()
    {
    }
};

TEST_F (InsertTwoInts, InsertLeft){
    tree.Insert(root);
    tree.Insert(left);
    auto inorder = tree.ReturnInOrder();
    ASSERT_EQ(left,inorder[0]);
    ASSERT_EQ(root,inorder[1]);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    ::testing::InitGoogleMock(&argc,argv);

    return RUN_ALL_TESTS();
}

