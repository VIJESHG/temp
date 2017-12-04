#include<stdio.h> 
#include<string.h> 

int i,j,l,m,n=0,o,p,nv,z=0,x=0; 
char str[10],temp,temp2[10],temp3[20],*ptr; 

struct prod 
{ 
    char lhs[10],rhs[10][10],ft[10]; 
    int n; 
}pro[10]; 

void findter(){ 
    int k,t; 
    for(k=0;k<n;k++) { 
        if(temp==pro[k].lhs[0]) { 
            for(t=0;t<pro[k].n;t++) { 
                if( pro[k].rhs[t][0]<65 || pro[k].rhs[t][0]>90 ) 
                    pro[i].ft[strlen(pro[i].ft)]=pro[k].rhs[t][0]; 
                else if( pro[k].rhs[t][0]>=65 && pro[k].rhs[t][0]<=90 ) { 
                    temp=pro[k].rhs[t][0]; 
                    if(temp=='S') 
                        pro[i].ft[strlen(pro[i].ft)]='#'; 
                    findter(); 
                } 
            } 
            break; 
        } 
    } 
} 


int main() { 
    FILE *f; 
    for(i = 0;i < 10; i++) 
        pro[i].n = 0; 

    f=fopen("tab5.txt","r"); 
    while(!feof(f)) { 
        fscanf(f,"%s",pro[n].lhs); 
        if(n>0) { 
            if( strcmp(pro[n].lhs,pro[n-1].lhs) == 0 ) { 
                pro[n].lhs[0]='\0'; 
                fscanf(f,"%s",pro[n-1].rhs[pro[n-1].n]); 
                pro[n-1].n++; 
                continue; 
            } 
        } 
        fscanf(f,"%s",pro[n].rhs[pro[n].n]); 
        pro[n].n++; 
        n++; 
    } 

    printf("\n\nTHE GRAMMAR IS AS FOLLOWS\n\n"); 
    for(i=0;i<n;i++) 
        for(j=0;j<pro[i].n;j++) 
            printf("%s -> %s\n",pro[i].lhs,pro[i].rhs[j]); 

    pro[0].ft[0]='#'; 
    for(i=0;i<n;i++) { 
        for(j=0;j<pro[i].n;j++) { 
            if( pro[i].rhs[j][0]<65 || pro[i].rhs[j][0]>90 ) { 
                pro[i].ft[strlen(pro[i].ft)]=pro[i].rhs[j][0]; 
            } 
            else if( pro[i].rhs[j][0]>=65 && pro[i].rhs[j][0]<=90 ) { 
                temp=pro[i].rhs[j][0]; 
                if(temp=='S') 
                    pro[i].ft[strlen(pro[i].ft)]='#'; 
                findter(); 
            } 
        } 
    } 
    printf("\n\nFIRST\n"); 
    for(i = 0;i < n; i++) { 
        printf("\n%s -> ",pro[i].lhs); 
        for(j = 0;j < strlen(pro[i].ft); j++) { 
            for(l=j-1;l>=0;l--) 
                if(pro[i].ft[l]==pro[i].ft[j]) 
                    break; 
            if(l==-1) 
                printf("%c",pro[i].ft[j]); 
        } 
    }  
}
