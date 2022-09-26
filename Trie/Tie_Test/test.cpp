#include "pch.h"
#include "Trie.h"

namespace datastructures {


std::string to_string(bool b) {
	return b == 0 ? "Doesn't exist in the trie" : "Exist in the trie";
}

TEST(TrieInsertionsAndSearch, InsertThenSearch) {
	Trie<char> trie;
	trie.Insert({ 'm','o','h','a','b' });
	trie.Insert({ 'm','e','n','n','a' });
	trie.Insert({ 'm','e','n','n','a','z' });
	trie.Insert({ 'm','e','n','o' });
	trie.Insert({ 'm','o','h','a' });
	trie.Insert({ 'e','m','a','d' });

	EXPECT_TRUE(trie.Search({ 'm','o','h','a','b' }));
	EXPECT_FALSE(trie.Search({ 'm','e','n','n','a' ,'z','z' }));
	EXPECT_TRUE(trie.Search({ 'm','e','n','n','a' }));
	EXPECT_TRUE(trie.Search({ 'm','e','n','n','a' ,'z' }));
	EXPECT_TRUE(trie.Search({ 'm','e','n','o' }));
	EXPECT_TRUE(trie.Search({ 'm','o','h','a' }));
	EXPECT_FALSE(trie.Search({ 'm','e','n','n','a' ,'z','z','z','z','z','z' }));
	EXPECT_TRUE(trie.Search({ 'e','m','a','d' }));
	EXPECT_FALSE(trie.Search({ 'm','o','h' }));
}

}
