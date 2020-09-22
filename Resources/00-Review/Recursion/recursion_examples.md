**1.** Write the `reverse()` function recursively. This function takes a string and the length of the string as arguments and returns the same string with its characters in the reverse order.

```cpp
void reverse(char *s, int len)
{
	char temp;
	if (len > 1) {
		temp = s[0];
		s[0] = s[len-1];
		s[len-1] = temp;
		reverse(s+1,len-2);
	}
}
```

**2.** A palindrome is a sequence of characters or numbers that looks the same forwards and backwards. For example, "Madam, I'm Adam" is a palindrome because it is spelled the same reading it from front to back as from back to front. The number 12321 is a numerical palindrome. Write a function that takes a string and its length as arguments and recursively determines whether the string is a palindrome: 

```cpp
int ispalindrome(char *s, int len)
{
	if (len <=1 ) 
		return 1;
	else 
		return((s[0] == s[len-1]) && ispalindrome(s+1, len-2));
}
```

**3.** Write a recursive function `void replace(char *s, char from, char to);` that changes all occurrences of 1 character in s from in s to another. For example, if s were "steve", and we were changing from == 'e' to == 'a', s would become "stava".

```cpp
void replace(char *s, char from, char to)
{
	if (*s != '\0') {
		if (*s == from) *s = to;
		replace(s+1, from, to);
	}
}
```

**4.** Write a function to recursively print out an integer in any base from base 2 to 
base 9.

```cpp
void print_base(int num, int base)
{
	if (num / base) 
		print_base(num / base, base);
	putchar(num % base + '0');
}
```

**5.** Write a recursive function `int count_digit(int n, int digit);` to count the number of digits in a number n (n > 0) that are equal to a specified digit. For example, if the digit we're searching for were 2 and the number we're searching were 220, the answer would be 2.

```cpp
int count_digit(int n, int digit)
{
	if (n == 0) return 0;

	if (n % 10 == digit) 
	    return 1 + count_digit(n / 10, digit);
	else 
	    return count_digit(n / 10, digit);
}
```

**6.** For some reason, the computer you're working on doesn't allow you to use the modulo operator `%` to compute the remainder of a division. Your friend proposes the following 

```cpp
function to do it: 
   int remainder(int num, int den)
{
	if (num < den) return num;
	else return(remainder(num - den, den));
}
```
    

Does the above function work? Is there a better way?

Yes, the function does work, however there is a much more efficient method to compute the remainder by taking advantage of integer division: 

```cpp
int remainder(int num, int den) {
	return num - (den * (num / den));
}
```

 
**7.** The following function iteratively computes exponentiation x<sup>n</sup> :

```cpp
int exponentiate_i(int x, int n){

// erased, you do it!

}
```

Write a function to do this recursively in `O(n)` time).

```cpp
int exponentiate_r(int x, int n){
    if (n==0) return 1;
    else return x * exponentiate_r(x, n-1);
}
```

**8.** Use the knowledge that `x`<sup>`n`</sup> `==` `(x2)`<sup>`(n/2)`</sup> when `n` is even to write a more efficient 
solution to the above problem. Not totally necessary, but pretty cool.

- If `n` is even, then `x`<sup>`n`</sup> `==` `(x2)`<sup>`(n/2)`</sup> . 
- If `n` is odd, then `x`<sup>`n`</sup> `==` `x * (x2)`<sup>`((n-1)/2)`</sup> . 

So: 

```cpp
int exponentiate2_r(int x, int n)
{
    if (n==0) return 1;
    else if (n % 2==0) return exponentiate2_r(x*x, n/2);
    else return x * exponentiate2_r(x*x, (n-1) / 2);
}
```

 
**9.** The classic fibonacci problem is where the next term in the sequence is the sum of the previous two terms. For example: `1 1 2 3 5 8 13 ...`

```cpp
int fib(int x) {
    if (x == 0)
        return 0;

    if (x == 1)
        return 1;

    return fib(x-1)+fib(x-2);
}
```
 

**10.** Can anyone fix the function below to make it work like the following:

- When p==0, return `n + m`
- When p==1, return `n * m` 
- When p==2, return `n ^ m` (n<sup>m</sup>)

```cpp
// Not working...
int mystery(n, m, p)
{
	int i, result = 0;
	
	if (p==0) return n+m;
	for (i=0; i< m; i++) result += mystery(result,n,p-1);
	return result;
}
```




 

