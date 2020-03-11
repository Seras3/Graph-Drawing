#include <iostream>
#include <graphics.h>
#include <cmath>
#include <cstdlib>

using namespace std;

int H,W,d,xc,yc,r,ok,cost;
int a[51][51],viz[51];
int p1=0,p2=0;

struct nod
{
    int x;
    int y;
} v[51];
int n;

void scnod(int x, int y)
{
    char ch[10];
    int i;
    int ok=0;
    for(i=1; i<=n&&ok==0; i++)
    {
        if(sqrt(pow(x-v[i].x,2)+pow(y-v[i].y,2))<=2*r)
            ok=1;
    }
    if(ok==0)
    {
        n++;
        v[n].x=x;
        v[n].y=y;
        itoa(n,ch,10);
        setcolor(15);
        circle(x,y,r);
        outtextxy(x-5,y-5,ch);
    }
}

void Select_nod(int x, int y)
{
    setcolor(5);
    circle(x,y,r);
}
void Deselect_nod(int x, int y)
{
    setcolor(15);
    circle(x,y,r);
}

void DF(int nd)
{
    delay(1000);
    Select_nod(v[nd].x,v[nd].y);
    viz[nd]=1;
    int i;
    for(i=1;i<=n;i++)
        if(a[nd][i]!=0&&viz[i]==0)
        {
            setcolor(3);
            delay(1000);
            line(v[nd].x,v[nd].y,v[i].x,v[i].y);
            DF(i);
        }

}

void BUTOANE()
{
    setcolor(15);
    readimagefile("poze/nod_free.jpg",W-d,0,W-1,d);
    readimagefile("poze/muchie_free.jpg",W-d,d+5,W-1,d+1*(d+5));
    readimagefile("poze/cost_free.jpg",W-d,2*(d+5),W-1,d+2*(d+5));
    readimagefile("poze/afis_free.jpg",W-d,3*(d+5),W-1,d+3*(d+5));
    readimagefile("poze/deep_free.jpg",W-d,4*(d+5),W-1,d+4*(d+5));
    readimagefile("poze/reset.jpg",W-d,5*(d+5),W-1,d+5*(d+5));

    readimagefile("poze/quit.jpg",W-d,H-d,W-1,H-1);
}

void VERIF_CLICK(int xc, int yc)
{
    if(W-d<xc&&xc<W-1&&0<yc&&yc<d)
        {
            BUTOANE();
            readimagefile("poze/nod_click.jpg",W-d,0,W-1,d);
            p1=p2=0;
            ok=1;
        }
    else
    if(W-d<xc&&xc<W-1&&d+5<yc&&yc<2*d+5)
        {
            BUTOANE();
            readimagefile("poze/muchie_click.jpg",W-d,d+5,W-1,d+1*(d+5));
            p1=p2=0;
            ok=2;
        }
    else
    if(W-d<xc&&xc<W-1&&2*(d+5)<yc&&yc<d+2*(d+5))
        {
            BUTOANE();
            readimagefile("poze/cost_click.jpg",W-d,2*(d+5),W-1,d+2*(d+5));
            p1=p2=0;
            ok=3;
        }
    else
    if(W-d<xc&&xc<W-1&&3*(d+5)<yc&&yc<d+3*(d+5))
        {
            BUTOANE();
            readimagefile("poze/afis_click.jpg",W-d,3*(d+5),W-1,d+3*(d+5));
            p1=p2=0;
            ok=4;
        }
    else
    if(W-d<xc&&xc<W-1&&4*(d+5)<yc&&yc<d+4*(d+5))
        {
            BUTOANE();
            readimagefile("poze/deep_click.jpg",W-d,4*(d+5),W-1,d+4*(d+5));
            p1=p2=0;
            ok=5;
        }
    else
    if(W-d<xc&&xc<W-1&&5*(d+5)<yc&&yc<d+5*(d+5))
        {
            p1=p2=0;
            ok=6;
        }
}

void ResetVal()
{
    int i,j;
    for(i=1;i<=n;i++)
        viz[i]=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            a[i][j]=0;
    n=0;
}

