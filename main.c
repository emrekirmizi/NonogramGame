#include <stdio.h>
#include <stdlib.h>
#define ROW 25
#define COLUMN 25

int getNumber(int,int);
void printScreen(char[ROW][COLUMN],char[ROW][COLUMN],int,int);
void dash(char[ROW][COLUMN],char[ROW][COLUMN],int,int);
int compare(char[ROW][COLUMN]);

int main()
{
    system("color 3f");
    system("mode 80, 46");
    printf("\n--------------------------------------------------------------------------------");
    printf("\n-----------------------------Welcome Nonogram Game------------------------------");
    printf("\n--------------------------------------------------------------------------------");
        FILE *textPtr;
    int i=0,j=0,k=0,m=0,rowCounter=0,columnCounter=0,rowCount=0,columnCount=0,count=0;
    char screenMatrix[ROW][COLUMN]={{0}};//ekranda görünecek olan matris
    int gameMatrix[ROW][COLUMN]={{0}};//dosyadan okunacak olan matris
    char rowChar,columnChar,selection;

    textPtr=fopen("image.txt","r");//dosyadan veri alaninin okunmasi
        if(textPtr==0)//gerekli dosya klasor icinde degilse hata mesajinin verilmesi
        {
            printf("\nLutfen image.txt isimli dosyayi programin bulundugu klasore atiniz...\n\n");
            return 0;
        }

    fscanf(textPtr,"%d%d",&rowCount,&columnCount);//dosyadan satir ve sutun sayisinin okunmasi

    for(i=0; i<rowCount; i++)
    {
    fscanf(textPtr,"\n");
        for(j=0; j<columnCount; j++)
            fscanf(textPtr,"%d ",&gameMatrix[i][j]);//dosyadan okunan verilerle oyun matrisinin olusturulmasi
    }

        for(i=1;i<=rowCount;i++)//ekranda gorunecek olan oyun matrisinin her elemanina'O' ataniyor..
            for(j=1;j<=columnCount;j++)
                screenMatrix[i][j]='O';

        for(i=0;i<ROW;i++)
        {
            if(i==0)
            {
                for(m=0;m<columnCount;m++)//sutun sayisi yazdiriliyor..
                {
                    screenMatrix[0][m+1]=m+1;
                }
                for(k=0;k<rowCount;k++)//satir sayisi yazdiriliyor..
                {
                    screenMatrix[k+1][0]=k+1;
                }
            }
            screenMatrix[0][0]=' ';//ekran matrisinin ilk adresine ekranda duzgun gorunmesi icin bosluk ataniyor..
        }


        rowCounter=1;
        for (i=0; i<rowCount; i++)//satirda karalama yapmak icin sag tarafta bulunan yere ipucu ataniyor..
        {
            for(j=0; j<columnCount; j++)
            {
                if(gameMatrix[i][j]==1)//oyun matrisinde bir olarak belirtilen yerler icin ekran matrisinin sag tarafinda bulunan yere ipucu ataniyor..
                {
                    screenMatrix[i+1][rowCounter+columnCount]++;
                        if(gameMatrix[i][j+1]!=1)
                        rowCounter++;//oyun matrisinin satirinda 1den sonra 0 varsa ekran matrisinin sag tarafinda bulunan yerde bir sonraki elemana ipucu ataniyor
                }
            }
            rowCounter=1;
        }

        columnCounter=1;
        for (k=0;k<rowCount;k++)//sutunda karalama yapmak icin asagida bulunan yere ipucu ataniyor..
        {
            for(m=0;m<columnCount;m++)
            {
                if(gameMatrix[m][k]==1)//oyun matrisinde bir olarak belirtilen yer icin ekran matrisinin asagi tarafinda bulunan yere ipucu ataniyor..
                {
                    screenMatrix[columnCounter+rowCount][k+1]++;
                        if(gameMatrix[m+1][k]!=1)
                        columnCounter++;//oyun matrisinin sutununda 1den sonra 0 varsa ekran matrisinin asagi tarafinda bulunan yerde bir sonraki elemana ipucu ataniyor
                }
            }
            columnCounter=1;
        }

    int condition=0;
    printScreen(gameMatrix,screenMatrix,rowCount,columnCount);//oyunun ekrana yazdirilmasi icin printScreen fonksiyonu cagiliyor..

    do
    {
        dash(gameMatrix,screenMatrix,rowCount,columnCount);//ekran matrisinde atama yapmak icin dash fonksiyonu cagiriliyor..
        condition=compare(screenMatrix);//compare fonksiyonuna kullanicidan alinarak olusturulan ekran matrisi gonderilerek oyun matrisiyle karsilastiriliyor
        system("cls");
        printf("\n--------------------------------------------------------------------------------");
        printf("\n-----------------------------Welcome Nonogram Game------------------------------");
        printf("\n--------------------------------------------------------------------------------");
        printScreen(gameMatrix,screenMatrix,rowCount,columnCount);//oyunun ekrana yazdirilmasi icin printScreen fonksiyonu cagiliyor..

    }while(condition!=1);//compare fonksiyonundan condition degiskenine atanan deger 1 olmadigi surece dongu donmeye devam ediyor..
    printf("\n--------------------------------------------------------------------------------");
    printf("\n-----------------------------------Game Over------------------------------------");
    printf("\n--------------------------------------------------------------------------------");

return 0;
}

