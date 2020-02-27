/*       Cấu Trúc Dữ Liệu Và Giải Thuật Phòng Máy B40a		
	       Bài Tập : Cây Nhị Phân Tìm Kiếm
	|-------------------------------------------------------------|
	|	Họ Tên Sinh Viên : Nguyễn Thị Nhung		      |
	|	Mã Số Sinh Viên  : 1261098			      |
	|	Lớp		 : 12CK1	      |								      													  
	|-------------------------------------------------------------|		
*/

/* Đề Bài :
	viết chương trình cho phép lưu trữ và thống kê số lượng kí tự trong văn bản ko dấu,xây dựng cây lưu trữ văn bản đó sao cho mỗi kí tự là 1 Node đồng thời quản lý được số lần xuất hiện các kí tự đó .

	Yêu Cầu Bài Cần Xây Dựng Các Tính Năng:
	+ Thêm
	+ Xóa
	+ Tìm Kiếm
1 kí tự bất kì và ghi nó xuống File
__________________________________________________________________
File input:

Tạo đc hình cái cây (max 10đ) ko thì in ra theo kiểu danh sách (max 9đ)
------------------------------------------------------------------
1. in cây:
2. cây sau khi thêm:
3. cây sau khi xóa:
4. kết quả tìm kiếm
P/s: nếu nhập: "hoeoe iaia" thì cây lưu các giá trị: h o e i a
khi xóa "i" thì vẫn còn lại 1 "i" xóa 2 lần mới hết "i"
*/

/* ============================================= BÀI LÀM =========================================================== */

/* Yêu Cầu Để Chạy Được Chương Trình : Bạn phải Copy 2 file : gioithieuchuongtrinh.txt va file InPut.txt (có sẵn trong file đính kèm) vào trong ổ đĩa C */
/* 

Tác giả: Nguyễn Việt Nam Sơn
Trung tâm đào tạo tin học - Thiết kế phần mềm - Sơn Đẹp Trai: www.SonDepTrai.com

Nguồn source code này Tôi viết vào năm 2012 lúc mới bắt đầu học lập trình C/C++ nên một số cách sẽ không được tối ưu - Bạn chỉ nên dùng trên tinh thần tham khảo thôi nhé.
Mong giúp đỡ được Bạn trên con đường Học Lập Trình.
TẤT CẢ VÌ SỰ THÀNH CÔNG CỦA BẠN

*/
/* ==================================== Các Thư Viện Sử Dụng Trong Chương Trình ==================================== */
#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "Windows.h"
#define n 4000
/* ================================================================================================================= */

/* ============================= Khai Báo Cấu Trúc Cây Nhị Phân Tìm Kiếm =========================================== */
typedef struct tagNODE
{
	char key; // Kiểu dữ liệu ký tự (char) ứng với thông tin lưu tại nút .
	struct tagNODE *pLeft,*pRight; // Lưu trữ thông tin địa chỉ nút gốc của cây con trái,cây con phải trong bộ nhớ .
	int Dem; // Số lần xuất hiện của ký tự .
}NODE;
typedef NODE *Tree;
/* ================================================================================================================= */

/* ===================================== Khởi Tạo Cây ============================================================== */
void INit(NODE* &Tree)
{
	Tree=NULL;
}
/* ================================================================================================================= */

