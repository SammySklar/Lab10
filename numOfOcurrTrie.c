#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Initializes a trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}

// Inserts the word into the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *crawler = pTrie->root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!crawler->children[index])
            crawler->children[index] = createTrieNode();
        crawler = crawler->children[index];
    }
    crawler->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct TrieNode *crawler = pTrie->root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!crawler->children[index])
            return 0;
        crawler = crawler->children[index];
    }
    return crawler->count;
}

// Deallocates the trie structure
void deallocateTrieUtil(struct TrieNode *node) {
    if (!node)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateTrieUtil(node->children[i]);
    }
    free(node);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (!pTrie)
        return NULL;
    deallocateTrieUtil(pTrie->root);
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie) {
        pTrie->root = createTrieNode();
    }
    return pTrie;
}

// This function reads words from a file and stores them in pInWords array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return 0;
    }

    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character if present
        pInWords[count] = strdup(buffer);
        count++;
    }
    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];
    
	//read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
	{
        	printf("%s\n", inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
	{
        	insert(pTrie, inWords[i]);
    }

	// parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
	{
        	printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        	printf("There is an error in this program\n");
    return 0;
}