int getNumber(int min,int max)//kullanicidan sayi almak icin kullanilan fonksiyon..
{
    int number;

    scanf("%d",&number);

        while (number<min||number>max)
        {
            printf("Lutfen [%d-%d] araliginda bir deger giriniz:",min,max);//kullanici belirtilen arada sayi girene kadar ekranda kulllaniciya hatasini belirtme..
            scanf("%d",&number);
        }
return number;
}

void printScreen(char gameMatrix[ROW][COLUMN],char screenMatrix[ROW][COLUMN],int rowCount,int columnCount)//ekrana matrisi yazdirma fonksiyonu..
{
    int i,j,count;
    printf("\n\n");
    for(i=0;i<=rowCount-1;i++)
    {
        printf("%3c",screenMatrix[0][0]);
            if(i==0)
            {
                for(j=1;j<=columnCount;j++)
                {
                    printf("%d ",screenMatrix[i][j]);//sutun sayisi ekrana yazdiriliyor
                }
            printf("\n   ");
                for(j=1;j<columnCount*2;j++)//sutun sayisinin alti ciziliyor
                printf("-");
            }
        printf("\n");//bir alt satira gec
        printf("%2d|",screenMatrix[i+1][0]);//satir sayisi ekrana yazdiliyor..

            printf("%c",screenMatrix[i+1][1]);//ilk satir elemani yazdiriliyor
            for(j=1;j<columnCount;j++)
            {
                printf(" ");//satir elemanlari arasinda birer bosluk birakiliyor
                printf("%c",screenMatrix[i+1][j+1]);//geri kalan satir elamanlari yazdiriliyor
            }
        printf(":");

        if(screenMatrix[i+1][j+1]!=0)
        printf("%2d ",screenMatrix[i+1][j+1]);//sag taraftaki ilk ipucu yazdiriliyor
            else
            printf(" ");//ipucu yoksa yani oyun matrisinin satirindaki tum elemanlar sifirsa ipucu yerine bosluk karakteri yazdiriliyor
            count=1;
                while(screenMatrix[i+1][j+1+count]!=0)//ekran matrisindeki ilk ipucundan sonraki karakter de bir ipucu oldugu surece
                {
                    printf("%d ",screenMatrix[i+1][j+1+count]);//sonraki ipuclari yazdiriliyor
                    count++;//bir sonraki ipucuna gecmek icin sayaci 1 artir
                }
        printf("\n   ");//alttaki ipuclarini yazdirmak icin alt satira geciliyor
    }

        for(j=1;j<columnCount*2;j++)
        printf("-");//ipuclarini oyundan ayri tutmak icin oyun ekraninin altini ciz
        printf("\n  ");//alttaki ipuclarini yazdirmak icin alt satira geciliyor

        for(j=0;j<columnCount;j++)
        {
            printf("%2d",screenMatrix[rowCount+1][j+1]);//sutunlar icin asagidaki ilk ipuclari yazdiriliyor
        }

        printf("\n\n  ");//bir alt satira geciliyor
        for(j=0;j<columnCount;j++)
        {
            count=1;
            if(screenMatrix[rowCount+1+count][j+1]==0)
            printf("  ");//ilk sutun icin ekran matrisinde ikinci bir ipucu yoksa ipucu yerine bosluk karakteri yazdiriliyor
                while(screenMatrix[rowCount+1+count][j+1]!=0)//sutunlar icin ekran matrisinde ikinci bir ipucu oldugu surece
                {
                    if(screenMatrix[rowCount+1+count][j+1]!=0)//sutunlar icin ekran matrisinde ikinci bir ipucu varsa
                    printf("%2d",screenMatrix[rowCount+1+count][j+1]);//ipucunu yazdir
                        else//yoksa
                        printf(" ");//ipucu yerine bosluk karakteri yazdir
                    count++;
                }
        }
}

