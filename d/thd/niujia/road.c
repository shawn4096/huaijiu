// Room: /u/jpei/thd/road.c

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
		"northwest": "/d/hz/qsddao3.c",
		"south": __DIR__"road1.c",
	]) );

	set("coor/x",60);
  set("coor/y",-330);
   set("coor/z",0);
   setup();
}