/* ================================= (Lặp) Thêm Nút Vào Cây Nhị Phân Tìm Kiếm ====================================== */ 
bool InsertNode(Tree &pRoot,char x)
{
	if(pRoot!=NULL)
	{	
		if(pRoot->key>x)
			InsertNode(pRoot->pLeft,x); // Tư tưởng đệ quy :Lợi dụng đặc trưng của cây nhị phân tìm kiếm nếu Node cần thêm vào nhỏ hơn nút gốc thì duyệt qua nhánh trái .
		else if(pRoot->key<x)
			InsertNode(pRoot->pRight,x); // Tư tưởng đệ quy :Lợi dụng đặc trưng của cây nhị phân tìm kiếm nếu Node cần thêm vào lớn hơn nút gốc thì duyệt qua nhánh phải .
		else if(pRoot->key==x) // Nếu bằng nhau (đã có)
		{
			pRoot->Dem++; // Đếm số lần xuất hiện tăng lên .
			return true; // Trả về true .
		}
	}
	else
	{
		pRoot=new NODE;
		if(pRoot==NULL)
			return false;
		pRoot->key=x;
		pRoot->Dem=1;
		pRoot->pLeft=pRoot->pRight=NULL;
		return true; // Thêm vào thành công .
	}
}
/* ================================================================================================================= */

/* ======================================== Nhập Dữ Liệu Vào Cho Cây =============================================== */
void CreatTree(Tree &pRoot,FILE *pFile)
{
	rewind(pFile); // Dời vị trí đọc ghi về đầu (byte 0) của tập tin pFile .
	char c;
	INit(pRoot); // Khởi tạo lại cây nhị phân tìm kiếm .
	while(!feof(pFile))
	{
		c=fgetc(pFile); // Đọc một ký tự từ tập tin pFile đã mở bởi hàm fopen . Giá trị trả về nếu thất bại trả về EOF khi kết thúc tập tin pFile hoặc gặp lỗi .
		if(c=='\n'||c==EOF)
			break; // Thoát ra khỏi vòng lặp .
		if(c==' ') // Nếu bằng ký tự rỗng thì chương trình tiếp tục duyệt xuống tiếp để thực hiện việc thêm ký tự .
			continue;
		InsertNode(pRoot,c); // Cuối cùng sau khi thỏa hết thì sẽ thực hiện việc thêm ký tự vào cây .
	}
}
/* ================================================================================================================= */

/* =================================== In Các Nút Của Cây Nhị Phân Tìm Kiếm ======================================== */
// Duyệt theo thứ tự giữa (Left - Node - Right):Kiểu duyệt này trước tiên thăm các nút của cây con trái sau đó thăm nút gốc rồi đến cây con phải .
void LNR(Tree pRoot,FILE* FileOutPut) 
{	
	if(pRoot!=NULL)
	{
		LNR(pRoot->pLeft,FileOutPut); // Duyệt trái .
		fprintf(FileOutPut,"<%c>(%d) ",pRoot->key,pRoot->Dem); // Ghi dữ liệu các ký tự phân biệt và tần suất xuất hiện của chúng vào file OutPut.txt .
		LNR(pRoot->pRight,FileOutPut); // Duyệt phải .
	}
}
/* ================================================================================================================= */

/* ================================== Tìm Kiếm Node Thay Thế Cho Node Bị Xóa ======================================= */
void SearchStandFor(Tree &p,Tree & q)
{
	// Tìm phần tử thế mạng cho nút p .
	if(q->pLeft)
		SearchStandFor(p,q->pLeft); // Tư tưởng đệ quy .
	else
	{
		p->key=q->key;
		p=q;
		q=q->pRight;
	}
}
/* ================================================================================================================= */

/* ====================================== Xóa Đi Một Node Trong Cây ================================================ */
bool DeleteNode(Tree &T,char x)
{
	if(T==NULL) // Cây rỗng thì trả về giá trị false .
		return false; 
	if(T->key>x)
		DeleteNode(T->pLeft,x); // Tư tưởng đệ quy - dựa vào tính chất của cây nhị phân tìm kiếm nếu Node x cần xóa nhỏ hơn nút gốc của cây thì duyệt qua nhánh trái của cây .
	if(T->key<x)
		DeleteNode(T->pRight,x); // Tư tưởng đệ quy - dựa vào tính chất của cây nhị phân tìm kiếm nếu Node x cần xóa lớn hơn nút gốc của cây thì duyệt qua nhánh phải của cây .
	else // T->key==x
	{
		if(T->Dem==1)
		{
			NODE *p=T;
			// Các trường hợp T có 1 con .
			if(T->pLeft==NULL)
				T=T->pRight; // Nhánh trái rỗng thì tiếp tục duyệt qua nhánh phải .
			else if(T->pRight==NULL)
					T=T->pLeft; // Nhánh phải rỗng thì tiếp tục duyệt qua nhánh trái .
				else // T có cả 2 con
				{
					NODE*q=T->pRight;
					SearchStandFor(p,q); // Tìm phần tử thế mạng .
				}
			delete p; // Xóa đi p .
			return true; // Trả về true .
		}
		else
		{
			T->Dem--;
			return true; // Trả về true .
		}
	}
}
/* ================================================================================================================= */

