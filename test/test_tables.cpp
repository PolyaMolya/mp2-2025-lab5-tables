#include "hash_table.h"
#include "polinom.h"
#include "rbtree_table.h"
#include "unsorted_table.h"
#include <gtest.h>
#include <sstream>

using namespace std;

// ==================== UnsortedArrayTable ====================

TEST(UnsortedArrayTableTest, InsertAndFind) {
  UnsortedArrayTable<string, Polinom> table;
  Polinom p = Polinom::parseFromString("2x^2 + 3y");

  table.insert("A", p);

  Polinom found;
  EXPECT_TRUE(table.find("A", found));

  ostringstream oss1, oss2;
  oss1 << p;
  oss2 << found;
  EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(UnsortedArrayTableTest, ContainsReturnsTrueForExistingKey) {
  UnsortedArrayTable<string, Polinom> table;
  table.insert("A", Polinom::parseFromString("x + y"));
  EXPECT_TRUE(table.contains("A"));
}

TEST(UnsortedArrayTableTest, ContainsReturnsFalseForNonExistingKey) {
  UnsortedArrayTable<string, Polinom> table;
  EXPECT_FALSE(table.contains("A"));
}

TEST(UnsortedArrayTableTest, RemoveExistingKey) {
  UnsortedArrayTable<string, Polinom> table;
  table.insert("A", Polinom::parseFromString("x + y"));
  EXPECT_TRUE(table.remove("A"));
  EXPECT_FALSE(table.contains("A"));
}

TEST(UnsortedArrayTableTest, SizeAfterInsert) {
  UnsortedArrayTable<string, Polinom> table;
  EXPECT_EQ(table.size(), 0);
  table.insert("A", Polinom());
  EXPECT_EQ(table.size(), 1);
  table.insert("B", Polinom());
  EXPECT_EQ(table.size(), 2);
}

TEST(UnsortedArrayTableTest, UpdateExistingKey) {
  UnsortedArrayTable<string, Polinom> table;
  Polinom p1 = Polinom::parseFromString("x + y");
  Polinom p2 = Polinom::parseFromString("2x + 2y");

  table.insert("A", p1);
  table.insert("A", p2);

  Polinom found;
  table.find("A", found);

  ostringstream oss;
  oss << found;
  EXPECT_EQ(oss.str(), "2x + 2y");
}

// ==================== RBTreeTable ====================

TEST(RBTreeTableTest, InsertAndFind) {
  RBTreeTable<string, Polinom> table;
  Polinom p = Polinom::parseFromString("2x^2 + 3y");

  table.insert("A", p);

  Polinom found;
  EXPECT_TRUE(table.find("A", found));
}

TEST(RBTreeTableTest, KeysAreSorted) {
  RBTreeTable<string, Polinom> table;
  table.insert("C", Polinom());
  table.insert("A", Polinom());
  table.insert("B", Polinom());

  auto keys = table.keys();
  ASSERT_EQ(keys.size(), 3);
  EXPECT_EQ(keys[0], "A");
  EXPECT_EQ(keys[1], "B");
  EXPECT_EQ(keys[2], "C");
}

TEST(RBTreeTableTest, UpdateExistingKey) {
  RBTreeTable<string, Polinom> table;
  Polinom p1 = Polinom::parseFromString("x + y");
  Polinom p2 = Polinom::parseFromString("2x + 2y");

  table.insert("A", p1);
  table.insert("A", p2);

  Polinom found;
  table.find("A", found);

  ostringstream oss;
  oss << found;
  EXPECT_EQ(oss.str(), "2x + 2y");
}

TEST(RBTreeTableTest, SizeAfterInsert) {
  RBTreeTable<string, Polinom> table;
  EXPECT_EQ(table.size(), 0);
  table.insert("A", Polinom());
  EXPECT_EQ(table.size(), 1);
  table.insert("B", Polinom());
  EXPECT_EQ(table.size(), 2);
}

// ==================== HashTable ====================

TEST(HashTableTest, InsertAndFind) {
  HashTable<string, Polinom> table;
  Polinom p = Polinom::parseFromString("2x^2 + 3y");

  table.insert("A", p);

  Polinom found;
  EXPECT_TRUE(table.find("A", found));
}

TEST(HashTableTest, LinearProbingWorks) {
  HashTable<string, Polinom> table(4);

  table.insert("A", Polinom::parseFromString("x + y"));
  table.insert(
      "E", Polinom::parseFromString("2x + 2y")); // Может вызвать коллизию с A
  table.insert("I", Polinom::parseFromString("3x + 3y"));

  EXPECT_TRUE(table.contains("A"));
  EXPECT_TRUE(table.contains("E"));
  EXPECT_TRUE(table.contains("I"));
}

TEST(HashTableTest, RehashOnFull) {
  HashTable<string, Polinom> table(2);
  table.insert("A", Polinom::parseFromString("x + y"));
  table.insert("B", Polinom::parseFromString("2x + 2y"));
  table.insert("C",
               Polinom::parseFromString("3x + 3y")); // Должен вызвать rehash

  EXPECT_EQ(table.size(), 3);
  EXPECT_TRUE(table.contains("A"));
  EXPECT_TRUE(table.contains("B"));
  EXPECT_TRUE(table.contains("C"));
}

TEST(HashTableTest, RemoveAndThenFind) {
  HashTable<string, Polinom> table;
  Polinom p = Polinom::parseFromString("x + y");

  table.insert("A", p);
  EXPECT_TRUE(table.contains("A"));

  table.remove("A");
  EXPECT_FALSE(table.contains("A"));
}

TEST(HashTableTest, UpdateExistingKey) {
  HashTable<string, Polinom> table;
  Polinom p1 = Polinom::parseFromString("x + y");
  Polinom p2 = Polinom::parseFromString("2x + 2y");

  table.insert("A", p1);
  table.insert("A", p2);

  Polinom found;
  table.find("A", found);

  ostringstream oss;
  oss << found;
  EXPECT_EQ(oss.str(), "2x + 2y");
}

TEST(HashTableTest, SizeAfterInsert) {
  HashTable<string, Polinom> table;
  EXPECT_EQ(table.size(), 0);
  table.insert("A", Polinom());
  EXPECT_EQ(table.size(), 1);
  table.insert("B", Polinom());
  EXPECT_EQ(table.size(), 2);
}

TEST(HashTableTest, ClearTable) {
  HashTable<string, Polinom> table;
  table.insert("A", Polinom());
  table.insert("B", Polinom());
  table.clear();
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains("A"));
  EXPECT_FALSE(table.contains("B"));
}

