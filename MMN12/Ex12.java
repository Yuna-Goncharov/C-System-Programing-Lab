  import java.util.Scanner;
/**
 * Write a description of class Ex12 here.
 * *
 * @Yona goncharov
 * id: 312631187
 */

public class Ex12
{
    /**q1:
     * 1. not correct
     * 2. not correct
     * 3. correct
     * 4. not correct
     * 5.correct
     * 6.correct
     **/
  public static boolean findValWhat(int[][]m, int val)
  {
     /**
      * Write a description of class findValWhat here
      * Finds val in the array
      * val is  given int
      * @param size the lenth og the arrays .
      * @param col is the columns 
      * @param row is the row in the arrays 
      * @param is found return true or false 
      **/
    int size = m.length;
    int col = 0;
    int row = size-1;
    boolean isfound = false;
    
    while (row >= 0 && col >= 0 && row < size && col < size)
    {
        int temp = m[row][col];
        if (temp == val)
        {
            isfound = true; 
            break;
        }  
        else if(temp < val)
        {
            row--;
        } 
        else 
        {
             col++;
        }    
    }
        
    return isfound;
    
  };
  public static boolean findValTest (int [][] m, int val)
    {
        int size = m.length;
        int low = 0, up = size-1;
        
        while((up - low) != 1)// search val as long as remain 2 rows to search the number (and val isn't found)
        {
            int mid = (low+up)/2;
            int temp = m[mid][0];
            
            if(temp == val)
                return true;
            else if(temp > val)// number can only be found in middle row and below it.
                    up = mid;
                 else//number can only be found in middle row and above it.
                    low = mid;
        }//end while
        
        int row = low, column = 0;
        
        while(row <= up)// search val as long as isn't finished the 2 possible rows (and val isn't found)
        {
            int temp = m[row][column];
            
            if(temp == val)
                return true;
            else if(column == size-1)// current element is the last element in this row.
                 {
                     column = 0;
                     row++;
                 }
                 else//current element isn't the last element in this row.
                    column++;
        }//end while
        
        return false;// number isn't found.
    };// end method findValTest
    
    
    /** Finds how much sub strings included inside a given string that starts and ends with
      * a given char and also contain only one of the given char between.
      * @param s The string to look the (char,char,char) pattern.
      * @param c The input char to look by
      * @return the numner of sub strings found
      **/
       public static int subStrC(String s, char c)
    {
        int count=0;
        
        for(int i=0; i<s.length(); i++)
            if(s.charAt(i) == c)
                count++;
        
        if(count < 3)
            count = 0;
        else//count >= 3
            count -= 2;
        
        return count;
    };// end method subStrC
        
  /**
  * Find a how much a sequence of a given char in a the pattern of (c,{c * k},c) included
  * in the given string
  * @param s The string to look the (char,char,char) pattern.
  * @param c The input char to look by
  * @param k The amount of chars inside the pattern
  * @return the numner of sub strings found
  */
      public static int subStrMaxC(String s, char c, int k)  {
        int counter = 0;
            
        for(int i = 0; i < s.length(); i++)
          if ( s.charAt(i) == c )
            counter++;
        return subStrMaxCRecursively(s,c,k,counter);
      }
        // recursive helper function that calc number of instances of our pattern given the 'c' sub
      private static int subStrMaxCRecursively(String s, char c, int k, int counter) {
        if (k < 0) return 0; // our exit strategy
        if ( counter < k + 2 )
          counter  = 0;
        else
          counter -= k + 1;
    
        return counter + subStrMaxCRecursively(s,c,k - 1,counter);
        
      }
      //// end method subStrMaxc
}
