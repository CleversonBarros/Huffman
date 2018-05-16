#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trieNode trieNode;

struct trieNode
{
	trieNode *children[26]; 
	int end; 
};


trieNode *createNode(void)
{
	trieNode *new = (trieNode*)malloc(sizeof(trieNode));
	int i;

	new->end = 0;

	for(i = 0; i < 26; i++)
	{
		new->children[i] = NULL;
	}

	return new;
}

void insert(trieNode *root, char *word)
{
	int i;
	int lenght = strlen(word); 
	int index; 

	trieNode *aux = root;

	for(i = 0; i < lenght; i++)
	{
		index = word[i] - 'a'; 

		if(aux->children[index] == NULL) 
		{
			aux->children[index] = createNode();
		}

		aux = aux->children[index];
	}
	aux->end = 1; 
}

int search(trieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    trieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = key[level] - 'a';
 
        if (!pCrawl->children[index])
            return 0;
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl != NULL && pCrawl->end);
}

int main()
{
	printf("hec da bia\n");
	char keys[][8] = {"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};

    char output[][32] = {"Not present in trie", "Present in trie"};

    trieNode *root = createNode();
    int i;
    for(i = 0; i < (sizeof(keys) / sizeof(keys[0])); i++)
    {
    	insert(root, keys[i]);	
    }

    printf("%s --- %s\n", "the", output[search(root, "the")]);
    printf("%s --- %s\n", "there", output[search(root, "there")]);

}