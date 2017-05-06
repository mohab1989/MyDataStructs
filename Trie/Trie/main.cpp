#include"trie.h"
#include<iostream>
#include<string>
std::string to_string(bool b) {
	return b == 0 ?  "Doesn't exist in the trie" : "Exist in the trie";
}
int main(int argc, char * argv[]) {
	Trie<char> trie;
	trie.Insert({ 'm','o','h','a','b' });
	trie.Insert({ 'm','e','n','n','a' });
	trie.Insert({ 'm','e','n','n','a','z'});
	trie.Insert({ 'm','e','n','o' });
	trie.Insert({ 'm','o','h','a'});
	trie.Insert({ 'e','m','a','d' });

	std::cout << to_string(trie.Search({ 'm','o','h','a','b' })) << std::endl;
	std::cout << to_string(trie.Search({ 'm','e','n','n','a' ,'z','z' })) << std::endl;
	std::cout << to_string(trie.Search({ 'm','e','n','n','a' })) << std::endl;
	std::cout << to_string(trie.Search({ 'm','e','n','n','a' ,'z'})) << std::endl;
	std::cout << to_string(trie.Search({ 'm','e','n','o'})) << std::endl;
	std::cout << to_string(trie.Search({ 'm','o','h','a' })) << std::endl;
	std::cout << to_string(trie.Search({ 'm','e','n','n','a' ,'z','z','z','z','z','z' })) << std::endl;
	std::cout << to_string(trie.Search({ 'e','m','a','d' })) << std::endl;
	std::cout << to_string(trie.Search({ 'm','o','h'})) << std::endl;




}