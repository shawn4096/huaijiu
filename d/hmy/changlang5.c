// /d/hmy/changlang5.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
һ�������Ĺ������������Զ���ǽ��ÿ�������ɣ�ǽ�϶�����һ֧����
�εľ���
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"houdian",
	  "south" : __DIR__"houhuayen",
	  "north" : __DIR__"dadian",
	  "west" : __DIR__"fengleitang",
]));

	setup();
}
