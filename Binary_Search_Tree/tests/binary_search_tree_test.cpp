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
    InsertTwoInts() = default;

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
};

TEST_F (InsertTwoInts, InsertRight){
    tree.Insert(root);
    tree.Insert(right);
    auto inorder = tree.ReturnInOrder();
    ASSERT_EQ(root,inorder[0]);
    ASSERT_EQ(right,inorder[1]);
}

class BalancedWithDepth2 : public ::testing::Test
{
    public:
    BinarySearchTree<int> tree;
    int root;
    int left;
    int right;
    int left_left;
    int left_right;
    int right_left;
    int right_right;
    int non_existant;
    BalancedWithDepth2()
    {
    }

    void SetUp()
    {
        non_existant = 10;
        root = 5;
        left = 2;
        left_left = 1;
        left_right = 3;
        right = 7;
        right_left = 6;
        right_right = 8;
        tree.Insert(root);
        tree.Insert(left);
        tree.Insert(right);
        tree.Insert(left_left);
        tree.Insert(left_right);
        tree.Insert(right_left);
        tree.Insert(right_right);
    }

    void TearDown()
    {
    }

    ~BalancedWithDepth2()
    {
    }
};

TEST_F (BalancedWithDepth2, InOrderCheck)
{
    auto inOrder = tree.ReturnInOrder();
    ASSERT_EQ(left_left, inOrder[0]);
    ASSERT_EQ(left_right, inOrder[2]);
    ASSERT_EQ(right_left, inOrder[4]);
    ASSERT_EQ(right_right, inOrder[6]);
}

TEST_F(BalancedWithDepth2, TestFind) {
    auto found_node = tree.Find(non_existant);
    ASSERT_EQ(found_node, nullptr);
    found_node = tree.Find(root);
    ASSERT_EQ(root, found_node->GetValue());
    found_node = tree.Find(left);
    ASSERT_EQ(left, found_node->GetValue());
    found_node = tree.Find(right);
    ASSERT_EQ(right, found_node->GetValue());
    found_node = tree.Find(left_left);
    ASSERT_EQ(left_left, found_node->GetValue());
    found_node = tree.Find(left_right);
    ASSERT_EQ(left_right, found_node->GetValue());
    found_node = tree.Find(right_left);
    ASSERT_EQ(right_left, found_node->GetValue());
    found_node = tree.Find(right_right);
    ASSERT_EQ(right_right, found_node->GetValue());
}

TEST_F (BalancedWithDepth2, SizeCheck)
{
    ASSERT_EQ(tree.size(), 7);
}

TEST_F (BalancedWithDepth2, DepthCheck)
{
    ASSERT_EQ(tree.depth(), 2);
}

class BalanceCheck : public ::testing::Test
{
public:
    BalanceCheck() {
        balanced_tree_ = CreateBalancedTree();
        unbalanced_tree_ = CreateUnbalancedTree();
    }
    BinarySearchTree<int> GetBalancedTree(){
        return balanced_tree_;
    }
    BinarySearchTree<int> GetUnbalancedTree() {
        return unbalanced_tree_;
    }
private:

    /* Creates the following balanced tree:
    *             |2|
    *            /   \
    *         |1|    |3|
    *         /
    *       |0|
    */
    BinarySearchTree<int> CreateBalancedTree() {
        auto balanced_tree = BinarySearchTree<int>();
        balanced_tree.Insert(2);
        balanced_tree.Insert(3);
        balanced_tree.Insert(1);
        balanced_tree.Insert(0);
        return balanced_tree;
    }


    /* Creates the following balanced tree:
     *             |3|
     *            /   \
     *         |2|    |4|
     *         /        \
     *       |1|        |5|
     *       /            \
     *     |0|            |6|
     */
    BinarySearchTree<int> CreateUnbalancedTree() {
        auto unbalanced_tree = BinarySearchTree<int>();
        unbalanced_tree.Insert(3);
        unbalanced_tree.Insert(2);
        unbalanced_tree.Insert(1);
        unbalanced_tree.Insert(0);
        unbalanced_tree.Insert(4);
        unbalanced_tree.Insert(5);
        unbalanced_tree.Insert(6);
        return unbalanced_tree;
    }

    BinarySearchTree<int> balanced_tree_;
    BinarySearchTree<int> unbalanced_tree_;
};

TEST_F(BalanceCheck, HeightChecker) {
    const auto& balancedTree = GetBalancedTree();
    auto height = balancedTree.Height(balancedTree.Find(2));
    ASSERT_EQ(height, 2);
    height = balancedTree.Height(balancedTree.Find(1));
    ASSERT_EQ(height, 1);
    height = balancedTree.Height(balancedTree.Find(0));
    ASSERT_EQ(height, 0);
    height = balancedTree.Height(balancedTree.Find(3));
    ASSERT_EQ(height, 0);
}

TEST_F(BalanceCheck, IsBalancedTrue) {
    const auto& balancedTree = GetBalancedTree();
    ASSERT_TRUE(balancedTree.IsBalanced());
}

TEST_F(BalanceCheck, IsBalancedFalse) {
    const auto& unbalancedTree = GetUnbalancedTree();
    ASSERT_FALSE(unbalancedTree.IsBalanced());
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    ::testing::InitGoogleMock(&argc,argv);

    return RUN_ALL_TESTS();
}

