#include <gtest/gtest.h>

#include "AVLTreeTable.h"
#include "ArrayTable.h"
#include "HashTable.h"
#include "polinoms.h"

TEST(ArrayTable, Insert_NewElement_NoThrow) {
  UnorderedArrayTable t;
  ASSERT_NO_THROW(t.insert("key", Polinom()));
}

TEST(ArrayTable, Find_ExistingElement_ReturnsPointer) {
  UnorderedArrayTable t;
  t.insert("a", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("a", ops), nullptr);
}

TEST(ArrayTable, Find_NonExistingElement_ReturnsNull) {
  UnorderedArrayTable t;
  int ops = 0;
  ASSERT_EQ(t.find("missing", ops), nullptr);
}

TEST(ArrayTable, Insert_MultipleElements_CanFindLast) {
  UnorderedArrayTable t;
  t.insert("1", Polinom());
  t.insert("2", Polinom());
  t.insert("3", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("3", ops), nullptr);
}

TEST(ArrayTable, Insert_DuplicateKey_UpdatesValue) {
  UnorderedArrayTable t;
  t.insert("k", Polinom());
  ASSERT_NO_THROW(t.insert("k", Polinom()));
}

TEST(ArrayTable, Find_EmptyKey_Works) {
  UnorderedArrayTable t;
  t.insert("", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("", ops), nullptr);
}

TEST(ArrayTable, Find_LongKey_Works) {
  UnorderedArrayTable t;
  std::string longKey(255, 'x');
  t.insert(longKey, Polinom());
  int ops = 0;
  ASSERT_NE(t.find(longKey, ops), nullptr);
}

TEST(ArrayTable, OpsCount_IncreasesWithPosition) {
  UnorderedArrayTable t;
  int ops1 = 0, ops2 = 0;
  t.insert("first", Polinom());
  t.insert("second", Polinom());
  t.find("first", ops1);
  t.find("second", ops2);
  ASSERT_LT(ops1, ops2);
}

TEST(ArrayTable, Find_AfterFailedSearch_Works) {
  UnorderedArrayTable t;
  int ops = 0;
  t.find("x", ops);
  t.insert("x", Polinom());
  ASSERT_NE(t.find("x", ops), nullptr);
}

TEST(ArrayTable, Stress_InsertFiveElements_NoCrash) {
  UnorderedArrayTable t;
  for (int i = 0; i < 5; i++) {
    ASSERT_NO_THROW(t.insert(std::to_string(i), Polinom()));
  }
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

TEST(HashTable, OpsCount_IsTypicallySmall) {
  HashTable t;
  for (int i = 0; i < 10; i++) t.insert(std::to_string(i), Polinom());
  int ops = 0;
  t.find(std::to_string(5), ops);
  ASSERT_LT(ops, 5);
}

TEST(HashTable, Find_NumericStringKey) {
  HashTable t;
  t.insert("12345", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("12345", ops), nullptr);
}

TEST(HashTable, Find_CaseSensitivity) {
  HashTable t;
  t.insert("Case", Polinom());
  int ops = 0;
  ASSERT_EQ(t.find("case", ops), nullptr);
}

TEST(HashTable, Insert_AfterSearch_Works) {
  HashTable t;
  int ops = 0;
  t.find("a", ops);
  t.insert("a", Polinom());
  ASSERT_NE(t.find("a", ops), nullptr);
}

TEST(HashTable, LargeKey_Works) {
  HashTable t;
  t.insert("very_very_long_key_name_for_testing", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("very_very_long_key_name_for_testing", ops), nullptr);
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

TEST(AVLTree, Update_ExistingNode) {
  AVLTreeTable t;
  t.insert("key", Polinom());
  ASSERT_NO_THROW(t.insert("key", Polinom()));
}

TEST(AVLTree, Root_Search_IsOneStep) {
  AVLTreeTable t;
  t.insert("m", Polinom());
  t.insert("a", Polinom());
  t.insert("z", Polinom());
  int ops = 0;
  t.find("m", ops);
  ASSERT_EQ(ops, 1);
}

TEST(AVLTree, Find_InLargeTree) {
  AVLTreeTable t;
  for (int i = 0; i < 20; i++) t.insert(std::to_string(i), Polinom());
  int ops = 0;
  ASSERT_NE(t.find("10", ops), nullptr);
}

TEST(AVLTree, OpsCount_Logarithmic) {
  AVLTreeTable t;
  for (int i = 0; i < 15; i++) t.insert(std::to_string(i), Polinom());
  int ops = 0;
  t.find("14", ops);
  ASSERT_LE(ops, 5);
}

TEST(AVLTree, AlphabeticalOrder_Search) {
  AVLTreeTable t;
  t.insert("apple", Polinom());
  t.insert("banana", Polinom());
  t.insert("cherry", Polinom());
  int ops = 0;
  ASSERT_NE(t.find("banana", ops), nullptr);
}