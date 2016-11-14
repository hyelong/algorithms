class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

def reverse(head):
    if not head or not head.next:
        return head
    pre, cur, next = None, head, None
    while cur:
        next = cur.next
        cur.next = pre

        pre = cur
        cur = next

    return pre

header = ListNode(1)
header.next = ListNode(2)
header.next.next = ListNode(3)

res = reverse(header)
while res:
    print(res.val),
    res = res.next
print('');