TEST(HashTableTest, KeysAfterMultipleInserts) {
  HashTable<string, Polinom> table;
  table.insert("A", Polinom::parseFromString("x"));
  table.insert("B", Polinom::parseFromString("y"));
  table.insert("C", Polinom::parseFromString("z"));

  auto keys = table.keys();
  EXPECT_EQ(keys.size(), 3);

  // Проверяем, что все ключи присутствуют
  bool hasA = false, hasB = false, hasC = false;
  for (const auto &key : keys) {
    if (key == "A")
      hasA = true;
    if (key == "B")
      hasB = true;
    if (key == "C")
      hasC = true;
  }
  EXPECT_TRUE(hasA);
  EXPECT_TRUE(hasB);
  EXPECT_TRUE(hasC);
}

// ==================== Сравнительные тесты для всех таблиц ====================

TEST(TablesComparisonTest, AllTablesBehaveConsistently) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  Polinom p1 = Polinom::parseFromString("x + y");
  Polinom p2 = Polinom::parseFromString("2x + 2y");

  // Вставка
  unsorted.insert("P1", p1);
  rbtree.insert("P1", p1);
  hash.insert("P1", p1);

  // Обновление
  unsorted.insert("P1", p2);
  rbtree.insert("P1", p2);
  hash.insert("P1", p2);

  // Проверка
  Polinom found;

  EXPECT_TRUE(unsorted.find("P1", found));
  ostringstream oss1;
  oss1 << found;
  EXPECT_EQ(oss1.str(), "2x + 2y");

  EXPECT_TRUE(rbtree.find("P1", found));
  ostringstream oss2;
  oss2 << found;
  EXPECT_EQ(oss2.str(), "2x + 2y");

  EXPECT_TRUE(hash.find("P1", found));
  ostringstream oss3;
  oss3 << found;
  EXPECT_EQ(oss3.str(), "2x + 2y");

  EXPECT_EQ(unsorted.size(), 1);
  EXPECT_EQ(rbtree.size(), 1);
  EXPECT_EQ(hash.size(), 1);
}

