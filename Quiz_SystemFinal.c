#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define questions 10
#define maxoption 10

struct Question 
{
    char questionText[100];
    char options[maxoption][50];
    char explanation[200];
    int no_of_options;
    int correctopt;
};
typedef struct 
{
    char name[100];
    int score;
    int ranking;
} Student;


void addQuestion(struct Question quiz[], int *no_of_ques) 
{
    int f;
    
        printf("Enter the question: ");
        getchar();
        fgets(quiz[*no_of_ques].questionText, sizeof(quiz[*no_of_ques].questionText), stdin);
        int c=0;
        for (int i = 0; i < 3; i++)
        {
            if(i>1)
            {
                printf("If you want to add options press 1 else press 0  ");
                scanf("%d",&f);
                getchar();
                if(f==1)
                {
                    i--;
                    f=0;
                }
                else
                break;
            }
            printf("Enter option %d: ", c+1);
            fgets(quiz[*no_of_ques].options[c], sizeof(quiz[*no_of_ques].options[c]), stdin);
            c++;
           // quiz[*no_of_ques].no_of_options[j]=c;
            
        }
       // quiz[*no_of_ques].options[c]="ok";
       
       quiz[*no_of_ques].no_of_options=c;
      
        printf("Enter the correct option (1-%d): ", c);
        scanf("%d", &quiz[*no_of_ques].correctopt);
        printf("Enter the explanation for the question:\n ");
       getchar();
        fgets(quiz[*no_of_ques].explanation, sizeof(quiz[*no_of_ques].explanation), stdin);
        (*no_of_ques)++;
}
void saveQuizToFile(struct Question quiz[], int no_of_ques) 
{
    FILE *file = fopen("quiz_data.txt", "w");
    
    fprintf(file, "%d\n", no_of_ques);

    for (int i = 0; i < no_of_ques; i++) 
    {
        
        fprintf(file, "%s", quiz[i].questionText);
        fprintf(file, "%d\n", quiz[i].no_of_options);
        for (int j = 0; j < quiz[i].no_of_options; j++) 
        {
            fprintf(file, "%s", quiz[i].options[j]);
        }
        fprintf(file, "%d\n", quiz[i].correctopt);
        fprintf(file, "%s", quiz[i].explanation);
    }

    fclose(file);
    printf("Quiz data saved to file.\n");
}
void loadQuizFromFile(struct Question quiz[], int *no_of_ques) 
{
   
    FILE *file = fopen("quiz_data.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening file for reading.\n");
        return;
    }
    
   *no_of_ques=0;
    char temp[10];
    fgets(temp, sizeof(temp), file);
    sscanf(temp, "%d", no_of_ques);
   // printf("%d\n",*no_of_ques);
    for (int i = 0; i < *no_of_ques; i++) 
    {   
        fgets(quiz[i].questionText, sizeof(quiz[i].questionText), file);
       // puts(quiz[i].questionText);

       fgets(temp, sizeof(temp), file);
       sscanf(temp, "%d", &quiz[i].no_of_options);
    //   printf("%d\n",quiz[i].no_of_options);
        for(int j = 0; j < quiz[i].no_of_options; j++) 
        {
            fgets(quiz[i].options[j], sizeof(quiz[i].options[j]), file);
          //  puts(quiz[i].options[j]);
            
        }
        fgets(temp, sizeof(temp), file);
       sscanf(temp, "%d", &quiz[i].correctopt);

      // printf("%d\n",quiz[i].correctopt);
       fgets(quiz[i].explanation, sizeof(quiz[i].explanation), file);
      //  puts(quiz[i].explanation[i]);
       
    }
   

    fclose(file);
    printf("Quiz data loaded from file.\n");
} 

float calculateClassAverage(Student students[], int numStudents) 
{
    int sum = 0;
    for (int i = 0; i < numStudents; i++) {
        sum += students[i].score;
    }
    return (float)sum / numStudents;
}
void calculateRankings(Student students[], int numStudents) 
{
    for (int i = 0; i < numStudents; i++) 
    {
        students[i].ranking = 1;
        for (int j = 0; j < numStudents; j++) 
        {
            if (students[j].score > students[i].score) 
            {
                students[i].ranking++;
            }
        }
    }
}
void conductQuiz(struct Question quiz[], int no_of_ques, int *numStudents, Student students[]) 
{
    loadQuizFromFile(quiz, &no_of_ques);
    FILE *st;
    int choice=0;
    printf("Enter name : ");
    getchar();
    fgets(students[*numStudents].name, sizeof(students[*numStudents].name), stdin);
    students[*numStudents].name[strlen(students[*numStudents].name)-1] = '\0';
    int score = 0;
    int c=1;
    for (int i = 0; i < no_of_ques; i++) 
    {
        printf("\nQuestion %d: %s\n", i + 1, quiz[i].questionText);
        c=1;
        
        for (int j = 0; j < quiz[i].no_of_options; j++) 
        {
            
            printf("%d. %s\n", c, quiz[i].options[j]);
            c++;
        } 

        
        printf("Enter your choice (1-%d): ", quiz[i].no_of_options);
        scanf("%d", &choice);

        if (choice == quiz[i].correctopt) 
        {
            printf("Correct!\n");
            score++;
        } else 
        {
            printf("Incorrect. Correct option is %d.\n", quiz[i].correctopt);
            printf("Explanation: %s " ,quiz[i].explanation);
        }
    }
    st=fopen("Stu_data.txt","a");
    //fputs(students[*numStudents].name, st);
    fprintf(st, "%s %d\n", students[*numStudents].name, score);
    numStudents++;
    fclose(st);
    printf("\nQuiz complete. Your score: %d/%d\n", score, no_of_ques);  
}
void showresult(Student students[], int *numStudents)
{
    FILE *file;
    file = fopen("Stu_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        
    }
    //*numStudents=0;
    // Read student data from the file
    while (fscanf(file, "%s %d", students[*numStudents].name, &students[*numStudents].score) == 2) 
    {
      
        (*numStudents)++;
        
    }
    //printf("%d",*numStudents);
    
    // Calculate rankings
    calculateRankings(students, *numStudents);

    // Display results
    printf("\nResults:\n");
    printf("Name\t\tScore\tRanking\n");
    for (int i = 0; i < *numStudents; i++) {
        printf("%s\t\t%d\t%d\n", students[i].name, students[i].score, students[i].ranking);
    }
    
    // Calculate and display class average
    float classAverage = calculateClassAverage(students, *numStudents);
    printf("\nClass Average: %.2f\n", classAverage);
    fclose(file);
}
int main() 
{
    
    Student students[10];
    system("color 3f");
    struct Question quiz[questions];
    int numStudents=0;
    int no_of_ques = 0;
    int choice;
    
    printf("Welcome to the Quiz Game!\n");
        

        do {
            
            printf("\n1. Add a question\n2. Save quiz data to file\n3. Conduct the quiz\n4. See Result\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    system("cls");
                    addQuestion(quiz, &no_of_ques);
                    break;
                case 2:
                    saveQuizToFile(quiz, no_of_ques);
                    break;
                case 3:
                    system("cls");
                    conductQuiz(quiz, no_of_ques, &numStudents, students);
                    break;
                case 4:
                    system("cls");
                    showresult(students, &numStudents);
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        } while (choice != 4);
 

    return 0;
}
