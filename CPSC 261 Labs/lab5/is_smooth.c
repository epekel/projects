long is_smooth(long *array, long size)
{
    long index;

    for (index = 1; index < size; index++)
    {
        if (array[index] - array[index-1] > 2 || array[index] - array[index-1] < -2)
	{
	    return 0;
        }
    }
    return 1;
}
