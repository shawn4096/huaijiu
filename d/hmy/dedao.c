// /d/hmy/dedao.c

inherit ROOM;

void create()
{
	set("short", "�ص�");
	set("long", @LONG
�ص�һ·���£����Ե��ż�յ�͵ƣ�����綹��һƬ�������أ����ҵ�
��������������ת����ͷ���ۻ���
LONG
	);
	set("exits", ([ 
	  "down" : __DIR__"xiaohuayuan",
	  "up" : __DIR__"dadian",
]));
	setup();
}
