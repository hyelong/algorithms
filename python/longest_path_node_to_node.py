class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
dp={}
def getHeight(root):
    if root==None: return 0
    if root in dp: return dp[root]
    height = 1+max(getHeight(root.left), getHeight(root.right))
    dp[root] = height
    return height


def longest_path(root):
    if root==None: return 0
    cur = 1+getHeight(root.left)+getHeight(root.right)
    return max(cur, max(longest_path(root.left),longest_path(root.right)))

root = TreeNode(1)
root.left = TreeNode(2)
root.left.left = TreeNode(3)
root.left.right = TreeNode(4)
root.left.right.right = TreeNode(5)
root.left.left.left = TreeNode(6)
print(longest_path(root))
