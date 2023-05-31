#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BSTnode
{
    char word[128], meaning[256];
    struct BSTnode *left, *right;
};
FILE *file;
FILE *file2;

struct BSTnode *root = NULL;

struct BSTnode * createNode(char *word, char *meaning)
{
    struct BSTnode *newnode;
    newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newnode->word, word);
    strcpy(newnode->meaning, meaning);
    newnode->left = newnode->right = NULL;
    return newnode;
}

void insert(char *word, char *meaning)
{
    struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
    int res = 0;
    if (!root)
    {
        root = createNode(word, meaning);
        return;
    }
    for (current = root; current !=NULL;
            current = (res > 0) ? current->right : current->left)
    {
        res = strcasecmp(word, current->word);
        if (res == 0)
        {
            printf("Duplicate entry!!\n");
            return;
        }
        parent = current;
    }
    newnode = createNode(word, meaning);
    res > 0 ? (parent->right = newnode) : (parent->left = newnode);
    return;
}

void deleteNode(char *str)
{
    struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
    int flag = 0, res = 0;
    if (!root)
    {
        printf("Word is not present!!\n");

        return;
    }
    current = root;
    while (1)
    {
        res = strcasecmp(current->word, str);
        if (res == 0)
            break;
        flag = res;
        parent = current;
        current = (res > 0) ? current->left : current->right;
        if (current == NULL)
            return;
    }
    /* deleting leaf node */
    if (current->right == NULL)
    {
        if (current == root && current->left == NULL)
        {
            free(current);
            root = NULL;
            return;
        }
        else if (current == root)
        {
            root = current->left;
            free (current);
            return;
        }

        flag > 0 ? (parent->left = current->left) :
        (parent->right = current->left);
    }
    else
    {
        /* delete node with single child */
        temp = current->right;
        if (!temp->left)
        {
            temp->left = current->left;
            if (current == root)
            {
                root = temp;
                free(current);
                return;
            }
            flag > 0 ? (parent->left = temp) :
            (parent->right = temp);
        }
        else
        {
            /* delete node with two children */
            struct BSTnode *successor = NULL;
            while (1)
            {
                successor = temp->left;
                if (!successor->left)
                    break;
                temp = successor;
            }
            temp->left = successor->right;
            successor->left = current->left;
            successor->right = current->right;
            if (current == root)
            {
                root = successor;
                free(current);
                return;
            }
            (flag > 0) ? (parent->left = successor) :
            (parent->right = successor);
        }
    }
    free (current);
    return;
}

void findElement(char *str) {
        struct BSTnode *temp = NULL;
        int flag = 0, res = 0;
        if (root == NULL) {
                printf("Binary Search Tree is out of station!!\n");
                return;
        }
        temp = root;
        while (temp) {
                if ((res = strcasecmp(temp->word, str)) == 0) {
                        printf("Word   : %s", str);
                        printf("Meaning: %s", temp->meaning);
                        flag = 1;
                        break;
                }
                temp = (res > 0) ? temp->left : temp->right;
        }
        if (!flag)
                printf("Search Word not found in Dictionary\n");
        return;
  }

void inorderTraversal(struct BSTnode *myNode)
{
    if (myNode)
    {
        inorderTraversal(myNode->left);
        printf("Word    : %s", myNode->word);
        printf("Meaning : %s", myNode->meaning);
        printf("\n");
        inorderTraversal(myNode->right);
    }
    return;
}
void similar(struct BSTnode *root, char *str)
{
    struct BSTnode *temp = NULL;
    int flag = 0, res = 0;
    temp = root;
    if(temp)
    {
        similar(temp->left,str);
        if ((res = strcasecmp(temp->meaning, str)) == 0)
        {
            printf("Word   : %s", temp->word);
        }
        similar(temp->right,str);

    }
    if(flag==0)
    {
        printf("There is no word in dictionary which contain this meaning\n");
        return;
    }

    return;
}

int main()
{
    int ch;
    char str[128], meaning[256];
    while (1)
    {
        printf("\n1.Add new word\t2.Delete word\n");
        printf("3.Search\t4.Print Dictionary\t5.Similar meaning word\n");
        printf("6. Exit\nEnter ur choice:");
        scanf("%d", &ch);
        getchar();
        switch (ch)
        {
        case 1:
            printf("Word to insert:");
            fgets(str, 100, stdin);
            printf("Meaning:");
            fgets(meaning, 256, stdin);
            insert(str, meaning);
            file=fopen("datasproject.txt","a");
            if(file==NULL)
            {
                printf("File is empty\n");
            }
            else
            {
                fprintf(file,"Name=%s  Meaning= %s\n",str,meaning);
                fclose(file);
            }
            break;
        case 2:
            printf("Enter the word to delete:");
            fgets(str, 100, stdin);
            deleteNode(str);
            break;
        case 3:
            printf("Enter the search word:");
            fgets(str, 100, stdin);
            findElement(str);
            break;
        case 4:
            inorderTraversal(root);
            break;
        case 5:
            printf("Enter the meaning:");
            fgets(str, 100, stdin);
            similar(root,str);
            break;
        case 6:
            exit(0);
        default:
            printf("You have entered wrong option\n");
            break;
        }
    }
    return 0;
}
