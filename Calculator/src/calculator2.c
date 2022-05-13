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
char input[259], output[259];
char h;
FILE *fin,*fout;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	do
	{
		puts ("Введите имя входного файла");
		scanf ("%s", input);
		puts ("Введите имя выходного файла");
		scanf ("%s", output);
		fin=fopen (input, "r");
		while (feof(fin) == 0)
		{
			// сначала запишем все функции и их обозначения
	//		printf ("сумма, знак +\n");
	//		printf ("разность, знак -\n");
	//		printf ("умножение, знак *\n");
	//		printf ("деление, знак /\n");
	//		printf ("степень, знак ^\n");
	//		printf ("факториал, знак !\n");
			if ((fout=fopen(output, "a"))==NULL)
			{
				fout=fopen(output, "w");
			}
			double a,b,d; // задаем переменные типа double
			char c; // задаем переменную типа char
			char regime;
			fscanf (fin, " %c %c", &c, &regime);
			switch (regime) //конструкция для выбора режима работы
			{
			case 'v':
			{
				int n; //задаем переменную для длины вектора
				fscanf (fin, "%i", &n); //считываем длину вектора
				switch (c)
				{
				case '+':
				{
					double *f,*g;
					f=malloc(n*sizeof(double)); //выделяем память для хранения вектора
					g=malloc(n*sizeof(double));
					fprintf (fout, "(");
					for (int i=0;i<n;i++) //считываем вектор
					{
						fscanf (fin, "%lf", &f[i]);
						fprintf (fout, "%lf ", f[i]);
					}
					fprintf (fout, ") + (");
					for (int i=0;i<n;i++)
					{
						fscanf (fin, "%lf", &g[i]);
						fprintf (fout, "%lf ", g[i]);
					}
					fprintf (fout, ") = (");
					for (int i=0;i<n;i++)
					{
						fprintf (fout, "%lf ", f[i]+g[i]);
					}
					fprintf (fout, ")\n");
					free (f);
					free (g);
					fclose (fout);
					break;
				}
				case '-':
				{
					double *f,*g;
					f=malloc(n*sizeof(double));
					g=malloc(n*sizeof(double));
					fprintf (fout, "(");
					for (int i=0;i<n;i++) //считываем вектор
					{
						fscanf (fin, "%lf", &f[i]);
						fprintf (fout, "%lf ", f[i]);
					}
					fprintf (fout, ") - (");
					for (int i=0;i<n;i++)
					{
						fscanf (fin, "%lf", &g[i]);
						fprintf (fout, "%lf ", g[i]);
					}
					fprintf (fout, ") = (");
					for (int i=0;i<n;i++)
					{
						fprintf (fout, "%lf ", f[i]-g[i]);
					}
					fprintf (fout, ")\n");
					free (f);
					free (g);
					fclose (fout);
					break;
				}
				case '*':
				{
					double *f,*g;
					f=malloc(n*sizeof(double));
					g=malloc(n*sizeof(double));
					fprintf (fout, "(");
					for (int i=0;i<n;i++) //считываем вектор
					{
						fscanf (fin, "%lf", &f[i]);
						fprintf (fout, "%lf ", f[i]);
					}
					fprintf (fout, ") * (");
					for (int i=0;i<n;i++)
					{
						fscanf (fin, "%lf", &g[i]);
						fprintf (fout, "%lf ", g[i]);
					}
					fprintf (fout, ") = ");
					double res; //задаем переменную для хранения результата
					for (int i=0;i<n;i++)
					{
						res+=f[i]*g[i];
					}
					fprintf (fout, "%lf\n", res);
					free (f);
					free (g);
					fclose (fout);
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
						fscanf (fin, "%lg %lg", &a, &b);
						fprintf (fout, " %lg + %lg = %lg\n", a,b,a+b);
						fclose (fout);
						break;
					case '-': // блок разности
						fscanf (fin, "%lg %lg", &a, &b);
						fprintf (fout, " %lg - %lg = %lg\n", a,b,a-b);
						fclose (fout);
						break;
					case '*': // блок умножения
						fscanf (fin, "%lg %lg", &a, &b);
						fprintf (fout, " %lg * %lg = %lg\n", a,b,a*b);
						fclose (fout);
						break;
					case '/': // блок деления
						fscanf (fin, "%lg %lg", &a, &b);
						fprintf (fout, " %lg / %lg = %lg\n", a,b,a/b);
						fclose (fout);
						break;
					case '^': // блок возведения в степень
						fscanf (fin, "%lg %lg", &a, &b);
						d=a; // приравниваем, чтобы посчитать степень
						for (int i=1;i<b;i++)
						{
							d=d*a;
						}
						fprintf (fout, " %lg ^ %lg = %lg\n", a,b,d);
						fclose (fout);
						break;
					case '!': // блок факториала
						d=1; // приравниваем, чтобы посчитать факториал
						fscanf (fin, "%lg", &a);
						if (a>=0) // так как факториал 0=1, сделаем такой цикл
						{
							for (int i=0;i<a;i++)
							{
								d=d*(i+1);
							}
							fprintf (fout, "%lg! = %lg\n", a,b);
						}
						else
							fprintf (fout, "nop");
						fclose (fout);
						break;
					default: fprintf (fout, "nop");
					fclose (fout);
					}
			break;
			}
			default: fprintf (fout, "такой операции нет, введите другую");
			fclose (fout);
			}
		}
		puts ("\nХотите продолжить? Введите y, если да, n, если нет");
		scanf (" %c", &h);
		fclose (fin);
		fclose (fout);
	}
	while (h!='n');
	return 0;
}
