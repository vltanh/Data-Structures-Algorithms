#include "SinglyLinkedList.h"
#include <iostream>
using namespace std;

// 01. Hàm so sánh 2 biến kiểu cấu trúc cho trước
// Đầu vào: biến cấu trúc (info1) và biến cấu trúc (info2)
// Đầu ra:	0 (bằng nhau), -1 (info1 nhỏ hơn info2), 1 (info1 lớn hơn info2)
int CompareData(Data info1, Data info2)
{
	if (info1.x < info2.x) return -1;
	if (info1.x == info2.x) return 0;
	return 1;
}

// 02. Hàm khởi tạo DSLK (rỗng)
// Đầu vào:	tham chiếu đến DSLK cần khởi tạo (l)
// Đầu ra:	Không có
void InitList(List& l)
{
	l.pHead = l.pTail = NULL;
}

// 03. Hàm kiểm tra DSLK cho trước có phải là DSLK rỗng hay không?
// Đầu vào:	DSLK cần kiểm tra (l)
// Đầu ra:	DSLK rỗng hay không (true/false)
bool IsEmptyList(List l)
{
	return l.pHead == NULL;	// true nếu rỗng, false nếu không
}

// 04. Hàm in DSLK cho trước
// Đầu vào: DSLK cần in (l) kèm theo chuỗi thông báo (str)
// Đầu ra:	Không có
void PrintList(List l, char* str)
{
	cout << str;
	Node *p = l.pHead;
	do {
		cout << p->info.x << " ";
		p = p->pNext;
	} while (p != l.pTail);
	cout << endl;
}

// 05. Hàm tạo một nút mới với dữ liệu cho trước
// Đầu vào:	Dữ liệu của nút (info)
// Đầu ra:	Con trỏ đến nút đó (trả về NULL nếu không tạo được)
Node* CreateNode(Data info)
{
	return new Node{ info, NULL };
}

// 06. Hàm tìm nút đầu tiên trong DSLK cho trước có dữ liệu cho trước
// Đầu vào:	DSLK (l), dữ liệu của nút cần tìm (info)
// Đầu ra:	Con trỏ đến nút tìm được (trả về NULL nếu không tìm được)
Node* GetNodePointer(List l, Data info)
{
	Node *p = l.pHead;
	do {
		if (CompareData(p->info, info) == 0)
			break;
		p = p->pNext;
	} while (p != l.pTail);
	return p;
}

// 07. Hàm tìm nút có chỉ số (bắt đầu từ 0) cho trước
// Đầu vào:	DSLK (l), chỉ số của nút cần lấy (index)
// Đầu ra:	Con trỏ đến nút tìm được (trả về NULL nếu không tìm được)
Node* GetNodePointer(List l, int index)
{
	Node *p = l.pHead;
	while (p && index > 0) {
		p = p->pNext;
		index--;
	}
	return p;
}

// 08. Hàm xác định vị trí của một nút cho trước trong DSLK cho trước
// Đầu vào:	DSLK (l), con trỏ đến nút cần xác định vị trí (pNode)
// Đầu ra:	Thứ tự của nút cho trước (trả về -1 nếu nút này không có trong DSLK)
int GetNodeIndex(List l, Node* pNode)
{
	Node *p = l.pHead;
	int k = 0;
	while (p && p != pNode) {
		k++;
		p = p->pNext;
	}
	if (p == pNode) return k;
	return -1;
}

// 09. Hàm xác định con trỏ đến nút đứng trước của một nút cho trước trong DSLK
// Đầu vào:	DSLK (l), con trỏ đến nút cho trước (pNode)
// Đầu ra:	Con trỏ đến nút tìm được (trả về NULL nếu không tìm được)
Node* GetPreviousNodePointer(List l, Node* pNode)
{
	Node *prev = NULL;
	Node *p = l.pHead;
	while (p != pNode) {
		prev = p;
		p = p->pNext;
	}
	return prev;
}

