// /d/xiangyang/outnroad4.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
�������¶��������·�ϣ�ż��������������ҴҶ����������Ѿ�������
�ؽ磬���Ͻ���������ڡ�������˿���·��������һ��С���䡣
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"west" : "/d/xingxiu/xxroad1",
		"south" : __DIR__"outnroad3",
		"northwest" : "/d/village/hsroad3",
	]));

	setup();
}

