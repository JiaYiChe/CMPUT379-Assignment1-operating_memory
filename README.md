# CMPUT379 Assignment 1:

ccid:jche

mem_1 allocatied a massive array with malloc and initializing it,this action's change is unset, This might caused by the malloc where giving out area randomly by the dynamic requirment 
mem_2 used mmap stored a large file in memory, this action had done the most affect to memory, writing in the file to memroy changed a big area's property to the mode mmap set to(read, write,protect...), and its affect depend on the size of file.
mem_3 invoked a recursive function with a considerable depth of recursion, this action also caused regions occure, but their area is stable and small, it might be the recursive function had already signed an area and the action did leave that space, its just keep cause new region occur whill recursive deeper.

the comment difference of all three action is the regions number increased, by the action many memory address had been used and signed to different properties. first five regions always the same, which I think Its caused by the build of stack, the first few areas were set constant