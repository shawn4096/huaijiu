// Room: /d/fuzhou/road4.c

inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һ��ɽ·�ϡ�ʱֵ���գ�·�Ե�ɽ���Ͽ����˽��ɫ���Ͳ˻�����
������븣������ɽ����
LONG
	);

	set("exits", ([
                "north" : __DIR__"road3",
		"south" : __DIR__"road5",
	]));

	set("outdoors", "����");
	set("coor/x",100);
  set("coor/y",-440);
   set("coor/z",0);
   setup();
}

