// Room: tianjing.c

inherit ROOM;

void create()
{
	set("short", "�쾮");
	set("long", @LONG
���߽�һ��С�쾮����ʯ����·��·��Χ�����ļ����ݣ�������������ͨ����
Ժ�䣬����һ��СС���쾮�����õ�Ҳ�Ǿ���ϸ�£���߽��ġ�
LONG
	);
 

	 set("objects", ([
//      	__DIR__"npc/": 1,
	 ]));
	
	set("exits", ([
		"north": __DIR__"shide",
		"south": __DIR__"houhua",
		"west":__DIR__"lianwu",
		"east":__DIR__"guifang",
	]) );

	setup();
}
