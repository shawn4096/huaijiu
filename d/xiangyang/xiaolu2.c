// /d/xiangyang/xiaolu2.c

inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG
�������˶��������С·�ϣ�ż��������������ҴҶ������������ĳ�
����������ͨ�������ǣ�����������Ĵ��Ĵ����
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"northeast" : __DIR__"xiaolu1",
		"west" : "/d/chengdu/eroad4",
	]));

	set("coor/x",-50);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

