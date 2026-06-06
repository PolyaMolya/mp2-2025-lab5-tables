#include <gtest/gtest.h>

#include "AVLTreeTable.h"
#include "SortedArrayTable.h"
#include "HashTable.h"
#include "polinoms.h"

TEST(SortedArrayTable, Insert_NewElement_NoThrow) {
  SortedArrayTable t;
  ASSERT_NO_THROW(t.insert("key", Polinom()));
}

TEST(SortedArrayTable, Find_ExistingElement_ReturnsPointer) {
  SortedArrayTable t;
  t.insert("a", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("a", ops), nullptr);
}

TEST(SortedArrayTable, Find_NonExistingElement_ReturnsNull) {
  SortedArrayTable t;
  int ops = 0;
  ASSERT_EQ(t.find("missing", ops), nullptr);
}

TEST(SortedArrayTable, Insert_MultipleElements_CanFindLast) {
  SortedArrayTable t;
  t.insert("1", Polinom());
  t.insert("2", Polinom());
  t.insert("3", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("3", ops), nullptr);
}

TEST(SortedArrayTable, Insert_DuplicateKey_UpdatesValue) {
  SortedArrayTable t;
  t.insert("k", Polinom());
  ASSERT_NO_THROW(t.insert("k", Polinom()));
}

TEST(SortedArrayTable, BinarySearch_ElementsAreOrdered) {
  SortedArrayTable t;
  t.insert("x", Polinom());
  t.insert("a", Polinom());
  t.insert("m", Polinom());
  int opsA = 0, opsX = 0;
  t.find("a", opsA);
  t.find("x", opsX);
  ASSERT_GT(opsA, 0);
  ASSERT_GT(opsX, 0);
}

TEST(SortedArrayTable, Find_AfterFailedSearch_Works) {
  SortedArrayTable t;
  int ops = 0;
  t.find("x", ops);
  t.insert("x", Polinom());
  ASSERT_NE(t.find("x", ops), nullptr);
}

TEST(HashTable, Insert_SingleElement) {
  HashTable t;
  ASSERT_NO_THROW(t.insert("k", Polinom()));
}

TEST(HashTable, Find_Existing) {
  HashTable t;
  t.insert("hash_key", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("hash_key", ops), nullptr);
}

TEST(HashTable, Find_NonExisting) {
  HashTable t;
  int ops = 0;
  ASSERT_EQ(t.find("not_there", ops), nullptr);
}

TEST(HashTable, Collision_CanFindBoth) {
  HashTable t;
  t.insert("key1", Polinom());
  t.insert("key2", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("key1", ops), nullptr);
  ASSERT_NE(t.find("key2", ops), nullptr);
}

TEST(HashTable, Insert_SameKeyTwice) {
  HashTable t;
  t.insert("a", Polinom());
  ASSERT_NO_THROW(t.insert("a", Polinom()));
}

TEST(AVLTree, Insert_RootElement) {
  AVLTreeTable t;
  ASSERT_NO_THROW(t.insert("m", Polinom()));
}

TEST(AVLTree, Find_Root) {
  AVLTreeTable t;
  t.insert("m", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("m", ops), nullptr);
}

TEST(AVLTree, Balance_LeftRotation) {
  AVLTreeTable t;
  t.insert("a", Polinom());
  t.insert("b", Polinom());
  t.insert("c", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("a", ops), nullptr);
}

TEST(AVLTree, Balance_RightRotation) {
  AVLTreeTable t;
  t.insert("c", Polinom());
  t.insert("b", Polinom());
  t.insert("a", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("a", ops), nullptr);
}

TEST(AVLTree, Find_NonExisting) {
  AVLTreeTable t;
  int ops = 0;
  ASSERT_EQ(t.find("ghost", ops), nullptr);
}

TEST(AVLTree, Find_InLargeTree) {
  AVLTreeTable t;
  for (int i = 0; i < 20; i++) t.insert(std::to_string(i), Polinom());
  int ops = 0;
  ASSERT_NE(t.find("10", ops), nullptr);
}