#define Herror int


//节点
struct HNode
{
	void* data;
	HNode* next;
	HNode* last;
};

//内容链表
typedef struct tag_HLink
{
	HNode* header;
	HNode* tail;
}HLink;

//删除链表
typedef struct tag_HLinkDel
{
	HLink del;
	HNode** buf;
	unsigned int size;
	int index;
	int nBuf;
}HLinkDel;

//链表管理
typedef struct tag_HList
{
	HLink    link;
	HLinkDel link_del;
}HList;


Herror hlink_empty(HLink& link);
Herror hlink_push_back(HLink& link, HNode* newNode);
Herror hlink_push_front(HLink& link, HNode* newNode);
Herror hlink_insert(HLink& link, void* data1, HNode* newNode);
Herror hlink_delete(HLink& link, void* data, HNode* &nodeDel);
Herror hlink_find(HLink& link, void* data, HNode* &nodeFind);

Herror hlinkdel_empty(HLinkDel& linkdel, unsigned int size = 1024, int nBuf = 16);
Herror hlinkdel_clear(HLinkDel& linkdel);
Herror hlinkdel_pop(HLinkDel& linkdel, HNode* &node);
Herror hlinkdel_push(HLinkDel& linkdel, HNode* node);
Herror hlinkdel_alloc(HLinkDel& linkdel);


Herror hlist_emtpy(HList& list);
Herror hlist_clear(HList& list);
Herror hlist_push_back(HList& list, void* data);
Herror hlist_push_front(HList& list, void* data);
Herror hlist_insert(HList& list, void* data1, void* data2);
Herror hlist_delete(HList& list, void* data);