/*
	coding as utf-8
*/ 
/*

    Author  : zong zong
    Connect : zongozngchu0408@gmail.com
    School  : 臺北市立中正高級中學
    GitHub  : https://github.com/zongzong0408/C-snake_game
    
	Last edited : 2022/10/15/06:00PM
    
*/


#include <stdio.h>			//Compiler version gcc  6.3.0
#include <stdlib.h>			//using ASCII standard code
#include <math.h>			// 
#include <string.h>			//			
#include <ctype.h>			//			
#include <time.h>			//			

#define MAX_STRING 50000	//Max string lenght is 500 char
#define MAX_SHIFT 10		//Max range lenght is 500 char
#define MAX_GOBAL 20		//the max number for null
#define MIN_GOBAL 1			//the min number for null


/*
	string range is:
	ASCII code range is 32( ) ~ 126(~) 
	
	1~9, 48 ~ 57
	A~Z, 65 ~ 90
	a~z, 97 ~ 122
	
*/


//=================
//Encrypt functions
//=================
void Encryption(void);				
//古典加密 
void Classical_Cryptography(void);	//Classical Cryptography	古典密碼學 
void CaesarCipher(void);			//Caesar Cipher							凱薩密碼 
void Advanced_CaesarCipher(void);	//Advanced Caesar Cipher				進階 凱薩密碼 
void MirrorCipher(void);			//Mirror Cipher							鏡像翻轉 
void PolybiusCipher(void);			//Polybius Checkerboard Cipher 			波利比奧斯棋盤

//現代加密 
void Modern_Cryptography(void);		//Modern Cryptography 		現代密碼學 
void MorseCipher(void);				//Morse Cipher							摩斯密碼 
int Base64(void);					//Base-64								Base64		
int RSA(void);						//RSA									RSA 加密演算法  
int DH(void);						//Diffie-Hellman key exchage			狄菲赫爾曼公鑰加密(密鑰交換)(輸入兩方私鑰求加密公鑰)
int Advanced_DH(void);				//Advanced Diffie-Hellman Key Exchage	狄菲赫爾曼公鑰加密(密鑰交換)(輸入明文和兩方私鑰求加密字串)
int DES(void);						//Data Encryption Standard 				資料加密標準  
int Triple_DES(void);				//
int AES(void);						//Advanced Encryption Standard 			進階加密標準  
int MD5(void);						//
int SHA_1(void);					//Secure Hash Algorithm 1 				安全雜湊演算法 - 1 - 


//=================
//Decrypt functions
//=================
void Decryption(void);				//not yet
void Violent(void);					//not yet
void Key(void);						//not yet


//========================
//Area of global  variable			//直覺就用全域變數解決了。有明確意義，不會造成變數汙染。 
//========================
int *INTptr[2] = {NULL};			//gobal *int[]  --> 暫存指標 										(Temporary pointers)
//char CHARStr[MAX_STRING] = {0};	//
//char *CHARptr = &CHARStr[0];		//
char *CHARptr = NULL;				// 
char InputStr[MAX_STRING];			//gobal char[] 	--> 要加密的字串 									Encrypt : array of encrypted string
int inputStr[MAX_STRING];			//gobal char[] 	--> 要加密的字串整數陣列 							Encrypt : Integer array of encrypted string
int Len;							//gobal int 	--> 要加密的字串的長度 								Encrypt : Length of encrypted string

char Mod[MAX_STRING];				//gobal char	--> 除法的餘數 										

char MuRange[MAX_SHIFT];			//gobal char[] 	-->	(進階凱薩密碼)位移的字串 						Advanced-DH : array of shitf range
int IMuRange[MAX_SHIFT];			//gobal int[] 	-->	(進階凱薩密碼)位移的整數陣列 					Advanced-DH : integer array of shift range
char MuPoly[MAX_STRING];			//gobal char[] 	--> (波利比奧斯棋盤)要加密的字串的密鑰 				Polybius : array of encrypted string	
int IMuPoly[MAX_STRING];			//gobal int[]	--> (波利比奧斯棋盤)要加密的字串的密鑰的整數陣列 	Polybius : integer array of encrypted string
unsigned LenOfRSA;					//gobal unsigned[] --> (RSA)平方的字串的長度						RSA : Length of pow string