// 10. Hàm chèn một nút cho trước vào đầu DSLK
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cần chèn (pNewNode)
// Đầu ra:	Không có
void AddHead(List& l, Node* pNewNode)
{
	if (IsEmptyList(l)) {
		l.pHead = l.pTail = pNewNode;
	}
	else {
		pNewNode->pNext = l.pHead;
		l.pHead = pNewNode;
	}
	l.pTail->pNext = l.pHead;
}

// 11. Hàm chèn một nút có dữ liệu cho trước vào đầu DSLK
// Đầu vào:	Tham chiếu đến DSLK (l), dữ liệu của nút cần chèn (info)
// Đầu ra:	Con trỏ đến nút được chèn (trả về NULL nếu không chèn được)
Node* AddHead(List& l, Data info)
{
	Node *p = CreateNode(info);
	if (p == NULL) return NULL;
	AddHead(l, p);
	return l.pHead;
}

// 12. Hàm chèn một nút cho trước vào cuối DSLK
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cần chèn (pNewNode)
// Đầu ra:	Không có
void AddTail(List& l, Node* pNewNode)
{
	if (IsEmptyList(l)) {
		l.pHead = l.pTail = pNewNode;
	}
	else {
		l.pTail->pNext = pNewNode;
		l.pTail = l.pTail->pNext;
	}
	l.pTail->pNext = l.pHead;
}

// 13. Hàm chèn một nút có dữ liệu cho trước vào cuối DSLK
// Đầu vào:	Tham chiếu đến DSLK (l), dữ liệu của nút cần chèn (info)
// Đầu ra:	Con trỏ đến nút được chèn (trả về NULL nếu không chèn được)
Node* AddTail(List& l, Data info)
{
	Node *p = CreateNode(info);
	if (p == NULL) return NULL;
	AddTail(l, p);
	return p;
}

// 14. Hàm chèn một nút cho trước vào sau một nút khác cho trước
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cho trước (q), con trỏ đến nút cần chèn (pNewNode)
// Đầu ra:	Không có
void AddAfter(List& l, Node* q, Node* pNewNode)
{
	pNewNode->pNext = q->pNext;
	q->pNext = pNewNode;
	if (q == l.pTail) l.pTail = pNewNode;
}

// 15. Hàm chèn một nút có dữ liệu cho trước vào sau một nút khác cho trước
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cho trước (q), dữ liệu của nút cần chèn (info)
// Đầu ra:	Con trỏ đến nút được chèn (trả về NULL nếu không chèn được)
Node* AddAfter(List& l, Node* q, Data info)
{
	Node *p = CreateNode(info);
	if (!p) return NULL;
	AddAfter(l, q, p);
	return q->pNext;
}

// 16. Hàm chèn một nút cho trước vào trước một nút khác cho trước
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cho trước (q), con trỏ đến nút cần chèn (pNewNode)
// Đầu ra:	Không có
void AddBefore(List& l, Node* q, Node* pNewNode)
{
	// Cách làm này thay đổi trường info của node q
	/*Data t = pNewNode->info;
	*pNewNode = *q;
	q->pNext = pNewNode;
	q->info = t;
	if (q == l.pTail) l.pTail = pNewNode;
	if (q == l.pHead) {
		AddHead(l, pNewNode);
	}
	else {
		Node *p = GetPreviousNodePointer(l, q);
		AddAfter(l, p, pNewNode);
	}*/
	Node *P = l.pHead;
	while (P->pNext != q)
		P = P->pNext;
	pNewNode->pNext = q;
	P->pNext = pNewNode;
}

// 17. Hàm chèn một nút có dữ liệu cho trước vào trước một nút khác cho trước
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cho trước (q), dữ liệu của nút cần chèn (info)
// Đầu ra:	Con trỏ đến nút được chèn (trả về NULL nếu không chèn được)
Node* AddBefore(List& l, Node* q, Data info)
{
	Node *p = CreateNode(info);
	if (p == NULL) return NULL;
	AddBefore(l, q, p);
	return GetPreviousNodePointer(l, q);
}

