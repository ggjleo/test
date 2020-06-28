#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
void create(int n);  //����n��������� Student
void deleteAll();    //������� 
void print();        //��ӡ����ѧ����Ϣ 
void addStudent();   //��β��׷��һ��ѧ�� 
void deleteStudent(char *n);  //ʵ��ɾ��ָ��ѧ�� 
struct Student *findStudent(char *n);  //����ָ��ѧ�� 
void writeFile();    //д�ļ� 
struct Student *readFile();     //���ļ� 

struct Student{
	char Name[30];  
	int Grade;
	char gender[2];
	char birthday[30];
	struct Student *next; 
};

struct Student *head = NULL; 
struct Student *end = NULL; 

int main(){
	int num,a;
	char flag,*f;
	     
	while(true){
	printf("**********************ѧ������ϵͳ***************************\n");
	printf("1.�������ѧ���������������\n2.�������\n3.β��׷��ѧ��\n4.ɾ��ѧ��\n5.����ѧ��\n6.��ӡѧ����Ϣ\n7.д���ļ�\n8.��ȡ�ļ�\n9.�˳�����\n");
	printf("���������ѡ��1-6����");
	scanf("%c",&flag);
	getchar();                 
	if(flag == '1'){                              //can use "switch-case" 
	printf("**********************�������ѧ��***************************\n");
	printf("����������Ҫ��ӵ�ѧ��������>0����");
	scanf("%d",&num);
	if(num <= 0){
		printf("���������0������\n");
		printf("*************************************************************\n");
	}else{ 
    printf("����������ѧ����Ϣ���������꼶���Ա�(m:�� w:Ů)�����գ���\n");
	create(num); }
	}else if(flag == '2'){
		deleteAll();	
	}else if(flag == '3'){
	printf("**********************β��׷��ѧ��***************************\n");
	addStudent(); 
	}else if(flag == '4'){
	printf("********************ɾ��ָ��ѧ��*************************\n");
	printf("����������Ҫɾ����ѧ�����֣�");
	f = (char*)malloc(sizeof(char) * 30);
	scanf("%s",f);
	deleteStudent(f);
	free(f);
	f = NULL;
	}else if(flag == '5'){
	printf("********************����ָ��ѧ��*************************\n");
	printf("����������Ҫ���ҵ�ѧ�����֣�");
	f = (char*)malloc(sizeof(char) * 30);
	scanf("%s",f);
	struct Student *temp = findStudent(f);
	if(temp == NULL){
		printf("��ѧ�������ڣ�\n");
	}else {
		printf("���ҽ�����£�\n");
		printf("%s\t%d\t%s\t%s\n",temp->Name,temp->Grade,temp->gender,temp->birthday); 
	}
	free(f);
	f = NULL;
	printf("*************************************************************\n");
	}else if(flag == '6'){
	printf("*************************************************************\n");
	print();	
	}else if(flag == '7'){
		writeFile();
	}else if(flag == '8'){
		struct Student *temp = readFile();
		printf("�ļ���ȡ�ɹ���\n");
		print(); 
	}else if(flag == '9'){
		exit(0);
	}
	fflush(stdin); 		
  } 
  return 0;
}

void create(int n){
	struct Student *node;
	if(head == NULL){   						       
	head = (struct Student *)malloc(sizeof(struct Student));
	end = head;
	}        									        
	for(int i=0;i<n;i++){								        
		node = (struct Student *)malloc(sizeof(struct Student));
		scanf("%s %d %s %s",&node->Name,&node->Grade,&node->gender,&node->birthday); 
		end->next = node;								
		end = node;     								
	}
	end->next = NULL;                                   
	printf("��ӳɹ���");
	print(); 
}

void deleteAll(){
	if(head == NULL){
		printf("������Ϊ�գ�\n");
	}else{ 
	struct Student *p = head; 
	while(p!=NULL){
		struct Student *temp = p;
		p = p->next;
		free(temp);
		temp = NULL;
	}
	head = NULL;
	end = NULL;
	printf("������ճɹ���\n");
	} 
}

