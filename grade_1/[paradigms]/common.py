class node:
    def __init__(self, l=None, r=None, x=None):
        self.key = x
        self.left = l
        self.right = r

def insert(root_node, x):
    if root_node.key == None:
        node.key = x
        return
    if (root_node.key >= x):
        root_node.left = insert(root_node.left, x)
    else:
        root_node.right = insert(root_node.right, x)
    return
    raise NotImplementedError

def inorder_traversal(node):
    if node == None:
        return
    inorder_traversal(node.left)
    print(node.key)
    inorder_traversal(node.right)
    return
    raise NotImplementedError
