import sys
import math

def LCS(X, Y):
    m = len(X)
    n = len(Y)
    # An (m+1) times (n+1) matrix
    C = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(1, m+1):
        for j in range(1, n+1):
            if X[i-1] == Y[j-1]: 
                C[i][j] = C[i-1][j-1] + 1
            else:
                C[i][j] = max(C[i][j-1], C[i-1][j])
    return C
    
def backTrack(C, X, Y, i, j):
    if i == 0 or j == 0:
        return ""
    elif X[i-1] == Y[j-1]:
        return backTrack(C, X, Y, i-1, j-1) + X[i-1]
    else:
        if C[i][j-1] > C[i-1][j]:
            return backTrack(C, X, Y, i, j-1)
        else:
            return backTrack(C, X, Y, i-1, j)

def backTrackAll(C, X, Y, i, j):
    if i == 0 or j == 0:
        return set([""])
    elif X[i-1] == Y[j-1]:
        return set([Z + X[i-1] for Z in backTrackAll(C, X, Y, i-1, j-1)])
    else:
        R = set()
        if C[i][j-1] >= C[i-1][j]:
            R.update(backTrackAll(C, X, Y, i, j-1))
        if C[i-1][j] >= C[i][j-1]:
            R.update(backTrackAll(C, X, Y, i-1, j))
        return R
        
def printDiff(C, X, Y, i, j):
    if i > 0 and j > 0 and X[i-1] == Y[j-1]:
        printDiff(C, X, Y, i-1, j-1)
        print("  " + X[i-1])
    else:
        if j > 0 and (i == 0 or C[i][j-1] >= C[i-1][j]):
            printDiff(C, X, Y, i, j-1)
            print("+ " + Y[j-1])
        elif i > 0 and (j == 0 or C[i][j-1] < C[i-1][j]):
            printDiff(C, X, Y, i-1, j)
            print("- " + X[i-1])       
                                
if __name__=='__main__':
       
    if len(sys.argv) < 2:
        sys.exit()
    else:

        ulist = []
        vlist = []

        with open(sys.argv[1]) as f:
            for line in f:
                line = line.strip()
                if len(line) == 0:
                    continue
                id,lls = line.split(':')
                lls = eval(lls.strip())
                
                ulist.append((id,lls[0][1],lls[0][0]))
                vlist.append((id,lls[1][1],lls[1][0]))     
                
        
        ulist = sorted(ulist,key=lambda x: x[1])
        vlist = sorted(vlist,key=lambda x: x[1])
        X = ''.join([x[0] for x in ulist])
        Y = ''.join([x[0] for x in vlist])
        m = len(X)
        n = len(Y)
        C = LCS(X,Y)
        
        all_lcs = backTrackAll(C, X, Y, m, n)
                
        all_lcs = set(''.join(all_lcs))

        for i in sorted(all_lcs):
            print(i)
         