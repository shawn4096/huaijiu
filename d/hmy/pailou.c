// /d/hmy/pailou.c

inherit ROOM;

void create()
{
	set("short", "��¥");
	set("long", @LONG
��ǰһ��������ľ޴���¥����¥���ĸ����ɫ�֡��󱻲�����������
������⣬���ɵ�������Ȼ�𾴡�
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"xiangfang",
	  "north" : __DIR__"shibanlu",
	  "west" : __DIR__"shiwu",
]));
	set("no_fight",1);
	setup();
}
