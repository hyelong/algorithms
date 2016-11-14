class QuadNode:
    def __init__(self,colour):
        self.color = colour
        self.children = [None]*4

def union(tree1, tree2):
    if tree1==None or tree2==None:
        return Node
    if tree1.children[0]==None and tree2.children[0]==None:
        color="black"
        if tree1.color=="white" and tree2.color=="white":
            color = "white"
        node = QuadNode(color)
        return node
    else:
        children = [None]*4
        color = "white"
        black_count = 0
        for i in range(4):
            children[i] = union(tree1.children[i], tree2.children[i])
            if children[i].color=="black": 
                black_count += 1
        if black_count==4:
            color = "black"
        elif black_count>0:
            color = "gray"
        node = QuadNode(color)
        node.children = children
        return node


tree1 = QuadNode("gray")
tree1.children=[QuadNode("white"),QuadNode("black"),QuadNode("black"),QuadNode("white")]
tree2 = QuadNode("gray")
tree2.children=[QuadNode("white"),QuadNode("black"),QuadNode("white"),QuadNode("white")]
res = union(tree1, tree2)
for node in res.children:
    print(node.color),

