class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

path = []
def print_path(root):

    if not root:
        return
    path.append(root.val)
    print_path(root.left)
    print_path(root.right)

    if not root.left and not root.right:
        for val in path:
            print(val),
        print("")
    path.pop()

root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
root.left.left = TreeNode(4)
"""root.left.right = TreeNode(5)"""
root.right.left = TreeNode(6)
root.right.right = TreeNode(7)
print_path(root)
