// Room: /d/fuzhou/road2.c

inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һ��ɽ·�ϡ�ʱֵ���գ�·�Ե�ɽ���Ͽ����˽��ɫ���Ͳ˻�����
��������븣������ɽ�����������ֱ�������ǡ�
LONG
	);

	set("exits", ([
                "northeast" : __DIR__"road1",
		"southwest" : __DIR__"road3",
	]));

	set("outdoors", "����");
	set("coor/x",110);
  set("coor/y",-420);
   set("coor/z",0);
   setup();
}

