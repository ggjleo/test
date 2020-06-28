#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
void create(int n);  //创建n个链表对象 Student
void deleteAll();    //清空链表 
void print();        //打印所有学生信息 
void addStudent();   //在尾部追加一个学生 
void deleteStudent(char *n);  //实现删除指定学生 
struct Student *findStudent(char *n);  //查找指定学生 
void writeFile();    //写文件 
struct Student *readFile();     //读文件 

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
	printf("**********************学生管理系统***************************\n");
	printf("1.批量添加学生（创建链表对象）\n2.清空链表\n3.尾部追加学生\n4.删除学生\n5.查找学生\n6.打印学生信息\n7.写入文件\n8.读取文件\n9.退出程序\n");
	printf("请输入你的选择（1-6）：");
	scanf("%c",&flag);
	getchar();                 
	if(flag == '1'){                              //can use "switch-case" 
	printf("**********************批量添加学生***************************\n");
	printf("请输入你想要添加的学生个数（>0）：");
	scanf("%d",&num);
	if(num <= 0){
		printf("请输入大于0的数！\n");
		printf("*************************************************************\n");
	}else{ 
    printf("请依次输入学生信息（姓名，年级，性别(m:男 w:女)，生日）：\n");
	create(num); }
	}else if(flag == '2'){
		deleteAll();	
	}else if(flag == '3'){
	printf("**********************尾部追加学生***************************\n");
	addStudent(); 
	}else if(flag == '4'){
	printf("********************删除指定学生*************************\n");
	printf("请输入你想要删除的学生名字：");
	f = (char*)malloc(sizeof(char) * 30);
	scanf("%s",f);
	deleteStudent(f);
	free(f);
	f = NULL;
	}else if(flag == '5'){
	printf("********************查找指定学生*************************\n");
	printf("请输入你想要查找的学生名字：");
	f = (char*)malloc(sizeof(char) * 30);
	scanf("%s",f);
	struct Student *temp = findStudent(f);
	if(temp == NULL){
		printf("该学生不存在！\n");
	}else {
		printf("查找结果如下：\n");
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
		printf("文件读取成功！\n");
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
	printf("添加成功！");
	print(); 
}

void deleteAll(){
	if(head == NULL){
		printf("链表已为空！\n");
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
	printf("链表清空成功！\n");
	} 
}

void print(){
	if(head == NULL || head->next == NULL){
		printf("暂无学生信息！\n");
	}else {
		printf("学生列表：\n");
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
	printf("请依次输入学生信息（姓名，年级，性别(m:男 w:女)，生日）:\n");
	scanf("%s %d %s %s",&node->Name,&node->Grade,&node->gender,&node->birthday);
	end->next = node; 
	end = node;
	end->next = NULL;
	printf("添加成功！\n");
	print(); 
}

void deleteStudent(char *name){         //删除指定的学生 
	struct Student *temp = findStudent(name);
	if(head == NULL){
		printf("链表为空！\n");
	}else if(temp == NULL){
		printf("该学生不存在！\n");
	}else if(head == end){         //只有一个学生 
		free(head);
		head = NULL;
		end = NULL;
		printf("删除成功！\n"); 
		print(); 
	}else if(head->next == end){  //有两个学生 
		if(temp == head){         //删除的属于头部 
			head = temp->next;
			end = temp->next;
			free(temp);
			temp = NULL;
			end->next = NULL; 
			printf("删除成功！\n");
			print(); 
		}else if(temp == end){   //删除的属于尾部 
			end = head;
			free(temp);
			temp = NULL;
			end->next = NULL;
			printf("删除成功！\n");
			print(); 
		}
	}else {                      //多个学生 
		if(temp == head){
			head = temp->next;
			free(temp);
			temp = NULL;
			printf("删除成功！\n");
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
			printf("删除成功！\n");
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
			 printf("删除成功！\n");
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
		printf("数据不存在，写入失败！\n");
	}else{
	struct Student *p = head->next;
	if((file = fopen("Student.txt","w")) == NULL){  //追加写入文件 w为覆盖写入文件 
	printf("不能打开数据文件。\n");
	return;
	}else{
	while(p){
	fprintf(file,"%s\t%d\t%s\t%s \n",p->Name,p->Grade,p->gender,p->birthday);
	p = p->next;
	}
	printf("文件写入成功！\n"); 
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

