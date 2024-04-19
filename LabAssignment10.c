#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie *children[26];
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    
    if (node) 
    {
        node->count = 0;

        for (int i = 0; i < 26; i++) 
        {
            node->children[i] = NULL;
        }
    }

    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *cur = pTrie;
    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';
        if (!cur->children[index]) 
        {
            cur->children[index] = createTrie();
        }
        cur = cur->children[index];
    }
    // Mark the end of word and increase the count
    cur->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *cur = pTrie;
    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';
        if (!cur->children[index]) 
        {
            return 0; // Word not found in trie
        }

        cur = cur->children[index];
    }
    // Word found in trie
    return cur->count;
}

// deallocate trie
struct Trie *deallocateTrie(struct Trie *pTrie)
{
     if (pTrie) 
     {
        for (int i = 0; i < 26; i++) {
            
            if (pTrie->children[i]) 
            {
                deallocateTrie(pTrie->children[i]);
            }
        }

        free(pTrie);
    }

    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *inFile = fopen(filename, "r");
    if (inFile == NULL) return -1;
    int count = 0;

    fscanf(inFile, "%d\n", &count);
    char word[100];
    for (int i = 0; i < count; i++)
    {
        fscanf(inFile, "%s\n", word);
        pInWords[i] = (char*)calloc(strlen(word), sizeof(char));
        strcpy(pInWords[i], word);
    }

    return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
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
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}