void dash(char gameMatrix[ROW][COLUMN],char screenMatrix[ROW][COLUMN],int rowCount,int columnCount)//kullanicidan alinacak satir ve sutun numaralarina gore karalanacak adresin belirlenmesi
{
    int selectedRow,selectedColumn,selection;
        printf("\n--------------------------------------------------------------------------------\n");
        printf("Lutfen karalamak istediginiz satir numarasini\n[1-%d] araliginda giriniz: ",rowCount);//kullanicidan satir numarasi aliniyor..
        selectedRow=getNumber(1,rowCount);
        printf("--------------------------------------------------------------------------------\n");
        printf("Lutfen karalamak istediginiz sutun numarasini\n[1-%d] araliginda giriniz: ",columnCount);//kullanicidan sutun numarasi aliniyor..
        selectedColumn=getNumber(1,columnCount);
        printf("--------------------------------------------------------------------------------\n");
        printf("Lutfen seciminizi\n[0-2] araliginda giriniz...\n[1:dolu, 0:bos, 2:belirsiz]: ");//kullanicidan oyunda yapmak istedigi hamle isteniyor..
        selection=getNumber(0,2);

        switch(selection)
        {
        case 0:
            screenMatrix[selectedRow][selectedColumn]='X';//selection sifir ise adrese 'X' harfi ataniyor..
            break;

        case 1:
            screenMatrix[selectedRow][selectedColumn]=219;//selection bir ise adrese karakter kodu 219 olan isaretci ataniyor..
            break;

        case 2:
            screenMatrix[selectedRow][selectedColumn]='O';//selection iki ise adrese 'O' harfi ataniyor..
            break;
        }
}

int compare(char screenMatrix[ROW][COLUMN])//compare fonksiyonu..
{
    int i,j,wrong=0,rowCount,columnCount;
    int compareMatrix[ROW][COLUMN]={{0}};
    int gameMatrix[ROW][COLUMN]={{0}};

    FILE *textPtr;//dosya aciliyor..
    textPtr=fopen("resim.txt.txt","r");
    fscanf(textPtr,"%d%d",&rowCount,&columnCount);//dosyadan satir ve sutun sayisi okunuyor..

    for(i=0; i<rowCount; i++)
        for(j=0; j<columnCount; j++)
            fscanf(textPtr,"%d ",&gameMatrix[i][j]);//dosyadaki veriler oyun matrisine ataniyor..

    for(i=0;i<rowCount;i++)
        for(j=0;j<columnCount;j++)
            compareMatrix[i][j]=1;//karsilastirmak icin bir matris tanimlanip,her elemani bir olarak ataniyor..

    for(i=0;i<rowCount;i++)
    {
        for(j=0;j<columnCount;j++)
        {
            switch(screenMatrix[i+1][j+1])
            {
                case'O':case'X':
                compareMatrix[i][j]=0;//ekran matrisinde 'O' ve 'X' olarak tanimlanan yerler karsilastirma matrisine sifir olarak ataniyor..
                //karsilastirma matrisinde geri kalan elemanlar,ekran matrisinde kare olsa da olmasa da zaten bir olarak atanmisti..
            }
        }
    }

    for(i=0;i<rowCount;i++)//karsilastirma matrisi ile oyun matrisi karsilastiriliyor..
    {
        for(j=0;j<columnCount;j++)
        {
            if(compareMatrix[i][j]!=gameMatrix[i][j])
            wrong++;//eger herhangi bir yanlis varsa wrong sayaci artiriliyor ve
        }
    }

if (wrong!=0)//eger yanlis varsa fonksiyon 0 donduruyor yoksa 1 donduruyor..
return 0;
    else
    return 1;
}
