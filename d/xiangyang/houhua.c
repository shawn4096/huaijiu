// Room: houhua.c

inherit ROOM;

void create()
{
	set("short", "��԰");
	set("long", @LONG
�㻺�����ɽ��ȥ����ɽҲ�����ߣ�������ľ�д䣬���������̱�����û��֦
Ҷ֮�䡣����̤��ݣ������Ų�Ҳ��������Ϣ������ɽ����ת�������䣬һ����磬
����ȫ�ǻ��㡣������ȥ�����¾��Ǻ�ɫ����ɫ����ɫ��õ�塣
LONG
	);
 

	set("objects", ([
		__DIR__"npc/wenyi": 1,
	]));
	
	set("exits", ([
		"north": __DIR__"tianjing",
	]) );

	setup();
}
