char* reverse(char arr[])
{
    int i = 0;
    int j = 0;
    char c;
    
    while (arr[i] != '\0')
    {
        i++;
    }
    
    if (i % 2 == 0)
    {
        while (i != j)
        {
            c = arr[j];
            arr[j] = arr[i-1];
            arr[i-1] = c;
            j++;
            i--;
        }
    }
    else
    {
        while (i != j + 1)
        {
            c = arr[j];
            arr[j] = arr[i-1];
            arr[i-1] = c;
            j++;
            i--;
        }
    }
    
    return arr;
}

