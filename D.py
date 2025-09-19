N,M = map(int, input().split())
S=input()
T=input()
for i in range(int(M)):
    l,r = map(int, input().split())
    s_sub = S[l-1:r]
    t_sub = T[l-1:r]
    S = S[:l-1] + t_sub + S[r:]
    T = T[:l-1] + s_sub + T[r:]
print(S)