// 18. Hàm chèn một nút cho trước sao cho DSLK cho trước vẫn tăng dần
// Đầu vào: Tham chiếu đến DSLK (l), con trỏ đến nút cần chèn (pNewNode)
// Đầu ra:	Không có
void AddAscendingList(List& l, Node* pNewNode)
{
	if (IsEmptyList(l)) {
		l.pHead = l.pTail = pNewNode;
		return;
	}
	
	Data t = pNewNode->info;
	Node *prev = NULL;
	Node *p = l.pHead;
	while (p && CompareData(t, p->info) == 1) {
		prev = p;
		p = p->pNext;
	}
	if (prev) AddAfter(l, prev, pNewNode);
	else AddHead(l, pNewNode);
}

// 19. Hàm chèn một nút có dữ liệu cho trước sao cho DSLK cho trước vẫn tăng dần
// Đầu vào: Tham chiếu đến DSLK (l), dữ liệu của nút cần chèn (info)
// Đầu ra:	Con trỏ đến nút được chèn (trả về NULL nếu không chèn được)
Node* AddAscendingList(List& l, Data info)
{
	Node *p = CreateNode(info);
	if (p == NULL) return NULL;

	AddAscendingList(l, p);
	return p;
}

// 20. Hàm hủy một nút đầu DSLK
// Đầu vào:	Tham chiếu đến DSLK (l)
// Đầu ra:	Con trỏ đến nút bị hủy (nếu có)
Node* RemoveHead(List& l)
{
	Node *p = l.pHead;
	if (p->pNext == NULL) {
		l.pHead = l.pTail = NULL;
	}
	else {
		l.pHead = p->pNext;
		p->pNext = NULL;
	}
	return p;
}

// 21. Hàm hủy một nút cuối DSLK
// Đầu vào:	Tham chiếu đến DSLK (l)
// Đầu ra:	Con trỏ đến nút bị hủy (nếu có)
Node* RemoveTail(List& l)
{
	Node *p = GetPreviousNodePointer(l, l.pTail);
	Node *q = l.pTail;
	if (p == NULL) {
		l.pHead = l.pTail = NULL;
	}
	else {
		p->pNext = NULL;
		l.pTail = p;
	}
	return q;
}

// 22. Hàm hủy một nút đứng sau một nút cho trước trong DSLK
// Đầu vào:	Tham chiếu đến DSLK (l), con trỏ đến nút cho trước (q)
// Đầu ra:	Con trỏ đến nút bị hủy (nếu có)
Node* RemoveAfter(List& l, Node* q)
{
	Node *p = q->pNext;
	if (p != NULL) {
		q->pNext = p->pNext;
		if (p == l.pTail) l.pTail = q;
	}
	return p;
}

// 23. Hàm hủy một nút có dữ liệu cho trước trong DSLK
// Đầu vào:	Tham chiếu đến DSLK (l), dữ liệu của nút cần xóa (info)
// Đầu ra:	Con trỏ đến nút bị hủy (nếu có)
Node* RemoveNode(List& l, Data info)
{
	Node *prev = NULL;
	Node *p = l.pHead;
	while (p && CompareData(p->info, info) != 0) {
		prev = p;
		p = p->pNext;
	}

	if (p) {
		if (prev == NULL) return RemoveHead(l);
		return RemoveAfter(l, prev);
	}
	else return NULL;
}

// 24. Hàm hủy toàn bộ DSLK cho trước
// Đầu vào:	Tham chiếu đến DSLK (l)
// Đầu ra:	Không có
void RemoveAll(List& l)
{
	while (l.pHead) {
		Node *p = RemoveHead(l);
		delete p;
	}
}