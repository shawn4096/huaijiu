// /d/xiangyang/xiaolu1.c

inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG
������һ��С·�ϣ�ż��������������ҴҶ������������ĳ���������
��ͨ�������ǣ�����ͨ���Ĵ���
LONG
	);
        set("outdoors", "����");

	set("objects", ([
		__DIR__"npc/mengmian-dadao" : 1,
	]) );
	set("exits", ([
		"northeast" : __DIR__"tanxi",
        "north" : __DIR__"xlu_lzz",
		"southwest" : __DIR__"xiaolu2",
	]));

	set("coor/x",-40);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

