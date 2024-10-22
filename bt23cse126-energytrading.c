#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#define NoOfTrans 100
#define ID_Len 10
#define Success 1
#define Failure 0
int current_trans=0;
struct transaction
 {
    char Trans_ID[ID_Len];
    char Buyer_ID[ID_Len];
    char Seller_ID[ID_Len]; 
    int Amt_energy; // in kwh
    float Price; // price per kwh
    char TimeStamp[20];   // YYYY-MM-DD,HH-MM-SS //24 hr format
 };
struct seller_list
 {
    char Seller_ID[ID_Len];
    int num_seller_trans;
    float seller_revenue;
 };
struct buyer_list
 {
    char Buyer_ID[ID_Len];
    int num_buyer_trans;
    int amount_energy_bought;  // total amount of energy bought by specific buyer!!
 };
struct pair
 {     
            char Seller_ID[ID_Len];
            char Buyer_ID[ID_Len];
            int num_transaction;
            float pair_revenue;  // total revenue generated by specific buyer!!
 };
// declartion of the function
void intiliasize_trans(struct transaction energy_trading[],int size);
void alreadyexisted_transactions(struct transaction energy_trading[]);
int insert_trans(struct transaction energy_trading[],int size,char transcation_id[],char buyer_id[],char seller_id[],int energy_amt,float cost,char timestamp[]);
void display_trans(struct transaction energy_trading[],int size);
void timeperiod_trans(struct transaction energy_trading[],int size,char starttime[],char endtime[]);
void month_maxtrans(struct transaction energy_trading[],int size);
float revenue_calc(struct transaction energy_trading[],int size,char seller[]);
void maxtrans_sortenergy(struct transaction energy_trading[],int size);
void max_seller_buyerpair(struct transaction energy_trading[],int size);
int listOFSeller(struct transaction energy_trading[],struct seller_list sellerlist[],int size );
void seller_display(struct transaction energy_trading[],struct seller_list sellerlist[],int size,int unqseller);
void sort_listseller_revenue(struct transaction energy_trading[],struct seller_list sellerlist[],int size,int unqseller);
int seller_partition(struct seller_list sellerlist[], int low, int high);
void seller_quicksort(struct seller_list sellerlist[], int low, int high);
int listOFBuyer(struct transaction energy_trading[],struct buyer_list buyerlist[],int size );
void buyer_display(struct transaction energy_trading[],struct buyer_list buyerlist[],int size,int unqbuyer);
void buyer_quicksort(struct buyer_list buyerlist[], int low, int high);
int buyer_partition(struct buyer_list buyerlist[], int low, int high);
int listOfpair(struct transaction energy_trading[],int size,struct pair traders[]);
void display_pair(struct pair traders[],int numpair);
void sort_listbuyer_amtenergy(struct transaction energy_trading[],struct buyer_list buyerlist[],int size,int unqbuyer);
void  sort_seller_buyer_pair(struct pair traders[],int choice,int numpair);
//main
int main()
 {  
    // assuming all transcation occur in one year only
    char transcation_id[ID_Len];
    char buyer_id[ID_Len];
    char seller_id[ID_Len];
    int energy_amt; // in kwh
    float cost;  // price per kwh($)
    char timestamp[20]; // YYYY-MM-DD,HH-MM-SS
    int newtrans;
    int statuscode;
    int choice;
    struct transaction energy_trading[NoOfTrans]; // structure for transaction!!
    struct pair traders[NoOfTrans];      // structure for seller buyer pair!!!
    struct seller_list sellerlist[NoOfTrans]; // structure for list of seller!!!
    struct buyer_list buyerlist[NoOfTrans]; // structure for list of buyerr!!!!
    intiliasize_trans(energy_trading,NoOfTrans);// intilazie the respective field with default value;
    alreadyexisted_transactions(energy_trading);// already existed transcation
    int ans=1;     // starrting the record!!
    while(ans)
     {
        printf("\nEnergy Trading Record Management System\n");
        printf("1. Add New Transaction\n");
        printf("2. Display All Transactions\n");
        printf("3. list of transaction of every seller\n");
        printf("4. Create a list of transactions for every buyer.\n");
        printf("5. Transactions in Time Period\n");
        printf("6. Month with Maximum Transactions in same year.\n");
        printf("7. Total Revenue by Seller\n");
        printf("8. Sorting  list of seller according revenue generated\n");
        printf("9. Find and Display the Transaction with the Highest Energy Amount and Sort it accordig to energy amount:\n");
        printf("10. Sorting  list of buyer according energy bought:\n");
        printf("11. Find out a pair of seller/buyer involved in maximum number of transactions.\n");
        printf("12. Sort all seller/buyer pairs in decreasing order of the number of transactions \n");
        printf("13. Sort all seller/buyer pairs in decreasing order of the total revenue generated  between them\n");
        printf("0. Exit\n");
        printf("\nEnter choice: ");  // Which OPeration you want to perform?
        scanf("%d",&choice);
        switch (choice)
         {
            case 0:
                        ans=0;
                        printf("Database exited successfully");
                        printf("\n_________________________________________________________________________________________________\n\n");
                        break;
            case 1:
                printf("\nAdd New Transcation");
                printf("\nHow Many New Transcation you wnat to enter? ");
                scanf("%d",&newtrans);
                for( int i=0;i<newtrans;i++)
                    {    
                        printf("\n");
                        printf("Enter the Transcation_ID: ");
                        scanf("%s",transcation_id);
                        int check=0;
                        for(int i=0;i<current_trans&&check==0;i++)
                                {
                                    if(strcmp(energy_trading[i].Trans_ID,transcation_id)==0)
                                        {       check=1;
                                                printf("\nTranscation Id already used.Enter new one:");
                                                printf("\n");
                                                printf("Enter the new Transcation_ID: ");
                                            scanf("%s",transcation_id);                            
                                        }
                                }
                            printf("Enter the Buyer_ID: ");
                            scanf("%s",buyer_id);
                            printf("Enter the seller ID: ");
                            scanf("%s",seller_id);
                            printf("Enter the amount of energy(in kwh): ");
                            scanf("%d",&energy_amt);
                            printf("Enter the price(per kwh($)): ");
                            scanf("%f",&cost);
                            printf("Enter date and time  of transcation:(YYYY:MM:DD,HH:MM:SS) ");
                            scanf("%s",timestamp);
                        statuscode=insert_trans(energy_trading,NoOfTrans,transcation_id,buyer_id,seller_id,energy_amt,cost,timestamp);
                        if(statuscode==1)
                        {
                            printf("\nGiven Transcation Entered succesfully");
                        }
                        else
                        {
                            printf("\nOperation unsuccesull");
                        }
                        printf("\n_________________________________________________________________________________________________\n\n");
                    }
                break;
            case 2:
                    printf("\nDisplay All Transcation");
                    printf("\n");
                    display_trans(energy_trading,NoOfTrans);
                    printf("\nOperation Successfull");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 3:
                    printf("list of transaction of every seller");
                    int unqseller=0;
                    unqseller=listOFSeller(energy_trading,sellerlist,NoOfTrans);
                    seller_display(energy_trading,sellerlist,NoOfTrans,unqseller); // display list of seller transcation!!!!
                    printf("\nOperation Successfull");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 4:
                    printf("Create a list of transactions for every buyer");
                    int unqbuyer=0;
                    unqbuyer=listOFBuyer(energy_trading,buyerlist,NoOfTrans);
                    buyer_display(energy_trading,buyerlist,NoOfTrans,unqbuyer); // display list of seller transcation!!!!
                    printf("\nOperation Successfull");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 5:  
                    printf("\nThe Transcation in given time period: ");
                    char start_time[20];  // YYYY-MM-DD,HH:MM:SS
                    char end_time[20];    // YYYY-MM-DD,HH:MM:SS
                    printf("\nEnter the start time: ");
                    scanf("%s",start_time); 
                    printf("Enter the end time: ");
                    scanf("%s",end_time);
                    printf("\n");
                    timeperiod_trans(energy_trading,NoOfTrans,start_time,end_time);
                    printf("\nOperation Successfull!!");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 6:
                    // assuming all transcation occur in one year only
                    printf("Find the month in which maximum transactions took place. ");
                    printf("\nJAN:01 \nFEB:02 \nMAR:03 \nAPR:04 \nMAY:05 \nJUNE:06 \nJULY:07 \nAUG:08 \nSEP:09 \nOCT:10 \nNOV:11 \nDEC:12");
                    month_maxtrans(energy_trading,NoOfTrans);
                    printf("\n");
                    printf("\nOperation Successfull!!");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 7:
                    printf("Calculate Total Revenue by Seller:");
                    char seller[ID_Len];
                    printf("\nEnter the seller ID: ");
                    scanf("%s",seller);
                    float Total_Revenue=revenue_calc(energy_trading,NoOfTrans,seller);
                    printf("\n");
                    printf("\nTotal revenue generated by seller %s is $%.2f",seller,Total_Revenue);
                    printf("\nOperation Successfull!!");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 8:
                        printf("\nSorting  list of seller according revenue generated: ");
                        int unqseller1=listOFSeller(energy_trading,sellerlist,NoOfTrans);
                        sort_listseller_revenue(energy_trading,sellerlist,NoOfTrans,unqseller1);
                        seller_display(energy_trading,sellerlist,NoOfTrans,unqseller1); // display list of sorted seller transcation!!!!
                        printf("\nOperation Successfull");
                        break;

            case 9:
                    printf("Find and Display the Transaction with the Highest Energy Amount and Sort iit accordig to   energy amount:");
                    maxtrans_sortenergy(energy_trading,NoOfTrans);
                    printf("\nOperation Successfull!!");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 10:
                    unqbuyer=listOFBuyer(energy_trading,buyerlist,NoOfTrans);
                    printf("\nSorting  list of buyer according energy bought:"); 
                    sort_listbuyer_amtenergy(energy_trading,buyerlist,NoOfTrans,unqbuyer);
                    buyer_display(energy_trading,buyerlist,NoOfTrans,unqbuyer); // display list of seller transcation!!!!
                    printf("\nOperation Successfull");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 11:
                    printf("Find out a pair of seller/buyer involved in maximum number of transactions. ");
                    max_seller_buyerpair(energy_trading,NoOfTrans);
                    printf("\nOperation Successfull!!");
                    printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 12:
                        printf("Sort all seller/buyer pairs in decreasing order of the number of transactions:.");
                        int numpair=0;
                        numpair=listOfpair( energy_trading,NoOfTrans,traders);
                        sort_seller_buyer_pair(traders,1,numpair); // 1 for sorting acc to no. of transaction..
                        printf("\n");
                        display_pair(traders,numpair);
                        printf("\nOperation Successfull!!");
                        printf("\n_________________________________________________________________________________________________\n\n");
                    break;
            case 13:
                        printf("Sort all seller/buyer pairs in decreasing order of the total revenue generated  between them");
                        int numpair1=0; // same as numpair
                        numpair1=listOfpair( energy_trading,NoOfTrans,traders);
                        sort_seller_buyer_pair(traders,2,numpair1); // 2 for soring acc to revernue generated btw pair!!!
                        printf("\n");
                        display_pair(traders,numpair1);
                        printf("\nOperation Successfull!!");
                        printf("\n_________________________________________________________________________________________________\n\n");
                    break;

            default:
                        printf("\nINVALID CHOICE");
                        break;
            }
    if(ans==1)
            {
                printf("\nDo you want to reusme(1) or quit(0)? ");
                printf("\nPress 1 for resume");
                printf("\nPress 0 for quit");
                int option;
                printf("\nEnter ans: ");
                scanf("%d",&option);
                if(option==0) 
                {
                    ans=0;
                    printf("Database exited successfully");
                    printf("\n_________________________________________________________________________________________________\n\n");
                }
                else ans=1;
            }
    }
 return 0;
 }
