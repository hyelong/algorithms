#!/usr/bin/python

class Node:
    """base class, you should not process one of these"""
    def process(self):
        raise('you should not be processing a node')

class BinaryNode(Node):
    """base class for binary nodes"""
    def __init__(self, _left, _right):
        self.left = _left
        self.right = _right
    def process(self):
        raise('you should not be processing a binarynode')

class Plus(BinaryNode):
    def process(self):
        return self.left.process() + self.right.process()

class Minus(BinaryNode):
    def process(self):
        return self.left.process() - self.right.process()

class Mul(BinaryNode):
    def process(self):
        return self.left.process() * self.right.process()

class Div(BinaryNode):
    def process(self):
        return self.left.process() / self.right.process()

class Num(Node):
    def __init__(self, _value):
        self.value = _value
    def process(self):
        return self.value

def demo(n):
    print n.process()

demo(Num(2))                                       # 2
demo(Plus(Num(2),Num(5)))                          # 2 + 3
demo(Plus(Mul(Num(2),Num(3)),Div(Num(10),Num(5)))) # (2 * 3) + (10 / 2)

