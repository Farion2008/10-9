//Обработать n1 матриц. Размеры матрицы n*m. Элементы матрицы – строка символов.
//В строке есть слово, состоящее только из цифр. Найти это слово, преобразовать в число и сохранить в массиве.
//Полученный массив вывести на экран.
//Ввод матриц, поиск слова, преобразование слова в число реализовывать в отдельных функциях.Память под матрицы отводить динамически.
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void preobraz_s(char* buf, int* a, int n2)//функция преобразования строки в число и запись в массив
{
	int l = strlen(buf), b = 0, i;
	for (i = 0; i < l - 1; i++, b *= 10)
	{
		b = (b + (buf[i] - 48));
	}
	b = (b + (buf[i] - 48));
	a[n2 - 1] = b;//записываем полученное число в массив
}
int poisk_s(char** text, int n, int* a, int n2)
{
	int flag = 0, ns, k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; text[i][j] != '\0'; j++)
		{
			if ((text[i][j] >= '0' && text[i][j] <= '9') &&flag == 0)//находим начало слова из цифр
			{
				n2++;
				ns = j;
				flag = 1;
			}
			else if ((!(text[i][j] >= '0' && text[i][j] <= '9') && ((text[i][j] >= 'Ђ' && text[i][j] <= 'ї') || text[i][j] == '\n' || text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.' || text[i][j] == '?' || text[i][j] == '"' || text[i][j] == '!' || text[i][j] == '-')) && flag == 1)//конец слова из цифр
			{
				flag = 0;
				char* buf = (char*)calloc(j - ns + 1, sizeof(char));//выделяем память под слово
				if (NULL == buf)
				{
					printf("Не удалось выделить память\n");
					exit(1);
				}
				for (k = 0; k < j - ns; k++)//записываем посимвольно слово в буфер
				{
					buf[k] = text[i][ns + k];
				}
				buf[k] = '\0';
				preobraz_s(buf, a, n2);//преобразуем полученную строку в число и записываем в массив
				free(buf);
			}
			else if ((text[i][j] >= 'А' && text[i][j] <= 'я')&&flag==1)//ситуация когда слово состоит не только из цифр
			{
				flag = 0;
				n2--;
			}
		}
	}
	return n2;
}
int vvod_matrix(int *a, int n2)//функция для динамического выделения памяти под матрицу и дальнейшего поиска слов состоящих из цифр
{
	char** text;
	int n, m, i;
	printf("Введите n:");
	scanf_s("%d", &n);
	text = (char**)calloc(n, sizeof(char*));
	if (NULL == text)
	{
		printf("Не удалось выделить память\n");
		exit(1);
	}
	printf("Введите m:");
	scanf_s("%d", &m);
	getchar();
	for (i = 0; i < n; i++)
	{
		text[i] = (char*)calloc(m, sizeof(char));
		if (NULL == text[i])
		{
			printf("Не удалось выделить память\n");
			exit(1);
		}
		printf("Введите %d строку\n", i+1);
		fgets(text[i], m, stdin);
	}
	n2 = poisk_s(text, n, a, n2);//ищим слово из чисел. Выводим количество таких слов
	for (i = 0; i < n; i++)
	{
		free(text[i]);
	}
	free(text);
	return n2;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int* a, n1, n2=0;
	printf("Сколько матриц вы хотите обработать?\n");
	scanf_s("%d", &n1);
	a = (int*)calloc(n1 * 10, sizeof(int));//выделяем память для массива чисел
	if (NULL == a)
	{
		printf("Не удалось выделить память\n");
		exit(1);
	}
	for (int i = 0; i < n1; i++)//последовательно обрабатываем матрицы и заносим числа в массив
	{
		printf("Введите n и m для %d матрицы\n", i + 1);
		n2 = vvod_matrix(a, n2);
	}
	printf("Итоговый массив чисел\n");
	for (int i = 0; i < n2; i++)//выводим полученный массив
	{
		printf("%d ", a[i]);
	}
	free(a);
	return 0;
}