// function defination!!!
void intiliasize_trans(struct transaction energy_trading[], int size)
 {
    for (int i = 0; i < size; i++) 
    {
        strcpy(energy_trading[i].Trans_ID, ""); 
        strcpy(energy_trading[i].Buyer_ID, ""); 
        strcpy(energy_trading[i].Seller_ID, ""); 
        energy_trading[i].Amt_energy = 0; 
        energy_trading[i].Price = 0; 
        strcpy(energy_trading[i].TimeStamp, "");
    }
 }
void alreadyexisted_transactions(struct transaction energy_trading[]) 
    {
        struct transaction transactions[] = {
        {"T000", "B101", "S201", 500, 0.11, "2024-01-01,14:30:00"},
        {"T001", "B101", "S201", 300, 0.10, "2024-01-15,16:00:00"},
        {"T002", "B102", "S202", 650, 0.12, "2024-02-01,19:00:00"},
        {"T003", "B103", "S203", 450, 0.13, "2024-03-03,18:35:00"},
        {"T004", "B102", "S202", 700, 0.12, "2024-04-04,11:30:00"},
        {"T005", "B101", "S201", 800, 0.11, "2024-05-05,15:45:00"},
        {"T006", "B104", "S204", 600, 0.15, "2024-06-10,09:00:00"},
        {"T007", "B102", "S202", 550, 0.14, "2024-07-12,10:15:00"},
        {"T008", "B106", "S206", 720, 0.16, "2024-07-20,08:30:00"},
        {"T009", "B107", "S207", 480, 0.13, "2024-08-05,14:00:00"},
        {"T010", "B108", "S208", 530, 0.15, "2024-08-12,16:45:00"},
        {"T011", "B101", "S201", 760, 0.14, "2024-09-01,11:00:00"},
        {"T012", "B110", "S201", 640, 0.12, "2024-09-10,17:20:00"},
        {"T013", "B101", "S202", 580, 0.13, "2024-09-15,09:30:00"},
        {"T014", "B102", "S203", 490, 0.14, "2024-09-20,13:45:00"},
        {"T015", "B102", "S202", 750, 0.15, "2024-09-25,12:30:00"},
        {"T016", "B104", "S205", 300, 0.11, "2024-10-01,14:00:00"},
        {"T017", "B105", "S206", 410, 0.14, "2024-10-05,10:15:00"},
        {"T018", "B106", "S207", 670, 0.12, "2024-10-10,09:45:00"},
        {"T019", "B102", "S202", 530, 0.15, "2024-10-15,16:00:00"},
        {"T020", "B104", "S205", 720, 0.12, "2024-10-20,11:30:00"},
        {"T021", "B105", "S206", 490, 0.13, "2024-10-25,13:45:00"},
        {"T022", "B106", "S207", 600, 0.14, "2024-10-30,15:00:00"},
        {"T023", "B107", "S208", 530, 0.15, "2024-11-05,10:30:00"},
        {"T024", "B108", "S209", 600, 0.12, "2024-11-10,14:00:00"},
        {"T025", "B109", "S210", 720, 0.16, "2024-11-15,12:30:00"},
        {"T026", "B110", "S201", 600, 0.14, "2024-11-20,09:00:00"},
        {"T027", "B101", "S202", 750, 0.15, "2024-11-25,10:15:00"},
        {"T028", "B102", "S203", 680, 0.14, "2024-11-30,11:00:00"},
        {"T029", "B103", "S204", 600, 0.13, "2024-12-05,14:45:00"}
    };
    // Copy the predefined transactions to the provided array
    for (int i = 0; i <30; i++) {
        energy_trading[i] = transactions[i];
    }
    current_trans = 30; // Update current transaction count
 }
