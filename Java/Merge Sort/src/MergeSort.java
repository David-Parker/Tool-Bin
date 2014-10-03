import java.util.*;

public class MergeSort{

     public static void main(String []args){
        List a = fillListRand(30);
        List sorted = mergeSort(a);
        System.out.println("Done.");
        System.out.println("Unsorted: " + a.toString());
        System.out.println("Sorted:   " + sorted.toString());
     }
     
     public static List mergeSort(List unsorted) {
        if(unsorted.size() == 1)
            return unsorted;
            
        return mergeLists(mergeSort(unsorted.subList(0,unsorted.size()/2)),
                          mergeSort(unsorted.subList(unsorted.size()/2,unsorted.size())));
     }
     
     public static List mergeLists(List a, List b) {
         List newList = new ArrayList();
         int aIndex = 0;
         int bIndex = 0;
         
         while((aIndex < a.size()) && (bIndex < b.size())) {
            if((int)a.get(aIndex) > (int)b.get(bIndex)) {
                newList.add(b.get(bIndex));
                bIndex++;
            }

            else {
                newList.add(a.get(aIndex));
                aIndex++;
            }
         }
         
        if(aIndex >= a.size())
            newList.addAll(b.subList(bIndex,b.size()));
            
        else if (bIndex >= b.size())
            newList.addAll(a.subList(aIndex,a.size()));
            
        return newList;
     }
     
     public static List fillListRand(int num) {
         List newList = new ArrayList();
         Random r = new Random();
         for(int i = 0; i < num; i++) {
             newList.add(r.nextInt(100));
         }
         return newList;
     }
}
