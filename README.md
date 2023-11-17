# Lab 1 - Multiway Merge of  Sorted Lists

In this lab you will code two different algorithms for merging *N* sorted lists into a single sorted list -- one iterative and one recursive.
Both algorithms will make use of a function that merges two sorted lists into a single sorted list.

In this lab you only need to write these three functions:

![image](https://user-images.githubusercontent.com/58283777/134788735-9c969bd7-4543-4cdd-914f-2c212fd6fd30.png)

These functions have already been stubbed out for you in the file *Merge.cpp*.  You are to add correct implementations for these functions to this file. Do not modify the rest of the files in the project.  

Once you clone the provided repo and create the CLion project, you should be able to successfully build the project.  When you try to run it, it will assert to let you know that the functions didn't do the right thing.  When you implement the functions correctly and run it, you will see something like that:

![image](https://user-images.githubusercontent.com/58283777/134788929-f06584e7-f967-46cd-9eb4-41e4e8d5aae9.png)

## Step 1:  

Add a file header comment to *Merge.cpp* and function header comments for each of the three functions.  Follow the course style guidelines described on the second day of class.  You may want to review the Powerpoint from that class session to get it right.  Using correct style will be part of the part of the lab grade.

## Step 2:

Implement `Merge`.  You use the public methods of the `VariableArrayList` class to build a single sorted list from the items in `list1` and `list2`.  If an item appears in both both, it will be duplicated in the result.  Place the resulting list into `mergedList`.  Note that you should not assume that `mergedList` is an empty list when the function is called.

You should use a loop, rather than recursion to implement this function.

After implementing `Merge` you can verify its correctness by building and running the lab.  Your goal is to make sure the run gets far enough to print *...Merge Test Correctness Succeeds*.

## Step 3:

Next implement `IterativeMultiMerge`.  The first parameter `listOfLists` contains the list of sorted lists that need to be merged into a single sorted list.  The second parameter `mergedList` should be initialized to be an empty list at the start of the function.  Then, using a loop over the sorted lists in `listOfLists`, on each iteration you should merge in the next list stored in `listOfLists`.

After implementing this function, you can again verify its correctness by building and running the lab to the point where *...Iterative Merge Test Correctness Succeeds.*

## Step 4:

Now it's time to implement `RecursiveMultiMerge`.  This job of this function is to merge the sorted lists in `listOfLists` at positions `start`, `start+1`, ... `end-1` into a singled sorted list and place the result into the parameter `mergedList`.  This function should be recursive.  The base cases for the recursion are when the range of lists only encompasses 0 or 1 lists.  In other cases, you should divide the range up into halves.  When the number of lists is odd, then one "half" will have one more list than the other.  You should call `RecursiveListMerge` recursively on the first half, and then recursively on the second half.  Then you will call `Merge` to merge the two results into a single sorted list.

Once you implement this function, you will want to verify its correctness by building the running the lab to completion.

## Step 5:

Now it's time to do collect some performance measurements and save them into a file.  

#### Let's look at the numbers first: 

For this you will need to work from the Linux command line.  Navigate into the *cmake-build-debug* directory of where your program runs, and run it with the *-perf* switch as shown:

![image](https://user-images.githubusercontent.com/58283777/134791490-bd532e7b-8590-4041-b627-b349b729f794.png)

Running your program with the *-perf* switch will first measure how long your `Merge` function takes to merge two lists of varying sizes.  In the screenshot, you can see my `Merge` function running on my desktop computer took an average of 3866 nanoseconds to merge two lists into a single list with 100 items, 6218 nanseconds to merge two lists into a single list with 200 items, etc.  For each line printed, 500 pairs of lists are generated randomly and merged, and the total time is divided by 500. 

Next the program goes on to measuring the times for iterative and recursive multimerge when there are 512 lists to merge.

![image](https://user-images.githubusercontent.com/58283777/134826608-39003e92-075d-4f68-be12-47fc9fc111de.png)

The first row under the column heading shows it took an average of 2208807 nanoseconds to iteratively merge 512 sorted lists into a single list with 512 items, and 189543 nanoseconds to do it recursively. The second row gives the average merge times when there are 512 lists, but the total number of items is 1024. 

Finally the program measures the times for iterative and recursive multimerge when there is a total of 8192 elements spread over the lists, but we vary the number of lists.

![image](https://user-images.githubusercontent.com/58283777/134826782-80a5ae8c-a83f-4d8b-864f-c9730d09d263.png)

The first line shows that it took 22177 nanoseconds to iteratively merge a single list, while it took 22002 nanoseconds.  These measurements are very close, and that's to be expected, because if there is only one list, the iterative and recursive cases basically do the same thing.  But, as the number of lists goes up the recursive algorithm starts to run much faster than the iterative algorithm.

#### Now let's collect the numbers into a file.  

You are going to save this file in your project's *cmake-build-debug* folder so you can access it with your favorite desktop tool for creating charts.  One easy option woudl be to use Microsoft Excel.  The columns are TAB delimited, so it's easy to open the files as spreadsheets, and then use Excel's chart functionality.

- Windows PC users:

Run the program from the command line again, this time "redirecting the output to a file."  For instance if you want to save the results into a file called *timings*, you could type

`./Multimerge -perf > timings`

When you do this, you won't see any output because it is being written to the file *timings*.  Be patient, unless you have a bug in your program, eventually the prompt will be printed and you will now have your performance measurements in a file which you can work with.

- Mac users:

Run Docker with a slightly different command:

`docker run -v 'pwd':/development -p 222:22 -it <your image id> /bin/bash`

When you run Docker this way, Docker will connect its  */development* folder in the virtual machine with the */development* folder in your Mac file system.  While Docker is running with this command, use *cd* to navigate into the *cmake-build-debug* directory of your project, build your program, and then you can use the command

`./Multimerge -perf > timings`

to save the timings in a file that you can access using ordinary charting tools.


## Step 6:

Now produce charts from your performance measurements.  You should create the following SEVEN charts and push these files to origin.

- Each chart should have a informative title, and the axes should labelled informatively.
- The file types of the files below could be .jpg, .png, .pdf, or a Microsoft Word file.  

*MergeChart*  A chart that plots a curve showing how the average Merge time for merging two lists varies as the total number of items in the list varies.  The times should be on the y-axis, and the item total on the x-axis.

*VaryNElements*  A chart that plots two curves on the same set of axes.  One curve will show the average iterative Multimerge time for merging 512 lists as the total number of items varies.  The other curve will show the average recursive Multimerge time for merging 512 lists as the total number of items varies.  Time on the y-axis, item total on the x-axis.

*VaryNElements-Iterative*  A chart that plots only the curve showing the average iterative Multimerge time for merging 512 lists as the total number of items varies.  Time on the y-axis, item total on the x-axis.

*VaryNElements-Recursive*  A chart that plots only the curve showing the average recursive Multimerge time for merging 512 lists as the total number of items varies.  Time on the y-axis, item total on the x-axis.

*VaryNLists*  A chart that plots two curves on the same set of axes.  One curve will show the average iterative Multimerge time for merging when there is a total of 8192 elements, but the number of lists varies.  The other curve will show the average recursive Multimerge time for merging.  Time on the y-axis, number of lists on the x-axis.

*VaryNLists-Iterative*  A chart that plots only the curve showing the average iterative Multimerge time for merging when there is a total of 8192 elements, but the number of lists varies.  Time on the y-axis, number of lists on the x-axis.

*VaryNLists-Recursive*  A chart that plots only the curve showing the average recursive Multimerge time for merging when there is a total of 8192 elements, but the number of lists varies.  Time on the y-axis, number of lists on the x-axis.