TEST(TablesComparisonTest, MultipleInsertsAndRemoves) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  vector<string> keys = {"Z", "A", "M", "B", "C", "K", "D"};

  // Вставка всех ключей
  for (const auto &key : keys) {
    unsorted.insert(key, Polinom::parseFromString(key + "_poly"));
    rbtree.insert(key, Polinom::parseFromString(key + "_poly"));
    hash.insert(key, Polinom::parseFromString(key + "_poly"));
  }

  EXPECT_EQ(unsorted.size(), keys.size());
  EXPECT_EQ(rbtree.size(), keys.size());
  EXPECT_EQ(hash.size(), keys.size());

  // Проверка, что все ключи существуют
  for (const auto &key : keys) {
    EXPECT_TRUE(unsorted.contains(key));
    EXPECT_TRUE(rbtree.contains(key));
    EXPECT_TRUE(hash.contains(key));
  }

  // Удаление одного ключа
  unsorted.remove("B");
  rbtree.remove("B");
  hash.remove("B");

  EXPECT_FALSE(unsorted.contains("B"));
  EXPECT_FALSE(rbtree.contains("B"));
  EXPECT_FALSE(hash.contains("B"));

  EXPECT_EQ(unsorted.size(), keys.size() - 1);
  EXPECT_EQ(rbtree.size(), keys.size() - 1);
  EXPECT_EQ(hash.size(), keys.size() - 1);
}

TEST(TablesComparisonTest, KeysCollection) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  vector<string> keys = {"D", "A", "C", "B"};

  for (const auto &key : keys) {
    unsorted.insert(key, Polinom());
    rbtree.insert(key, Polinom());
    hash.insert(key, Polinom());
  }

  auto unsortedKeys = unsorted.keys();
  auto rbtreeKeys = rbtree.keys();
  auto hashKeys = hash.keys();

  // Все таблицы должны содержать все ключи
  EXPECT_EQ(unsortedKeys.size(), 4);
  EXPECT_EQ(rbtreeKeys.size(), 4);
  EXPECT_EQ(hashKeys.size(), 4);

  // Упорядоченное дерево должно возвращать отсортированные ключи
  EXPECT_EQ(rbtreeKeys[0], "A");
  EXPECT_EQ(rbtreeKeys[1], "B");
  EXPECT_EQ(rbtreeKeys[2], "C");
  EXPECT_EQ(rbtreeKeys[3], "D");
}

TEST(TablesComparisonTest, ClearAllTables) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  unsorted.insert("A", Polinom());
  unsorted.insert("B", Polinom());
  rbtree.insert("A", Polinom());
  rbtree.insert("B", Polinom());
  hash.insert("A", Polinom());
  hash.insert("B", Polinom());

  unsorted.clear();
  rbtree.clear();
  hash.clear();

  EXPECT_EQ(unsorted.size(), 0);
  EXPECT_EQ(rbtree.size(), 0);
  EXPECT_EQ(hash.size(), 0);

  EXPECT_FALSE(unsorted.contains("A"));
  EXPECT_FALSE(rbtree.contains("A"));
  EXPECT_FALSE(hash.contains("A"));
}

// ==================== Тесты для счётчиков операций ====================