/* ========================================== Xóa Đi Ký Tự Trong File ============================================== */
bool DeleteCharactersInFile(Tree &pRoot,FILE *FileInPut,FILE *FileOutPut)
{
	rewind(FileInPut); // Dời vị trí đọc ghi về đầu (byte 0) của tập tin InPut.txt .
	char s[n]; // Khai báo chuỗi s tối đa 4000 ký tự .
	for(int i=0;i<2;i++)
	{
		fgets(s,n,FileInPut); // Ý Nghĩa : Đọc một dãy ký tự từ tập tin InPut.txt vào vùng nhớ s,kết thúc khi đủ n-1 ký tự hoặc gặp ký tự xuống dòng,lưu ký tự xuống dòng vào chuỗi s nếu dòng ít hơn n-1 ký tự,tự động thêm ký tự kết thúc chuỗi .
						// Gía trị trả về : Thành công -> trả về địa chỉ vùng nhớ s . Thất bại -> trả về NULL khi gặp lỗi hoặc gặp ký tự EOF .
	}
	char c;
	while(!feof(FileInPut))
	{
		c=fgetc(FileInPut); // Đọc một ký tự từ tập tin InPut.txt được mở bởi hàm fopen trong hàm main . Giá trị trả về nếu thất bại trả về EOF khi kết thúc tập tin InPut.txt hoặc gặp lỗi .
		if(c=='\n'||c==EOF)
			break; // Thoát ra khỏi vòng lặp .
		if(c==' ') // Nếu bằng ký tự rỗng thì chương trình tiếp tục duyệt xuống tiếp để thực hiện việc xóa ký tự .
			continue;
		// Thực hiện việc xóa ký tự .
		if(DeleteNode(pRoot,c)==true)
		{
			fprintf(FileOutPut," %c Da Xoa Duoc\t",c); // Kết quả trả về trong File OutPut.txt
		}
		else
		{
			fprintf(FileOutPut,"<%c> Khong Xoa Duoc\t",c); // Kết quả trả về trong File OutPut.txt
		}
	}
	return true; // Trả về true .
}
/* ================================================================================================================= */

/* ============================================== Thêm Ký Tự ======================================================= */
void AddCharacters(NODE* &Tree,FILE *FileInPut)
{
	rewind(FileInPut); // Dời vị trí đọc ghi về đầu (byte 0) của tập tin InPut.txt .
	char s[n]; // Khai báo chuỗi s tối đa 4000 ký tự .
	fgets(s,n,FileInPut); // Ý Nghĩa : Đọc một dãy ký tự từ tập tin InPut.txt vào vùng nhớ s,kết thúc khi đủ n-1 ký tự hoặc gặp ký tự xuống dòng,lưu ký tự xuốn dòng vào chuỗi s nếu dòng ít hơn n-1 ký tự,tự động thêm ký tự kết thúc chuỗi .
					// Gía trị trả về : Thành công -> trả về địa chỉ vùng nhớ s . Thất bại -> trả về NULL khi gặp lỗi hoặc gặp ký tự EOF .
	char c;
	while(!feof(FileInPut))
	{
		c=fgetc(FileInPut); // Đọc một ký tự từ tập tin InPut.txt đã mở bởi hàm fopen trong hàm main . Giá trị trả về nếu thất bại trả về EOF khi kết thúc tập tin InPut.txt hoặc gặp lỗi .
		if(c=='\n'||c==EOF)
			break; // Thoát ra khỏi vòng lặp .
		if(c==' ') // Nếu bằng ký tự rỗng thì chương trình tiếp tục duyệt xuống tiếp để thực hiện việc thêm ký tự .
			continue;
		InsertNode(Tree,c); // Thêm ký tự .
	}
}
/* ================================================================================================================= */

