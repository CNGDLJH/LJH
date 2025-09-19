import heapq
import sys

def main():
    # 读取查询数量
    Q = int(sys.stdin.readline())
    
    # 创建一个空堆
    heap = []
    
    # 处理每个查询
    for _ in range(Q):
        query = sys.stdin.readline().split()
        
        # 类型1：添加元素到堆中
        if query[0] == '1':
            x = int(query[1])
            heapq.heappush(heap, x)
        
        # 类型2：取出并输出最小值
        else:
            min_val = heapq.heappop(heap)
            print(min_val)

if __name__ == "__main__":
    main()