int insert_trans(struct transaction energy_trading[],int size,char transcation_id[],char buyer_id[],char seller_id[],int energy_amt,float cost,char timestamp[])
 {
    int status_code=Success;
    if(current_trans<size)
    {
       strcpy(energy_trading[current_trans].Trans_ID,transcation_id);
       strcpy(energy_trading[current_trans].Buyer_ID,buyer_id);
       strcpy(energy_trading[current_trans].Seller_ID,seller_id);
       energy_trading[current_trans].Amt_energy=energy_amt;
       energy_trading[current_trans].Price=cost;
       strcpy(energy_trading[current_trans].TimeStamp,timestamp);
       current_trans=current_trans+1;
    }
    else
    {
        status_code=Failure;
    }
    return status_code;   
 }
void display_trans(struct transaction energy_trading[],int size)
 {  
    printf("\n  Sno. | Transaction_ID    | Buyer_ID   | Seller_ID   | Energy Amount (kWh) | Price($/kWh)| Timestamp (YYYY-MM-DD,HH:MM:SS)");
    for (int j = 0; j < current_trans; j++) 
    {
        printf("\n %3d  | %-17s | %-10s | %-10s | %10d          | %15.2f | %18s",
                j + 1,
                energy_trading[j].Trans_ID,
                energy_trading[j].Buyer_ID,
                energy_trading[j].Seller_ID,
                energy_trading[j].Amt_energy,
                energy_trading[j].Price,
                energy_trading[j].TimeStamp);
    }
 }
