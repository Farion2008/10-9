//���������� n1 ������. ������� ������� n*m. �������� ������� � ������ ��������.
//� ������ ���� �����, ��������� ������ �� ����. ����� ��� �����, ������������� � ����� � ��������� � �������.
//���������� ������ ������� �� �����.
//���� ������, ����� �����, �������������� ����� � ����� ������������� � ��������� ��������.������ ��� ������� �������� �����������.
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void preobraz_s(char* buf, int* a, int n2)//������� �������������� ������ � ����� � ������ � ������
{
	int l = strlen(buf), b = 0, i;
	for (i = 0; i < l - 1; i++, b *= 10)
	{
		b = (b + (buf[i] - 48));
	}
	b = (b + (buf[i] - 48));
	a[n2 - 1] = b;//���������� ���������� ����� � ������
}
int poisk_s(char** text, int n, int* a, int n2)
{
	int flag = 0, ns, k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; text[i][j] != '\0'; j++)
		{
			if ((text[i][j] >= '0' && text[i][j] <= '9') &&flag == 0)//������� ������ ����� �� ����
			{
				n2++;
				ns = j;
				flag = 1;
			}
			else if ((!(text[i][j] >= '0' && text[i][j] <= '9') && ((text[i][j] >= '�' && text[i][j] <= '�') || text[i][j] == '\n' || text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.' || text[i][j] == '?' || text[i][j] == '"' || text[i][j] == '!' || text[i][j] == '-')) && flag == 1)//����� ����� �� ����
			{
				flag = 0;
				char* buf = (char*)calloc(j - ns + 1, sizeof(char));//�������� ������ ��� �����
				if (NULL == buf)
				{
					printf("�� ������� �������� ������\n");
					exit(1);
				}
				for (k = 0; k < j - ns; k++)//���������� ����������� ����� � �����
				{
					buf[k] = text[i][ns + k];
				}
				buf[k] = '\0';
				preobraz_s(buf, a, n2);//����������� ���������� ������ � ����� � ���������� � ������
				free(buf);
			}
			else if ((text[i][j] >= '�' && text[i][j] <= '�')&&flag==1)//�������� ����� ����� ������� �� ������ �� ����
			{
				flag = 0;
				n2--;
			}
		}
	}
	return n2;
}
int vvod_matrix(int *a, int n2)//������� ��� ������������� ��������� ������ ��� ������� � ����������� ������ ���� ��������� �� ����
{
	char** text;
	int n, m, i;
	printf("������� n:");
	scanf_s("%d", &n);
	text = (char**)calloc(n, sizeof(char*));
	if (NULL == text)
	{
		printf("�� ������� �������� ������\n");
		exit(1);
	}
	printf("������� m:");
	scanf_s("%d", &m);
	getchar();
	for (i = 0; i < n; i++)
	{
		text[i] = (char*)calloc(m, sizeof(char));
		if (NULL == text[i])
		{
			printf("�� ������� �������� ������\n");
			exit(1);
		}
		printf("������� %d ������\n", i+1);
		fgets(text[i], m, stdin);
	}
	n2 = poisk_s(text, n, a, n2);//���� ����� �� �����. ������� ���������� ����� ����
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
	printf("������� ������ �� ������ ����������?\n");
	scanf_s("%d", &n1);
	a = (int*)calloc(n1 * 10, sizeof(int));//�������� ������ ��� ������� �����
	if (NULL == a)
	{
		printf("�� ������� �������� ������\n");
		exit(1);
	}
	for (int i = 0; i < n1; i++)//��������������� ������������ ������� � ������� ����� � ������
	{
		printf("������� n � m ��� %d �������\n", i + 1);
		n2 = vvod_matrix(a, n2);
	}
	printf("�������� ������ �����\n");
	for (int i = 0; i < n2; i++)//������� ���������� ������
	{
		printf("%d ", a[i]);
	}
	free(a);
	return 0;
}