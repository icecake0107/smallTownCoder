def subArraySum(self,arr, n, s): 
    #Write your code here

    startInd = 0
    endInd = 1
    if( arr[startInd] == s ):
        return (startInd + 1,startInd + 1)
			
    sum = arr[startInd] + arr[endInd]
    if( sum == s ):
        return (startInd + 1, endInd + 1)

    endInd = endInd + 1 #2
    while( endInd < n ):    
        if sum == s:
		        if ( s == 0 and (arr[startInd] + arr[endInd]) != 0):
		            return {-1}
		        return (startInd + 1, endInd + 1)
		        
		    if arr[endInd] == s:
		        startInd = endInd
		        return (startInd + 1, endInd + 1);
		    
		    if( sum + arr[endInd] > s ):
				sum = sum - arr[startInd]
				startInd = startInd + 1
			else:
			    sum = sum + arr[endInd]
			    if( sum != s ):
			        endInd = endInd + 1

		return {-1}
