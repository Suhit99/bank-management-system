#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<ctype.h>

//Class
class account
{
	int acno, deposit, withdraw;
	char name[50];
	public:
	void create_account()
	{
		cout<<"\n\n====NEW ACCOUNT ENTRY FORM====\n\n";
		cout<<"\nEnter The account Number : ";
		cin>>acno;
		cout<<"\nEnter The Name of The account Holder : ";
		gets(name);
		cout<<"\nEnter Initial amount for current :";
		cin>>deposit;
		cout<<"\n\n\nYour Account Created Successfully ..";
	}
	void show_account()
	{
		cout<<"\n\n----ACCOUNT STATUS----\n";
		cout<<"\nAccount No. : "<<acno;
		cout<<"\nAccount Holder Name : "<<name;
		cout<<"\nBalance amount : "<<deposit;
	}
	void modify_account()
	{
		cout<<"\nAccount No. : "<<acno;
		cout<<"\nModify Account Holder Name : ";
		gets(name);
		cout<<"Modify Balance amount : ";cin>>deposit;
	}
	void dep(int x)
	{
		deposit+=x;
	}
	void draw(int x)
	{
		deposit-=x;
	}
	void report()
	{
		cout<<acno<<"\t"<<name<<"\t\t"<<deposit<<endl;
	}
	int retacno()
	{
		return acno;
	}
	float retdeposit()
	{
		return deposit;
	}
};		//class ends here


// 	global declaration for stream object, object



 fstream fp;
 account ac;


// 	function to write in file


void write_account()
{
	fp.open("account.dat",ios::out|ios::app);
	ac.create_account();
	fp.write((char*)&ac,sizeof(account));
	fp.close();
}


// 	function to read specific record from file



void display_sp()
{
	int n;
	cout<<"\n\n====BALANCE DETAILS====";
	cout<<"\n\nEnter the Account Number : ";
	cin>>n;
	int flag=0;
	fp.open("account.dat",ios::in);
	while(fp.read((char*)&ac,sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
		cout<<"\n\nAccount Number does not exist";
	getch();
}
 

// 	function to modify record of file


void modify_account()
{
	int no,found=0;
	cout<<"\n\n====MODIFY RECORD====";
	cout<<"\n\nEnter the Account No. : ";
	cin>>no;
	fp.open("account.dat",ios::in|ios::out);
	while(fp.read((char*)&ac,sizeof(account)) && found==0)
	{
		if(ac.retacno()==no)
		{
			ac.show_account();
			cout<<"\n\n\n----Enter the New Details----\n";
			ac.modify_account();
			int pos=-1*sizeof(ac);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&ac,sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}


// 	function to delete record of file


void delete_account()
{
	int no;
	cout<<"\n\n====Delete Record====";
	cout<<"\n\nEnter The Account No. : ";
	cin>>no;
	fp.open("account.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&ac,sizeof(account)))
	{
		if(ac.retacno()!=no)
		{
			fp2.write((char*)&ac,sizeof(account));
		}
	}
	fp2.close();
	fp.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}


// 	function to display all accounts deposit list


void display_all()
{
	fp.open("account.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.\tNAME\t\tBalance\n";
	cout<<"====================================================\n";
	while(fp.read((char*)&ac,sizeof(account)))
	{
		ac.report();
	}
	fp.close();
	getch();
}


// 	function to deposit and withdraw amounts


void deposit_withdraw(int option)
{
	int no,found=0,amt;
	cout<<"\n\n====ACCOUNT TRANSCATION FORM====";
	cout<<"\n\nEnter The account No. : ";
	cin>>no;
	fp.open("account.dat",ios::in|ios::out);
	while(fp.read((char*)&ac,sizeof(account)) && found==0)
	{
		if(ac.retacno()==no)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\nEnter The amount to DEPOSIT : ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\nEnter The amount to WITHDRAW : ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<1000))
					cout<<"\nInsufficience balance";
				else
					ac.draw(amt);
			}
			int pos=-1*sizeof(ac);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&ac,sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}




// 	THE MAIN FUNCTION OF PROGRAM


void main()
{
	char ch;
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		ch=getche();
		clrscr();
		switch(ch)
		{
			case '1': write_account();
				getch();
				break;
			case '2': deposit_withdraw(1);
				break;
			case '3': deposit_withdraw(2);
				break;
			case '4': display_sp();
				break;
			case '5': display_all();
				break;
			case '6': delete_account();
				break;
			case '7': modify_account();
				break;
			case '8': exit(0);
			default : cout<<"\a";
		}
	}while(ch!='8');
}
