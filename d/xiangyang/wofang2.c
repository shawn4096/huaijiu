// Room: wofang2.c

inherit ROOM;

void create()
{
	set("short", "�Է�");
	set("long", @LONG
���߽�һ�����ң�����װ�εĺ�������������ǽ��һ�Ŵ󴲣����ϱ����������
����̻Ի͡�����һ������ͭ��¯����������Ѭ���㣬һ��Ũ���˱ǣ���ֻ������Ȼ
�������˯��
LONG
	);
	 

	set("objects", ([
		__DIR__"npc/wenfangshi": 1,
		__DIR__"npc/wenfangwu": 1,
	]));
	
	set("exits", ([
		"west":__DIR__"shide",
	]) );

	setup();
}
