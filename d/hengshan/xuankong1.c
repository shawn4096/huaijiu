// Room: /d/hengshan/xuankong1.c

inherit ROOM;

void create()
{
	set("short", "�����±�¥");
	set("long", @LONG
�����������µı���¥��Ҳ�Ǳ���ͤ����¥���ӣ�������Ԩ��
�ȵ���������ڼ䵤�����������ջ��ͨ����¥��
LONG
	);
	set("exits", ([
		"south"    : __DIR__"zhanqiao",
		"up"       : __DIR__"sanjiaodian",
		"westdown" : __DIR__"cuiping2",
	]));
	set("objects", ([
		__DIR__"npc/yafu" : 1,
	]));

	set("coor/x",50);
  set("coor/y",120);
   set("coor/z",30);
   setup();
}

