   #include <fstream>
#include <iostream>
#include <string>
 #include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
using namespace std;
extern int readDir(char *dirName, vector<string> &filesName);
  char* CharNameCH[]={"¾©","»¦","½ò","Óå","¼½","½ú","ÃÉ","ÁÉ","¼ª","ºÚ","ËÕ","Õã","Íî","Ãö","¸Ó","Â³","Ô¥","¶õ",
		                            "Ïæ","ÔÁ","¹ð","Çí","´¨","¹ó","ÔÆ","²Ø","ÉÂ","¸Ê","Çà","Äþ","ÐÂ","Ñ§","¾¯","¸Û","°Ä","¹Ò",
									"Ê¹","Áì","Ãñº½","0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H",
									"J","K","L","M","N","P","Q","R","S","T","U","V","W","X","Y","Z","-"};


int test16_1(int argc, char *argv[])  
{
	string path="I:/lstm-×Ö·û/data0-data9";
	string pathtrain="I:/lstm-×Ö·û/data0-data9/0_train.txt";
	fstream fintrain;	
	fintrain.open(pathtrain,ios::out);
	 if(!fintrain.is_open())
	 {
		 printf("fintrain,open fail!\n");
		 system("pause");
	 }
	vector<string> file;
	 readDir((char*)path.c_str(), file);
	 for(int i=0;i<file.size();i++)
	 {
		  string pathImg=file[i];
		  Mat img=imread(pathImg.c_str());
		  if(img.data==NULL)
		  {
			  printf("img.data==NULL\n");
				 continue;
		  }
			int pos=pathImg.find_first_of('.');
			int pos2=pathImg.find_last_of('/');
			string name1=pathImg.substr(pos2+1,pos-pos2-1);
			int pos3=name1.find_first_of('_');
			string charName=name1.substr(0,pos3);
			int num=0;	int label[16]={0};
			for(int j=0;j<charName.size();)
			{
				char onechar =charName[j];
				string str;
				if(onechar<0)
				{
				 str=charName.substr(j,2);
					j=j+2;
				}
				else
				{
					 str=charName.substr(j,1);
					j=j+1;
				}

				for(int k=0;k<74;k++)
				{
					string str1=CharNameCH[k];
					if(strcmp(str1.c_str(),str.c_str())==0)
					{
						  label[num]=k;
					}
				}
				if(label[num]==0)
				{
					printf("Ã»ÓÐÕÒµ½Æ¥Åä±êÇ©\n");
					  system("pause");
				}
				  num++;
			}

			fintrain<<pathImg.c_str()<<" ";
			for(int j=0;j<num;j++)
			{
				 fintrain<<label[j]<<" ";
			}

			//fintrain<<"0"<<endl;

			fintrain<<endl;


	 }

	 fintrain.close();
   return 0;
}
int test16_2(int argc, char *argv[])  
{
	string path="I:/lstm-×Ö·û/data0-data9";
	string pathtrain="I:/lstm-×Ö·û/data0-data9/0_train.txt";
	string pathval="I:/lstm-×Ö·û/data0-data9/0_val.txt";
	fstream fintrain;	
	fintrain.open(pathtrain,ios::out);
	 if(!fintrain.is_open())
	 {
		 printf("fintrain,open fail!\n");
		 system("pause");
	 }

	  fstream finval;	
	finval.open(pathval,ios::out);
	 if(!finval.is_open())
	 {
		 printf("finval,open fail!\n");
		 system("pause");
	 }

	vector<string> file;
	 readDir((char*)path.c_str(), file);
	 int numall=file.size(); int i25=0;
	 for(int i=0;i<file.size();i++)
	 {
		  string pathImg=file[i];
			//string pathImg="I:/lstm-×Ö·û/data0-data9/WJ¾©30015_0000.jpg";
		  Mat img=imread(pathImg.c_str());
		  if(img.data==NULL)
		  {
			  printf("img.data==NULL\n");
				 continue;
		  }
			int pos=pathImg.find_first_of('.');
			int pos2=pathImg.find_last_of('/');
			string name1=pathImg.substr(pos2+1,pos-pos2-1);
			int pos3=name1.find_first_of('_');
			string charName=name1.substr(0,pos3);
			int num=0;	int label[16]={0};
			for(int j=0;j<charName.size();)
			{
				char onechar =charName[j];
				string str;
				if(onechar<0)
				{
				 str=charName.substr(j,2);
					j=j+2;
				}
				else
				{
					 str=charName.substr(j,1);
					j=j+1;
				}

				int fnum=0;
				for(int k=0;k<74;k++)
				{
					string str1=CharNameCH[k];
					if(strcmp(str1.c_str(),str.c_str())==0)
					{
						  label[num]=k;
						  fnum=1;
					}
				}
				if(fnum==0)
				{
					 cout<<pathImg.c_str()<<endl;
					 cout<<charName.c_str()<<":"<<j<<endl;
					printf("Ã»ÓÐÕÒµ½Æ¥Åä±êÇ©\n");
					  system("pause");
				}
				  num++;
			}

			 i25=i%25;
			 if(i25<24)
			 {
				 fintrain<<pathImg.c_str()<<" ";
				 for(int j=0;j<num;j++)
				 {
					 fintrain<<label[j]<<" ";
				 }

				 if(num==8)
				 {
					fintrain<<endl;
				 }
				 else if(num==7)
				 {
					 fintrain<<"73"<<endl;
				 }
				  
				 else
				 {
					 cout<<pathImg.c_str()<<endl;
					 printf("plate num is not 7 or 8!\n");
					 system("pause");
				 }
				 
			 }
			 else
			 {
				 finval<<pathImg.c_str()<<" ";
				 for(int j=0;j<num;j++)
				 {
					 finval<<label[j]<<" ";
				 }

				  if(num==8)
				 {
					finval<<endl;
				 }
				 else if(num==7)
				 {
					 finval<<"73"<<endl;
				 }
				 
				 else
				 {
					 cout<<pathImg.c_str()<<endl;
					 printf("plate num is not 7 or 8!\n");
					 system("pause");
				 }
			 }
			


	 }

	 fintrain.close();
   return 0;
}

   int test16(int argc, char *argv[])
   {
	   // only train
		//test16_1(argc,argv);
		  // train,and ,val
		 test16_2(argc,argv);
		 return 0;
   }