void print(){
	if(head == NULL || head->next == NULL){
		printf("����ѧ����Ϣ��\n");
	}else {
		printf("ѧ���б�\n");
		struct Student *p = head;
		int i = 1; 
		p = p->next; 
		while(p != NULL){
		printf("%d\t%s\t%d\t%s\t%s\n",i,p->Name,p->Grade,p->gender,p->birthday);
		p = p->next;
		i++;
	    }
    }
	printf("*************************************************************\n");
}

void addStudent(){
	if(head == NULL){   						
	head = (struct Student *)malloc(sizeof(struct Student)); 
	end = head;
	} 
	struct Student *node = (struct Student *)malloc(sizeof(struct Student));  
	printf("����������ѧ����Ϣ���������꼶���Ա�(m:�� w:Ů)�����գ�:\n");
	scanf("%s %d %s %s",&node->Name,&node->Grade,&node->gender,&node->birthday);
	end->next = node; 
	end = node;
	end->next = NULL;
	printf("��ӳɹ���\n");
	print(); 
}

void deleteStudent(char *name){         //ɾ��ָ����ѧ�� 
	struct Student *temp = findStudent(name);
	if(head == NULL){
		printf("����Ϊ�գ�\n");
	}else if(temp == NULL){
		printf("��ѧ�������ڣ�\n");
	}else if(head == end){         //ֻ��һ��ѧ�� 
		free(head);
		head = NULL;
		end = NULL;
		printf("ɾ���ɹ���\n"); 
		print(); 
	}else if(head->next == end){  //������ѧ�� 
		if(temp == head){         //ɾ��������ͷ�� 
			head = temp->next;
			end = temp->next;
			free(temp);
			temp = NULL;
			end->next = NULL; 
			printf("ɾ���ɹ���\n");
			print(); 
		}else if(temp == end){   //ɾ��������β�� 
			end = head;
			free(temp);
			temp = NULL;
			end->next = NULL;
			printf("ɾ���ɹ���\n");
			print(); 
		}
	}else {                      //���ѧ�� 
		if(temp == head){
			head = temp->next;
			free(temp);
			temp = NULL;
			printf("ɾ���ɹ���\n");
			print(); 
		}
		else if(temp == end){
			struct Student *p1 = head,*pr = head; 
			while(pr!=end){
				p1 = pr;
				pr = pr->next;
			}
			end = p1;
			free(temp);
			temp = NULL;
			end->next = NULL;
			printf("ɾ���ɹ���\n");
			print(); 
		}else {
			struct Student *p2 = head;
			while(p2->next!=temp)
			{
				p2 = p2->next;
			}
			 p2->next = temp->next;
			 free(temp);
			 temp = NULL;
			 printf("ɾ���ɹ���\n");
			 print(); 
		}
	}
} 

struct Student *findStudent(char *name){
	struct Student *p = head;
	while(p != NULL)
	{
	if(strcmp(p->Name,name)==0)
	{
		return p;
	}
	p = p->next;
	}
	return NULL;	
}

void writeFile(){
	FILE *file;
	if(head == NULL || head->next == NULL){
		printf("���ݲ����ڣ�д��ʧ�ܣ�\n");
	}else{
	struct Student *p = head->next;
	if((file = fopen("Student.txt","w")) == NULL){  //׷��д���ļ� wΪ����д���ļ� 
	printf("���ܴ������ļ���\n");
	return;
	}else{
	while(p){
	fprintf(file,"%s\t%d\t%s\t%s \n",p->Name,p->Grade,p->gender,p->birthday);
	p = p->next;
	}
	printf("�ļ�д��ɹ���\n"); 
	}
	fclose(file);
}
}

struct Student *readFile() {  
    struct Student *pointer;
    FILE *fp;  
    if(head == NULL){   						
	head = (struct Student *)malloc(sizeof(struct Student)); 
	end = head;
	end->next = NULL;
	}
    fp=fopen("Student.txt","r");
    char name[30];
    int grade;
    char gender[2];
    char birthday[30];
    while(fscanf(fp,"%s %d %s %s\n",&name,&grade,&gender,&birthday)!=EOF)
    {      
	pointer=(struct Student*)malloc(sizeof(struct Student)); 
    strcpy(pointer->Name,name);
    pointer->Grade = grade;
    strcpy(pointer->gender,gender);
    strcpy(pointer->birthday,birthday);
    end->next=pointer;  
    end = pointer;  
    }
    end->next=NULL; 
    fclose(fp);
    return head;
}

