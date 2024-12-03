#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
typedef struct NODE_s *NODE;
typedef struct NODE_s{
    int data;
    NODE left;
    NODE right;
    int height;
    int duplication;
}NODE_t[1];

NODE create_node(int data){
    NODE new = (NODE)malloc(sizeof(NODE_t[1]));
    if(new == NULL) return NULL;

    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->duplication = 0;
    new->height = 1;
return new;
}
/*to check the selected node exists*/
bool is_there(NODE node , int key){
    if(node == NULL)return false;

    if(node->data == key){
        return true;
    }else if(node->data > key){
        return is_there(node->left , key);
    }else if(node->data < key){
        return is_there(node->right , key);
    }
    return false;
}
/*function for preorder traversal root left right*/
void Pre_order_traversal(NODE node){
    if(node == NULL){
        return;
    }
    printf("%d ",node->data);
    Pre_order_traversal(node->left);
    Pre_order_traversal(node->right);
}
/*function for in order traversal left root right*/
void In_order_traversal(NODE node){
    if(node == NULL){
        return;
    }
    In_order_traversal(node->left);
    printf("%d ",node->data);
    In_order_traversal(node->right);
}
/*to find height of node*/
int height(NODE node){
    if(node == NULL){
        return 0;
    }
    int left_h = height(node->left);
    int right_h = height(node->right);
    int max;
    if(left_h > right_h){
        max = left_h;
    }else{
        max = right_h;
    }
    return max + 1 ;
}
/*this function makes right rotation*/
NODE right_rotate(NODE node){
    NODE tempA = node->left;
    NODE tempB = tempA->right;
    /*for rotation*/
    tempA->right = node;
    node->left =tempB;
    /*to update heights*/
    int left_h_node = height(node->left);
    int right_h_node = height(node->right);
    if (left_h_node >right_h_node)
    {
        node->height = left_h_node +1;
    }else{
        node->height = right_h_node +1;
    }
    int left_h_tempA = height(tempA->left);
    int right_h_tempA = height(tempA->right);
    if(left_h_tempA > right_h_tempA){
        tempA->height = left_h_node +1;
    }else{
        tempA->height = right_h_tempA +1;
    }
    
return tempA;
}
/*this function makes left rotation*/
NODE left_rotate(NODE node){
    NODE tempA = node->right;
    NODE tempB = tempA->left;
    /*for rotation*/
    tempA->left = node;
    node->right = tempB;
    /*to update heights*/
    int left_h_node = height(node->left);
    int right_h_node = height(node->right);
    if (left_h_node >right_h_node)
    {
        node->height = left_h_node +1;
    }else{
        node->height = right_h_node +1;
    }
    int left_h_tempA = height(tempA->left);
    int right_h_tempA = height(tempA->right);
    if(left_h_tempA > right_h_tempA){
        tempA->height = left_h_node +1;
    }else{
        tempA->height = right_h_tempA +1;
    }
return tempA;
}
/*to find balancer factor that used in AVL Tree*/
int find_balance_factor(NODE node){
    if(node == NULL){
        return 0;
    }

    int left_h = height(node->left);
    int right_h = height(node->right);
return left_h - right_h;
}
/*to insert and balance the tree*/
NODE insert(NODE root , int data){
    /*finds the correct place to insert and inserts */
    if(root == NULL)return (create_node(data));

    if(data < root->data){
        root->left = insert(root->left , data );
    }else if(data > root->data){
        root->right = insert(root->right , data);
    }else{
        root->duplication = root->duplication + 1;
        return root;
    }
    /*to balance the tree after insertion if it's needed*/
int balance = find_balance_factor(root);
    if(balance > 1 && data < root->left->data){
        return right_rotate(root);
    }
    if (balance < -1 && data > root->right->data){
        return left_rotate(root);
    }
    if(balance > 1 && data > root->left->data){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if(balance < -1 && data < root->right->data){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
return root;
}
bool duplicated_find(NODE node , int key ){
    if(node->data == key && node->duplication > 0 ){
        return true;
    }else if(node->data > key){
        return is_there(node->left , key);
    }else if(node->data < key){
        return is_there(node->right , key);
    }
return false;
}
NODE delete(NODE root , int key){
    /*if the tree is empty it returns root*/
    if(root == NULL){
        return root;
    }
    //if the node exist and duplicated we all need to decrease the number of duplication 
        if(duplicated_find(root,key)){
            if(root->data == key && root->duplication > 0 ){
            root->duplication = root->duplication -1;
            return root;
        }else if(root->data > key){
            return delete(root->left , key);
        }else if(root->data < key){
            return delete(root->right , key);
        }    
    }
    /*finds the node that will be deleted and deletes it */
    if (key < root->data)
    {
        root->left = delete(root->left , key);
    }else if(key > root->data){
        root->right = delete(root->right , key);
    }else{
        if(root->left == NULL || root->right == NULL){
            NODE temp;
            if(root->left != NULL){
                temp = root->left;
            }else{
                temp = root->right;
            }
            /*no child*/
            if(temp == NULL){
                temp = root;
                root = NULL;
            }else{
                /*1 child */
                root = temp; 
            }
            free(temp);
        }else{
            /*2 child */
            NODE temp = root->right;
            while (temp->left != NULL){
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete(root->right , temp->data);
        }
    }
    /*if the root has 1 node we have to return root*/
    if(root == NULL){
        return root;
    }
    /*to update the heights*/
    int left_h = height(root->left);
    int right_h = height(root->right);
    if(left_h > right_h){
        root->height = left_h +1;
    }else{
        root->height = right_h +1;
    }
    // we have to find balancer factor to decide which rotations will be applied for the balancing 
    int balance = find_balance_factor(root);
    //we apply right rotation on root node  
    if(balance > 1 && find_balance_factor(root->left) >= 0){
        return right_rotate(root);
    }
    //we apply left rotation to root node
    if(balance < -1 && find_balance_factor(root->right) <=0){
        return left_rotate(root);
    }
    //we applied left rotation to left child of the root and then applied right rotation to root
    if(balance > 1 && find_balance_factor(root->left) < 0){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    //we applied right rotation on right child of root and then applied left rotation to root
    if(balance < -1 && find_balance_factor(root->right) > 0 ){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
return root;
}

NODE update(NODE root , int selected , int updated){
if(is_there(root, selected)){
    root = delete(root , selected);
    root = insert(root , updated);
    return root;
}else{
    printf("node does not exist\n");
  
}

}
void print_choices(){
    printf("\n------------------\n AVL TREE - MENU \n------------------\n 1. INSERT \n 2. DELETE \n 3. UPDATE \n 4. Traverse the Tree in Preorder \n 5. Traverse the Tree in Inorder \n 6. Exit \n");    }

bool value_taker(int* data) 
{
    while ( !scanf("%d",data) ) {
        printf("Please try again :  ");
        while(getchar()!='\n'); //if the user presses enter it will prevent crashing the menu
    }
    return true;
}

bool continue_checker(char cont){
if(cont == 'Y' || cont == 'y'){
    printf("Proccessing continues \n");
    return true;
}else if(cont == 'n' || cont == 'N'){
    printf("Returning the menu... \n");
    return false;
}else{
    printf("Invalid answer , returning the menu...\n");
    return false;
}
}

int main(){
NODE root = NULL;
int choice = 0, data = 0 ;
char to_continue;
do{
    print_choices();
    if((!value_taker(&choice))){
        //do nothing
    }else if((choice > 6) || (choice <= 0)){
        printf("Please enter valid option \n");
    }else{
    if(choice == 1){
              do {//insert
                printf("please enter the value that will be inserted : ");
                if(value_taker(&data)){
                 root = insert(root , data);
                printf("do you want to continue inserting ? (Y or N)");
                scanf(" %c ",&to_continue);
                printf("\t %c \t",to_continue);
                if(!continue_checker(to_continue))break;
                }
            }while(true);
    }else if(choice == 2 ){
        do { // delete
        if(root == NULL){printf("the tree is empty\n"); break;}
                printf("please enter the value that will be deleted : ");
                if(value_taker(&data) && (root != NULL) && is_there(root,data)){
                root = delete(root,data);
                printf("%d is deleted\n",data);
                printf("Do you want to continue deleting? (Y or N)");
                scanf(" %c ",&to_continue);
                if(!continue_checker(to_continue))break;
                }
            }while(root != NULL);
    }else if(choice == 3){
        do {//update
        if(root == NULL){printf("the tree is empty\n"); break;}
                int updated ;
                printf("please enter the value that will be updated : ");
                if(value_taker(&data) && printf("what will be updated to ?") && value_taker(&updated)){
                root = update(root ,data , updated );
                printf("Do you want to continue updating? (Y or N) ");
                scanf(" %c ",&to_continue);
                if(!continue_checker(to_continue))break;
                }
            }while(true);
    }else if(choice == 4 ){
        if (root != NULL)
        {
            printf("Traverse in Pre-order\n");
            Pre_order_traversal(root);
        }else{
            printf("The tree is empty , there is nothing to print\n");
        }
    }else if(choice == 5){
        if (root != NULL)
        {
            printf("Traverse in In-order\n");
            In_order_traversal(root);
        }else{
            printf("The tree is empty , there is nothing to print\n");
        }
    }
    }
}while(choice != 6);

return 1;
}