void afi()
{
    int i,j;
    cout<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    int i;
    char ch[10];
    r=20;
    H=700;
    d=80;
    W=800+d;
    initwindow(W,H,"Graf");

    BUTOANE();

    while(xc<W-d||yc<H-d)
    {
        getmouseclick(WM_LBUTTONDOWN,xc,yc);

        VERIF_CLICK(xc,yc);

        //cout<<xc<<" "<<yc<<" -- "<<ok<<endl;

        delay(10);/// For visual effects

        if(ok==1&&r<xc&&xc<W-d-r&&r<yc&&yc<H-r)
        {
            scnod(xc,yc);
        }
        else if(ok==2)
        {
            if(p1==0)
            {
                if(xc>0&&xc<W-d&&yc>0&&yc<H)
                {
                    for(i=1; i<=n; i++)
                        if(sqrt(pow(xc-v[i].x,2)+pow(yc-v[i].y,2))<=r)
                        {
                            p1=i;
                            Select_nod(v[i].x,v[i].y);
                        }

                }
            }
            else
            if(p2==0)
            {
                if(xc>0&&xc<W-d&&yc>0&&yc<H)
                {
                    for(i=1; i<=n; i++)
                        if(sqrt(pow(xc-v[i].x,2)+pow(yc-v[i].y,2))<=r)
                        {
                            p2=i;
                            Select_nod(v[i].x,v[i].y);
                        }
                }
            }
           // cout<<p1<<" "<<p2<<endl;
            if(p1!=0&&p2!=0)
            {
                setcolor(10);
                line(v[p1].x,v[p1].y,v[p2].x,v[p2].y);
                a[p1][p2]=a[p2][p1]=1;
                Deselect_nod(v[p1].x,v[p1].y);
                Deselect_nod(v[p2].x,v[p2].y);
                p1=0;
                p2=0;
            }
        }
        else if(ok==3)
        {
            if(p1==0)
            {
                if(xc>0&&xc<W-d&&yc>0&&yc<H)
                {
                    for(i=1; i<=n; i++)
                        if(sqrt(pow(xc-v[i].x,2)+pow(yc-v[i].y,2))<=r)
                        {
                            p1=i;
                            Select_nod(v[i].x,v[i].y);
                        }

                }
            }
            else
            if(p2==0)
            {
                if(xc>0&&xc<W-d&&yc>0&&yc<H)
                {
                    for(i=1; i<=n; i++)
                        if(sqrt(pow(xc-v[i].x,2)+pow(yc-v[i].y,2))<=r)
                        {
                            p2=i;
                            Select_nod(v[i].x,v[i].y);
                        }
                }
            }

            if(p1!=0&&p2!=0)
            {
                if(a[p1][p2]==1)
                {
                cin>>cost;
                a[p1][p2]=a[p2][p1]=cost;
                itoa(cost,ch,10);
                setcolor(3);
                outtextxy((v[p1].x+v[p2].x)/2,(v[p1].y+v[p2].y)/2,ch);
                }
                else
                    cout<<"alegeti alte noduri "<<endl;
                Deselect_nod(v[p1].x,v[p1].y);
                Deselect_nod(v[p2].x,v[p2].y);
                p1=0;
                p2=0;
            }

        }
        else
            if(ok==4)
        {
            ok=0;
            afi();
        }
        else
            if(ok==5)
        {
            if(p1==0)
            {
                if(xc>0&&xc<W-d&&yc>0&&yc<H)
                {
                    for(i=1; i<=n; i++)
                        if(sqrt(pow(xc-v[i].x,2)+pow(yc-v[i].y,2))<=r)
                        {
                            p1=i;
                            Select_nod(v[i].x,v[i].y);
                        }
                }
            }
            if(p1!=0)
            {
                DF(p1);
                ok=0;
            }
        }
        else
            if(ok==6)
        {
            cleardevice();
            BUTOANE();
            ResetVal();
            ok=0;
        }
    }
    return 0;
}
