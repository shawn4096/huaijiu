//Room: /d/xiangyang/ymdatang.c

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
���������ŵ����ã����϶����������ס������һ������������������ϸ
��������ǽ������һ�����ң����顰����������ĸ���������Ĵ��֡�������
�����ְֳ��Ӳ������ԡ�
LONG
	);

	set("exits", ([
        "north" : __DIR__"yamen",
	]));
	set("objects", ([
        __DIR__"npc/lvwende" : 1,
	]));

   setup();
}

