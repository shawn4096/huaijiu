// Room: wofang1.c

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
		__DIR__"npc/wenfangda": 1,
		__DIR__"npc/wenfangyi": 1,
		__DIR__"npc/wenfangshan": 1,
	]));
	
	set("exits", ([
		"east":__DIR__"shide",
	]) );

	setup();
}
