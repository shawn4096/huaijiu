// /d/hmy/changlang2.c

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
	  "east" : __DIR__"qianqiudian",
	  "south" : __DIR__"chengdedian",
	  "west" : __DIR__"qinglongtang",
]));
	setup();
}
