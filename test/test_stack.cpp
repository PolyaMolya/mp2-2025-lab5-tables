#include "stack.h"
#include <gtest.h>

TEST(StackTest, DefaultConstructorCreatesEmptyStack) {
    Stack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, EmptyStackHasZeroSize) {
    Stack<int> stack;
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PushIncreasesSize) {
    Stack<int> stack;
    stack.push(10);
    EXPECT_EQ(stack.size(), 1);
}

TEST(StackTest, PopDecreasesSize) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
}

TEST(StackTest, PopReturnsLastPushedValue) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    EXPECT_EQ(stack.pop(), 20);
}

TEST(StackTest, PeekReturnsTopElementWithoutRemoving) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.peek();
    EXPECT_EQ(stack.size(), 2);
}

TEST(StackTest, PeekReturnsCorrectValue) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    EXPECT_EQ(stack.peek(), 20);
}

TEST(StackTest, PopOnEmptyStackThrowsException) {
    Stack<int> stack;
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTest, PeekOnEmptyStackThrowsException) {
    Stack<int> stack;
    EXPECT_THROW(stack.peek(), std::out_of_range);
}

TEST(StackTest, ClearMakesStackEmpty) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, StackAutoResizesWhenFull) {
    Stack<int> stack;
    for (int i = 0; i < 100; ++i) {
        stack.push(i);
    }
    EXPECT_GE(stack.getCapacity(), 100);
}

TEST(StackTest, CopyConstructorCreatesIdenticalStack) {
    Stack<int> original;
    original.push(10);
    original.push(20);

    Stack<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
}

TEST(StackTest, CopyIsIndependentFromOriginal) {
    Stack<int> original;
    original.push(10);
    original.push(20);

    Stack<int> copy(original);
    copy.pop();
    EXPECT_NE(copy.size(), original.size());
}

TEST(StackTest, AssignmentOperatorCreatesIdenticalStack) {
    Stack<int> stack1;
    stack1.push(10);
    stack1.push(20);

    Stack<int> stack2;
    stack2 = stack1;
    EXPECT_EQ(stack2.size(), stack1.size());
}

TEST(StackTest, SelfAssignmentDoesNotBreakStack) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    stack = stack;
    EXPECT_EQ(stack.size(), 2);
}

TEST(StackTest, StackWorksWithStringType) {
    Stack<std::string> stack;
    stack.push("test");
    EXPECT_EQ(stack.pop(), "test");
}

TEST(StackTest, StackWorksWithDoubleType) {
    Stack<double> stack;
    stack.push(3.14);
    EXPECT_DOUBLE_EQ(stack.pop(), 3.14);
}

TEST(StackTest, PushPopSequenceMaintainsLIFO) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    EXPECT_EQ(stack.pop(), 2);
}

TEST(StackTest, CanPushAfterClear) {
    Stack<int> stack;
    stack.push(10);
    stack.clear();
    stack.push(20);
    EXPECT_EQ(stack.pop(), 20);
}

TEST(StackTest, CapacityIncreasesWhenNeeded) {
    Stack<int> stack;
    size_t initialCapacity = stack.getCapacity();

    for (int i = 0; i < static_cast<int>(initialCapacity) + 1; ++i) {
        stack.push(i);
    }

    EXPECT_GT(stack.getCapacity(), initialCapacity);
}

TEST(StackTest, StackWorksWithCharType) {
    Stack<char> stack;
    stack.push('a');
    stack.push('b');
    EXPECT_EQ(stack.pop(), 'b');
    EXPECT_EQ(stack.pop(), 'a');
}

TEST(StackTest, MultiplePushPopOperations) {
    Stack<int> stack;

    for (int i = 0; i < 10; ++i) {
        stack.push(i);
    }

    for (int i = 9; i >= 0; --i) {
        EXPECT_EQ(stack.pop(), i);
    }
}

TEST(StackTest, StackSizeAfterMultipleOperations) {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.pop();
    stack.push(3);
    stack.push(4);
    stack.pop();

    EXPECT_EQ(stack.size(), 2);
}