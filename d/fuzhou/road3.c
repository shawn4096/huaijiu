// Room: /d/fuzhou/road3.c

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
                "northeast" : __DIR__"road2",
                "south" : __DIR__"road4",
	]));

	set("outdoors", "����");
	set("coor/x",100);
  set("coor/y",-430);
   set("coor/z",0);
   setup();
}