/* =================================== Tìm Kiếm Một Node Trong Cây ================================================= */
NODE* SearchNode(Tree T,char x)
{
	if(T)
	{
		if(T->key==x) return T;
		if(T->key>x)
			return SearchNode(T->pLeft,x); // Tư tưởng đệ quy:Dựa vào tính chất của cây nhị phân tìm kiếm nếu Node x nhỏ hơn nút gốc => Ta sẽ duyệt qua nhánh trái của cây .
		else if(T->key<x)
			return SearchNode(T->pRight,x); // Tư tưởng đệ quy:Dựa vào tính chất của cây nhị phân tìm kiếm nếu Node x lớn hơn nút gốc => Ta sẽ duyệt qua nhánh phải của cây .
	}
	return NULL;
}
/* ================================================================================================================= */

/* ================================= Tìm Kiếm Ký Tự Với Dữ Liệu Từ File ============================================ */
void SearchCharactersInFile(NODE* TREE,FILE *FileInPut,FILE *FileOutPut)
{
	rewind(FileInPut); // Dời vị trí đọc ghi về đầu (byte 0) của tập tin InPut.txt  .
	char s[n]; // Khai báo chuỗi s tối đa 4000 ký tự .
	for(int i=0;i<3;i++)
	{
		fgets(s,n,FileInPut); // Ý Nghĩa : Đọc một dãy ký tự từ tập tin InPut.txt vào vùng nhớ s,kết thúc khi đủ n-1 ký tự hoặc gặp ký tự xuống dòng,lưu ký tự xuốn dòng vào chuỗi s nếu dòng ít hơn n-1 ký tự,tự động thêm ký tự kết thúc chuỗi .
						// Gía trị trả về : Thành công -> trả về địa chỉ vùng nhớ s . Thất bại -> trả về NULL khi gặp lỗi hoặc gặp ký tự EOF .
	}
	char c;
	while(!feof(FileInPut))
	{
		c=fgetc(FileInPut); // Đọc một ký tự từ tập tin InPut.txt đã mở bởi hàm fopen trong hàm main . Giá trị trả về nếu thất bại trả về EOF khi kết thúc tập tin InPut.txt hoặc gặp lỗi .
		if(c=='\n'||c==EOF)
			break; // Thoát ra khỏi vòng lặp .
		NODE* p=SearchNode(TREE,c); // Tìm kiếm ký tự .
		if(p==NULL)
			fprintf(FileOutPut,"Khong Tim Thay Duoc Ky Tu : <%c>\t",c); // Trả về kết quả trong file OutPut.txt
		else
			fprintf(FileOutPut,"Da Tim Thay Ky Tu: %c(%d)\t",p->key,p->Dem); // Trả về kết quả trong file OutPut.txt
	}
}
/* ================================================================================================================= */

/* ============================================ Các Hàm Đồ Họa ===================================================== */
// Hàm tăng kích cỡ của khung CMD
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm lấy tọa độ vị trí .
void gotoxy(int x,int y)
{
	HANDLE hstdout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition(hstdout,position);
}

// Hàm tô màu .
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
/* ================================================================================================================= */

