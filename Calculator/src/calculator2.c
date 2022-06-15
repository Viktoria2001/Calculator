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

typedef struct element
{
	char c;
	char regime;
	double result;
	double *x,*y;
	double *res;
	int size;
	struct element *next;
} element;

typedef struct queue
{
	element *head;
	element *tail;
} queue;

void initqueue (queue *q)
{
	q->head = NULL;
	q->tail = NULL;
}

void enqueue (queue *q, element *data)
{
	element* tmp = malloc (sizeof(element));
	tmp->c = data->c;
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->regime = data->regime;
	tmp->res = data->res;
	tmp->size = data->size;
	tmp->next = NULL;
	tmp->result = data->result;
	if (q->tail != NULL)
	{
		q->tail->next = tmp;
	}
	q->tail = tmp;
	if (q->head == NULL)
	{
		q->head = tmp;
	}
}

element* dequeue (queue *q)
{
	element *out;
	out = malloc (sizeof (element));
	if (q->head == NULL)
	{
		out = NULL;
		return out;
	}
	element *tmp = q->head;
	out->c = tmp->c;
	out->res = tmp->res;
	out->result = tmp->result;
	out->x = tmp->x;
	out->y = tmp->y;
	out->size = tmp->size;
	out->regime = tmp->regime;
	q->head = q->head->next;
	if (q->head == NULL)
	{
		q->tail = NULL;
	}
	free (tmp);
	return out;
}
typedef struct node
{
	double x;
	struct node *next;
} node;
typedef struct stack
{
	node *head;
} stack;
void init_stack (stack *s)
{
	s->head = NULL;
}
void push (stack *s, double number)
{
	node * tmp = malloc (sizeof (node));
	tmp->x = number;
	tmp->next = s->head;
	s->head = tmp;
}
double pop (stack *s)
{
	node *tmp;
	tmp = malloc (sizeof (node));
	tmp = s->head;
	s->head = s->head->next;
	return tmp->x;
}

FILE *fin,*fout;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input[259], output[259], in[256];
	char h, m, sign;
	double d, num;
	double *result;
	double res; //задаем переменную для хранения результата
	element *var;
	stack s;
	queue q1,q2;
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
			break;
		}
			fclose (fout);
		puts ("\nХотите продолжить? Введите y, если да, n, если нет");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
