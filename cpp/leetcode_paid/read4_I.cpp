/*
 * The API: int read4(char *buf) reads 4 characters at a time from a file.
 * The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
 * By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
 * Note:
 * The read function will only be called once for each test case.
 */
 
int read4(char *buf)

/**
 * @param buf Destination buffer
 * @param n Maximum number of characters to read
 * @return The number of characters read
 * */
int read(char *buf, int n){
  int i = 0, step = 0;
  while(i<n && (step = read4(buf+i))) i += step;
  //this line is not needed
  if(i>n) buf[n]='\0';
  return min(i, n);
}