/* ======================================== Lời Giới Thiệu Đầu Chương Trình ======================================== */
int gioithieu()
{
	FILE* f = fopen("C:\\gioithieuchuongtrinh.txt","rt");
	if (f != NULL)
	{
		while (1)
		{			
			if (feof(f)) 
				break;
			if (kbhit())
			{
				char key;
				key = getch();
				if (key == 13 || key == 27)
					return 0;
			}
			char x;
			x = fgetc(f);
			printf("%c",x);	
			Sleep(35);	// Điều chỉnh tốc độ chạy dữ liệu trong file : Sleep càng nhỏ thì tốc độ chạy chữ càng nhanh và ngược lại .			
		}
		fclose(f);
	}
	else 
		printf("Khong co File gioithieuchuongtrinh.txt");	
	getch();
}
/* ================================================================================================================= */

/* ================================= Hiển Thị Lời Chào Khi Kết Thúc Chương Trình =================================== */
void Thanks()
{
	system("cls"); // Xóa đi mọi dữ liệu đã làm trước đó .
	srand(time(NULL));
	for(int j=1;j<=20;j++)
	{
		int color=rand()%15+1; // Khởi tạo màu chạy ngẫu nhiên trong đoạn thang màu [1,15].
		Sleep(300);
		gotoxy(j-1,40);
		printf("			");
		gotoxy(j,40);
		textcolor(color);
		printf("\nThanks You For Using The Program ! Goodbye And See You Later !\n"); // Khi người dùng thoát chương trình sẽ hiển thị lời chào !
	}
	textcolor(15);
	getch();
	gotoxy(3,42);
}
/* ================================================================================================================= */

