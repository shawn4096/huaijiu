// Room: /u/jpei/thd/road1.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
һ���������·��Զ���ƺ��������䡣
LONG
	);
	set("no_clean_up", 0);
	set("outdoors","ţ�Ҵ�");

	set("exits", ([
		"north": __DIR__"road.c",
		"southeast": __DIR__"road2.c",
	]) );

	set("coor/x",60);
  set("coor/y",-340);
   set("coor/z",0);
   setup();
}

