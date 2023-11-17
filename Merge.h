//
// Created by Max Benson on 8/13/2021.
//

#ifndef MERGE_H
#define MERGE_H

void Merge(const VariableArrayList<int>& list1, const VariableArrayList<int>& list2, VariableArrayList<int>& mergedList);
void IterativeMultiMerge(const VariableArrayList<VariableArrayList<int>>& listOfLists, VariableArrayList<int>& mergedList);
void RecursiveMultiMerge(const VariableArrayList<VariableArrayList<int>>& listOfLists, size_t start, size_t end, VariableArrayList<int>& mergedList);

#endif //MERGE_H
