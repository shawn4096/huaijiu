// /d/xiangyang/outwroad1.c

inherit ROOM;

void create()
{
	set("short", "ɽ��С·");
	set("long", @LONG
������һ�����Ѷ��ϵ�ɽ��С·�ϣ�����ʮ�ֻ�����ǰ�治Զ������
һЩС���֣���������С·ͨ���������
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"northdown" : __DIR__"shanlu1",
		"southwest" : __DIR__"shanlu3",
	]));

	set("coor/x",-20);
  set("coor/y",-10);
   set("coor/z",10);
   setup();
}