int listOFSeller(struct transaction energy_trading[],struct seller_list sellerlist[],int size )
 {

    int unqseller=0;
     for(int i=0;i<NoOfTrans;i++)
    {
        strcpy(sellerlist[i].Seller_ID, ""); 
        sellerlist[i].num_seller_trans=0;
        sellerlist[i].seller_revenue=0;
    }
       for(int i=0;i<current_trans;i++)
        { 
             int unq=1;
             int found=0;
                for(int j=0;j<unqseller&&unq==1;j++)
                { 
                        if(strcmp(energy_trading[i].Seller_ID,sellerlist[j].Seller_ID)==0)
                    {
                        sellerlist[j].num_seller_trans++;
                        sellerlist[j].seller_revenue=sellerlist[j].seller_revenue+(energy_trading[i].Amt_energy*energy_trading[i].Price);
                        unq=0;
                        found=1;
                    }
                }
            if(!found)
            {
                strcpy(sellerlist[unqseller].Seller_ID,energy_trading[i].Seller_ID);
                sellerlist[unqseller].num_seller_trans=1;
                sellerlist[unqseller].seller_revenue=energy_trading[i].Amt_energy*energy_trading[i].Price;
                unqseller++;
            }     
        }
    return unqseller;
 }
// display list of seller
void seller_display(struct transaction energy_trading[],struct seller_list sellerlist[],int size,int unqseller)  
 {
        // display list of transcation of seller
        for(int i=0;i<unqseller;i++)
        {
            printf("\n");
             printf("\nSeller_ID: %s (No. of transactions: %d) (Revenue Generated: %.2f ($)", 
            sellerlist[i].Seller_ID, 
            sellerlist[i].num_seller_trans, 
            sellerlist[i].seller_revenue);
             printf("\nTransaction_ID    | Buyer_ID   | Energy Amount (kWh) | Price ($/kWh) | Timestamp (YYYY-MM-DD,HH:MM:SS) ");
            for (int j = 0; j < current_trans; j++) 
            {
                if (strcmp(energy_trading[j].Seller_ID, sellerlist[i].Seller_ID) == 0)
                 {
                        printf("\n%-17s | %-10s | %20d | %10.2f | %s",
                        energy_trading[j].Trans_ID,
                        energy_trading[j].Buyer_ID,
                        energy_trading[j].Amt_energy,
                        energy_trading[j].Price,
                        energy_trading[j].TimeStamp);
                }
            }
        }
 }
