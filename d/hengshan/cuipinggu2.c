// Room: /d/hengshan/cuipinggu2.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����Ͽ�����ʯ�ڶ�ֱ�����±�����һ�����������������
���յĺ�ɽɽ���У�ȴ����ʮ���������ڴ���ɽ������������Σ�ң�
������ȣ��������£���������¥�Կ���ȽȽ���䡣�Ǿ���������
�ˡ�
LONG
	);
	set("exits", ([
		"up"         : __DIR__"cuiping1",
		"northwest"  : __DIR__"cuipinggu1",
	]));

        set("outdoors", "��ɽ");
        set("no_clean_up", 0);
	set("coor/x",50);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

