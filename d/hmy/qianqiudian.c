// /d/hmy/qianqiudian.c

inherit ROOM;

void create()
{
	set("short", "ǧ���");
	set("long", @LONG
���ڰڷ��������СС������,ÿ�����Ӷ����������������ţ�����֮
�����������໥���ţ�������������װ�ŵ�����ǳ���Ҫ��
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"changlang3",
	  "south" : __DIR__"chengdedian",
	  "west" : __DIR__"changlang2",
]));
	set("objects", ([ 
	  __DIR__"npc/qu" : 1,
]));

	setup();
}
