void encode_preorder_traversal(struct MinHeapNode * root, char * serialized_string, int * serialized_string_idx)
{
    if(root)
    {
        char * tmp_str = (char *)malloc(sizeof(char) * 10);
        sprintf(tmp_str, "%d", root->val);
        int tmp_str_len = strlen(tmp_str);

        memcpy(&serialized_string[*serialized_string_idx], tmp_str, tmp_str_len);
        *serialized_string_idx += tmp_str_len;
        serialized_string[*serialized_string_idx] = ',';
        *serialized_string_idx += 1;

        free(tmp_str);

        encode_preorder_traversal(root->left, serialized_string, serialized_string_idx);
        encode_preorder_traversal(root->right, serialized_string, serialized_string_idx);
    }
    else
    {
        serialized_string[*serialized_string_idx] = '#';
        *serialized_string_idx += 1;
        serialized_string[*serialized_string_idx] = ',';
        *serialized_string_idx += 1;
    }
    return;
}

/** Encodes a tree to a single string. */
char* serialize(struct MinHeapNode* root)
{
    char * serialized_string = (char *)malloc(sizeof(char) * (10001 * 10));
    int serialized_string_idx = 0;

    encode_preorder_traversal(root, serialized_string, &serialized_string_idx);
    serialized_string[serialized_string_idx] = '\0';
    printf("%s", serialized_string);
    return serialized_string;
}

struct TreeNode * decode_preorder_traversal(struct MinHeapNode ** root, char * data, int * index)
{
    if(data[*index] != '\0')
    {
        if(data[*index] == '#')
        {
            *index += 2;
            return NULL;;
        }


        int val;
        char * tmp_str = (char *)malloc(sizeof(char) * 10);
        int tmp_str_idx = 0;
        while(data[*index] != ',')
        {
            tmp_str[tmp_str_idx++] = data[*index];
            *index += 1;
        }
        *index += 1;
        tmp_str[tmp_str_idx] = '\0';

        val = atoi(tmp_str);
        struct MinHeapNode * new_node = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
        new_node->val = val;
        new_node->left = NULL;
        new_node->right = NULL;

        if(*root == NULL)
        {
            *root = new_node;
        }

        new_node->left = decode_preorder_traversal(root, data, index);
        new_node->right = decode_preorder_traversal(root, data, index);
        return new_node;
    }
    return NULL;
}

/** Decodes your encoded data to tree. */
struct MinHeapNode* deserialize(char* data)
{
    struct MinHeapNode * root = NULL;

    int index = 0;
    decode_preorder_traversal(&root, data, &index);
    return root;
}