// Волченскова В.Р.
// Лицензия. GNU GPL
// Калькулятор считает со знаками после запятой, способен
// сумма (+)
// разность (-)
// умножение (*)
// деление (/)
// степень (^)
// факториал (!)
// чтобы вернуться в начало программы, будем использовать do
#include <stdio.h>
#include <stdlib.h>
char regul;
int main(int argc, char *argv[])
{
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);
char e;
do
{
    // сначала запишем все функции и их обозначения
	printf ("сумма, знак +\n");
	printf ("разность, знак -\n");
	printf ("умножение, знак *\n");
	printf ("деление, знак /\n");
	printf ("степень, знак ^\n");
	printf ("факториал, знак !\n");
	double a,b,d; // задаем переменные типа double
	char c; // задаем переменную типа char
	printf ("введите операцию "); // выводим надпись, где введем нужную операцию
	scanf (" %c", &c); // вводим с
	char regime;
	printf ("Ведите v для векторного режима и n для обычного режима"); //выбираем режим работы
	scanf (" %c", &regime);
	switch (regime) //конструкция для выбора режима работы
	{
	case 'v':
	{
		int n; //задаем переменную для длины вектора
		printf ("Введите длину вектора ");
		scanf ("%i", &n); //считываем длину вектора
		switch (c)
		{
		case '+':
		{
			double *f,*g;
			f=malloc(n*sizeof(double)); //выделяем память для хранения вектора
			g=malloc(n*sizeof(double));
			for (int i=0;i<n;i++) //считываем вектор
			{
				scanf ("%lf", &f[i]);
			}
			for (int i=0;i<n;i++)
			{
				scanf ("%lf", &g[i]);
			}
			for (int i=0;i<n;i++)
			{
				printf ("%lf ", f[i]+g[i]);
			}
			free (f);
			free (g);
			break;
		}
		case '-':
		{
			double *f,*g;
			f=malloc(n*sizeof(double));
			g=malloc(n*sizeof(double));
			for (int i=0;i<n;i++)
			{
				scanf ("%lf", &f[i]);
			}
			for (int i=0;i<n;i++)
			{
				scanf ("%lf", &g[i]);
			}
			for (int i=0;i<n;i++)
			{
				printf ("%lf ", f[i]-g[i]);
			}
			free (f);
			free (g);
			break;
		}
		case '*':
		{
			double *f,*g;
			f=malloc(n*sizeof(double));
			g=malloc(n*sizeof(double));
			for (int i=0;i<n;i++)
			{
				scanf ("%lf", &f[i]);
			}
			for (int i=0;i<n;i++)
			{
				scanf ("%lf", &g[i]);
			}
			double res; //задаем переменную для хранения результата
			for (int i=0;i<n;i++)
			{
				res+=f[i]*g[i];
			}
			printf ("%lf", res);
			free (f);
			free (g);
			break;
		}
		}
	break;
	}
	case 'n':
	{
		switch (c) //блок функций
			{
			case '+': // блок суммы
				printf ("введите первое число a= ");
				scanf (" %lg", &a);
				printf ("введите второе число b= ");
				scanf (" %lg", &b);
				printf (" %lg plus %lg = %lg", a,b,a+b);
				break;
			case '-': // блок разности
				printf ("введите первое число a= ");
				scanf (" %lg", &a);
				printf ("введите второе число b= ");
				scanf (" %lg", &b);
				printf (" %lg minus %lg = %lg", a,b,a-b);
				break;
			case '*': // блок умножения
				printf ("введите первое число a= ");
				scanf (" %lg", &a);
				printf ("введите второе число b= ");
				scanf (" %lg", &b);
				printf (" %lg multiply by %lg = %lg", a,b,a*b);
				break;
			case '/': // блок деления
				printf ("введите первое число a= ");
				scanf (" %lg", &a);
				printf ("введите второе число b= ");
				scanf (" %lg", &b);
				printf (" %lg divide by %lg = %lg", a,b,a/b);
				break;
			case '^': // блок возведения в степень
				printf ("введите первое число a= ");
				scanf (" %lg", &a);
				printf ("введите второе число b= ");
				scanf (" %lg", &b);
				d=a; // приравниваем, чтобы посчитать степень
				for (int i=1;i<b;i++)
				{
					d=d*a;
				}
				printf (" %lg в степени %lg = %lg", a,b,d);
				break;
			case '!': // блок факториала
				d=1; // приравниваем, чтобы посчитать факториал
				printf ("введите первое число a= ");
				scanf (" %lg", &a);
				if (a>=0) // так как факториал 0=1, сделаем такой цикл
				{
					for (int i=0;i<a;i++)
					{
						d=d*(i+1);
					}
					printf ("факториал %lg = %lg", a,b);
				}
				else
					puts ("nop");
				break;
			default: puts ("nop");
			}
	break;
	}
	default: puts ("такой операции нет, введите другую");
	}

	puts ("\nХотите продолжить? Введите y, если да, n, если нет");
	scanf (" %c", &e);
}

while (e!='n');
	return 0;
}