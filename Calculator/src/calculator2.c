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
#include "structs.h"
#include "queue.h"
#include "stack.h"
#include "list.h"

FILE *fin,*fout;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input[259], output[259], in[256];
	char h, m, sign, r;
	double d, num;
	double *result;
	double res; //задаем переменную для хранения результата
	element *var;
	stack s;
	queue q1,q2;
	list l1,l2;
	do
	{
		puts ("Выберете режим работы (r для работы с обратной польской нотацией и n для обычной):");
		scanf (" %c", &m);
		puts ("Введите имя входного файла");
		scanf ("%s", input);
		puts ("Введите имя выходного файла");
		scanf ("%s", output);
		fin=fopen (input, "r");
		switch (m)
		{
		case 'r':
			init_stack (&s);
			if ((fout=fopen(output, "a")) == NULL)
			{
				fout=fopen(output, "w");
			}
			while (feof (fin)==0)
			{
				fscanf (fin, "%s", in);
				if (atof (in)==0)
				{
					sign = in[0];
					switch (sign)
					{
					case '+':
						push (&s, pop (&s)+ pop(&s));
						break;
					case '-':
						push (&s, pop (&s)- pop(&s));
						break;
					case '*':
						push (&s, pop (&s)* pop(&s));
						break;
					case '/':
						push (&s, pop (&s)/ pop(&s));
						break;
					case '!':
						d=1; // приравниваем, чтобы посчитать факториал
						num = pop (&s);
						if (num >=0) // так как факториал 0=1, сделаем такой цикл
						{
							for (int i=0;i<num;i++)
							{
								d=d*(i+1);
							}
						}
						push (&s, d);
						break;
					case '^':
						num = pop (&s);
						d=num; // приравниваем, чтобы посчитать степень
						for (int i=1;i<pop (&s);i++)
						{
							d=d*num;
						}
						push (&s, d);
						break;
					case '=':
						fprintf (fout, "%lf\n", pop (&s));
						break;
					}
				}
				else
				{
					num = atof (in);
					push (&s, num);
				}
			}
			fclose (fin);
			break;
		case 'n':
			puts ("Выберете с чем работать (списки(l)/очередь(q))");
			scanf (" %c", &r);
			if (r=='q')
			{
				initqueue (&q1);
				initqueue (&q2);
				var = malloc (sizeof (element));
				while (feof(fin) == 0)
				{
					fscanf (fin, " %c %c", &var->c, &var->regime);
					switch (var->regime) //конструкция для выбора режима работы
					{
					case 'v':
						fscanf (fin, "%i", &var->size); //считываем длину вектора
						var->x = malloc (var->size*sizeof(double));
						var->y = malloc (var->size*sizeof(double));
						for (int i=0;i<var->size;i++) fscanf (fin, "%lf", &var->x[i]);
						for (int i=0;i<var->size;i++) fscanf (fin, "%lf", &var->y[i]);
						break;
					case 'n':
						var->size = 1;
						if (var->c == '!')
						{
							var->x = malloc (sizeof (double));
							fscanf (fin, "%lf", &var->x[0]);
							var->y = NULL;
						}
						else
						{
							var->x = malloc (sizeof(double));
							var->y = malloc (sizeof(double));
							fscanf (fin, "%lf", &var->x[0]);
							fscanf (fin, "%lf", &var->y[0]);
						}
						break;
					}
					enqueue (&q1, var);
				}
				free (var);
				fclose (fin);
				while ((var = dequeue(&q1)) != NULL)
				{
					switch (var->regime)
					{
					case 'v':
						switch (var->c)
						{
						case '+':
							result = malloc (var->size*sizeof(double));
							for (int i=0;i<var->size;i++) result[i] = var->x[i]+var->y[i];
							var->res = result;
							break;
						case '-':
							for (int i=0;i<var->size;i++) result[i] = var->x[i]-var->y[i];
							var->res = result;
							break;
						case '*':
							res = 0;
							for (int i=0;i<var->size;i++)
							{
								res+=var->x[i]*var->y[i];
							}
							var->result = res;
							break;
						}
						break;
						case 'n':
							switch (var->c)
							{
							case '+': // блок суммы
								var->result = var->x[0]+var->y[0];
								break;
							case '-': // блок разности
								var->result = var->x[0]-var->y[0];
								break;
							case '*': // блок умножения
								var->result = var->x[0]*var->y[0];
								break;
							case '/': // блок деления
								var->result = var->x[0]/var->y[0];
								break;
							case '^': // блок возведения в степень
								d=var->x[0]; // приравниваем, чтобы посчитать степень
								for (int i=1;i<var->y[0];i++)
								{
									d=d*var->x[0];
								}
								var->result = d;
								break;
							case '!': // блок факториала
								d=1; // приравниваем, чтобы посчитать факториал
								if (var->x[0]>=0) // так как факториал 0=1, сделаем такой цикл
								{
									for (int i=0;i<var->x[0];i++)
									{
										d=d*(i+1);
									}
								}
								var->result = d;
								break;
							}
					}
					enqueue (&q2, var);
				}
				if ((fout=fopen(output, "a"))==NULL)
				{
					fout=fopen(output, "w");
				}
				while ((var = dequeue(&q2)) != NULL)
				{
					switch (var->regime)
					{
					case 'v':
						fprintf (fout, "( ");
						for (int i=0;i<var->size;i++)
						{
							if (i==var->size-1)
							{
								fprintf (fout, "%lf", var->x[i]);
							}
							else fprintf (fout, "%lf ", var->x[i]);
						}
						fprintf (fout, " ) %c ( ", var->c);
						for (int i=0;i<var->size;i++)
						{
							if (i==var->size-1)
							{
								fprintf (fout, "%lf", var->y[i]);
							}
							else fprintf (fout, "%lf ", var->y[i]);
						}
						if (var->c == '+' || var->c == '-')
						{
							fprintf (fout, " ) = ( ");
							for (int i=0;i<var->size;i++)
							{
								if (i == var->size-1)
								{
									fprintf (fout, "%lf", var->res[i]);
								}
								else fprintf (fout, "%lf ", var->res[i]);
							}
							fprintf (fout, " )\n");
						}
						else fprintf (fout, " ) = %lf\n", var->result);
						break;
					case 'n':
						if (var->c == '!')
						{
							fprintf (fout, "%lf! = %lf\n", *var->x, var->result);
						}
						else fprintf (fout, "%lf %c %lf = %lf\n", *var->x, var->c, *var->y, var->result);
					}
				}
				fclose (fout);
			}
			else if (r=='l')
			{
						initList (&l1);
						initList (&l2);
						var = malloc (sizeof (element));
						while (feof(fin) == 0)
						{
							fscanf (fin, " %c %c", &var->c, &var->regime);
							switch (var->regime) //конструкция для выбора режима работы
							{
							case 'v':
								fscanf (fin, "%i", &var->size); //считываем длину вектора
								var->x = malloc (var->size*sizeof(double));
								var->y = malloc (var->size*sizeof(double));
								for (int i=0;i<var->size;i++) fscanf (fin, "%lf", &var->x[i]);
								for (int i=0;i<var->size;i++) fscanf (fin, "%lf", &var->y[i]);
								break;
							case 'n':
								var->size = 1;
								if (var->c == '!')
								{
									var->x = malloc (sizeof (double));
									fscanf (fin, "%lf", &var->x[0]);
									var->y = NULL;
								}
								else
								{
									var->x = malloc (sizeof(double));
									var->y = malloc (sizeof(double));
									fscanf (fin, "%lf", &var->x[0]);
									fscanf (fin, "%lf", &var->y[0]);
								}
								break;

							}
							pushlist (&l1, var);
						}
						fclose (fin);
						l1.current = l1.head;
						while (l1.current != NULL)
						{
							var->regime = l1.current->regime;
							var->c = l1.current->c;
							var->x = l1.current->x;
							var->y = l1.current->y;
							var->result = l1.current->result;
							var->res = l1.current->res;
							var->size = l1.current->size;
							switch (var->regime)
							{
							case 'v':
								switch (var->c)
								{
								case '+':
									result = malloc (var->size*sizeof(double));
									for (int i=0;i<var->size;i++) result[i] = var->x[i]+var->y[i];
									var->res = result;
									break;
								case '-':
									for (int i=0;i<var->size;i++) result[i] = var->x[i]-var->y[i];
									var->res = result;
									break;
								case '*':
									for (int i=0;i<var->size;i++)
									{
										res+=var->x[i]*var->y[i];
									}
									var->result = res;
									break;
								}
								break;
								case 'n':
									switch (var->c)
									{
									case '+': // блок суммы
										var->result = var->x[0]+var->y[0];
										break;
									case '-': // блок разности
										var->result = var->x[0]-var->y[0];
										break;
									case '*': // блок умножения
										var->result = var->x[0]*var->y[0];
										break;
									case '/': // блок деления
										var->result = var->x[0]/var->y[0];
										break;
									case '^': // блок возведения в степень
										d=var->x[0]; // приравниваем, чтобы посчитать степень
										for (int i=1;i<var->y[0];i++)
										{
											d=d*var->x[0];
										}
										var->result = d;
										break;
									case '!': // блок факториала
										d=1; // приравниваем, чтобы посчитать факториал
										if (var->x[0]>=0) // так как факториал 0=1, сделаем такой цикл
										{
											for (int i=0;i<var->x[0];i++)
											{
												d=d*(i+1);
											}
										}
										var->result = d;
										break;
									}
							}
							pushlist (&l2, var);
							next (&l1);
						}
						if ((fout=fopen(output, "a"))==NULL)
						{
							fout=fopen(output, "w");
						}
						free (var);
						l1.current = l1.head;
						l2.current = l2.head;
						while (l2.current != NULL)
						{
							switch (l2.current->regime)
							{
							case 'v':
								fprintf (fout, "( ");
								for (int i=0;i<l2.current->size;i++)
								{
									if (i==l2.current->size-1)
									{
										fprintf (fout, "%lf", l2.current->x[i]);
									}
									else fprintf (fout, "%lf ", l2.current->x[i]);
								}
								fprintf (fout, " ) %c ( ", l2.current->c);
								for (int i=0;i<l2.current->size;i++)
								{
									if (i==l2.current->size-1)
									{
										fprintf (fout, "%lf", l2.current->y[i]);
									}
									else fprintf (fout, "%lf ", l2.current->y[i]);
								}
								if (l2.current->c == '+' || l2.current->c == '-')
								{
									fprintf (fout, " ) = ( ");
									for (int i=0;i<l2.current->size;i++)
									{
										if (i == l2.current->size-1)
										{
											fprintf (fout, "%lf", l2.current->res[i]);
										}
										else fprintf (fout, "%lf ", l2.current->res[i]);
									}
									fprintf (fout, " )\n");
								}
								else fprintf (fout, " ) = %lf\n", l2.current->result);
								break;
							case 'n':
								if (l2.current->c == '!')
								{
									fprintf (fout, "%lf! = %lf\n", *l2.current->x, l2.current->result);
								}
								else fprintf (fout, "%lf %c %lf = %lf\n", *l2.current->x, l2.current->c, *l2.current->y, l2.current->result);
							}
							next (&l2);
						}
						fclose (fout);
						while (l1.head != NULL)
						{
							delete (&l1);
						}
						while (l2.head != NULL)
						{
							delete (&l2);
						}
			}
			break;
		}
		puts ("\nХотите продолжить? Введите y, если да, n, если нет");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
