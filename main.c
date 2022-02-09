#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct Node {
  int val;
  struct Node *left, *right;
} Node;

Node* addNode(int value) {
  Node *node = malloc(sizeof(Node));
  node->val = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

Node* initTree(int value) {
  return addNode(value);
}

void addLeft(Node* node, int value) {
  node->left = addNode(value);
}

void addRight(Node* node, int value) {
  node->right = addNode(value);
}

void insertValue(Node* node, int value) {
  Node** wtf = NULL;
  while(node != NULL) {
    if(node->val == value) {
      puts("exists already");
      return;
    } else if(value < node->val) {
      wtf = &node->left;
      node = node->left;
    } else {
      wtf = &node->right;
      node = node->right;
    }
  }
  node = addNode(value);
  if(wtf != NULL) {
    *wtf = node;
  }
}

void freeTree(Node* node) {
  if(node == NULL) {
    return;
  }
  freeTree(node->left);
  freeTree(node->right);
  printf("Deleting: %d\n", node->val);
  free(node);
  node = NULL;
}

int findDepth(Node* node, int value) {
  int depth = 1;
  while(node != NULL) {
    if(node->val == value) {
      return depth;
    } else if(value < node->val) {
      node = node->left;
    } else {
      node = node->right;
    }
    depth++;
  }
  return 0;
}

int countElements(Node* node) {
  if(node == NULL) {
    return 0;
  }
  return 1 + countElements(node->left) + countElements(node->right);
}

void assignElements(int* result, Node* node, int* index) {
  if(node == NULL) {
    return;
  }
  assignElements(result, node->left, index);
  assignElements(result, node->right, index);
  result[*index] = node->val;
  (*index)++;
}

int* getAllNumbers(Node* node, int* size) {
  *size = countElements(node);
  if(*size == 0) {
    return NULL;
  }
  int* result = malloc(*size * sizeof(int));
  int index = 0;
  assignElements(result, node, &index);
  return result;
}

int main(int argc, char** argv) {
  srand(time(0));

  Node* tree = NULL;

  int number;
  for(int i = 0; scanf("%d", &number) == 1; i++) {
    if(i == 0) {
      tree = initTree(number);
    } else {
      insertValue(tree, number);
    }
  }
  int numbersSize;
  int* numbers = getAllNumbers(tree, &numbersSize);
  printf("Tree element count: %d\n", numbersSize);

  double sum = 0.0;
  int n = 1000;
  if(argc > 1) {
    n = atoi(argv[1]);
  }

  for(int i = 0; i < n; i++) {
    int randomIndex = rand() % numbersSize;
    int depth = findDepth(tree, numbers[randomIndex]);
    sum += depth;
  }
  sum /= (double) n;
  printf("AVG depth = %g\n", sum);
  freeTree(tree);
  free(numbers);
  return 0;
}