TEST(CounterTest, UnsortedArrayInsertCounter) {
  UnsortedArrayTable<string, Polinom> table;

  table.resetCounters();
  table.insert("A", Polinom());

  // В неупорядоченном массиве вставка нового элемента не требует сравнений
  // (только цикл поиска существующего, который проходит по всем элементам)
  EXPECT_GE(table.getComparisons(), 0);
  EXPECT_GE(table.getOperations(), 1);
}

TEST(CounterTest, UnsortedArrayFindCounter) {
  UnsortedArrayTable<string, Polinom> table;
  table.insert("A", Polinom());

  table.resetCounters();
  Polinom found;
  table.find("A", found);

  // Поиск существующего элемента проходит по массиву
  EXPECT_GE(table.getComparisons(), 1);
  EXPECT_GE(table.getOperations(), 1);
}

TEST(CounterTest, SortedTreeInsertCounter) {
  RBTreeTable<string, Polinom> table;

  table.resetCounters();
  table.insert("A", Polinom());

  // В дереве вставка требует сравнений при спуске
  EXPECT_GE(table.getComparisons(), 0);
  EXPECT_GE(table.getOperations(), 1);
}

TEST(CounterTest, HashTableInsertCounter) {
  HashTable<string, Polinom> table;

  table.resetCounters();
  table.insert("A", Polinom());

  // Хеш-таблица делает сравнения при линейном пробировании
  EXPECT_GE(table.getComparisons(), 1);
  EXPECT_GE(table.getOperations(), 1);
}

// ==================== Тесты для граничных случаев ====================

TEST(EdgeCasesTest, EmptyTableFind) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  Polinom found;

  EXPECT_FALSE(unsorted.find("A", found));
  EXPECT_FALSE(rbtree.find("A", found));
  EXPECT_FALSE(hash.find("A", found));
}

TEST(EdgeCasesTest, RemoveFromEmptyTable) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  EXPECT_FALSE(unsorted.remove("A"));
  EXPECT_FALSE(rbtree.remove("A"));
  EXPECT_FALSE(hash.remove("A"));
}

TEST(EdgeCasesTest, DuplicateKeys) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  Polinom p1 = Polinom::parseFromString("x");
  Polinom p2 = Polinom::parseFromString("y");
  Polinom p3 = Polinom::parseFromString("z");

  unsorted.insert("A", p1);
  unsorted.insert("A", p2);
  unsorted.insert("A", p3);

  rbtree.insert("A", p1);
  rbtree.insert("A", p2);
  rbtree.insert("A", p3);

  hash.insert("A", p1);
  hash.insert("A", p2);
  hash.insert("A", p3);

  Polinom found;

  // Во всех таблицах должно остаться последнее значение
  unsorted.find("A", found);
  ostringstream oss1;
  oss1 << found;
  EXPECT_EQ(oss1.str(), "z");

  rbtree.find("A", found);
  ostringstream oss2;
  oss2 << found;
  EXPECT_EQ(oss2.str(), "z");

  hash.find("A", found);
  ostringstream oss3;
  oss3 << found;
  EXPECT_EQ(oss3.str(), "z");

  // Размер должен быть 1
  EXPECT_EQ(unsorted.size(), 1);
  EXPECT_EQ(rbtree.size(), 1);
  EXPECT_EQ(hash.size(), 1);
}

TEST(EdgeCasesTest, VeryLongKey) {
  UnsortedArrayTable<string, Polinom> unsorted;
  RBTreeTable<string, Polinom> rbtree;
  HashTable<string, Polinom> hash;

  string longKey =
      "very_very_long_key_name_that_should_work_fine_" + string(100, 'a');
  Polinom p = Polinom::parseFromString("x + y");

  unsorted.insert(longKey, p);
  rbtree.insert(longKey, p);
  hash.insert(longKey, p);

  EXPECT_TRUE(unsorted.contains(longKey));
  EXPECT_TRUE(rbtree.contains(longKey));
  EXPECT_TRUE(hash.contains(longKey));

  Polinom found;
  unsorted.find(longKey, found);

  ostringstream oss;
  oss << found;
  EXPECT_EQ(oss.str(), "x + y");
}