/* ========================================= MeNu ================================================ */
void MeNu()
{
	resizeConsole(1000,550); // Tăng kích cỡ của khung CMD lên thành chiều rộng 1000,chiều cao 550 .
	textcolor(14); // Tô màu vàng cho chữ .
	gioithieu(); // In ra lời giới thiệu từ File .
	textcolor(7); // Trả về màu chữ bình thường .
	remove("C:\\OutPut.txt"); // Xóa đi các dữ liệu trong file OutPut.txt .
	NODE* TREE;
	FILE *FileInPut,*FileOutPut; // Khởi tạo File nhị phân InPut.txt để chứa dữ liệu đầu vào và OutPut.txt để ghi kết quả .
	FileInPut=fopen("C:\\InPut.txt","r"); // Mở tập tin InPut.txt ở trong ổ đĩa C để đọc dữ liệu . Trả về NULL nếu không tìm thấy tập tin .
	int luachon;
	if(FileInPut!=NULL)
	{
		FileOutPut=fopen("C:\\OutPut.txt","a+"); // Mở tập tin OutPut.txt để thêm dữ liệu vào cuối tập tin và đọc tập tin . Tập tin sẽ đơợc tạo mới nếu chưa có .
		
		// In Cây là mặc định bắt buộc phải có của chương trình . Sau khi quá trình in cây thực hiện xong thì bảng MeNu sẽ đưa ra cho người dùng các sự lựa chọn tùy theo nhu cầu là thêm - xóa - tìm kiếm hay cùng lúc cả thêm,xóa,tìm kiếm luôn .
		
		printf("\n>>>>>>>>>>>>>>>>>>> In Cay <<<<<<<<<<<<<<<<<<<<<\n");
		CreatTree(TREE,FileInPut);
		LNR(TREE,FileOutPut);
		fprintf(FileOutPut,"\n");
		printf("\n------------------------------------------------\n");

		printf("\n------------ Bang Lua Chon --------------\n");
		printf("\n 2.Cay Sau Khi Them ");
		printf("\n 3.Cay Sau Khi Xoa ");
		printf("\n 4.Ket Qua Tim Kiem ");
		printf("\n 5.Them - Xoa - Tim Kiem ");
		printf("\n 0.Thoat ");
		printf("\n-----------------------------------------\n");
		printf("\n");
		quaylai:printf("\nNhap vao lua chon cua ban:");
		scanf("%d",&luachon);
		printf("\n");
		printf("\nKet Qua:");
		
		if(luachon==2)
		{
			printf("\n>>>>>>>>>>>>>>>>>>> Cay Sau Khi Them <<<<<<<<<<<<<<<<<\n");
			AddCharacters(TREE,FileInPut);
			LNR(TREE,FileOutPut);
			fprintf(FileOutPut,"\n");
			printf("\n-------------------------------------------------------\n");
			printf("\n Loading....");
			printf("\n");
			printf("\nYeu Cau Cua Ban Da Duoc Thuc Hien Xong.Xin Moi Vao C:\\ OutPut.txt De Xem Ket Qua!");
			fcloseall(); // Đóng tất cả File lại .
		}
		else if(luachon==3)
		{
			printf("\n>>>>>>>>>>>>>> Cay Sau Khi Xoa <<<<<<<<<<<<<<<<<<<<<\n");
			DeleteCharactersInFile(TREE,FileInPut,FileOutPut);
			fprintf(FileOutPut,"\n");
			printf("\n----------------------------------------------------\n");
			printf("\n Loading....");
			printf("\n");
			printf("\nYeu Cau Cua Ban Da Duoc Thuc Hien Xong.Xin Moi Vao C: \\OutPut.txt De Xem Ket Qua!");
			fcloseall(); // Đóng tất cả File lại .
		}
		else if(luachon==4)
		{
			printf("\n>>>>>>>>>>>>>>> Tim Kiem Ky Tu <<<<<<<<<<<<<<<<<<<<<<\n");
			SearchCharactersInFile(TREE,FileInPut,FileOutPut);
			printf("\n----------------------------------------------------------------\n");
			printf("\n Loading....");
			printf("\n");
			printf("\nYeu Cau Cua Ban Da Duoc Thuc Hien Xong.Xin Moi Vao C: \\OutPut.txt De Xem Ket Qua!");
			fcloseall(); // Đóng tất cả File lại .
		}
		else if(luachon==5)
		{
			printf("\n>>>>>>>>>>>>>>>>>>>>> Them - Xoa - Tim Kiem <<<<<<<<<<<<<<<<<<<<<<");
			/* ============ Thêm Ký Tự ================= */
			AddCharacters(TREE,FileInPut);
			LNR(TREE,FileOutPut);
			fprintf(FileOutPut,"\n");
			/* ========================================= */

			/* =============== Xóa Ký Tự =============== */
			DeleteCharactersInFile(TREE,FileInPut,FileOutPut);
			fprintf(FileOutPut,"\n");
			/* ========================================= */

			/* ============= Tìm Kiếm Ký Tự ============ */
			SearchCharactersInFile(TREE,FileInPut,FileOutPut);
			printf("\n----------------------------------------------------------------\n");
			/* ========================================= */
			printf("\n Loading....");
			printf("\n");
			printf("\nYeu Cau Cua Ban Da Duoc Thuc Hien Xong.Xin Moi Vao C: \\OutPut.txt De Xem Ket Qua!");
			fcloseall(); // Đóng tất cả File lại .
		}
		else if(luachon==0)
		{
			Thanks();
		}
		if(luachon!=2&&luachon!=3&&luachon!=4&&luachon!=5&&luachon!=0)
		{
			printf("\nLua chon ban nhap vao khong hop le!Xin vui long nhap lai!");
			goto quaylai;
		}
	}
	else
	{
		printf("\nKhong Tim Thay File InPut.txt Trong O Dia C!");
		printf("\n");
		printf("\nBan Can Phai Tao 1 File Co Ten La: InPut.txt Trong O Dia C Va Nhap Du Lieu Vao Do!");
	}
}
/* =================================================================================================== */

/* ========================================= Main ==================================================== */
void main()
{
	MeNu();
}
/* ==================================================================================================== */

/* ======================================== THE END =================================================== */

/* ============================= Designed By : Nguyễn Thị Nhung ======================================= */