void sort_listseller_revenue(struct transaction energy_trading[],struct seller_list sellerlist[],int size,int unqseller)
{
    seller_quicksort(sellerlist, 0, unqseller - 1);
 }
int seller_partition(struct seller_list sellerlist[], int low, int high) 
{
    // Choose the first element as the pivot
    float pivot = sellerlist[low].seller_revenue;
    int i=low;
    int j=high;
    while((i<j)&&(sellerlist[i].seller_revenue<=pivot)) i++;
    while((i<j)&&(sellerlist[j].seller_revenue>pivot)) j--;
    if(sellerlist[j].seller_revenue>pivot)j--;
    while(i<j)
    {
            // Swap sellerlist[i] and sellerlist[j]
            struct seller_list temp = sellerlist[i];
            sellerlist[i] = sellerlist[j];
            sellerlist[j] = temp;
            i++;
            j--;
        while(sellerlist[i].seller_revenue<=pivot) i++;
        while(sellerlist[j].seller_revenue>pivot) j--;
    }
    return j;
}
void seller_quicksort(struct seller_list sellerlist[], int low, int high) 
{
    if (low < high) 
    {
        // Partition the array and get the pivot index
        int pi = seller_partition(sellerlist, low, high);   
        struct seller_list temp = sellerlist[pi];
            sellerlist[pi] = sellerlist[low];
            sellerlist[low] = temp;
        // Recursively sort elements before and after partition
        seller_quicksort(sellerlist, low, pi - 1);
        seller_quicksort(sellerlist, pi + 1, high);
    }
}
int listOFBuyer(struct transaction energy_trading[],struct buyer_list buyerlist[],int size )
 {
    int unqbuyer=0;
    for(int i=0;i<NoOfTrans;i++)
    {
        strcpy(buyerlist[i].Buyer_ID, ""); 
        buyerlist[i].num_buyer_trans=0;
        buyerlist[i].amount_energy_bought=0;
    }
    for(int i=0;i<current_trans;i++)
        { 
             int unq1=0;
             int found1=0;
                for(int j=0;j<unqbuyer&&unq1==0;j++)
                { 
                        if(strcmp(energy_trading[i].Buyer_ID,buyerlist[j].Buyer_ID)==0)
                    {
                        buyerlist[j].num_buyer_trans++;
                        buyerlist[j].amount_energy_bought=buyerlist[j].amount_energy_bought+energy_trading[i].Amt_energy;
                        unq1=1;
                        found1=1;
                    }
                }
            if(!found1)
            {
                strcpy(buyerlist[unqbuyer].Buyer_ID,energy_trading[i].Buyer_ID);
                buyerlist[unqbuyer].num_buyer_trans=1;
                buyerlist[unqbuyer].amount_energy_bought=energy_trading[i].Amt_energy;
                unqbuyer++;
            }     
        }
    return unqbuyer;
 }
