/* Project by Yashodhar Meduri,Tarun Raheja and Ahraz Rizvi*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
/* function for printing the specific boundary*/
void printspec(set< vector<int> >specB,map<int,int>data[17],int ans)
{
  vector<int> check;
  cout<<"\nSpecific border for "<<ans<<":"<<endl;
  if (specB.empty()) cout << "Not consistent with the data";
  else
  {
    check = *(specB.begin());
    cout<<"< ";
    for(int i=0; i<16; i++)
    {
        if( check[i]==1000)cout<<"?"<<" ";
        else
        {
            for(map<int,int>::iterator itr = data[i].begin(); itr!=data[i].end();itr++)
            {
                if(itr->second == check[i])
                cout<< itr->second <<" ";
            }
        }
    }
  }
  cout<<">\n";
}
/* function for printing the genric boundary*/
void printgen(set< vector<int> >genB,map<int,int>data[17],int ans)
{
  vector<int> check;
  cout<<"\nGeneral border for "<<ans<<":"<<endl;
  if (genB.empty()) cout << "< Not consistent with the data >";
  for(set< vector<int> >::iterator it= genB.begin(); it!=genB.end(); it++)
  {
    check = *it;
    cout<<"< ";
    for(int i=0; i< 16; i++)
    {
        if( check[i]==1000 )cout<<"?"<<" ";
        else
        {
            for(map<int,int>::iterator itr = data[i].begin(); itr!=data[i].end();itr++)
            {
             if(itr->second == check[i])
             cout<<itr->second<<" ";
            }
        }
    }
    cout<<">\n";
  }
}

int main()
{

  vector <int> attribute(16);
  map <int, int> data[17];


/*Animal name has been ignored.The numbering of the features start from 0 to 15.
  16th attribute is our target attribute*/
/*Values each Attribute can take*/
  for(int i=0; i<16; i++)
  {if(i!=12){
    data[i][0]=0;
    data[i][1]=1;
    }
    else{
  data[12][0] = 0;
  data[12][2] = 2;
  data[12][4] = 4;
  data[12][5] = 5;
  data[12][6] = 6;
  data[12][8] = 8;

    }
  }
  data[16][1] = 1;
  data[16][2] = 2;
  data[16][3] = 3;
  data[16][4] = 4;
  data[16][5] = 5;
  data[16][6] = 6;
  data[16][7] = 7;

while(1){
  int ans;
  cout<<"Enter the class for which you want the boundaries[1-7] or press 0 to exit: ";
  cin>> ans;
  if(ans==0) return(0);


  set< vector<int> > genB,specB;
  vector<int>inputdata(17),tempdata(16);

/*Initialize the boundaries*/
  for(int i=0; i<16; i++)
  {
    tempdata[i]=-1;
  }
  specB.insert(tempdata);

  for(int i=0; i<16; i++)
  {
    tempdata[i]=1000;
  }
  genB.insert(tempdata);

/* Reading input*/
  string line;
  ifstream myfile ("zooey.txt");
  if (myfile.is_open())
  {

    while ( getline (myfile,line) )
    {
        if(line.size()==0)continue;

        char temp;
        int ct = 0;
        int len = line.size();
        for( int i=0; i<len; i++ )
        {
            if(line[i]==' '|| i==len) continue;
            else temp = line[i];
            inputdata[ct] = temp-'0';
            ct++;
        }
        /* If a positive Example is read*/
        if(inputdata[16]== ans)
        {
            /*Checking if general boundaries are consistent with the example*/
            set< vector<int> >tempG;
            vector<int>check;
            tempG=genB;
            for(set< vector<int> >::iterator itr=tempG.begin();itr!=tempG.end();itr++)\
            {
                check=*(itr);
                for(int i=0;i<16;i++)
                {
                    if(check[i]==inputdata[i] || check[i]==1000) continue;
                    else
                    {
                        tempG.erase(check);
                        break;
                    }
                }
            }
            genB=tempG;
            /* Generalizing the Specific boundary to fit the data*/
            check=*(specB.begin());
            specB.erase(check);
            for(int i=0; i<16; i++)
            {
                if(check[i]== -1)
                {
                    check[i] = inputdata[i];
                }
                else if(check[i]!=inputdata[i])
                {
                    check[i]=1000;
                }
            }
            specB.insert(check);
        }
        /*Negative Example Encountered*/
        else
        {
            vector<int>spec=*(specB.begin());
            set< vector<int> >tempG;
            vector<int> check,tempH;
            int flag;
            for(set< vector<int> >::iterator itr=genB.begin();itr!=genB.end();itr++)
            {
                check=*itr;
                flag=0;
                /*checking if the general boundary holds good for the input*/
                for(int i=0;i<16;i++)
                {
                    if( check[i]!=1000 && check[i]!=inputdata[i])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)tempG.insert(check);/* holds.*/
                else
                {
                    /*specializing the general boundary*/
                    for(int i=0;i<16;i++)
                    {
                        if(check[i]==1000)
                        {
                            tempH=check;
                            for(map<int,int>::iterator it=data[i].begin(); it!=data[i].end();it++)
                            {
                                if(inputdata[i]==it->second) continue;
                                else
                                {
                                    tempH[i] = it->second;
                                    bool flag1=true;
                                    for(int k=0;k<16;k++)
                                    {
                                        if(tempH[k]!=spec[k] && spec[k]!=-1 && tempH[k]!=1000)
                                        {
                                            flag1=false;
                                            break;
                                        }
                                    }
                                    if(flag1) tempG.insert(tempH);
                                }
                            }
                        }
                    }
                }
            }
            /* Keeping only the most generic hypothesis in genB*/
            genB.clear();
            vector<int>check1,check2;
            set< vector<int> > tempG1;
            for(set< vector<int> >::iterator it1= tempG.begin(); it1!=tempG.end(); it1++)
            {
                check1 =*it1;
                for( set< vector<int> >::iterator it2= tempG.begin(); it2!=tempG.end(); it2++)
                {
                    check2 = *it2;
                    if(it1==it2)continue;
                    bool flag1 = true;
                    for(int k=0; k<16; k++)
                    {
                        if(check1[k]!=1000 && check1[k]!=check2[k])
                        {
                            flag1 = false;
			    break;

                        }
                    }
                    if(flag1)tempG1.insert(check2);
                }
            }
                /* Adding all those hypothesis which are in tempG and not in tempG1*/
           for( set< vector<int> >::iterator itr= tempG.begin(); itr!=tempG.end(); itr++)
            {
                check =*itr;
                if(tempG1.find(check)==tempG1.end()) genB.insert(check);
            }
        }
    }

   myfile.close();
  }
  else cout << "Unable to open file";

   /* Printing the boundaries */
    if(specB.empty()|| genB.empty()) cout <<"\nCannot learn the concept :( \n\n         ********************\n\n";
    else
    {
        printspec(specB,data,ans);
        printgen(genB,data,ans);
        cout<<"\n\n\n        **********************\n\n\n";
    }

}
return 0;
}
