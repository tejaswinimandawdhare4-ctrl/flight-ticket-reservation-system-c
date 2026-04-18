#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    int ticketID;
    char name[50];
    char source[50];
    char destination[50];
    struct node *prev, *next;
} node;
typedef struct DL
{
    node *start;
} DL;

void display(DL *l)
{
    node *p;
    if(l->start == NULL)
    {
        printf("\nList is Empty");
        return;
    }
    p = l->start;
    while(p != NULL)
    {
        printf("\nTicket ID: %d", p->ticketID);
        printf("\nName: %s", p->name);
        printf("\nFrom: %s", p->source);
        printf("\nTo: %s\n", p->destination);
        p = p->next;
    }
}

void insert(DL *l)
{
    node *newrec;
    newrec = (node*)malloc(sizeof(node));
    printf("\nEnter Ticket ID: ");
    scanf("%d", &newrec->ticketID);
    printf("Enter Name: ");
    scanf(" %[^\n]", newrec->name);
    printf("Enter Source: ");
    scanf(" %[^\n]", newrec->source);
    printf("Enter Destination: ");
    scanf(" %[^\n]", newrec->destination);
    newrec->prev = NULL;
    newrec->next = l->start;
    if(l->start != NULL)
    {
        l->start->prev = newrec;
    }
    l->start = newrec;
    printf("\nBooking Added!");
}

void searchBooking(DL *l)
{
    node *p;
    int tid;
    int found = 0;

    if(l->start == NULL)
    {
        printf("\nList is Empty");
        return;
    }

    printf("\nEnter Ticket ID to search: ");
    scanf("%d", &tid);

    p = l->start;

    while(p != NULL)
    {
        if(p->ticketID == tid)
        {
            printf("\nBooking Found!");
            printf("\nTicket ID: %d", p->ticketID);
            printf("\nName: %s", p->name);
            printf("\nFrom: %s", p->source);
            printf("\nTo: %s\n", p->destination);
            found = 1;
            break;
        }
        p = p->next;
    }

    if(!found)
    {
        printf("\nTicket ID %d not found!", tid);
    }
}

void deleteB(DL *l)
{
    node *p;
    int tid;
    
    if(l->start == NULL)
    {
        printf("\nList is Empty");
        return;
    }
    
    printf("\nEnter Ticket ID to delete: ");
    scanf("%d", &tid);
    
    p = l->start;
    while(p != NULL)
    {
        if(p->ticketID == tid)
        {
            if(p->prev != NULL)
                p->prev->next = p->next;
            else
                l->start = p->next;  // deleting head node
            
            if(p->next != NULL)
                p->next->prev = p->prev;
            
            free(p);
            printf("\nBooking Deleted!");
            return;
        }
        p = p->next;
    }
    printf("\nTicket ID %d not found!", tid);
}

void saveToFile(DL *l)
{
    FILE *fp;
    node *p;
    fp = fopen("flights.csv", "w");
    if(fp == NULL)
    {
        printf("\nFile Error!");
        return;
    }
    fprintf(fp, "TicketID,Name,Source,Destination\n");
    p = l->start;
    while(p != NULL)
    {
        fprintf(fp, "%d,%s,%s,%s\n",
                p->ticketID,
                p->name,
                p->source,
                p->destination);
        p = p->next;
    }
    fclose(fp);
    printf("\nData saved to flights.csv (Open in Excel!)");
}

int main()
{
    int ch;
    DL l;
    l.start = NULL;
    while(1)
    {
        printf("\nMenu:");
        printf("\n1-Add Booking");
        printf("\n2-Delete Booking");
        printf("\n3-Display");
        printf("\n4-Search Booking");
        printf("\n5-Save to Excel");
        printf("\n6-Exit");
        printf("\nEnter Choice : ");
        scanf("%d", &ch);
        if(ch == 6)
            break;
        switch(ch)
        {
            case 1:
                insert(&l);
                break;

            case 2:
                deleteB(&l);
                break;

            case 3:
                display(&l);
                break;
                
			      case 4:
                searchBooking(&l);
                break;
                
            case 5:
                saveToFile(&l);
                break;

            default:
                printf("\nInvalid Choice...");
        }
    }
    return 0;
}