// display list of buyer!!!!
void buyer_display(struct transaction energy_trading[],struct buyer_list buyerlist[],int size,int unqbuyer)  
 {
       // Display list of transactions for each buyer
    for (int i = 0; i < unqbuyer; i++) 
     {
        printf("\n");
        printf("\nBuyer_ID: %s (No. of transactions: %d) (Amount Energy bought: %d kWh)\n", 
            buyerlist[i].Buyer_ID, 
            buyerlist[i].num_buyer_trans, 
            buyerlist[i].amount_energy_bought);  
        printf("Transaction_ID    | Seller_ID   | Energy Amount (kWh) | Price ($/kWh) | Timestamp (YYYY-MM-DD,HH:MM:SS) ");
        for (int j = 0; j < current_trans; j++) 
        { 
            if (strcmp(energy_trading[j].Buyer_ID, buyerlist[i].Buyer_ID) == 0)
            { 
                     printf("\n%-17s | %-10s | %20d | %14.2f | %s",
                    energy_trading[j].Trans_ID,
                    energy_trading[j].Seller_ID,
                    energy_trading[j].Amt_energy,
                    energy_trading[j].Price,
                    energy_trading[j].TimeStamp);
            }
        }
     }
 }
void sort_listbuyer_amtenergy(struct transaction energy_trading[],struct buyer_list buyerlist[],int size,int unqbuyer)
{
    buyer_quicksort(buyerlist, 0, unqbuyer - 1);
}
int buyer_partition(struct buyer_list buyerlist[], int low, int high) 
{
    // Choose the first element as the pivot
    float pivot = buyerlist[low].amount_energy_bought;
    int i=low;
    int j=high;
    while((i<j)&&(buyerlist[i].amount_energy_bought<=pivot)) i++;
    while((i<j)&&(buyerlist[j].amount_energy_bought>pivot)) j--;
    if(buyerlist[j].amount_energy_bought>pivot)j--;
    while(i<j)
    {
            // Swap sellerlist[i] and sellerlist[j]
            struct buyer_list temp = buyerlist[i];
            buyerlist[i] = buyerlist[j];
            buyerlist[j] = temp;
            i++;
            j--;
            while(buyerlist[i].amount_energy_bought<=pivot) i++;
           while(buyerlist[j].amount_energy_bought>pivot) j--;
    }
    return j;
}
void buyer_quicksort(struct buyer_list buyerlist[], int low, int high)
{
    if (low < high) 
    {
        int pi = buyer_partition(buyerlist, low, high);
        struct buyer_list temp = buyerlist[pi];
        buyerlist[pi] = buyerlist[low];
        buyerlist[low] = temp;
        buyer_quicksort(buyerlist, low, pi - 1);
        buyer_quicksort(buyerlist, pi + 1, high);
    }
}
void timeperiod_trans(struct transaction energy_trading[],int size,char starttime[],char endtime[])
 {
    int i=0;
    int found=0;
    printf("\n  Sno.| Transaction_ID | Buyer_ID | Seller_ID | Energy Amount (kWh) | Price ($/kWh) | Timestamp (YYYY-MM-DD,HH:MM:SS) ");
    for(i=0;i<current_trans;i++)
    {
        if(strcmp(energy_trading[i].TimeStamp,starttime)>=0&&strcmp(energy_trading[i].TimeStamp,endtime)<=0)
        {
                found=1;
               printf("\n %3d | %-15s | %-10s | %-10s | %10d | %14.2f | %s",
       i + 1,
       energy_trading[i].Trans_ID,
       energy_trading[i].Buyer_ID,
       energy_trading[i].Seller_ID,
       energy_trading[i].Amt_energy,
       energy_trading[i].Price,
       energy_trading[i].TimeStamp);
       }
    }
    if(found==0)
    {
       printf("\nNo transcation btween that time period");
    }
 }
