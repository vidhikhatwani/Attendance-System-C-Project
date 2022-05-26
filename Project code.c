#include<stdio.h>
struct student{
  	char name[20];
  	long int pr_no;
 	int present;
  	int total;
};

int main(){
  	FILE *outfile, *infile;		//Files for writing, reading 
  	int i, num, choice = 0;
  	char pres;
  	while(choice != 4){
        	printf("1)Feed fresh data\n2)Take attendance\n3)Check atrendance percentage\n4)Exit\nEnter the choice: ");
        	scanf(" %d",  &choice);
        	if(choice == 1){ 
        	    	outfile = fopen("Attendance.bin", "wb");        //wb: open an binary file for reading
            		printf ("Enter the no. of students in the class: ");
            		scanf (" %d", &num);
			struct student temp;
            		for(i=0; i<num;i++){
                		printf("Enter the %d student's name: ", i+1);
               		 	scanf(" %s", temp.name);
                		printf("Enter the %d student's prn: ", i+1);
                		scanf(" %lu", &temp.pr_no);
                		temp.present = 0;
                		temp.total = 0;
                		fwrite(&temp, sizeof(struct student), 1, outfile);
              		}
			fclose(outfile);
          	}
       		else if (choice == 2){
            		infile = fopen("Attendance.bin", "rb");      //rb: open an binary file for reading
            		outfile = fopen("temp.bin", "wb");
              		printf("Enter p if present and a if absent\n");
			struct student temp;
			num = 0;
			while(fread(&temp, sizeof(struct student), 1, infile)){
				num++;
			}
			fseek(infile, 0, SEEK_SET);         //SEEK_SET (position from where offset is added): Beginning of file
            		for(i=0; i<num; i++){
                 		fread(&temp, sizeof(struct student), 1, infile);
				printf ("Mark for student %d : ", i+1);
				scanf (" %c", &pres);
                 		if (pres == 'p' || pres == 'P'){
                       			temp.present++;
                       			temp.total++;
                       			fwrite(&temp, sizeof(struct student), 1, outfile);
                    		}
                 		else if (pres == 'a' || pres == 'A'){
                       			temp.total++;
                       			fwrite(&temp, sizeof(struct student), 1, outfile);
                     		}
                 		else{
                       			printf ("Enter a valid option\n");
                       			i--;
                                }
                     
               		}
            		fclose(outfile);
            		fclose(infile);
			infile = fopen("temp.bin", "rb");
			outfile = fopen("Attendance.bin", "wb");
			for(i=0; i<num; i++){
				fread(&temp, sizeof(struct student), 1, infile);
				fwrite(&temp, sizeof(struct student), 1, outfile);
			}
			fclose(infile);
			fclose(outfile);
          	}

          else if(choice==3)
            {
               float percentage;              //for calculation of attendance percentage
               long int cprn;                 // for inputting the prn from user to check 
               int flag=0;
               struct student temp;
               num = 0;
               infile = fopen("Attendance.bin","rb");
			   while(fread(&temp, sizeof(struct student),1,infile))     //calculating the no. of records in the file
			     {
			 	     num++;
		         }
               printf("Enter the prn of the student: ");
               scanf("%lu",&cprn);
               fseek(infile, 0, SEEK_SET);
               
               for(i=0; i<num;i++)                                        //checking the records for the required prn
                 {
                     fread(&temp, sizeof(struct student),1,infile);
                     if(temp.pr_no==cprn)
                       {
                           percentage=(float)temp.present*100/(float)temp.total;
                           flag=1;
                           break;
                       }
                       
                 }
                if(flag==1)                  //displaying
                {
                    printf("Name: %s\nPRN: %lu\nAttendance percentage: %f\n",temp.name,temp.pr_no,percentage);
                }
                else if(flag==0)
                {
                    printf("PRN not found\n");
                }
                fclose(infile);
            }
    	}
 	return 0;
}
