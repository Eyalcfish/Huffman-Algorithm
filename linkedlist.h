#include <stdio.h>
#include <malloc.h>

typedef struct node {
    void *val;
    struct node * next;
} node_t;


void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", *(int *)current->val);
        current = current->next;
    }
}

void pushend(node_t * head, void *val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void pushstart(node_t ** head, void *val) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

void *pop(node_t ** head) {
    void *retval = NULL;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

void *remove_last(node_t * head) {
    void *retval = NULL;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;

}

void *remove_by_index(node_t ** head, int n) {
    int i = 0;
    void *retval = NULL;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return NULL;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return NULL;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}