void month_maxtrans(struct transaction energy_trading[],int size)
 {
    int month[13]={0}; // there are 12 month in year so hash array of 13 size
    // intilaize month array  with 0
    int maxtrans=0;
    int maxtrans_month=0;
    for(int i=0;i<current_trans;i++)
    {
        char mnth[3]={energy_trading[i].TimeStamp[5],energy_trading[i].TimeStamp[6],'\0'};
        int num=atoi(mnth);
        month[num]++;
    }
    for(int i=1;i<=12;i++)
    {
        if(month[i]>maxtrans) 
       { 
        maxtrans=month[i];
        maxtrans_month=i;
       }
    }
    printf("\n");
    printf("\nthe max trans occur in month %d and no of transcation is :%d",maxtrans_month,maxtrans); 
 }
float revenue_calc(struct transaction energy_trading[],int size,char seller[])
 {
        int found=0;
        float return_value=0;
        float total_revenue=0;
        for(int i=0;i<size;i++)
        {
            if(strcmp(seller,energy_trading[i].Seller_ID)==0)
            {
                found=1;
                total_revenue=total_revenue+((energy_trading[i].Amt_energy)*(energy_trading[i].Price));
            }
        }
        if(found==1)
        {
            return_value=total_revenue;
        }
        else
        {
            printf("SELLER does not found!!!");
            return_value=0;
        }
        return return_value;
 }
void maxtrans_sortenergy(struct transaction energy_trading[],int size)
 {
    struct transaction temp_trans[NoOfTrans]; // for saving original database it does not effect while sorting
    for(int i=0;i<current_trans;i++)
    {
        strcpy(temp_trans[i].Trans_ID,energy_trading[i].Trans_ID); 
        strcpy(temp_trans[i].Buyer_ID,energy_trading[i].Buyer_ID); 
        strcpy(temp_trans[i].Seller_ID,energy_trading[i].Seller_ID); 
        temp_trans[i].Amt_energy=energy_trading[i].Amt_energy; 
        temp_trans[i].Price=energy_trading[i].Price; 
        strcpy(temp_trans[i].TimeStamp,energy_trading[i].TimeStamp);
    }
    int maxposi=-1;
    for (int i = 1; i < current_trans; i++) 
    {
        struct transaction key = energy_trading[i];
        int j = i - 1;
        while (j >= 0 && energy_trading[j].Amt_energy > key.Amt_energy) {
            energy_trading[j + 1] = energy_trading[j];
            j--;
        }
        energy_trading[j + 1] = key;
    }
    maxposi=current_trans-1;
    printf("\n MAXIMUM TRADING EVEVNT:");
    printf("\n  Sno.|Transaction_ID| Buyer_ID | Seller_ID | Energy Amount (kWh) | Price ($/kWh) | Timestamp (YYYY-MM-DD,HH:MM:SS) ");
    printf("\n %3d | %-15s | %-10s | %-10s | %10d | %16.2f | %s",
        1,
        energy_trading[maxposi].Trans_ID,
        energy_trading[maxposi].Buyer_ID,
        energy_trading[maxposi].Seller_ID,
        energy_trading[maxposi].Amt_energy,
        energy_trading[maxposi].Price,
        energy_trading[maxposi].TimeStamp);
    printf("\n Ater sorting acc with amnt of energy");
  
 display_trans(energy_trading,NoOfTrans);
 }