void StartRun(void);													//使用者可能要重複執行，所以宣告一個新的主函式來呼叫 main()
void Error(int Line, int Col)											//Function to tell user where the error is
{
	if(Line != 0 && Col != 0)
	{
		printf("\033[33m%d_%d<Error!>\033[m\n", Line, Col);
	}
}
static inline int isPrime(int number)									//Function to judge is prime number or not (is : 1, no : 0)
{
	for(int i = 2; i < (int)sqrt(number); ++i)		//use sqrt() to decrease time
	{
		if(number % i == 0) return 0;
	}
	
	return 1;										//is --> 1
}
static inline int GCD(int num1, int num2)								//Function to find two numbers Greatest-Common-Divisor(GCD)
{
	if(num1 % num2 == 0)
		return num2;
	else
		return GCD(num2, num1 % num2);
}
unsigned Digits(unsigned number)										//Function to count the number of digits
{
	unsigned digits = 0;
	
	while(number > 0)
	{
		number /= 10;
		++digits;
	}
	
	return digits; 
}
static inline short Comparsion(int digit1, char num1[], int digit2, char num2[])		//Function to judge the size before and after ()
{
	if(num1[digit1 - 1] >= 0 && num2[digit2 - 1] >= 0)									//number >= 0
	{
		if(digit1 == digit2)
		{
			if(num1[digit1 - 1] > num2[digit1 - 1]) return 1;
			else if(num1[digit1 - 1] < num2[digit1 - 1]) return 2;
			else
			{
				int count = 0;
				for(int i = 0; i < digit1; ++i)
				{
					if(num1[i] == num2[i]) ++count;
				}
				if(count == digit1) return 3;	
			}
		}
		else if(digit1 > digit2) return 1;
		else return 2;
	}
	else if(num1[digit1 - 1] >= 0 && num2[digit2 - 1] < 0)								//number < 0
	{
		return 1;
	}
	else if(num1[digit1 - 1] < 0 && num2[digit2 - 1] >= 0)
	{
		return 2;
	}
	else
	{
		if(digit1 == digit2)
		{
			if(num1[digit1 - 1] > num2[digit1 - 1]) return 2;
			else if(num1[digit1 - 1] < num2[digit1 - 1]) return 1;
			else
			{
				int count = 0;
				for(int i = 0; i < digit1; ++i)
				{
					if(num1[i] == num2[i]) ++count;
				}
				if(count == digit1) return 3;	
			}
		}
		else if(digit1 > digit2) return 2;
		else return 1;
	}
}
static inline char* Addition(int digit1, char num1[], int digit2, char num2[])			//Function to do bignum addition arithmetic (+)
{
	char Sum[MAX_STRING];
	memset(Sum, 0, MAX_STRING);
	char *ptr = &Sum[0];
	
	int compare = Comparsion(digit1, num1, digit2, num2);
	
	if(compare == 1 || compare == 3)
	{											//先全部做加減 
		for(int i = 0; i < digit1; ++i) Sum[i] = num1[i] + num2[i];
		for(int i = 0; i < digit1; ++i)
		{
			if(Sum[i] >= 10)
			{
				Sum[i] -= 10;
				++Sum[i + 1];
			}
		}		
	}
	else
	{
		for(int i = 0; i < digit2; ++i) Sum[i] = num2[i] + num1[i];
		for(int i = 0; i < digit2; ++i)
		{
			if(Sum[i] >= 10)
			{
				Sum[i] -= 10;
				++Sum[i + 1];
			}
		}		
	}
	
	//找回傳字串的顯示長度 
	for(int i = 0; ; ++i)
	{
		int count = 0;
		for(int j = i; j < i + 100; ++j)					//若從該字元往後10位均為 0 的話便確定長度為該字元編號 
		{
			if(Sum[j] == 0) ++count;
		}
		if(count == 100)
		{
			INTptr[0] = &i;
			break;
		} 
	}
		
	return ptr;
	
}
static inline char* Subtraction(int digit1, char num1[], int digit2, char num2[])		//Function to do bignum subtraction arithmetic (-)
{
	char Sum[MAX_STRING];
	memset(Sum, 0, MAX_STRING);
	char *ptr = &Sum[0];
	
	int compare = Comparsion(digit1, num1, digit2, num2);
	
	if(compare == 1)
	{
		for(int i = 0; i < digit1; ++i) Sum[i] = num1[i] - num2[i];
		
		for(int i = 0; i < digit1; ++i)
		{
			if(Sum[i] < 0)
			{
				--Sum[i + 1];
				Sum[i] += 10;
			}
		}		
	}
	else if(compare == 3)
	{
		ptr[0] = 0;
		
		*INTptr[0] = 1;
		
		return ptr;
	}
	else
	{
		for(int i = 0; i < digit2 - 1; ++i) Sum[i] = num2[i] - num1[i];
		
		for(int i = 0; i < digit2 - 1; ++i)
		{
			if(Sum[i] < 0)
			{
				--Sum[i + 1];
				Sum[i] += 10;
			}
		}
	}
	
	for(int i = 0; ; ++i)
	{
		int count = 0;
		for(int j = i; j < i + 100; ++j)
		{
			if(Sum[j] == 0) ++count;
		}
		if(count == 100)
		{
			INTptr[0] = &i;
			break;
		} 
	}
		
	return ptr;
	
}
static inline char* Multiplication(int digit1, char num1[], int digit2, char num2[])	//Function to do bignum multiplication arithmetic (*)
{
	char Product[MAX_STRING];
	memset(Product, 0, MAX_STRING);
	char *ptr = &Product[0];
	
	for(int i = 0; i < digit1; ++i)
	{
		for(int j = 0; j < digit2; ++j)
		{
			ptr[i + j] += num1[i] * num2[j];
		}
	}	
	
	for(int i = 0; ; ++i)
	{
		int count = 0;
		for(int j = i; j < i + 100; ++j)
		{
			if(ptr[j] == 0) ++count;
		}
		if(count == 100)
		{
			INTptr[0] = &i;
			
			break;
		}
		
	 	while(ptr[i] >= 10)
		{
			++ptr[i + 1];
			ptr[i] -= 10;
		}
	}
	
	return ptr;
	
}
static inline char* Division(int digit1, char num1[], int digit2, char num2[])			//Function to do bignum division arithmetic (/)
{
	char Quotient[MAX_STRING];						//商數 
	memset(Quotient, 0, MAX_STRING);
	char *ptr1 = &Quotient[0];
	
	int compare = Comparsion(digit1, num1, digit2, num2);
	
	if(compare == 3)
	{
		ptr1[0] = 0;
	
		int temp01 = 0, temp02 = 1;
		
		INTptr[0] = &temp02;
		INTptr[1] = &temp01;
	
		return ptr1;
		
	}		
	else if(digit2 == 1)
	{
		int divisor = num2[0];
		int carry = 0;
		
		for(int i = digit1 - 1; i >= 0; --i)
		{
			carry = carry * 10 + num1[i];
			Quotient[i] = carry / divisor;
			carry %= divisor;
		}
		
		INTptr[1] = &carry;
		
		for(int i = 0; ; ++i)
		{
			int count = 0;
			for(int j = i; j < i + 100; ++j)
			{
				if(Quotient[j] == 0) ++count;
			}
			if(count == 100)
			{
				INTptr[0] = &i;
				break;
			} 
		}
		
		return ptr1; 
	}
	else
	{
		char Product[MAX_STRING];					//暫存乘數 line 214 
		memset(Product, 0, MAX_STRING);
		char *ptr2 = &Product[0];
		int LenOfQuo = 0;	
			
		for(LenOfQuo; Comparsion(digit1, num1, digit2, num2) == 1; ++LenOfQuo)
		{		
			memset(Product, 0, MAX_STRING);
			
			ptr2 = Subtraction(digit1, num1, digit2, num2);
			int TEMP = *INTptr[0];
			digit1 = TEMP;
			INTptr[1] = &TEMP;
			
			for(int j = 0; j < digit1; ++j) num1[j] = ptr2[j];
			
			INTptr[0] = &LenOfQuo;
			
		}
		//printf("(Quo, Mod) len are, (%d %d)\n", *INTptr[0], *INTptr[1]);
		
		CHARptr = &num1[0];
		
		return CHARptr;
	}
		
}
void InputString(int mode)							//Function to input string 輸入字串的函式
//(0 : Encrypt, 1 : Diffie-Hellman, 2 : Advanced Diffie-Hellman, 3 : Polybius, 4 : RSA, 5 : Encrypt, 6 : DES, 7 : AES)
{
	int Fix;			//the variable of need correct seletion or not
	
	if(mode == 0)									//0 : Encrypt : Input encrypted string
	{
		do
		{	 
			printf("\033[32m(The max lenght of encrypted string is 500(int))\033[m\n");
			printf("\033[32mPls enter the encrypted string: \033[m");
			
			setbuf(stdin, NULL);					//清空輸入區存緩 
//			for(int i = 0; i < MAX_STRING; ++i)
//			{
//				InputStr[i] = 0;					//清空 InputStr[] 
//			}
			memset(InputStr, 0, MAX_STRING);
			
			fgets(InputStr, MAX_STRING, stdin);
//			scanf("%s", InputStr);
//			for(int i = 0; i < MAX_STRING - 1; ++i)	//BUG max is 255char
//			{
//				char temp = getchar();
//				if(temp == '\n') break;
//				else InputStr[i] = temp;
//			}	
			
			printf("\033[33mYour encrypted string is --> %s\033[m", InputStr);
			Len = strlen(InputStr) - 1;
			printf("\033[33mThe length of the encrypted string is --> %d\n\033[m", Len);
			
			printf("\033[32mDo you want to modify the encrypted string you entered ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
	
	}
	else if(mode == 1)								//1 : Diffie-Hellman : Input secret key or public key...(two)
	{
		int A, B;
		do
		{	 
			printf("\033[32mPls enter 2 numbers (EX : 6 15): \033[m");
			
			scanf("%d %d", &A, &B);
			
			printf("\033[33mA & B number are --> %d & %d\n\033[m", A, B);
			
			printf("\033[32mDo you want correct any number ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
		
		INTptr[0] = &A;
		INTptr[1] = &B;
	
	}
	else if(mode == 2)								//2 : Advanced Diffie-Hellman : Input secret key or public key...(one)
	{
		int Own;
		do
		{	 
			printf("\033[32mPls enter your own secret key (EX : 6): \033[m");
			
			scanf("%d", &Own);
			
			printf("\033[33mown key number is --> %d\n\033[m", Own);
			
			printf("\033[32mDo you want correct the number you entered ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
		
		INTptr[0] = &Own;
	
	}
	else if(mode == 3)								//3 : Polybius : Input secret string
	{
		do
		{	 
			short INVALID = 1;
			
			while(INVALID == 1)
			{
				INVALID = 0;
				
				printf("\033[32m(The max lenght of encrypted string is 500(int) and except letters (ASCII: A ~ z) all can not be added)\nThe String will all be translate to capital...\033[m\n");
				printf("\033[32mPls enter the encrypted string: \033[m");
				
				setbuf(stdin, NULL);				//清空輸入區存緩 
				memset(InputStr, 0, MAX_STRING);
				
				fgets(InputStr, MAX_STRING, stdin);
				
				Len = strlen(InputStr) - 1;
				
				for(int i = 0; i < Len; ++i)
				{
//					scanf("%c", &InputStr[i]);
					
					if(isalpha(InputStr[i]) == 0)
					{
						printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
						INVALID = 1;
						break;
					}
				}
					
			}
			for(int i = 0; i < Len; ++i)
			{
				if(97 <= InputStr[i] && InputStr[i] <= 122)
				{
					InputStr[i] -= 32;
				}
			}
			
			printf("\033[33mYour encrypted string is --> %s\033[m", InputStr);
			
			printf("\033[33mThe length of the encrypted string is --> %d\n\033[m", Len);
			
			printf("\033[32mDo you want to modify the encrypted string you entered ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
	}
	else if(mode == 4)								//4 : RSA : Input two prime numbers (p & q)
	{
		int p, q;
		do
		{	 
			printf("\033[32mPls enter 2 prime numbers (EX : 61 53): \033[m");
			
			scanf("%d %d", &p, &q);
			
			printf("\033[33mp & q number are --> %d & %d\n\033[m", p, q);
			
			printf("\033[32mDo you want correct any number ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
		
		INTptr[0] = &p;
		INTptr[1] = &q;
	
	}
	else if(mode == 5)								//5 : Encrypt : (char)InputStr --> (int)inputStr
	{
		memset(inputStr, 0, MAX_STRING);
		
		for(int i = 0; i < Len; ++i)
		{
			inputStr[i] = (int)InputStr[i];
		}
	
	}
	else if(mode == 6)								//6 : DES : Enter (8 or 8 * n)bits main Key
	{
		char Key[48000];
		do
		{	 
			printf("\033[32mPls enter your main Key, it must be 8bits or (8 * n)bits (EX : 0001001100110100010101110111100110011011101111001101111111110001): \033[m");
			
			scanf("%s", Key);
			
			printf("\033[33mown key number is --> %s\n\033[m", Key);
			
			printf("\033[32mDo you want correct the Key you entered ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
		
		CHARptr = &Key[0];
	}
	if(mode == 7)									//7 : AES : Input 16bits Plaintext
	{
		do
		{	 
			printf("\033[32m(The max lenght of encrypted string is 16(int))\033[m\n");
			printf("\033[32mPls enter the encrypted string: \033[m");
			
			scanf("%s", InputStr);
			
			Len = strlen(InputStr);
			if(Len != 16)
			{
				printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
				continue;
			}
			
			printf("\033[33mYour encrypted string is --> %s\033[m", InputStr);
			
			printf("\033[33mThe length of the encrypted string is --> %d\n\033[m", Len);
			
			printf("\033[32mDo you want to modify the encrypted string you entered ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
			
		}while(Fix == 1);
	
	}
	
}
int ModeChoice(int limit)							//Function to input selection mode(number of patterns) 輸入選擇模式的函數 
{
	int Mode;			//the variable of mode choose
	int Fix;			//the variable of need correct seletion or not
	int INVALID = 0;	//the variable of mistake number (1 = true, 0 = false)
	do
	{
		printf("\033[32mYour choice: \033[m");
		scanf("%d", &Mode);
		for(int i = 1; i <= limit; ++i)
		{
			if(Mode == i)
			{
				INVALID = 0;
				break;
			}
		}
		if(INVALID == 1)
		{
			printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
			INVALID = 1;
			continue;
		}
		printf("\033[33mYour mode choice is --> %d\033[m\n", Mode);
		
		printf("\033[32mDo you want correct your choice ? Yes(1) || No(2)\033[m\n");
		printf("\033[32mYour choice: \033[m");
		scanf("%d", &Fix);
		
	}while(Fix == 1 || INVALID == 1);
	
	return Mode; 
	
}
int Shift(int limit)								//Function to input displacement 輸入位移量的函式 
//(1 : CaesarCipher, 2 : Advanced_CaesarCipher, 3 : PolybiusCipher, 4 : Diffie-Hellman key exchage)
{
	int Range;			//the variable of shift range 
	int Fix;			//the variable of need correct seletion or not
	int INVALID = 0;	//the variable of mistake number (1 = true, 0 = false)
	if(limit == 1)									//1 : Basic_CaesarCipher
	{
		do
		{
			printf("\033[32mPls enter your move range: \033[m");
			scanf("%d", &Range);
			printf("\033[33mYour move range is --> %d\033[m\n", Range);
			
			printf("\033[32mDo you want correct range ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
		
		}while(Fix == 1);
		
		return Range;
		
	}
	else if(limit == 2)								//2 : CaesarCipher
	{
		int RangeLen;	//the variable of the lenght of MuRange[]
		do
		{ 
			memset(MuRange, 0, MAX_SHIFT);
			memset(IMuRange, 0, MAX_SHIFT);
			
			printf("\033[32mPls enter your move ranges...(EX : 1234 means first char moves 1, second moves 2...etc): \033[m");
			
			scanf("%s", MuRange);
			RangeLen = strlen(MuRange);
			
			printf("\033[33mYour move range is --> %s\033[m\n", MuRange);
			
			printf("\033[32mDo you want correct range ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
		
		}while(Fix == 1);
		
		for(int i = 0; i < RangeLen; ++i) IMuRange[i] = (int)MuRange[i] - 48;
		
		return RangeLen;
		
	}
	else if(limit == 3)								//3 : PolybiusCipher
	{
		int RangeLen;	//the variable of the lenght of MuPoly[]
		do
		{ 			
			do
			{
				memset(MuPoly, 0, MAX_STRING);		//若太大用不到可改 MAX_GOBAL
				memset(IMuPoly, 0, MAX_STRING);
				setbuf(stdin, NULL);
				
				printf("\033[32mPls enter your secret key(only alpha)...\n(EX : ABC means first char moves (int)A, second moves (int)B...etc): \033[m");
				
				fgets(MuPoly, MAX_STRING, stdin);
				RangeLen = strlen(MuPoly) - 1;
				
				for(int i = 0; i < RangeLen; ++i)
				{
					if(isalpha(MuPoly[i]) == 0)
					{
						printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
						INVALID = 1;
						break;
					}
				}
				
			}while(INVALID == 1);
			
			printf("\033[33mYour move range is --> %s\033[m", MuPoly);
			
			printf("\033[32mDo you want correct range ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
		
		}while(Fix == 1);
		
		for(int i = 0; i < RangeLen; ++i)
		{
			if(65 <= MuPoly[i] && MuPoly[i] <= 90)
			{
				IMuPoly[i] = (int)MuPoly[i] - 65;
			}
			else
			{
				IMuPoly[i] = (int)MuPoly[i] - 97;
			}
		}
		
		return RangeLen;
		
	}
	else if(limit == 4)								//4 : Diffie-Hellman key exchage
	{ 
		int Clock;		//the variable of modulo arithmetic	求餘 
		int Base;		//the variable of cardinal number	基數
		do
		{ 
			do
			{
				printf("\033[32mPls enter your clock & base number (EX : 23 5)\n\033[m");
				printf("\033[33m(The clock & base number must be prime number)\n\033[m");
				printf("\033[32mYour choice: \033[m");
				
				scanf("%d %d", &Clock, &Base);
				
				if(isPrime(Clock) == 0)
				{
					printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
					INVALID = 1;
					break;
				}
				if(isPrime(Base) == 0)
				{
					printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
					INVALID = 1;
					break;
				}
				
			}while(INVALID == 1);
			
			printf("\033[33mYour move clock & base is --> %d & %d\n\033[m", Clock, Base);
			
			printf("\033[32mDo you want correct range ? Yes(1) || Not(2)\033[m\n");
			printf("\033[32mYour choice: \033[m");
			scanf("%d", &Fix);
		
		}while(Fix == 1);
		
		INTptr[0] = &Clock;
		INTptr[1] = &Base;
		
		return 1;
		
	}
	
}
void Continue(void)
{
	printf("\033[32m\nDo you want run this program again ? --> OK!(1) || No, thank you!(2)\033[m\n");
	int Mode = ModeChoice(2);		//the variable of mode choose
	
	if(Mode == 1)
	{
		printf("\033[33m\nThe Cryptography.c program has been fully executed and will be restarted soon... =)\033[m\n\n");
	    system("pause");
	    system("cls");
	    StartRun();
	}
	else
	{
		printf("\033[33m\nThe Cryptography.c program has been fully implemented, thank you for using it ! =)\033[m\n");
	}
	//else wiil return --> StartRun() --> main() --> END
}	




//==============================
//***Command Start*** 主函式開始
//==============================
int main()
{	
	//initialization 初始環境 
	system("color A");			//顏色初始化 terminal color 為 green(A) 
	srand(time(NULL));			//亂數種子為 computer time
	
	StartRun();					//參 line:68 
	
	return 0;					//the only situation to END the program
}
void StartRun(void)
{
	//編譯 & 執行開始 compile & run...
	printf("\033[33m		* * *Program Is Starting* * *\033[m\n\n");
	printf("\033[33m		***compiler version gcc  6.3.0***\033[m\n\n");
	printf("\033[33m		***using ASCII standard code***\033[m\n\n");
	
//	for(int i = 0; i < MAX_STRING; ++i)
//	{
//		InputStr[i] = 0;			//清空 InputStr[] 
//	} 	
	memset(InputStr, 0, MAX_STRING);//通過 0 整數值來清除字元陣列 
	//選擇 加密模式 或 解密模式 
	printf("\033[32mWhich mode do you choose ? --> code(1) || decode(2)\033[m\n");
	int Mode = ModeChoice(2);		//the variable of mode choose
		
	if(Mode == 1) Encryption();		//開始加密		
//	else if(Mode == 2) Decode();	//開始解密 
	
	//is going to again or not
    Continue();
    
}


//==============================
//***Encrypt Start*** 主函式開始
//==============================
void Encryption(void)
{
	printf("\033[33m		* * *Is running Encryption program...* * *\033[m\n");
	
	printf("\033[32mWhat kind of cryptography do you want to choose ? --> Classical Cryptography(1) || ModernCry ptography(2)\033[m\n");
	int Mode = ModeChoice(2);		//the variable of mode choose
	
	if(Mode == 1) Classical_Cryptography();
	else if(Mode == 2) Modern_Cryptography();
	
}
//Classical Cryptography		古典密碼學
void Classical_Cryptography(void)
{
	printf("\033[33m		* * *Is running Classical Cryptography program...* * *\033[m\n");
	
	printf("\033[32mWhich encryption method do you want to use ?\033[m\n");
	printf("\033[32m --> Caesar Cipher(1) || Advanced Caesar Cipher(2) || Mirror Cipher(3) || Polybius Cipher(4)\033[m\n");
	int Mode = ModeChoice(5);		//the variable of mode choose
	
	switch(Mode)
	{
		case(1):
			CaesarCipher();
			break;
		case(2):
			Advanced_CaesarCipher();
			break;
		case(3):
			MirrorCipher();
			break;
		case(4):
			PolybiusCipher();
			break;
		default:
			printf("\033[33mYour mode chose is invalid. Pls enter the currect input!\033[m\n");
			break;
	}
	
}
//Caesar Cipher					凱薩密碼  
void CaesarCipher(void)	
{	
	//CaesarCipher program...
	printf("\033[33m		* * *Is running Caesar Cipher program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe operating principle of this cryptography is to add displacement to each character in the string to get the ciphertext.\033[m\n");
	printf("\033[36mEX : (shift is +1) King's Landing --> Ljoh(t!Mboejoh\033[m\n");
	
	//Encrypting string...
	InputString(0);
	int Range = Shift(1);
	
	printf("\033[33mYour Caesar Cipher encrypt string is --> \033[m");
	
	for(int i = 0; i < Len; ++i)
	{
		int temp = (int)InputStr[i];		// 1~9, 48 ~ 57
			
		temp += Range;						// A~Z, 65 ~ 90
				
		while(temp > 127)					// a~z, 97 ~ 122
		{										
			temp = temp - 127 + 32;
		}	
		InputStr[i] = temp;
			
		printf("\033[36m%c\033[m", InputStr[i]);
	
	}	
}
//Advanced Caesar Cipher		進階 凱薩密碼 
void Advanced_CaesarCipher(void)
{
	//Advanced_CaesarCipher program...
	printf("\033[33m		* * *Is running Advanced CaesarCipher program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe operating principle of this cryptography is to add displacement to each character in the string to get the ciphertext.\033[m\n");
	printf("\033[36mEX : (shift is +1) King's Landing --> Ljoh(t!Mboejoh\033[m\n");
	
	//Encrypting string...
	InputString(0);
	int RangeLen = Shift(2);
	
	printf("\033[33mYour Advanced Caesar Cipher encrypt string is --> \033[m");
	
	int count = 0;						//Range count 計算 MuRange[] 的區間，以符合(EX : 1234 means first char moves 1, second moves 2...etc)
	for(int i = 0; i < Len; ++i)
	{
		if(count < RangeLen)			//假設 RangeLen = 4, count == 4 時會歸零，range 0 ~ 3 , 4 --> 0 
		{	
			InputStr[i] = (int)InputStr[i] + IMuRange[count];
			printf("\033[36m%c\033[m", InputStr[i]);
			++count;
		}
		else
		{
			count = 0;
			InputStr[i] = (int)InputStr[i] + IMuRange[count];
			printf("\033[36m%c\033[m", InputStr[i]);
			++count;
		}
	}
	
}
//Mirror Cipher					鏡像翻轉 
void MirrorCipher(void)
{
	//MirrorCipher program...
	printf("\033[33m		* * *Is running MirrorCipher program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe working principle of this cryptography is to reverse each word in the string to get the ciphertext.\033[m\n");
	printf("\033[36mEX : King's Landing --> gnidnaL s'gniK\033[m\n");
	
	//Encrypting string...
	InputString(0);
	
	printf("\033[33mYour Mirror Cipher encrypt string is --> \033[m");
	
//	int words;							//反轉字串裡的單詞 
//	for(int i = 0; i < Len; ++i)
//	{
//		if(isalpha(InputStr[i]) != 0 && isalpha(InputStr[i + 1]) == 0)
//		{
//			++words;
//		}
//	}
//	
//	int location[words][2];
//	memset(location, 0, words);
//	
//	int count = 1;
//	for(int i = 0; i < Len; ++i)
//	{
//		if(isalpha(InputStr[i]) != 0 && isalpha(InputStr[i + 1]) == 0)
//		{
//			location[count][0] = location[count - 1][1] + 2;
//			location[count][1] = i;
//			++count;
//		}
//	}
//
//	for(int i = 1; i <= words; ++i)
//	{
//		for(int j = location[i + 1][1]; j >= location[i + 1][0]; --j)
//		{
//			printf("\033[36m%c\033[m", InputStr[j]);
//		}
//		printf(" ");
//	}
	
	for(int i = Len - 1; i >= 0; --i)	//單純倒轉字串 
	{
		printf("\033[36m%c\033[m", InputStr[i]);
	}
	
}
//Polybius Checkerboard Cipher	波利比奧斯棋盤
void PolybiusCipher(void)
{
	//PolybiusCipher program...
	printf("\033[33m		* * *Is running Polybius Cipher program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe operating principle of this cryptography is to use multiple CaesarCipher in the string to get the ciphertext.\033[m\n");
	printf("\033[36mEX : (shift is +1) King's Landing --> Ljoh(t!Mboejoh\033[m\n");
	
	//Encrypting string...
	InputString(3);
	int RangeLen = Shift(3);
	
	printf("\033[33mYour Polybius Cipher encrypt string is --> \033[m");
	
	int count = 0;						//Range count 計算 Polybius[] 的區間，以符合(EX : 1234 means first char moves 1, second moves 2...etc)
	for(int i = 0; i < Len; ++i)
	{
		if(count < RangeLen)			//假設 RangeLen = 4, count == 4 時會歸零，range 0 ~ 3 , 4 --> 0 
		{
			InputStr[i] = (int)InputStr[i] + IMuPoly[count];
			printf("\033[36m%c\033[m", InputStr[i]);
			++count;
		}
		else
		{
			count = 0;
			InputStr[i] = (int)InputStr[i] + IMuPoly[count];
			printf("\033[36m%c\033[m", InputStr[i]);
			++count;
		}
	}
	
}




//==============================
//***Decrypt Start*** 主函式開始
//==============================
//Classical Cryptography		古典密碼學
void Modern_Cryptography(void)	
{
	printf("\033[33m		* * *Is running Modern Cryptography program...* * *\033[m\n");
	
	printf("\033[32mWhich encryption method do you want to use ?\033[m\n");
	printf("\033[32m --> Morse Cipher(1) || Base64(2) || RSA(3) || DH(4) || Advanced DH(5)\n\tDES(6) || Triple_DES(7) || AES(8) || MD5(9) || SHA-1(10)\033[m\n");
	int Mode = ModeChoice(9);		//the variable of mode choose
	
	switch(Mode)
	{
		case(1):
			MorseCipher();
			break;
		case(2):
			Base64();
			break;
		case(3):
			RSA();
			break;
		case(4):
			DH();
			break;
		case(5):
			Advanced_DH();
			break;
		case(6):
			DES();
			break;
//		case(7):
//			Triple_DES();
//			break;
		case(8):
			AES();
			break;
//		case(9):
//			MD5();
//			break;
//		case(10):
//			SHA_1();
//			break;
		default:
			printf("\033[33mYour mode chose is invalid. Pls enter the currect input!\033[m\n");
			break;
	}
}
//Morse Cipher					摩斯密碼
void MorseCipher(void)
{
	//BasicCaesarCipher program...
	printf("\033[33m		* * *Is running Morse Cipher program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe operating principle of this cryptography is to convert each character in the string into Morse code and to get the ciphertext.\033[m\n");
	printf("\033[36mEX : (shift is +1) King's Landing --> Ljoh(t!Mboejoh\033[m\n");
	
	static const char Alpha[26][4] = {
	    ".-",   //A
	    "-...", //B
	    "-.-.", //C
	    "-..",  //D
	    ".",    //E
	    "..-.", //F
	    "--.",  //G
	    "....", //H
	    "..",   //I
	    ".---", //J
	    "-.-",  //K
	    ".-..", //L
	    "--",   //M
	    "-.",   //N
	    "---",  //O
	    ".--.", //P
	    "--.-", //Q
	    ".-.",  //R
	    "...",  //S
	    "-",    //T
	    "..-",  //U
	    "...-", //V
	    ".--" , //W
	    "-..-", //X
	    "-.--", //Y
	    "--..", //Z
	};
	static const char Num[10][5] = {
	    "-----", //0
	    ".----", //1
	    "..---", //2
	    "...--", //3
	    "....-", //4
	    ".....", //5
	    "-....", //6
	    "--...", //7
	    "---..", //8
	    "----.", //9
	};
	static const char Dot[][6] = { 		//Punctuation Marks
		".-.-.-", //.
		"--..--", //,
		"..--..", //?
		".----.", //'
		"-.-.--", //!
		"-..-.",  ///
		//...
	};
	
	//Encrypting string...
	InputString(0);
	
	printf("\033[33mYour Morse Cipher encrypt string is --> \033[m");
	
	for(int i = 0; i < Len; ++i)
	{
		int location; 
		if(isalpha(InputStr[i]) != 0)		//Alpha
		{
			if(97 <= InputStr[i] && InputStr[i] <= 122)			// A ~ Z 97 ~ 122
			{
				location = InputStr[i] - 97;
				for(int j = 0; j < 4; ++j)
				{
					if(Alpha[location][j] != ' ') printf("%c", Alpha[location][j]);
				}		
			}
			else //if(65 <= InputStr[i] && InputStr[i] <= 90)	// a ~ z 65 ~ 90
			{
				location = InputStr[i] - 65;
				for(int j = 0; j < 4; ++j)
				{
					if(Alpha[location][j] != ' ') printf("%c", Alpha[location][j]);
				}		
			}
		}
		else if(isdigit(InputStr[i]) != 0)	//Number
		{
			location = InputStr[i] - 48;
			for(int j = 0; j < 5; ++j)
			{
				if(Num[location][j] != ' ') printf("%c", Num[location][j]);
			}	
		}
		else if(InputStr[i] == ' ') printf("/");
		
		printf(" ");
		
	}
}
//Diffie-Hellman key exchage	狄菲赫爾曼密鑰交換 
int DH(void)
{
	//DH program...
	printf("\033[33m		* * *Is running Diffie-Hellman key exchage program...* * *\033[m\n");

	//Explain the principle 解釋原理 
	/*
		1. 選出一個較大的質數 p(Clcok)，接著選出質數 p 的原根 q(Base) (q 最好較小，組合較多)，並公開兩數。 
		2. 甲方選出任一數 A(私人密鑰)，並計算 APPN = pow(q, A)mod p 並公開。 
		3. 乙方選出任一數 B(私人密鑰)，並計算 BPPN = pow(q, B)mod p 並公開。
		4. 甲乙雙方傳送各自 PPN 給對方。
		5. 甲乙雙方各自計算 K(私密公鑰)，KA = pow(BPPN, A)mod p, KB = pow(APPN, B)mod p，可得 KA = KB，即私密公鑰。
		6. 由計算 K(私密公鑰)之方法可知 : KA = (q^B^A)mod p, KB = (q^A^B)mod p，所以 (q^B^A) = (q^A^B)。因此可得另一人之密鑰。 
	*/
	printf("\033[36mThe principle of this cryptography is to input two prime numbers,\nwhich are clock number (using the remainder method) and base number (must be the primitive roots of the clock numbers),\nand then go through a series of remainder methods and prime numbers to multiply... etc,\nand finally to get the Ciphertext.\033[m\n");
	printf("\033[36mEX : clock is 23, base is 5 & A use 6, B use 15 --> common key is 2\033[m\n");
	
	//Encrypting string...
	
	//1.
	Shift(4);
	int Clock = *INTptr[0];	//the variable of modulo arithmetic	求餘 
	int Base = *INTptr[1];	//the variable of cardinal number	基數
	
	//2. 3.
	InputString(1);
	int A = *INTptr[0];
	int B = *INTptr[1];
	
	unsigned Appn = (size_t)pow(Base, A) % Clock;
	unsigned Bppn = (size_t)pow(Base, B) % Clock;
	
	//5. 6.
	unsigned KeyA = (size_t)pow(Bppn, A) % Clock; 
	unsigned KeyB = (size_t)pow(Appn, B) % Clock;
	
	if(KeyA == KeyB)
	{
		printf("\033[33mYou Secret Public Key is --> \033[m");
		printf("\033[36m%u\033[m", KeyA);
	}
	else
	{
		Error(2, 3);
	}
		
	return 1;
	
}
//Advanced Encryption Standard 	進階加密標準 
int Advanced_DH(void)
{
	//DH program...
	printf("\033[33m		* * *Is running Advanced Diffie-Hellman key exchage program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe principle of this cryptography is to input two prime numbers,\nwhich are clock number (using the remainder method) and base number (must be the primitive roots of the clock numbers),\nand then go through a series of remainder methods and prime numbers to multiply... etc,\nand finally to get the Ciphertext.\033[m\n");
	printf("\033[36mEX : clock is 23, base is 5 & A use 6, B use 15 --> common key is 2\033[m\n");
	
	//Encrypting string...
	InputString(2);
	
	//1.
	Shift(4);
	int Clock = *INTptr[0];	//the variable of modulo arithmetic	求餘 
	int Base = *INTptr[1];	//the variable of cardinal number	基數
	
	//2. 3.
	int Own = *INTptr[0];
	
	unsigned Ownppn = (size_t)pow(Base, Own) % Clock;
	
	//5. 6. 
	
	InputString(0);
	
	printf("\033[33mYou encrypted string is --> \n\033[m");
	
	for(int i = 0; i < Len; ++i)
	{
		int str = InputStr[i] - 32;

		unsigned strPPN = (size_t)pow(Base, str) % Clock;
		
		unsigned strKey= (size_t)pow(Ownppn, str) % Clock;
		unsigned OwnKey= (size_t)pow(strPPN, Own) % Clock;		
		
		//Over Flow
		if(strKey == OwnKey)
		{
//			printf("\033[33mYou Secret Key is --> \033[m");
//			printf("\033[36m%u\033[m", OwnKey);
			str += OwnKey + 32;
		}
		else
		{
//			Error(2, 4);
			str += OwnKey + 32;
		}
		
		printf("\033[36m%c\033[m", str);
		
	}
	
	return 1;
		
} 
//Base-64
int Base64(void)
{
	//Base64 program...
	printf("\033[33m		* * *Is running Base64 program...* * *\033[m\n"); 
	
	//Explain the principle 解釋原理 
	printf("\033[36mThe principle is to re-divide every 3 bytes of binary data into 4 groups\n(each three 8-bit groups, that is, a total of 24 bits, which can be represented by four 6-bit Base64 values),\nand then look up the code table as an index , Get the corresponding characters,\nand then get the encoded string.\033[m\n");
	printf("\033[36mEX : NEW --> TkVX\033[m\n");
	
	//Encrypting string...
	InputString(0); 
	InputString(5); 
	
	int baseN;							//baseN:是新編碼的間隔長度(6 * baseN) 
	int baseMAX = 8 * Len;				//baseMAX:是原加密字串一個字元8bits後的長度(8 * len)
	
	if(Len * 8 % 6 != 0) baseN = Len * 8 / 6 + 1;		//judge is float or not
	else baseN = Len * 8 / 6;
	
	
	int bin[Len][8];					//Dec(10)instr --> Bin(2) 
	int base[baseN][6];					//Bin(8*)instr --> Bin(6*)
	
	for(int i = 0; i < Len; ++i)		
	{
		for(int j = 0; j < 8; ++j)		//initialization bin[], base[]
		{
			if(j < 6) base[i][j] = 0;
			else bin[i][j] = 0;
		}
	}
	for(int i = 0; i < Len; ++i)		//Dec --> Bin
	{
		int temp = inputStr[i];
		int j = 0;
		while(temp > 0)
		{
			bin[i][j] = temp % 2;
			temp /= 2;
			++j;
		}
	}
//	for(int i = 0; i < Len; ++i)		//Dec show
//	{
//		for(int j = 8 - 1; j >= 0; --j)
//		{
//			printf("%d", bin[i][j]);
//		}
//		printf("\n");
//	}
	int icount = 0, jcount = 8 - 1, count = 0;			//Bin --> Bin
	for(int i = 0; i < baseN; ++i)		
	{
		for(int j = 0; j < 6; ++j)
		{
			if(count <= baseMAX)
			{
				if(jcount == -1)
				{
					jcount = 7;
					++icount;
				}
				base[i][j] = bin[icount][jcount];
				--jcount;
				++count;
			}
			else
			{
				if(jcount == -1)
				{
					jcount = 7;
					++icount;
				}
				base[i][j] = 0;
				--jcount;
				++count;
			}
		}
	}
//	for(int i = 0; i < baseN; ++i)		//Bin show
//	{
//		for(int j = 0; j < 6; ++j)
//		{
//			printf("\033[36m%d\033[m", base[i][j]);
//		}
//		printf("\n");
//	}
	for(int i = 0; i < baseN; ++i)		//finall code
	{
		size_t temp = 0;
		for(int j = 0; j < 6; ++j)
		{
			temp += base[i][j] * (size_t)pow(2, 5 - j);
		}
		
		printf("\033[36m%d\t\033[m", temp);
		
		if(0 <= temp && temp <= 25)
		{
			printf("\033[36m%c\n\033[m", temp + 65);	
		}
		else if(26 <= temp && temp <= 51)
		{
			printf("\033[36m%c\n\033[m", temp + 71);
		}
		else if(52 <= temp && temp <= 61)
		{
			printf("\033[36m%c\n\033[m", temp - 4);
		}
		
	}
	
	return 1;
	
}
//RSA
int RSA(void)
{
	//RSA program...
	printf("\033[33m		* * *Is running RSA program...* * *\033[m\n");
	
	//Explain the principle 解釋原理 
	/*
		符號意義 : 
		
		p, q : 任意兩質數  
		N = p * q : 計算出正整數  
		EulerN : N 的 歐拉函數()  
		e , limit(1 < e < Euler(N), 且與 N 互質) : 公鑰  
		d : 密鑰(e 的模反元素) 
		 
		{e, N} : 公鑰組  
		{d, N} : 密鑰組  
		
		流程 : 
		
		1. 求 p, q 兩任意質數 
		2. 計算 N  
		3. 計算 Euler(N)
		4. 求隨機數 e
		5. 根據 e * d / EulerN = k...1
		   可得 d = (EulerN * k + 1) / e, ++k --> k = 1, 2, 3...
		6. 將要加密的字串轉成ASCII碼，然後 pow(字串裡的單一字元, e) mod N 
		
	*/
	printf("\033[36m1. Find p, q two arbitrary prime numbers\n2. Calculate N\n3. Calculate Euler(N)\n4. Find the random number e\n5. According to e * d / EulerN = k...1\nWe can get d = (EulerN * k + 1) / e, ++k --> k = 1, 2, 3...\n6. Convert the string to be encrypted into ASCII code, and then pow(a single character in the encrypted string, e) mod N\033[m\n");
	printf("\033[36mEX : \033[m\n");
	
	//Encrypting string...
	InputString(4);
	
	int p = *INTptr[0];
	int q = *INTptr[1];
		
	int N = p * q;							//calculate Positive integer(Len of secret key)
	printf("\033[32mp * q(N) is \033[m");
	printf("\033[36m%d\033[m\n", N);
	
	int NLen = 0;							//calculate len of secret key
	int TEMP = N;
	
	while(TEMP > 0)
	{
		TEMP /= 10;
		++NLen;
	}
	TEMP = N;
	int SKL = 0;							//Len of secret key	
	while(TEMP > 0)							//Dec --> Bin
	{
		TEMP /= 2;		
		++SKL;
	}
	printf("\033[33mLen of Secret-Key is \033[m");
	printf("\033[36m%u\033[m\n", SKL);
	
	int EulerN = (p - 1) * (q - 1);
	printf("\033[32mEuler function of N is \033[m");
	printf("\033[36m%lu\033[m\n", EulerN);
	  
	int IMUrand[EulerN - 2];								//IMUrand[] == e 的所有可能 
	for(int i = 2; i < EulerN; ++i)							//不得重複選取。可用動態陣列、CPU計算、大量記憶體擇一
	{														//使用 洗牌演算法 取一定範圍亂數
		IMUrand[i - 2] = i; 								
	}
	for(int i = 0; i < (int)pow(10, 6); ++i)				//洗牌，百萬次 
	{
		int TEMP01 = rand() % ((EulerN - 1) - 2 + 1) + 2; 
		int TEMP02 = rand() % ((EulerN - 1) - 2 + 1) + 2;
		
		int TEMP = IMUrand[TEMP01];
		IMUrand[TEMP01] = IMUrand[TEMP02];
		IMUrand[TEMP02] = TEMP;		
	}
	int e = 0;
	for(int i = 0; i < EulerN; ++i)
	{
		if(GCD(EulerN, IMUrand[i]) == 1)
		{
			e = IMUrand[i];
			printf("\033[33mPublic-key number is \033[m");	//public key nummber
			printf("\033[36m%zu\033[m\n", e);
			
			printf("\033[32mIt is random\033[m");
			printf("\033[36m %d \033[m", (int)pow(10, 6) + i + 1);
			printf("\033[32mtimes...\033[m\n");
			
			break;
		}
	}
	
	int d = 0;
	for(int k = 1; k < EulerN; ++k)					//k : 1, 2, 3...
	{
		double d = ((double)EulerN * k + 1) / (double)e;
		if((int)(d * (double)10.0) % 10 == 0)
		{
			printf("\033[33mSecret-key number is \033[m");	//secret key nummber
			printf("\033[36m%d\033[m\n", (int)d);	
			break;
		}
	}
	
	InputString(0);  
	InputString(5);
		
	printf("\033[33mYour encrypt string is \033[m");
	
	char StrSum[MAX_STRING];
	memset(StrSum, 0, MAX_STRING);
	char *ptrOfSum = &StrSum[0];
	
	for(int j = 0; j < Len; ++j)
	{
		memset(StrSum, 0, MAX_STRING);
		
		int TEMP = inputStr[j];
		
		int dight_TEMP = Digits(TEMP);
		
		char StrTEMP[MAX_STRING];
		memset(StrTEMP, 0, MAX_STRING);
		
		for(int i = dight_TEMP - 1; i >= 0; --i) StrTEMP[i] = TEMP / (unsigned)pow(10, i) % 10; 
		
		for(int i = 0; i < e; ++i)
		{
			if(i == 0)
			{
				ptrOfSum = Multiplication(dight_TEMP, StrTEMP, dight_TEMP, StrTEMP);
				LenOfRSA = *INTptr[0];
				for(int k = 0; k < LenOfRSA; ++k) StrSum[k] = ptrOfSum[k];
//				for(int k = 0; k < LenOfRSA; ++k) printf("%d", StrSum[k]);
//				printf("\n");
			}
			else
			{
				ptrOfSum = Multiplication(LenOfRSA, StrSum, dight_TEMP, StrTEMP);
				LenOfRSA = *INTptr[0];
				for(int k = 0; k < LenOfRSA; ++k) StrSum[k] = ptrOfSum[k];
//				for(int k = 0; k < LenOfRSA; ++k) printf("%d", StrSum[k]);
//				printf("\n");
			}
		}
		
		int digitOfN = Digits(N);							//unsigned N --> char N
		
		char StrN[MAX_STRING];
		memset(StrN, 0, MAX_STRING);
		char *ptrOfN = &StrN[0];
		
		char StrNmax[MAX_STRING];
		int digitOfNmax = digitOfN;
		memset(StrNmax, 0, MAX_STRING);
		char *ptrOfNmax = &StrNmax[0];
		
		char RATE[1] = {[0] = 10};
		
		for(int i = digitOfN - 1; i >= 0; --i)
		{
			StrN[i] = N / (int)pow(10, i) % 10;
			StrNmax[i] = StrN[i];
		}

		while(1)
		{
			if(Comparsion(LenOfRSA, StrSum, digitOfNmax, StrNmax) == 3) goto Equal;
			else if(Comparsion(LenOfRSA, StrSum, digitOfNmax, StrNmax) == 1)
			{
				ptrOfNmax = Multiplication(digitOfNmax, StrNmax, 1, RATE);
				digitOfNmax = *INTptr[0];
				for(int k = 0; k < digitOfNmax; ++k) StrNmax[k] = ptrOfNmax[k];
			}
			else if(Comparsion(LenOfRSA, StrSum, digitOfNmax, StrNmax) == 2)
			{
				ptrOfNmax = Division(digitOfNmax, StrNmax, 1, RATE);
				digitOfNmax = *INTptr[0];
				for(int k = 0; k < digitOfNmax; ++k) StrNmax[k] = ptrOfNmax[k];
				
				break;
			}
		}
		
		Equal:
			printf("\033[36m%d \033[m", 0);
		
		ptrOfSum = Subtraction(LenOfRSA, StrSum, digitOfNmax, StrNmax);
		LenOfRSA = *INTptr[0];
		for(int k = 0; k < LenOfRSA; ++k) StrSum[k] = ptrOfSum[k];
		
		//ptrOfSum <-- Quotient[]
		ptrOfSum = Division(LenOfRSA, StrSum, digitOfN, StrN);
		LenOfRSA = *INTptr[1];								//lenght of Mod	
		
		//if(LenOfRSA != 0) printf("\n\033[36mmod len : %d\n\033[m", LenOfRSA);
		
		for(int i = 0; i < LenOfRSA; ++i) StrSum[i] = ptrOfSum[i];
		for(int i = LenOfRSA - 1; i >= 0; --i) printf("\033[36m%d\033[m", StrSum[i]);
		printf(" ");
				
	}
		
	return 1;
	
}
//Data Encryption Standard		資料加密標準 
int DES(void)
{
	//Data Encryption Standard program...
	printf("\033[33m		* * *Is running Data Encryption Standard program...* * *\033[m\n");
	
	/*
	大概流程 :
	
		1. 將輸入的資料做 初始置換 IP(initial permutation，初始排列)
		
		2. 將資料切割成左右。
		
			(F函式， F-function(Feistel Cipher) ) x 16
				3. 右邊資料作 F函式 後跟左邊做 XOR。
			
				4. 然後左右邊對調後重複 F函式 16次。
		
		5. 最後在做 FP(逆 IP)。
		
		F函式，F-function(Feistel Cipher) :
	
			1. 擴張 E (Expansion)
			
			2. 跟子密鑰 ki 做 XOR
			
			3. 進入 S-Box (Substitution-Box)代換 
			
			4. 排列 P (Permutation)
	
	.C 大概流程 :
	
		1.	輸入 : 明文(資料)
	 
		2.	進行 IP 
		
		3.	金鑰 K 的獲取 
		
		4.	密碼函式 F-function(Feistel Cipher) 
		
		5.	尾置換 FP
	
	*/ 
	
	//Explain the principle 解釋原理 
	printf("\033[36m\n1. Input plaintext(8bits or 8 * n)\n2. Permutation plaintext by use IP table\n3. Input the main Key K(8bits or 8 * n)\n4. Enter data in F-function(Feistel Cipher)\n5. Permutation CipherText by use FP table\033[m\n");
	printf("\033[36m\nEX : \n\tPlainText[64] is 0000000100100011010001010110011110001001101010111100110111101111\n\tKey[64] is 0001001100110100010101110111100110011011101111001101111111110001\033[m\n\n");
	
	//Encrypting string...
	
	static const int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,			//(IP) Initial permutation，初始排列 
				60, 52, 44, 36, 28, 20, 12, 4,							//重新排列明文的過程   
				62, 54, 46, 38, 30, 22, 14, 6,
				64, 56, 48, 40, 32, 24, 16, 8,
				57, 49, 41, 33, 25, 17, 9,  1,
				59, 51, 43, 35, 27, 19, 11, 3,
				61, 53, 45, 37, 29, 21, 13, 5,
				63, 55, 47, 39, 31, 23, 15, 7};
	
	static const int FP[64] = {40, 8, 48, 16, 56, 24, 64, 32,			//(FP) Inverse initial permutation 最終排列排列(初始排列的逆運算) 
				39, 7,  47, 15, 55, 23, 63, 31,
				38, 6,  46, 14, 54, 22, 62, 30,
				37, 5,  45, 13, 53, 21, 61, 29,
				36, 4,  44, 12, 52, 20, 60, 28,
				35, 3,  43, 11, 51, 19, 59, 27,
				34, 2,  42, 10, 50, 18, 58, 26,
				33, 1,  41, 9,  49, 17, 57, 25};
	
	static const int PC1[56] = {57, 49, 41, 33, 25, 17, 9,				//(PC_1) Permuted choice 1 
				1,  58, 50, 42, 34, 26, 18,								//將 F函數 生成的子密鑰去除 奇偶較驗(parity bit)  
				10, 2,  59, 51, 43, 35, 27,
				19, 11, 3,  60, 52, 44, 36,
				63, 55, 47, 39, 31, 23, 15,
				7,  62, 54, 46, 38, 30, 22,
				14, 6,  61, 53, 45, 37, 29,
				21, 13, 5  ,28, 20, 12, 4};
	
	static const int PC2[48] = {14, 17, 11, 24, 1, 5,					//(PC_2) Permuted choice 2
				3,  28, 15, 6,  21, 10,									//將 F函數 生成的子密鑰去除 奇偶較驗(parity bit) 
				23, 19, 12, 4,  26, 8,
				16, 7,  27, 20, 13, 2,
				41, 52, 31, 37, 47, 55,
				30, 40, 51, 45, 33, 48,
				44, 49, 39, 56, 34, 53,
				46, 42, 50, 36, 29, 32};
		
	static const int E[48] = {32, 1, 2, 3, 4, 5,						//(E) Expansion
				4,  5,  6,  7,  8,  9,									//
				8,  9,  10, 11, 12, 13,
				12, 13, 14, 15, 16, 17,
				16, 17, 18, 19, 20, 21,
				20, 21, 22, 23, 24, 25,
				24, 25, 26, 27, 28, 29,
				28, 29, 30, 31, 32, 1};
	
	static const int P[32] = {16, 7, 20, 21,							//(P) Permutation
				29, 12, 28, 17,											//
				1,  15, 23, 26,
				5,  18, 31, 10,
				2,  8,  24, 14,
				32, 27, 3,  9,
				19, 13, 30, 6,
				22, 11, 4,  25};
	
	static const int S[8][4][16] = {									//(S) S-Box
				//R1													//經過 XOR 後資料 48bits --> 6 * 8(bits) ==> 將 6bits 轉成 4bits 
				14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7,		
				0,  15, 7,  4,  14, 2,  13, 1,  10, 6,  12, 11, 9,  5,  3,  8,
				4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0,
				15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0,  6,  13,
				//R2
				15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5,  10,
				3,  13, 4,  7,  15, 2,  8,  14, 12, 0,  1,  10, 6,  9,  11, 5,
				0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15,
				13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 10, 5,  14, 9,
				//R3
				10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
				13, 7,  0,  9,  3,  4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,
				13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
				1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12,
				//R4
				7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15,
				13, 8,  11, 5,  6,  15, 0,  3,  4,  7,  2,  12, 1,  10, 14, 9,
				10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4,
				3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7,  2,  14,
				//R5
				2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9,
				14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9,  8,  6,
				4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14,
				11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4,  5,  3,
				//R6
				12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
				10, 15, 4,  2,  7,  12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8,
				9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
				4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13,
				//R7
				4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1,
				13, 0,  11, 7,  4,  9,  1,  10, 14, 3,  5,  12, 2,  15, 8,  6,
				1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2,
				6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2,  3,  12,
				//R8
				13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
				1,  15, 13, 8,  10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2,
				7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
				2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11};	
				
	
	//排列函式 (P)，Permutation(輸入的指標陣列，置換表，儲存結果的指標陣列，置換長度) 
	//Function to : 輸入一個長度為(Len)的指標陣列(*Input)，並根據置換表(Table)來重新排列，將結果存入儲存結果的指標陣列(*Output) 
	void Permutation(char* Input, const int* Table, char* Output, int Len)
	{
		for(int i = 0; i < Len; ++i)
		{
			Output[i] = Input[Table[i] - 1];				//減一是因為陣列由 0 開始排列 
		}
		
		return ;
	}

	//左移函式 (L)， Rotate_Left(輸入的指標陣列，儲存結果的指標陣列，置換長度，迴圈左移長度)
	//Function to : 輸入一個長度為(Len)的指標陣列(*Input)，並迴圈左移 Shift 位後，將結果存入貯存結果的指標陣列(*Output) 
	void Rotate_Left(char* Input, char* Output, int Len, int Shift)
	{
		for(int i = 0; i < Len; ++i)
		{
			Output[i] = Input[(i + Shift) % Len];			//用取餘數的方法來迴圈左移 
		}
		for(int i = 0; i < Len; ++i) Input[i] = Output[i];
		
		return ;
	}
	
	//十進位轉二進位函式 (Dec --> Bin)
	//Function to : 將十進位制c轉換成二進位制並存到rlt陣列，借鑑了位元組轉位元函式
	void DecToBin(char Decimal, char* Binary)
	{
		//bytes --> bits, 1 byte == 4 bits 
		for(int i = 0; i < 4; ++i)
		{
			char m = 1;
			
			*(Binary + 3 - i) = (Decimal & (m << i)) >> i;
		}
	}
	
	//子金鑰(ki)獲取函式 (K)， SubKey_Generate(金鑰陣列 64bits，子金鑰陣列)
	//Function to : 輸入 主金鑰(Key)，再生成其他 16 個 子金鑰(SubKey) 
	void SubKey_Generate(char* Key, char SubKey[][48])
	{
		char KLeft_part[17][28], KRigit_part[17][28];
		char KTempArray[56];
		
		Permutation(Key, PC1, KTempArray, 56); 				//將金鑰用 PC_1 置換  
		
		for(int i = 0; i < 56; ++i)
		{
			if(i < 28) KLeft_part[0][i] = KTempArray[i];
			else KRigit_part[0][i - 28] = KTempArray[i];
		}
		for(int i = 1; i <= 16; ++i)						
		{
			if(i == 1 || i == 2 || i == 9 || i == 16)		//如果為第 1、2、9、16 輪，則 KLeft_part[]、KRigit_part[] 迴圈左移1位，其他輪次則迴圈左移2位
			{
				Rotate_Left(KLeft_part[i - 1], KLeft_part[i], 28, 1);
				Rotate_Left(KRigit_part[i - 1], KRigit_part[i], 28, 1);
			}
			else
			{
				Rotate_Left(KLeft_part[i - 1], KLeft_part[i], 28, 2);
				Rotate_Left(KRigit_part[i - 1], KRigit_part[i], 28,2);
			}
			
			for(int j = 0; j < 56; ++j)						//將 Left_part[] & Rigit_part[] 兩部合拼成 TempArray[] 
			{ 
				if(j < 28) KTempArray[j] = KLeft_part[i][j];
				else KTempArray[j] = KRigit_part[i][j - 28];
			}
			
			Permutation(KTempArray, PC2, SubKey[i - 1], 48); //用 PC_2 得到 子金鑰(ki) 
			
		}
		
//		printf("16 Sub-Keys are：\n");
//		for(int i = 0; i < 16; ++i)
//		{
//		    printf("SubKey-%d is : ", i);
//			for(int j = 0; j < 48; ++j) printf("%d", SubKey[i][j]);
//			printf("\n");
//		}
//		printf("\n\n\n\n");
		
	}
	
	//費斯妥密碼 (F)， Feistel_Cipher(明文 64bits，金鑰 64bits， 密文 64bits) 
	//Function to : 輸入 明文(PlainText)和 主金鑰(Key)，輸出 密文(CipherText) 
	void Feistel_Cipher(char* Input, char* Key, char* Output)	
	{
		char Left_part[17][32], Right_part[17][32];
		char TempArray[64], SubKey[16][48];
		
		//2. permutation IP
		Permutation(Input, IP, TempArray, 64); 				//將明文進行 IP置換 
		
//		printf("Permutation IP : ");
//		for(int i = 0; i < 64; i++) printf("%d", TempArray[i]);
//		printf("\n\n");
		
		//3. get ki
		SubKey_Generate(Key, SubKey); 						//獲取子金鑰  
		
		for(int i = 0; i < 64; ++i)							//初始化 Left_part[]、 Right_part[]
		{
			if(i < 32) Left_part[0][i] = TempArray[i];
			else Right_part[0][i - 32] = TempArray[i];
		}
		
		for(int i = 1; i <= 16; ++i)						//進行 16 輪運算 
		{													//獲得 Left_part[]
			for(int j = 0; j < 32; ++j) Left_part[i][j] = Right_part[i - 1][j];
			
			//用置換表 E 對 TempArray[] 進行擴充(Expansion)  
			Permutation(Right_part[i - 1], E, TempArray, 48);
			
//			printf("Round %d, permutation E(Right_part[%d]) is : ", i, i - 1);
//		    for(int j = 0; j < 48; ++j) printf("%d", TempArray[j]);
//		    printf("\n");
//		    printf("Round %d, Right_part[%d] XOR SubKey[%d] is : ", i, i - 1, i);
//	        for(int j = 0; j < 48; ++j) printf("%d", TempArray[j] ^ SubKey[i - 1][j]);
//		    printf("\n");
		    
			for(int j = 0; j < 48; ++j) Right_part[i - 1][j] = TempArray[j] ^ SubKey[i - 1][j];
			int location = 0; 								//location 表示在 Right_part[] 中的位置
															//use S-box 48bits --> 32bits
			for(int j = 0; j < 48; j += 6)
			{ 												//位元重組，將 48bits --> 8 * 6bits 
				char TEMP1, TEMP2, TEMP3, bits[6];
				
				for(int k = 0; k < 6; ++k) bits[k] = Right_part[i - 1][j + k];
				
				TEMP1 = bits[0] * 2 + bits[5]; 				//bits[0]、bits[5] 作行號，存在 TEMP1[] 中 

				//bits[1]、bits[2]、bits[3]、bits[4]作列號存在 TEMP2 中 
				TEMP2 = bits[1] * 8 + bits[2] * 4 + bits[3] * 2 + bits[4];		
		
				//根據第 j / 6 組的第 TEMP1 行第 TEMP2 列查 S-box 
				TEMP3 = S[j / 6][TEMP1][TEMP2]; 			
 				
				//將 Decimal --> 4位 Binary 存到 Right_part[] 中 
				DecToBin(TEMP3, Right_part[i - 1] + location); 		
				
				location += 4; 								//因為存入了四位二進位制數，location 指向 Right_part[] 的位置 +4
			
			}
			
//			printf("Round %d, S-box is : ", i);
//			for(int j = 0; j < 32; ++j) printf("%d", Right_part[i - 1][j]);
//			printf("\n");
			
			//permutation IP 
			Permutation(Right_part[i - 1], P, TempArray, 32);
			
//			printf("Round %d, permutation P(Right_part[%d]) is : ", i, i - 1);
//			for(int j = 0; j < 32; ++j) printf("%d", TempArray[j]);
//			printf("\n");
			
			//兩個 xor 得到 Right_part[]
			for(int j = 0; j < 32; ++j) Right_part[i][j] = Left_part[i - 1][j] ^ TempArray[j];
//			printf("Round %d, Left_part[%d] XOR TempArray[%d] is : ", i, i - 1, i); 
//			for(int j = 0; j < 32; ++j) printf("%d", Right_part[i][j]);
//			printf("\n\n");
		
		}
		for(int i = 0; i < 64; ++i)
		{ 	
			//將 Left_part[] 和 Right_part[] 兩個合在一起存到 TempArray[] 中 
			if(i < 32) TempArray[i] = Right_part[16][i];
			else TempArray[i] = Left_part[16][i - 32];
		}
		
		Permutation(TempArray, FP, Output, 64); 			//permutation FP 得到最終的密文 
		
		return ;
	}
	
	//1. input : 明文、金鑰 
	char CipherText[48000]; 								//CipherText 儲存加密後的結果 
	char PlainText[48000];
	char Key[48000];
	
	InputString(0);											//input PlainText
	InputString(6);											//input main Key
	
	for(int i = 0; i < 48000; ++i) Key[i] = CHARptr[i];
		
	Feistel_Cipher(PlainText, Key, CipherText);
	
	printf("\033[33mYour encrypt string is \033[m");
	for(int i = 0; i < 64; ++i) printf("%d", CipherText[i]);
	
	return 1;	
	
}		
//
int Triple_DES(void)
{
	
	return 0;
}
//Advanced Encryption Standard 	進階加密標準 
int AES(void)
{
	//Advanced Encryption Standard program...
	printf("\033[33m		* * *Is running Advanced Encryption Standard program...* * *\033[m\n");
	
	/*
		AES-128, AES-192, AES-256
		ECB, CBC, CFB, OFB, CTR
		//可以考慮分開單獨做 AES 全套加密
		 
		 						個別差異和單位 : 
								=================================================
								=			=128 bits	=192 bits	=256 bits	=
								=================================================
								=KeyLen		=4 bytes	=6 bytes	=8 bytes	= 
								=Group		=4 bytes	=4 bytes	=4 bytes	=
								=Round		=10 times	=12	times	=14 times	=
								=================================================
		(我那時一直看不懂為啥是要輸入 16chars，原來 密鑰 & 分組長度單位式 byte，而且 1 char = 1 bytes...(尷尬)) 
		
		.C 大概流程 : 
			本次使用 AES-128, ECB加密模式 (最基本的款式，沒有初始向量IV) 
			
			1. 輸入明文, 16bits
			
			2. 輸入主金鑰, 16bytes
			
			3. 加密 :  
				每個 block 定義為代表 column (一列 4 個小區塊，每區塊 8bits)
				
				1 block = 4 * 4 (bytes)
				
				1. 字節替代（SubBytes）
					利用下面的S-box中的每一格代換掉，S-box是經過設計的，能提供非線性的變換 
				
				2. 行移位（ShiftRows）
				
				3. 列混淆（MixColumns）
				
				4. 輪密鑰加（AddRoundKey）
			
			4. 輸出密文 Hex(16進位) 
	*/
	
	//Explain the principle 解釋原理 
	printf("\033[36m    \033[m\n");
	printf("\033[36mEX :     \033[m\n");
	
	//Encrypting string...
	#define BLOCK 4
	
	short RunRound = 0;										//計算 加密的回和數 
	short NumOfKey = 0;										//計算 鑰匙的數量 
	
	char Keys[32];											//Main Key (上限 32 bytes) 
	char RoundKey[240];										//儲存 Main Key & SubKey 
	char State[4][4]; 										//儲存加密運算過程中的的狀態陣列 4 * 4 bytes 
	
	static const int S[256] =   							//(S) SubBytes 16*16
	{
	//	 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
	    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
	    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
	    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
	    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
	    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
	    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
	    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
	    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
	    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
	    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
	    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
	    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
	    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
	    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
	    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  //F
	};
	
	static const int E[11] = 								//(E) Key-Expansion，AES-128 最多使用到 10， AES-192 使用最多到 8， AES-256 使用最多到 7。 
	{
	//   0     1     2     3      4    5     6     7     8    9     10
	    0x87, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
	//
	};
	
	//生成回合金鑰函式(K)， SubKey_Generate : generate SubKey & expansion SubKey
	//Function to : 生成回合金鑰 
	void SubKey_Generate(void)
	{
		
		/*
			最後一個 word，也就是 w3 (w(4n-1)) 會先經過 f(g)。 
			
			f(g) 的內容是：
			要先向上旋轉一格，接著每一格都經過 Table S 轉換後，最左邊的 byte 要和回合係數 (RC, == NumOfKey) 做 XOR
			最後跟 w0 (w(4n-4)) 做 XOR 後得到的結果成為 w4。 
			
			w5 只要將上一個 w(t - 1) 和 w(t - 3) 做 XOR 即得到 w(t)。
			
			================================================
			
			第一輪 SubKey = Main-Key，劃分為 NumOfKey 塊 (每個 32 bits)[w0, w1, w2, w3]
			
			每個塊(block)分為 4個子塊(sub-block)(8 bits) --> 1 Block == 4 Sub_Block == 8 * 4 bits ==> 一個 Sub_Block == 8 bits = 1 character(char)
			
			Ex: AES-128, Nb_k = 4, 4 block W0 ~ W3
	    	Ex: AES-256, Nb_k = 8, 8 block W0 ~ W7
		*/
		
    	char TempByte[4] = {0}; 							// store 4 temp Byte(1 word) when generate subkey
		char TEMP = 0;      	 							// store byte when execute RotWord function
	    
		for (int i = 0; i < NumOfKey; ++i)
		{
	        RoundKey[i * 4] = Keys[i * 4];
	        RoundKey[i * 4 + 1] = Keys[i * 4 + 1];
	        RoundKey[i * 4 + 2] = Keys[i * 4 + 2];
	        RoundKey[i * 4 + 3] = Keys[i * 4 + 3];
	        
//	        for(int j = 0; j < 4; ++j)
//	        {
//	        	RoundKey[i * 4 + j] = Keys[i * 4 + j];
//			}

	    }

	     /*
	     	Generate other Sub-Key
			Ex: AES-128: i = 4 ~ 43, 共 11 個 4 block(128 bits), 需 44 個 word (W0 ~ W43).
	    	Ex: AES-256: i = 8 ~ 59, 共需要 15 個 4 block(128 bits), 需 60 個 word (W0~ W59)
		 */
	    for(int i = NumOfKey; i < (NumOfKey * (RunRound + 1)); ++i)
	    {													
	        for(int j = 0; j < 4; ++j)
			{ 	
				//處理每個 block(W)
	            TempByte[j] = RoundKey[(i - 1) * 4 + j]; 	//要新增一個 block(Word)故取前一個的 W 值存入 tempW 
	        }
	        if (i % NumOfKey == 0)
			{
	            /**
	             * Ex: AES-128 when generate W4, will use W3 do SubWord(RotWord(tempW)) XOR Rcon[4/4]
	             *     AES-128 i 是 4 的倍數的 Wi 用 Wi-1產生 Wi =  SubWord(RotWord(Wi-1)) XOR Rcon[i/4]
	             */
	            //RotWord function, [a0, a1, a2, a3](4byte) left circular shift in a word [a1, a2, a3, a0]
	            TEMP = TempByte[0];
	            TempByte[0] = TempByte[1];
	            TempByte[1] = TempByte[2];
	            TempByte[2] = TempByte[3];
	            TempByte[3] = TEMP;
	
	            //SubWord function (S-Box substitution)
	        	TempByte[0] = S[(int)TempByte[0]];
	            TempByte[1] = S[(int)TempByte[1]];
	            TempByte[2] = S[(int)TempByte[2]];
	            TempByte[3] = S[(int)TempByte[3]];
	            
//	            for(int k = 0; k < 4; ++k)
//	            {
//	            	TempByte[k] = S[(int)TempByte[k]];
//				}
	            
	            //XOR [i/4], only leftmost byte are changed (只會XOR最左的byte)
	            TempByte[0] = TempByte[0] ^ E[i / NumOfKey]; 
	            
	        }
	        else if (NumOfKey == 8 && i % NumOfKey == 4)	//only AES-256 use
	        {
	            TempByte[0] = S[(int)TempByte[0]];
	            TempByte[1] = S[(int)TempByte[1]];
	            TempByte[2] = S[(int)TempByte[2]];
	            TempByte[3] = S[(int)TempByte[3]];
	            
//	            for(int k = 0; k < 4; ++k)
//	            {
//	            	TempByte[k] = S[(int)TempByte[k]];
//				}
	            
	        }
	        /**
	         * Wn = Wn-1 XOR Wk    k = current word - Nb_k
	         * Ex: AES-128   Nb_k = 4  when W5 = Wn-1(W4) XOR Wk(W1)
	         * Ex: AES-256   Nb_k = 8  when W10 = Wn-1(W9) XOR Wk(W2) 
	         */
	        RoundKey[i * 4 + 0] = RoundKey[(i - NumOfKey) * 4 + 0] ^ TempByte[0];
	        RoundKey[i * 4 + 1] = RoundKey[(i - NumOfKey) * 4 + 1] ^ TempByte[1];
	        RoundKey[i * 4 + 2] = RoundKey[(i - NumOfKey) * 4 + 2] ^ TempByte[2];
	        RoundKey[i * 4 + 3] = RoundKey[(i - NumOfKey) * 4 + 3] ^ TempByte[3];
			
//			for(int k = 0; k < 4; ++k)
//			{
//				RoundKey[i * 4 + k] = RoundKey[(i - NumOfKey) * 4 + k] ^ TempByte[k];
//			}
			   
	    }
	}
	
	//加入回合金鑰函式 (A)， Add Round-Key(Sub-Key), 金鑰 XOR 函數 
	//Function to : 加入回合金鑰 
	void AddRoundKey(int Round)
	{
	    /**
	     * 根據round來使用key(每次用1個block = 16byte)
	     * first key index = round * 16 bytes = round * Nb * 4;
	     * Nb = 4
	     */
	    for (int i = 0; i < 4; ++i)
	    {
	    	for (int j = 0; j < 4; ++j)
	        {
	        	State[j][i] ^= RoundKey[(i * BLOCK + j) + (Round * BLOCK * 4)];    	
			}
		}
	}
	
	//S盒排列函式 (S)， SubBytes(void)
	//Function to : 使用 table S 排列 State[]														
	void SubBytes(){										//S-Box Substitution
	    for (int i = 0; i < 4; ++i)							//let state[] : state[i][j] = state[i][(j + i) % 4] 其中 i、j 屬於 [0, 3]
	    {
	    	for (int j = 0; j < 4; ++j)
	        {
	        	 State[i][j] = S[State[i][j]];
			}
		}
	}
	
	//列移位函數 (L)， ShiftRows(row)
	//Function to : 正向列移位 --> 第一行保持不變，第二行循環左移 8bits，第三行循環左移 16bits，第四行循環左移 24bits
	void ShiftRows(void)
	{
		char TempByte;
	    
	    // 2nd row left Circular Shift 1 byte
	    TempByte = State[1][0];
	    State[1][0] = State[1][1];
	    State[1][1] = State[1][2];
	    State[1][2] = State[1][3];
	    State[1][3] = TempByte;
	
	    // 3th row left Circular Shift 2 byte
	    TempByte = State[2][0];
	    State[2][0] = State[2][2];
	    State[2][2] = TempByte;
	
	    TempByte = State[2][1];
	    State[2][1] = State[2][3];
	    State[2][3] = TempByte;
	
	    // 4th row left Circular Shift 3 byte
	    TempByte = State[3][0];
	    State[3][0] = State[3][3];
	    State[3][3] = State[3][2];
	    State[3][2] = State[3][1];
	    State[3][1] = TempByte;
	}
	
	/**
	 *  xtime macro: (input * {02}) mod {1b}  GF(2^8)
	 *  02 = x = 00000010(binary) over GF(2^8)
	 *  1b = x^8 + x^4 + x^3 + x^1 + 1 = 00011011(binary) over GF(2^8) 
	 *  
	 *  
	 *  (x << 1) -- 代表 input * {02}  = shift 1 bit
	 *  (x >> 7) -- input / 2^7, 代表只取第8個bit
	 *  ((x >> 7) & 1) * 0x1b ----
	 *  第 8 個 bit 若為 1 則代表 mod(2^7) 後會剩 => 00011011, 最後整個xtime(x)變成(x << 1) xor 00011011 (詳情請見GF(2^n)快速 mod運算的方式)
	 *  第 8 個 bit 若為 0 會變成0 * 0x1b,                    最後整個xtime(x) (x << 1) XOR 0 = (x << 1)
	 */
	//GF(2 ^ n) 快速 mod 式 
	#define xtime(x) ((x << 1) ^ (((x >> 7) & 0x01) * 0x1b))
	
	//混合行運算函數 (M)， Mix Columns
	//Function to : 做一線性轉換(linear transform)，執行 4 次(4 Sub-Block) 行混合 
	void MixColumns(void)
	{
	    char TEMP, TEMP2, TEMP3;
	    
	    /*	
					=======================
					=c0     2 3 1 1   	b0=
					=c1     1 2 3 1    	b1=
					=c2     1 1 2 3    	b2=
					=c3     3 1 1 2   	b3=
					=======================
		*/
	    
		for(int i = 0; i < 4; ++i)
	    {    
	        TEMP3 = State[0][i];
	        TEMP = State[0][i] ^ State[1][i] ^ State[2][i] ^ State[3][i];
	        
			TEMP2  = State[0][i] ^ State[1][i]; 
			TEMP2 = xtime(TEMP2); 
			State[0][i] ^= TEMP2 ^ TEMP ;
	        
			TEMP2  = State[1][i] ^ State[2][i]; 
			TEMP2 = xtime(TEMP2); 
			State[1][i] ^= TEMP2 ^ TEMP ;
	        
			TEMP2  = State[2][i] ^ State[3][i]; 
			TEMP2 = xtime(TEMP2); 
			State[2][i] ^= TEMP2 ^ TEMP ;
	        
			TEMP2  = State[3][i] ^ TEMP3;           
			TEMP2 = xtime(TEMP2); 
			State[3][i] ^= TEMP2 ^ TEMP ;
	    }
	}
	

	//1. input 明文、主金鑰 
	char PlainText[16] = {0};								//明文必須是 16 bytes 的整數倍 						
	char CipherText[16] = {0};								//密文 (Hex) 
	char Key[32] = {0};										//主金鑰 Main-Key 
	
	printf("\033[32mWhat kind of AES encryption mode do you want to choose ? --> AES-128(1) || AES-192(2) || AES-256(3)\033[m\n");
	
    short Mode = ModeChoice(3);
	int KeySize;
	
	if(Mode == 1)
	{
		short INVILD = 0;		
		short NUM = 16;
        
		printf("\033[32mEnter Main-Key (%d chars) : \033[m", NUM);
        
		do
		{	
			scanf("%s", Key);
			
	        short Check = strlen(Key);
	        
	        if(Check == NUM)
	        {
	        	printf("\033[33mYour Main-Key is : %s\033[m\n", Key);
	        	printf("\033[33mLen is : %d\033[m\n", Check);
	        	KeySize = NUM;
	        	for(int i = 0; i < NUM; ++i) Keys[i] = Key[i];
			}
			else
			{
				printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
				INVILD = 1;
			}
			
		}while(INVILD == 1);
            
    }
    else if(Mode == 2)
	{
        short INVILD = 0;		
		short NUM = 21;
        
		printf("\033[32mEnter Main-Key (%d chars) : \033[m", NUM);
        
		do
		{	
			scanf("%s", Key);
			
	        short Check = strlen(Key);
	        
	        if(Check == NUM)
	        {
	        	printf("\033[33mYour Main-Key is : %s\033[m\n", Key);
	        	printf("\033[33mLen is : %d\033[m\n", Check);
	        	KeySize = NUM;
	        	for(int i = 0; i < NUM; ++i) Keys[i] = Key[i];
			}
			else
			{
				printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
				INVILD = 1;
			}
			
		}while(INVILD == 1);
    }
    else if(Mode == 3)
	{
        short INVILD = 0;		
		short NUM = 32;
        
		printf("\033[32mEnter Main-Key (%d chars) : \033[m", NUM);
        
		do
		{	
			scanf("%s", Key);
			
	        short Check = strlen(Key);
	        
	        if(Check == NUM)
	        {
	        	printf("\033[33mYour Main-Key is : %s\033[m\n", Key);
	        	printf("\033[33mLen is : %d\033[m\n", Check);
	        	KeySize = NUM;
	        	for(int i = 0; i < NUM; ++i) Keys[i] = Key[i];
			}
			else
			{
				printf("\033[33mYour choice is invalid. Pls enter the currect input!\033[m\n");
				INVILD = 1;
			}
			
		}while(INVILD == 1);
    }
    else
	{
        //Error(0, 0);
        return -1;
    }
//			for(int c = 0; c < 16; ++c)
//			{
//      		plaintext_block[c] = PlainText[c];
//				
//          	if(plaintext_block[c] == 0){
//              		for(int padding = c; padding < 16; ++padding)
//						{
//                   		plaintext_block[padding] = 0x00;
//                		}
//            		}
//        	}
    
    NumOfKey = KeySize / 32;     							// Number of block of key, 計算 Key Block 數量 (EX : AES-128 : 4) 
    RunRound = NumOfKey + 6;         						// Number of round(RunRound), 計算 AES 運算回合次數 (EX : AES-128 : 10)
    
    InputString(7);
    for(int i = 0; i < 16; ++i) PlainText[i] = InputStr[i];
    
    //Generate SubKey & Expansion Main-Key, 擴充鑰匙函數產生所有鑰匙
    SubKey_Generate(); 										// Expansion Keys - AES-128(44words/176 bytes), AES-192(52w/208 bytes), AES-256(60w/260bytes)
    
    int Round = 0;
    /*
							Permutation Input[]
							
										  =================
										  =b00 b04 b08 b12=
			[b0, b1, ... , b15]	   --> 	  =b01 b05 b09 b13=
										  =b02 b06 b10 b14=
										  =b03 b07 b11 b15=
										  =================
	*/
    for (int i = 0; i < 4; ++i)
    {
    	for (int j = 0; j < 4; ++j)
        {
        	State[j][i] = PlainText[i * 4 + j];				//Plaintext --> column形式 [w0, w1, w2, w3]
		}
	}
    
    //	Round 0 : Add Round Key, 第 0 回合 : 僅執行 Key XOR Block 
    AddRoundKey(0);

    // Round 1 ~ RunRound - 1, 反覆執行 1 ~ RunRound - 1 回合
    for(Round = 1; Round < RunRound; ++Round)
	{
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey(Round);
    }

    // Round RunRound, no MixColumns(), 第 RunRound 回合沒有 混合行運算 MixColumns()
    SubBytes();
    ShiftRows();
    AddRoundKey(RunRound);
    
    /*
							State[] --> Output[]
							
				================= 
				=c00 c04 c08 c12= 
				=c01 c05 c09 c13=	-->	  [c0, c1, c2, ... , c15] 
				=c02 c06 c10 c14= 
				=c03 c07 c11 c15= 
				================= 
	*/
    for(int i = 0; i < 4; ++i) 
    {
    	for(int j = 0; j < 4; ++j)
        {
        	CipherText[i * 4 + j] = State[j][i];
		}
	}
	
	printf("\033[33mYour encrypt string is \033[m");
	for(int i = 0; i < 16; ++i) printf("%x ", CipherText[i]);

	//abcdefghijklmnop

	return 1;
		
}
int MD5(void)
{
	
	return 0;
}
int SHA_1(void)
{
	
	return 0;
}













