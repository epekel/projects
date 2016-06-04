Jerry Zhang
Emre Pekel

We have read and understood the plagiarism policies contained in the file
http://www.ugrad.cs.ubc.ca/∼cs261/2015W2/cheat.html


Observation from 4.2: Removing the synchronization from tictactoe.c
	
	By changing the DO_LOCK value from 1 to 0 we are removing the mutual exclusion access of our critical section in the thread_body function. By doing so, when the three threads attempt to access the critical section at the same time, there will be incorrect operations that corrupt the output.

For 4.3 we used resources from http://stackoverflow.com/questions/26753957/how-to-dynamically-allocateinitialize-a-pthread-array to help us allocate the dynamic pthreads array.