void max_seller_buyerpair(struct transaction energy_trading[],int size)
 {
    char seller[ID_Len];
    char buyer[ID_Len];
    int maxtrans=0;
    for(int i=0;i<current_trans;i++)
    { 
        int notrans=0;
        for(int j=0;j<current_trans;j++)
        {
            if((strcmp(energy_trading[i].Seller_ID,energy_trading[j].Seller_ID)==0)&&strcmp(energy_trading[i].Buyer_ID,energy_trading[j].Buyer_ID)==0)
            {
                notrans=notrans+1;
            }
        }
        if(notrans>maxtrans)
        {
            maxtrans=notrans;
            strcpy(seller,energy_trading[i].Seller_ID);
            strcpy(buyer,energy_trading[i].Buyer_ID);
        }
    }
    printf("\n");
    printf("\npair of seller/buyer involved in maximum number of transactions is(%s,%s) and number of transaction is:%d",seller,buyer,maxtrans);
 }
int listOfpair(struct transaction energy_trading[],int size,struct pair traders[])
 {
    int numpair=0;
    for(int i=0;i<current_trans;i++)
        { 
             int flag=0;
             int found=0;
                for(int j=0;j<numpair&&flag==0;j++)
                { 
                        if((strcmp(energy_trading[i].Seller_ID,traders[j].Seller_ID)==0)&&strcmp(energy_trading[i].Buyer_ID,traders[j].Buyer_ID)==0)
                    {
                        traders[j].num_transaction++;
                        traders[j].pair_revenue=traders[j].pair_revenue+(energy_trading[i].Amt_energy*energy_trading[i].Price);
                        found=1;
                        flag=1;
                    }
                }
            if(!found)
            {
                strcpy(traders[numpair].Seller_ID,energy_trading[i].Seller_ID);
                strcpy(traders[numpair].Buyer_ID,energy_trading[i].Buyer_ID);
                traders[numpair].num_transaction=1;
                traders[numpair].pair_revenue=energy_trading[i].Amt_energy*energy_trading[i].Price;
                numpair=numpair+1;
            }     
        }
    return numpair;   
 }
void display_pair(struct pair traders[],int numpair)
   {  
    // Display all seller/buyer pairs in decreasing order of the number of transactions between them.
    printf("\nseller ID       | buyer ID        | no. of trans | pair revenue ($)");
    for (int j = 0; j < numpair; j++) 
    {
                printf("\n%-15s | %-15s | %12d | %10.2f",
            traders[j].Seller_ID,
            traders[j].Buyer_ID,
            traders[j].num_transaction,
            traders[j].pair_revenue);
    }

    } 
void  sort_seller_buyer_pair(struct pair traders[],int choice,int numpair)
    {  
        int sort=0;
        for(int i=0;i<numpair-1&&sort==0;i++)
        {
            sort=1;
            for(int j=0;j<numpair-i-1;j++)
            {
            int condition = 0;
                if (choice == 1) 
                { // Sort by number of transactions
                    condition = traders[j].num_transaction < traders[j + 1].num_transaction;
                } 
                else if (choice== 2)
                { // Sort by pair revenue
                    condition = traders[j].pair_revenue < traders[j + 1].pair_revenue;
                }
                if (condition)
            {
                struct pair temp;
                temp=traders[j];
                traders[j]=traders[j+1];
                traders[j+1]=temp;
                sort=0;
            }  
            }
        }
    }
// end of the database
//RONAK SINGH  
//BT23CSE126