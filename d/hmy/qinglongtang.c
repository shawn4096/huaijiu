//  /d/hmy/qinglongtang.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����������ʽ���̾ߣ���΢�������֮�£�ɢ���ű���ĺ��⣬����
Խ��Խ�����з�ë����������֮�����ֲ�״������ҵĽ��������и���
��һ�󾪲���
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"changlang2",
]));
        set("objects", ([ 
          __DIR__"npc/shang" : 1,
]));
	setup();
}
