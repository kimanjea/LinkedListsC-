// Defines merge function
// Author: Azhar Amir Kimanje
// Date: 09/29/2021

#include "VariableArrayList.h"


void Merge(const VariableArrayList<int>& list1, const VariableArrayList<int>& list2, VariableArrayList<int>& mergedList) {
 int list1Item=0;
 int list2Item=0;
 int j=0;
 int i=0;
 int k=0;
 mergedList.Clear();
 while( i<list1.Size() || j<list2.Size()) {

     list1.Get(i,list1Item);
     list2.Get(j,list2Item);

     if(list1.Get(i,list1Item)==false){
         mergedList.Insert(k,list2Item);
         j++;
     } else if(list2.Get(j,list2Item)==false){
         mergedList.Insert(k,list1Item);
        i++;
     } else if(list1Item<=list2Item) {
         mergedList.Insert(k,list1Item);

         i++;
     } else {
         mergedList.Insert(k,list2Item);

         j++;
     }
k++;
 }
}

void IterativeMultiMerge(const VariableArrayList<VariableArrayList<int>>& listOfLists, VariableArrayList<int>& mergedList) {
    mergedList.Clear();
    VariableArrayList<int> firstlist;
    VariableArrayList<int> nextlist;
    int i = 1;

    listOfLists.Get(0, mergedList);

    while (i < listOfLists.Size()) {

        listOfLists.Get(i, firstlist);

            Merge(firstlist, mergedList, nextlist);

            mergedList=nextlist;
        i++;
    }
}

void RecursiveMultiMerge(const VariableArrayList<VariableArrayList<int>>& listOfLists, size_t start, size_t end, VariableArrayList<int>& mergedList) {
    VariableArrayList<int> firsthalf;
    VariableArrayList<int> secondhalf;

    if(end-start>2) {
        if (start == 0) {
            RecursiveMultiMerge(listOfLists, start, end / 2, mergedList);
            firsthalf = mergedList;
            RecursiveMultiMerge(listOfLists, ((end / 2)), end, mergedList);
            secondhalf = mergedList;
            Merge(firsthalf, secondhalf, mergedList);
        } else {

            RecursiveMultiMerge(listOfLists, start, ((end / 2) + (start / 2)), mergedList);
            firsthalf = mergedList;
            RecursiveMultiMerge(listOfLists, ((end / 2) + (start / 2)), end, mergedList);
            secondhalf = mergedList;
            Merge(firsthalf, secondhalf, mergedList);
        }
    }else if(end-start==2 ) {
        listOfLists.Get(start,firsthalf);
        listOfLists.Get(end -1, secondhalf);
        Merge(firsthalf,secondhalf,mergedList);

    }  else{
        listOfLists.Get(start,mergedList);

    }
}



