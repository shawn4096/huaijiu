// Room: /u/jpei/thd/road2.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
һ���������·�����Ϸ�����һ��СС�Ĵ��䡣
LONG
	);
	set("no_clean_up", 0);
	set("outdoors","ţ�Ҵ�");

	set("exits", ([
		"northwest": __DIR__"road1.c",
		"southeast": __DIR__"njwest.c",
	]) );

	set("coor/x",70);
  set("coor/y",-350);
   set("coor/z",0);
   setup();
}

