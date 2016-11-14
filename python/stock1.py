import sys

def maxProfit(prices):
    profit = -1
    lowest = sys.maxint
    highest = -1
    buy = -1
    sell = -1
    for price in prices:
        lowest = min(lowest, price)
        
        cur = price-lowest
        if cur>0 and profit<cur:
            highest = price
            profit = cur
            buy = lowest
            sell = highest
    return (buy, sell, profit)


prices = [1,5,3,1]
print(maxProfit(prices))
