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

typedef struct list
{
	element *head;
	element *current;
} list;

void initList (list *l)
{
	l->head = NULL;
	l->current = NULL;
}

void push (list *l, element *data)
{
	element* tmp = malloc (sizeof(element));
	element *last = l->head;
	tmp->c = data->c;
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->regime = data->regime;
	tmp->res = data->res;
	tmp->size = data->size;
	tmp->next = NULL;
	if (l->head==NULL)
	{
		l->head = tmp;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = tmp;
	return;
}

void delete (list *l)
{
	element *tmp;
	if (&l->head == NULL) return;
	tmp = l->head;
	l->head = l->head->next;
	free (tmp);
}

element* next (list *l)
{
	l->current = l->current->next;
	return l->current;
}

FILE *fin,*fout;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input[259], output[259];
	char h;
	element *var;
	list l1,l2;
	do
	{
		initList (&l1);
		initList (&l2);
		puts ("Введите имя входного файла");
		scanf ("%s", input);
		puts ("Введите имя выходного файла");
		scanf ("%s", output);
		fin=fopen (input, "r");
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
			push (&l1, var);
		}
		fclose (fin);
		l1.current = l1.head;
		while (l1.current != NULL)
		{
			var->regime = l1.current->regime;
			var->c = l1.current->c;
			var->x = l1.current->x;
			var->y = l1.current->y;
			var->size = l1.current->size;
			switch (var->regime)
			{
			case 'v':
				switch (var->c)
				{
				var->res = malloc (var->size*sizeof(double));
				case '+':
					for (int i=0;i<var->size;i++) var->res[i] = var->x[i]+var->y[i];
					break;
				case '-':
					for (int i=0;i<var->size;i++) var->res[i] = var->x[i]-var->y[i];
					break;
				case '*':
					double res; //задаем переменную для хранения результата
					for (int i=0;i<var->size;i++)
					{
						res+=var->x[i]*var->y[i];
					}
					break;
				}
				break;
				case 'n':
					double d;
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
			push (&l2, var);
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
				else fprintf (fout, " ) = %lf\n", *l2.current->res);
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
		puts ("\nХотите продолжить? Введите y, если да, n, если нет");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
